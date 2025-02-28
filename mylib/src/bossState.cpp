//#include "bossState.h"
//#include "boss.h"
//
//BossState::BossState()
//{
//    // First phase
//    m_statesP1[BossStateNames::BossStatePhaseOne::Idle] = std::make_shared<BossIdleState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::Run] = std::make_shared<BossRunState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::JumpAttack] = std::make_shared<BossJumpState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::Hurt] = std::make_shared<BossHurtState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::Attack1] = std::make_shared<BossFirstAttackState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::Attack2] = std::make_shared<BossSecondAttackState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::Attack3] = std::make_shared<BossThirdAttackState>();
//    m_statesP1[BossStateNames::BossStatePhaseOne::Transformation] = std::make_shared<BossTransformationState>();
//
//    /* Second one*/
//    m_statesP2[BossStateNames::BossStatePhaseTwo::IdleFlame] = std::make_shared<BossIdleFlameState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::RunFlame] = std::make_shared<BossRunFlameState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::JumpAttackFlame] = std::make_shared<BossJumpFlameState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::HurtFlame] = std::make_shared<BossHurtFlameState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::Death] = std::make_shared<BossDeathState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::AttackFlame1] = std::make_shared<BossFirstAttackFlameState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::AttackFlame2] = std::make_shared<BossSecondAttackFlameState>();
//    m_statesP2[BossStateNames::BossStatePhaseTwo::AttackFlame3] = std::make_shared<BossThirdAttackFlameState>();
//
//    m_currentState = m_statesP1[BossStateNames::BossStatePhaseOne::Idle];
//}
//
//BossState::~BossState()
//{
//    m_statesP1.clear();
//    m_statesP2.clear();
//    m_currentState = nullptr;
//}
//
//void BossState::setState(Boss* boss, BossStateNames::BossStatePhaseOne newState)
//{
//    if (m_statesP1.find(newState) == m_statesP1.end())
//        return;
//
//    m_currentState = m_statesP1[newState];
//
//    if (boss != nullptr)
//        m_currentState->setBossTexture(*boss);
//}
//
//void BossState::setState2(Boss* boss, BossStateNames::BossStatePhaseTwo newState)
//{
//    if (m_statesP2.find(newState) == m_statesP2.end())
//        return;
//
//    m_currentState = m_statesP2[newState];
//
//    if (boss != nullptr)
//        m_currentState->setBossTexture(*boss);
//}
//
//std::shared_ptr<IBossState> BossState::getCurrentState() const
//{
//    return m_currentState;
//}
//
//void BossState::update(Boss& boss, float deltaTime) const
//{
//    if (m_currentState != nullptr)
//		m_currentState->update(boss, deltaTime);
//}