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
    public:
        IfHealthLow(ICompositeNode* node) : BehaviorNodeDecorator(node) {}
        bool condition() override
        {
            return getGameObject()->getHp() < 100;
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
    public:
        BossAttack1(ICompositeNode* parent, Game* game)
            : BehaviorNodeDecorator(parent), m_game(game) {}

        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack1);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::Attack1));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::Attack1);

            if (m_game)
            {
                Hero& player = m_game->getPlayer();
                if (getGameObject()->getHitbox().intersects(player.getHitbox()))
                {
                    player.takeDamage(damage);
                }
            }

            return Success;
        }
    };


    class BossAttackFlame1 : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class BossAttack2 : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class BossAttackFlame2 : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class BossAttack3 : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class BossAttackFlame3 : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class BossJumpAttack : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossJumpAttack(ICompositeNode* parent, Game* game)
            : BehaviorNodeDecorator(parent), m_game(game) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::BossJumpAttack);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture(Boss::BossStatePhaseOne::BossJumpAttack));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseOne::BossJumpAttack);
            if (m_game)
                m_game->getPlayer().takeDamage(damage);
            return Success;
        }
    };

    class BossJumpAttackFlame : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        Game* m_game;
    public:
        BossJumpAttackFlame(ICompositeNode* parent, Game* game)
            : BehaviorNodeDecorator(parent), m_game(game) {}
        Status tick() override
        {
            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::BossJumpAttackFlame);
            getGameObject()->getSprite().setTexture(getGameObject()->getTexture2(Boss::BossStatePhaseTwo::BossJumpAttackFlame));
            int damage = getGameObject()->getAttackDamage(Boss::BossStatePhaseTwo::BossJumpAttackFlame);
            if (m_game)
                m_game->getPlayer().takeDamage(damage);
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

            float distance = std::abs(directionX);

            if (distance < 50.0f)
                return Success;

            float moveSpeed = 200.0f;
            float deltaTime = 0.016f;

            if (directionX > 0)
            {
                boss->getSprite().move(moveSpeed * deltaTime, 0.0f);
                sf::Vector2f currentPos = boss->getSprite().getPosition();
                boss->getSprite().setScale(2.f, 2.f);
                boss->isFacingLeft(false);
                boss->getSprite().setPosition(currentPos);
            }
            else if (directionX < 0)
            {
                boss->getSprite().move(-moveSpeed * deltaTime, 0.0f);
                sf::Vector2f currentPos = boss->getSprite().getPosition();
                boss->getSprite().setScale(-2.f, 2.f);
                boss->isFacingLeft(true);
                boss->getSprite().setPosition(currentPos);
            }
            return Running;
        }
    };

    /*class RandomAttackSelector : public ICompositeNode
    {
    private:
        std::vector<IActionNode*> m_children;
    public:
        RandomAttackSelector(ICompositeNode* parent)
            : ICompositeNode(parent)
        {}

        void addChild(IActionNode* child)
        {
            m_children.push_back(child);
        }

        Status tick() override
        {
            if (m_children.empty())
                return Failed;
            int index = std::rand() % m_children.size();
            return m_children[index]->tick();
        }

        void display() override
        {
            for (auto child : m_children)
                child->display();
        }
    };*/

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

    class Hurt : public BehaviorNodeDecorator<class Boss, IActionNode>
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

    class Wait : public IActionNode {
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
}