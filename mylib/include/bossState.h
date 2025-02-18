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

    void setState(Hero* hero, BossStateNames::BossStatePhaseOne newState);
    std::shared_ptr<IState> getCurrentState() const { return m_currentState; }

    void handleInput(Hero& hero);
    void update(Hero& hero, float deltaTime);

private:
    std::map<StateEnumP1, std::shared_ptr<IState>> m_statesP1;
    std::map<StateEnumP2, std::shared_ptr<IState>> m_statesP2;
    std::shared_ptr<IState> m_currentState;
};