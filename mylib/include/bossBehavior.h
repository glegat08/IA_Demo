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
        IfPhaseTwo(ICompositeNode* node) : BehaviorNodeDecorator(node) {}

        bool condition() override
        {
            return getGameObject()->m_phaseTwoActive;
        }
    };

    class IfHealthLow : public BehaviorNodeDecorator<Boss, IConditionalNode>
    {
    public:
        IfHealthLow(ICompositeNode* node) : BehaviorNodeDecorator(node) {}

        bool condition() override
        {
            return getGameObject()->getHp() < 100;
        }
    };

    class TransformToPhaseTwo : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        TransformToPhaseTwo(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Transformation);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Transformation));
            getGameObject()->switchToPhaseTwo();
            return Success;
        }
    };

    class BossAttack1 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttack1(ICompositeNode* parent, Game* game)
            : BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack1);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack1));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack1);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };


    class BossAttackFlame1 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttackFlame1(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame1);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::AttackFlame1));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame1);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class BossAttack2 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttack2(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack2);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack2));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack2);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class BossAttackFlame2 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttackFlame2(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame2);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::AttackFlame2));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame2);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class BossAttack3 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttack3(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack3);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack3));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack3);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class BossAttackFlame3 : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossAttackFlame3(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame3);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::AttackFlame3));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame3);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class JumpAttack : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        JumpAttack(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::JumpAttack);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::JumpAttack));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::JumpAttack);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class FlameJumpAttack : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        FlameJumpAttack(ICompositeNode* parent, Game* game)
    		: BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::JumpAttackFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::JumpAttackFlame));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::JumpAttackFlame);

            if (m_game)
                m_game->getPlayer().takeDamage(damage);

            return Success;
        }
    };

    class RunTowardsPlayer : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        RunTowardsPlayer(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Run);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Run));
            return Success;
        }
    };

    class RunFlameTowardsPlayer : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        RunFlameTowardsPlayer(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::RunFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::RunFlame));
            return Success;
        }
    };

    class Idle : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Idle(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Idle));
            return Success;
        }
    };

    class IdleFlame : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        IdleFlame(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::IdleFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::IdleFlame));
            return Success;
        }
    };

    class Hurt : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Hurt(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Hurt);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Hurt));
            return Success;
        }
    };

    class HurtFlame : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        HurtFlame(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            //take damage
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::HurtFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::HurtFlame));
            return Success;
        }
    };

    class Death : public BehaviorNodeDecorator<Boss, IActionNode>
    {
    public:
        Death(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::Death);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::Death));
            //game over
            return Success;
        }
    };
}