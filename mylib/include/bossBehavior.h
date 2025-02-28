#pragma once

#include "behaviorTree.h"
#include "boss.h"
#include "game.h"

class Game;

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
            getGameObject()->setState(Boss::BossStatePhaseOne::Transformation);
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
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack1);

            m_player.takeDamage(damage);

            return Success;
        }
    };

    class BossAttackFlame1 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttackFlame1(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::AttackFlame1);
            return Success;
        }
    };

    class BossAttack2 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttack2(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::Attack2);
            return Success;
        }
    };

    class BossAttackFlame2 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttackFlame2(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::AttackFlame2);
            return Success;
        }
    };

    class BossAttack3 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttack3(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::Attack3);
            return Success;
        }
    };

    class BossAttackFlame3 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        BossAttackFlame3(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::AttackFlame3);
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

    class FlameJumpAttack : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        FlameJumpAttack(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::JumpAttackFlame);
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

    class RunFlameTowardsPlayer : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        RunFlameTowardsPlayer(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::RunFlame);
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

    class IdleFlame : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        IdleFlame(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::IdleFlame);
            return Success;
        }
    };

    class Hurt : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Hurt(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState(Boss::BossStatePhaseOne::Hurt);
            return Success;
        }
    };

    class HurtFlame : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        HurtFlame(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::HurtFlame);
            return Success;
        }
    };

    class Death : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Death(ICompositeNode* parent) : BehaviorNodeDecorator<Boss, IActionNode>(parent) {}

        Status tick() override
        {
            getGameObject()->setState2(Boss::BossStatePhaseTwo::Death);
            return Success;
        }
    };
}