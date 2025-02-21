#pragma once

#include "state.h"
#include <map>

class Hero;

namespace HeroStateNames
{
    enum class stateName;
}

class HeroState
{
public:
    HeroState();
    ~HeroState();

    using StateEnum = HeroStateNames::stateName;

    void setState(Hero* hero, HeroStateNames::stateName newState);
    std::shared_ptr<IState> getCurrentState() const;

    void handleInput(Hero& hero);
    void update(Hero& hero, float deltaTime);

private:
    std::map<StateEnum, std::shared_ptr<IState>> m_states;
    std::shared_ptr<IState> m_currentState;
};