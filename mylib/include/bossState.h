#pragma once

#include "state.h"
#include <map>

class Boss;

namespace BossStateNames
{
    enum class BossStatePhaseOne;
    enum class BossStatePhaseTwo;
}

class BossState
{
public:
    BossState();
    ~BossState();

    using StateEnumP1 = BossStateNames::BossStatePhaseOne;
    using StateEnumP2 = BossStateNames::BossStatePhaseTwo;

    void setState(Boss* boss, BossStateNames::BossStatePhaseOne newState); 
    void setState2(Boss* boss, BossStateNames::BossStatePhaseTwo newState);
    std::shared_ptr<IBossState> getCurrentState() const;

    void update(Boss& boss, float deltaTime);

private:
    std::map<StateEnumP1, std::shared_ptr<IBossState>> m_statesP1;
    std::map<StateEnumP2, std::shared_ptr<IBossState>> m_statesP2;
    std::shared_ptr<IBossState> m_currentState;
};