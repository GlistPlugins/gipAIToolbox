#include <AIToolbox/Factored/Bandit/Experience.hpp>

#include <AIToolbox/Factored/Utils/Core.hpp>

namespace AIToolbox::Factored::Bandit {
    Experience::Experience(Action a, const std::vector<PartialKeys> & dependencies) :
            A(std::move(a)), timesteps_(0)
    {
        qfun_.bases.resize(dependencies.size());
        counts_.resize(dependencies.size());
        M2s_.resize(dependencies.size());

        for (size_t i = 0; i < qfun_.bases.size(); ++i) {
            qfun_.bases[i].tag = dependencies[i];
            qfun_.bases[i].values.resize(factorSpacePartial(dependencies[i], A));
            qfun_.bases[i].values.setZero();

            M2s_[i].resize(qfun_.bases[i].values.size());
            M2s_[i].setZero();
            counts_[i].resize(qfun_.bases[i].values.size());
        }
    }

    void Experience::record(const Action & a, const Rewards & rews) {
        assert(static_cast<size_t>(rews.size()) == qfun_.bases.size());

        ++timesteps_;

        for (size_t i = 0; i < qfun_.bases.size(); ++i) {
            const auto aId = toIndexPartial(qfun_.bases[i].tag, A, a);

            auto & c = counts_[i];
            auto & q = qfun_.bases[i].values;
            auto & m = M2s_[i];

            ++c[aId];

            const auto delta = rews[i] - q[aId];
            // Rolling average for this bandit arm
            q[aId] += delta / c[aId];
            // Rolling sum of square diffs.
            m[aId] += delta * (rews[i] - q[aId]);
        }
    }

    void Experience::reset() {
        for (auto & basis : qfun_.bases)
            basis.values.setZero();
        for (auto & m : M2s_)
            m.setZero();
        for (auto & c : counts_)
            std::fill(std::begin(c), std::end(c), 0);
        timesteps_ = 0;
    }

    unsigned long Experience::getTimesteps() const { return timesteps_; }
    const QFunction & Experience::getRewardMatrix() const { return qfun_; }
    const Experience::VisitsTable & Experience::getVisitsTable() const { return counts_; }
    const std::vector<Vector> & Experience::getM2Matrix () const { return M2s_; }
    const Action & Experience::getA() const { return A; }
}
