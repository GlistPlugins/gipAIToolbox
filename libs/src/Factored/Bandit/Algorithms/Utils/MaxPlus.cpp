#include <AIToolbox/Factored/Bandit/Algorithms/Utils/MaxPlus.hpp>

#include <AIToolbox/Impl/Logging.hpp>

namespace AIToolbox::Factored::Bandit {
    MaxPlus::Result MaxPlus::operator()(const Action & A, const Graph & graph, size_t iterations) {
        // Preallocate memory.
        // - retval keeps the best currently found solution.
        // - bestCurrent keeps the currently found solution.
        Result retval, bestCurrent;
        std::get<0>(retval).resize(A.size());
        std::get<1>(retval) = std::numeric_limits<double>::lowest();
        std::get<0>(bestCurrent).resize(A.size());

        // Initialize the message caches.
        // - inMessages are the previous timestep's messages sent
        // to agents, which need to be read by the factors.
        // - outMessages are the messages outbound from the factors
        // to the agent.
        // We need both to avoid overwriting old messages during a
        // single message-passing step.
        std::vector<Matrix2D> inMessages(A.size()), outMessages(A.size());
        for (size_t a = 0; a < A.size(); ++a) {
            const auto rows = graph.getFactors(a).size();
            // Here each row corresponds to the message from
            // a factor to this agent.
            // We add an additional row to store the sum of all
            // rows, to avoid having to re-sum the whole matrix
            // all the time.
            inMessages[a].resize(rows + 1, A[a]);
            outMessages[a].resize(rows + 1, A[a]);

            // We don't need to zero inMessages, we do it at the start
            // of the each message passing iteration, just after the swap.
            outMessages[a].setZero();
        }

        // Initialize temporary local factor message with max possible size.
        long maxSize = 0;
        for (auto f = graph.begin(); f != graph.end(); ++f)
            maxSize = fmax(maxSize, f->getData().size());
        Vector message(maxSize);

        for (size_t iters = 0; iters < iterations; ++iters) {
            // Since we have processed outMessages in the previous iteration
            // step, we can now swap in&out, and reset the out for this
            // iteration.
            std::swap(inMessages, outMessages);
            for (auto & m : outMessages)
                m.setZero();

            AI_LOGGER(AI_SEVERITY_DEBUG, "MaxPlus: iteration " << iters + 1);

            for (auto f = graph.begin(); f != graph.end(); ++f) {
                const auto & aNeighbors = graph.getVariables(f);

                // For each factor in the graph, we compute its unmaximized
                // message by summing its original function with the
                // appropriate messages from its adjacent agents.
                //
                // Note: we use head to avoid Eigen reallocating memory.
                // message is also only accessed by indexes (and we never take
                // its size directly), so it should be ok.
                const size_t fSize = f->getData().size();
                message.head(fSize) = f->getData();

                size_t len = 1;
                for (const auto a : aNeighbors) {
                    const auto & fNeighbors = graph.getFactors(a);
                    const auto fId = std::distance(std::begin(fNeighbors), std::find(std::begin(fNeighbors), std::end(fNeighbors), f));

                    const auto bottomRowId = inMessages[a].rows() - 1;

                    // Remove from sum the message coming from this factor
                    inMessages[a].row(bottomRowId) -= inMessages[a].row(fId);

                    // Add each element of the message in the correct place for the
                    // cross-sum across all agents. This code is basically equivalent to
                    //
                    //     message += np.tile(np.repeat(inMessage, len), ...)
                    size_t i = 0;
                    while (i < fSize)
                        for (size_t j = 0; j < A[a]; ++j)
                            for (size_t l = 0; l < len; ++l)
                                message[i++] += inMessages[a].row(bottomRowId)[j];

                    // Restore sum message for later
                    inMessages[a].row(bottomRowId) += inMessages[a].row(fId);

                    len *= A[a];
                }

                // Once the overall message is computed, we selectively
                // maximize over it depending on which agent we are sending the
                // message (we maximize all other agents).
                for (const auto a : aNeighbors) {
                    // Figure out the ID of this factor w.r.t. the current agent
                    // so we know which row of messages to read.
                    const auto & fNeighbors = graph.getFactors(a);
                    const auto fId = std::distance(std::begin(fNeighbors), std::find(std::begin(fNeighbors), std::end(fNeighbors), f));

                    // Compute the out message for each action of this agent.
                    double norm = 0.0;
                    for (size_t av = 0; av < A[a]; ++av) {
                        // Here we list all joint-action ids where the action
                        // of agent 'a' is equal to 'av'. We use them to access
                        // the appropriate 'message' values, and we maximize
                        // over them into 'outMessage'.
                        PartialIndexEnumerator e(A, aNeighbors, a, av);

                        double outMessage = std::numeric_limits<double>::lowest();
                        while (e.isValid()) {
                            outMessage = std::max(outMessage, message[*e]);
                            e.advance();
                        }
                        outMessages[a](fId, av) = outMessage;
                        norm += outMessage;
                    }
                    // Finally, we normalize the message (from the MaxPlus
                    // paper). This is done to avoid value explosions in loopy
                    // graphs (as a factor's messages will eventually come back
                    // to it over the loops and be summed infinitely).
                    outMessages[a].row(fId).array() -= norm / A[a];
                }
            }

            // Finally check whether we have a new best action, and
            // compute the messages for the next iteration.
            auto & [rAction, rValue] = retval;
            auto & [cAction, cValue] = bestCurrent;

            // Here we also handle the agent nodes' part of the work. We sum
            // all messages received in the last row of the outMessages
            // (reserved for this purpose), and use it to see if we have found
            // a better joint action.
            //
            // We still keep the rest of the matrix so it's easier to compute
            // the inMessages next iteration (one subtraction for each factor,
            // rather than re-summing the matrix every time).
            cValue = 0.0;
            for (size_t a = 0; a < A.size(); ++a) {
                auto & m = outMessages[a];
                // Also last row ID
                const auto rowsMinusOne = m.rows() - 1;

                // Compute "generic" message, we subtract each row one
                // at a time when it is needed. Note that we need to
                // avoid summing the last row since we have
                // "incorrectly" subtracted the normalization from it.
                m.row(rowsMinusOne) = m.topRows(rowsMinusOne).colwise().sum();

                // Compute the local best action for this agent (and its value,
                // which would ideally be the overall joint action value *for
                // all agents*).
                // Note that given the fact that we are also summing this over
                // all agents it basically guarantees that in the end cValue
                // won't be equal to the true value of the action.
                cValue += m.row(rowsMinusOne).maxCoeff(&cAction[a]);
            }

            // We only change the selected action if it improves on the
            // previous best value.
            // TODO: The paper specifies checking against the *true* value of
            // the joint action. I'm not yet sure whether using cValue makes
            // sense at all, but for now we keep it like this.
            if (cValue > rValue) {
                rValue = cValue;
                rAction = cAction;
            }
        }
        return retval;
    }
}
