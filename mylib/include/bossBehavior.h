#pragma once

#include "behaviorTree.h"
#include "boss.h"
#include "game.h"

class Game;

namespace BT
{
    class IfPhaseTwo : public BehaviorNodeDecorator<class Boss, IConditionalNode>
    {
    public:
        IfPhaseTwo(ICompositeNode* node) : BehaviorNodeDecorator(node) {}
        bool condition() override
        {
            return getGameObject()->m_phaseTwoActive;
        }
    };

    class IfHealthLow : public BehaviorNodeDecorator<class Boss, IConditionalNode>
    {
    private:
        int m_threshold;

    public:
        IfHealthLow(ICompositeNode* node, int threshold)
            : BehaviorNodeDecorator(node), m_threshold(threshold) {}

        bool condition() override
        {
            return getGameObject()->getHp() < m_threshold;
        }
    };

    class TransformToPhaseTwo : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class BossAttack1 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossAttack1(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack1);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack1));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack1);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossAttackFlame1 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossAttackFlame1(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame1);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::AttackFlame1));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame1);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossAttack2 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossAttack2(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack2);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack2));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack2);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossAttackFlame2 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossAttackFlame2(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame2);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::AttackFlame2));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame2);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossAttack3 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossAttack3(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack3);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack3));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack3);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossAttackFlame3 : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossAttackFlame3(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame3);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::AttackFlame3));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame2);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossJumpAttack : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossJumpAttack(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::BossJumpAttack);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::BossJumpAttack));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::BossJumpAttack);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class BossJumpAttackFlame : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
        float m_attackRange;

    public:
        BossJumpAttackFlame(ICompositeNode* parent, Game* game, float attackRange)
            : BehaviorNodeDecorator(parent), m_game(game), m_attackRange(attackRange) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::BossJumpAttackFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::BossJumpAttackFlame));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::BossJumpAttackFlame);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                sf::Vector2f bossPos = getGameObject()->getSprite().getPosition();
                sf::Vector2f playerPos = player.getPlayerPosition();
                float distance = std::sqrt(std::pow(bossPos.x - playerPos.x, 2) + std::pow(bossPos.y - playerPos.y, 2));

                if (distance <= m_attackRange && getGameObject()->getHitbox().intersects(player.getHitbox()))
                    player.takeDamage(damage);
            }

            return Success;
        }
    };

    class CheckTargetInRange : public IConditionalNode
    {
    private:
        float m_range;
    public:
        CheckTargetInRange(ICompositeNode* parent, float range)
            : IConditionalNode(parent), m_range(range)
        {}

        bool condition() override
        {
            auto boss = dynamic_cast<class Boss*>(getGameObject());
            if (!boss || !boss->getCurrentTarget())
                return false;

            sf::Vector2f bossPos = boss->getSprite().getPosition();
            sf::Vector2f targetPos = boss->getCurrentTarget()->getPlayerPosition();
            float dx = bossPos.x - targetPos.x;
            float dy = bossPos.y - targetPos.y;
            float dist = std::sqrt(dx * dx + dy * dy);
            return dist <= m_range;
        }

        void display() override
        {
            std::cout << "CheckTargetInRange: range = " << m_range << std::endl;
        }
    };

    class RunTowardsTarget : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        bool m_isPlayer;

    public:
        RunTowardsTarget(ICompositeNode* parent, bool isPlayer)
            : BehaviorNodeDecorator(parent), m_isPlayer(isPlayer) {}

        Status tick() override
        {
            auto boss = dynamic_cast<class Boss*>(getGameObject());
            if (!boss || (m_isPlayer && !boss->getCurrentTarget()))
                return Failed;

            boss->getSprite().setTexture(boss->getTexture(Boss::BossStatePhaseOne::Run));

            auto target = boss->getCurrentTarget()->getPlayerPosition();
            sf::Vector2f bossPos = boss->getSprite().getPosition();
            float directionX = target.x - bossPos.x;

            float moveSpeed = 200.0f;
            float deltaTime = 0.016f;

            if (directionX > 0)
            {
                boss->getSprite().move(moveSpeed * deltaTime, 0.0f);
                boss->getSprite().setScale(2.f, 2.f);
                boss->isFacingLeft(false);
            }
            else if (directionX < 0)
            {
                boss->getSprite().move(-moveSpeed * deltaTime, 0.0f);
                boss->getSprite().setScale(-2.f, 2.f);
                boss->isFacingLeft(true);
            }

            float distanceToTarget = std::sqrt(std::pow(target.x - bossPos.x, 2) + std::pow(target.y - bossPos.y, 2));
            if (distanceToTarget <= 10.0f)
            {
                return Success;
            }
            return Running;
        }
    };


    class AttackOrChaseSelector : public ICompositeNode
    {
    public:
        AttackOrChaseSelector(ICompositeNode* parent)
            : ICompositeNode(parent)
        {}

        Status tick() override
        {
            for (auto child : getChildren())
            {
                Status status = child->tick();
                if (status == Success || status == Running)
                    return status;
            }
            return Failed;
        }

        void display() override
        {
            for (auto child : getChildren())
                child->display();
        }
    };

    class RunFlameTowardsPlayer : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class Idle : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class IdleFlame : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class Hurt : public IConditionalNode
    {
    public:
        Hurt(ICompositeNode* parent, Game* game) : IConditionalNode(parent), m_game(game) {}

        bool condition() override
        {
            if (!m_game)
                return false;

            auto* boss = dynamic_cast<Boss*>(getGameObject());
            if (!boss)
                return false;

            Hero& player = m_game->getPlayer();
            int damage = player.getDamage();

            if (damage > 0)
            {
                boss->takeDamage(damage);
                return true;
            }
        }

        Status tick() override
        {
            if (!m_isTickingChildNode)
            {
                if (condition())
                    m_isTickingChildNode = true;
                else
                    return Success;
            }

            return tickChildren();
        }

    private:
        Game* m_game;
        bool m_isTickingChildNode = false;
    };


    class HurtFlame : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    public:
        HurtFlame(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::HurtFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::HurtFlame));
            return Success;
        }
    };

    class Death : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    public:
        Death(ICompositeNode* parent) : BehaviorNodeDecorator(parent) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::Death);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::Death));
            return Success;
        }
    };

    class Wait : public IActionNode
	{
    private:
        sf::Time m_duration;
        sf::Clock m_timer;
        bool m_started = false;

    public:
        Wait(ICompositeNode* parent, float duration)
            : IActionNode(parent), m_duration(sf::seconds(duration)) {}

        Status tick() override
    	{
            if (!m_started) 
            {
                m_started = true;
                m_timer.restart();
            }

            if (m_timer.getElapsedTime() >= m_duration) 
            {
                m_started = false;
                return Success;
            }

            return Running;
        }
    };

    class WaitForAnimation : public IActionNode
	{
    public:
        WaitForAnimation(ICompositeNode* parent, Boss* boss) : IActionNode(parent), m_boss(boss) {}

        Status tick() override
    	{
            if (m_boss->isAnimationComplete())
                return Success;
            return Running;
        }

    private:
        Boss* m_boss;
    };

}