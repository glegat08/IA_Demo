#include "bossState.h"
#include "boss.h"
#include "state.h"

BossState::BossState()
{
    // First phase
    m_statesP1[BossStateNames::BossStatePhaseOne::Idle] = std::make_shared<BossIdleState>();
    //m_statesP1[BossStateNames::BossStatePhaseOne::Run] = std::make_shared<BossRunState>();
    //m_statesP1[BossStateNames::BossStatePhaseOne::JumpAttack] = std::make_shared<BossJumpState>();
   /* m_statesP1[BossStateNames::BossStatePhaseOne::Hurt] = std::make_shared<BossHurtState>();*/
    //m_statesP1[BossStateNames::BossStatePhaseOne::Attack1] = std::make_shared<BossFirstAttackState>();
    //m_statesP1[BossStateNames::BossStatePhaseOne::Attack2] = std::make_shared<BossSecondAttackState>();
    //m_statesP1[BossStateNames::BossStatePhaseOne::Attack3] = std::make_shared<BossThirdAttackState>();
    /*m_statesP1[BossStateNames::BossStatePhaseOne::Transformation] = std::make_shared<BossTransformationState>();*/

    // Second one
    //m_statesP2[BossStateNames::BossStatePhaseTwo::IdleFlame] = std::make_shared<BossIdleFlameState>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::RunFlame] = std::make_shared<BossRunFlameState>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::JumpAttackFlame] = std::make_shared<BossJumpAttackFlameState>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::HurtFlame] = std::make_shared<BossHurtFlameState>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::Death] = std::make_shared<BossDeathState>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::AttackFlame1] = std::make_shared<BossAttackFlame1State>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::AttackFlame2] = std::make_shared<BossAttackFlame2State>();
    //m_statesP2[BossStateNames::BossStatePhaseTwo::AttackFlame3] = std::make_shared<BossAttackFlame3State>();
}

BossState::~BossState()
{
}

void BossState::setState(Boss* boss, BossStateNames::BossStatePhaseOne newState)
{
    if (m_statesP1.find(newState) != m_statesP1.end()) {
        m_currentState = m_statesP1[newState];
        m_currentState->setTexture(*boss);
    }
}

void BossState::setState(Boss* boss, BossStateNames::BossStatePhaseTwo newState)
{
    if (m_statesP2.find(newState) != m_statesP2.end()) {
        m_currentState = m_statesP2[newState];
        m_currentState->setTexture(*boss);
    }
}

void BossState::update(Boss& boss, float deltaTime)
{
    m_currentState->update(boss, deltaTime);
}
