/*
 * gipAIToolbox.h
 *
 *  Created on: Mar 11, 2023
 *      Author: Noyan Culum
*/

#ifndef SRC_GIPAITOOLBOX_H_
#define SRC_GIPAITOOLBOX_H_


#include "gBaseComponent.h"
#include "aitoolbox.h"


class gipAIToolbox : public gBaseComponent{
public:
	typedef AIToolbox::MDP::QGreedyPolicy QGreedyPolicy;
	typedef AIToolbox::MDP::EpsilonPolicy EpsilonPolicy;
	typedef AIToolbox::MDP::Model Model;
	typedef AIToolbox::MDP::GridWorld GridWorld;
	typedef AIToolbox::MDP::ValueIteration ValueIteration;

	gipAIToolbox();
	virtual ~gipAIToolbox();

	using Matrix2D = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor | Eigen::AutoAlign>;
	using SparseMatrix2D = Eigen::SparseMatrix<double, Eigen::RowMajor>;
	using Matrix3D = std::vector<Matrix2D>;
    /*template <bool UseEntropy>
    using HeadBeliefNode = AIToolbox::POMDP::HeadBeliefNode<UseEntropy>;
    template <typename State, typename Sampling, typename Action>
    using PolicyInterface = AIToolbox::PolicyInterface<State, Sampling, Action>;

    template <typename State, typename Sampling, typename Action>
    using EpsilonPolicyInterface = AIToolbox::EpsilonPolicyInterface<State, Sampling, Action>;

    template <typename IdsIterator, typename Container>
    using IndexMapIterator = AIToolbox::IndexMapIterator<IdsIterator, Container>;

    template <typename IdsContainer, typename Container>
    using IndexMap = AIToolbox::IndexMap<IdsContainer, Container>;
    template <typename IdsContainer, typename Container>
    using IndexSkipMapIterator = AIToolbox::IndexSkipMap<IdsContainer, Container>;
    template <typename IdsContainer, typename Container>
    using IndexSkipMap = AIToolbox::IndexSkipMap<IdsContainer, Container>;*/

    //AIToolbox::MDP::QFunction runQLearning(const AIToolbox::MDP::SparseModel & problem);
	//AIToolbox::MDP::QFunction runPrioritizedSweeping(const AIToolbox::MDP::SparseModel & problem);

	gipAIToolbox::Model  makeCornerProblem(const GridWorld & grid, double stepUncertainty = 0.8);
	gipAIToolbox::Model* getModel();

private:
	Model* model;
};

#endif /* SRC_GIPAITOOLBOX_H_ */
