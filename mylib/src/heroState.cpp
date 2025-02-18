// heroState.cpp
#include "heroState.h"
#include "hero.h"

HeroState::HeroState() : m_currentState(nullptr)
{
    m_states[StateEnum::idle] = std::make_shared<IdleState>();
    m_states[StateEnum::run] = std::make_shared<RunState>();
    m_states[StateEnum::jump] = std::make_shared<JumpState>();
    m_states[StateEnum::attack] = std::make_shared<AttackState>();
    m_states[StateEnum::dodge] = std::make_shared<DodgeState>();

    m_currentState = m_states[StateEnum::idle];
}

HeroState::~HeroState()
{
    m_states.clear();
    m_currentState = nullptr;
}

void HeroState::setState(Hero* hero, HeroStateNames::stateName newState)
{
    if (m_states.find(newState) == m_states.end())
        return;

    m_currentState = m_states[newState];

    if (hero != nullptr)
        m_currentState->setTexture(*hero);
}

void HeroState::handleInput(Hero& hero)
{
    if (m_currentState != nullptr)
        m_currentState->handleInput(hero);
}

void HeroState::update(Hero& hero, float deltaTime)
{
    if (m_currentState != nullptr)
        m_currentState->update(hero, deltaTime);
}