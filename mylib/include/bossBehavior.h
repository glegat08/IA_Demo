#pragma once

#include "behaviorTree.h"
#include "boss.h"

namespace BT
{
    class IfPhaseTwo : public BehaviorNodeDecorator<Boss, IConditionalNode>
    {
    public:
        IfPhaseTwo(ICompositeNode* node) : BehaviorNodeDecorator<Boss, IConditionalNode>(node) {}

        bool condition() override
        {
            return getGameObject()->m_phaseTwoActive;
        }
    };

    class IfHealthLow : public BehaviorNodeDecorator<Boss, IConditionalNode>
    {
    public:
        IfHealthLow(ICompositeNode* node) : BehaviorNodeDecorator<Boss, IConditionalNode>(node) {}

        bool condition() override
        {
            return getGameObject()->getHp() < 100;
        }
    };

    class TransformToPhaseTwo : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        TransformToPhaseTwo(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->switchToPhaseTwo();
            return Success;
        }
    };

    class BossAttack1 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttack1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::Attack1);
            return Success;
        }
    };

    class BossAttackFlame1 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttackFlame1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseTwo::AttackFlame1);
            return Success;
        }
    };

    class Attack2 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Attack2(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->attacking();
            return Success;
        }
    };

    class JumpAttack : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        JumpAttack(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::JumpAttack);
            return Success;
        }
    };

    class RunTowardsPlayer : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        RunTowardsPlayer(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::Run);
            return Success;
        }
    };

    class Idle : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::Idle);
            return Success;
        }
    };
}