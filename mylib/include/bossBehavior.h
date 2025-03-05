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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseOne(Boss::BossStatePhaseOne::Attack1);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseOne::Attack1);
                player.takeDamage(damage);
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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::IdleFlame);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame1);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame1);
                player.takeDamage(damage);
            }

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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseOne(Boss::BossStatePhaseOne::Attack2);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseOne::Attack2);
                player.takeDamage(damage);
            }

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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::IdleFlame);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame2);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame2);
                player.takeDamage(damage);
            }

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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseOne(Boss::BossStatePhaseOne::Attack3);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseOne::Attack3);
                player.takeDamage(damage);
            }

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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::IdleFlame);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::AttackFlame3);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseTwo::AttackFlame3);
                player.takeDamage(damage);
            }

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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseOne(Boss::BossStatePhaseOne::BossJumpAttack);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseOne::BossJumpAttack);
                player.takeDamage(damage);
            }

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
            if (!m_game) return Failed;

            Hero& player = m_game->getPlayer();
            Boss* boss = getGameObject();

            if (player.getHp() <= 0)
            {
                boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::IdleFlame);
                std::cout << "Hero is dead!" << std::endl;
                return Failed;
            }

            boss->setStatePhaseTwo(Boss::BossStatePhaseTwo::BossJumpAttackFlame);

            sf::FloatRect bossAttackHitbox = boss->getHitbox();
            sf::FloatRect heroHitbox = player.getHitbox();

            if (bossAttackHitbox.intersects(heroHitbox))
            {
                int damage = boss->getAttackDamage(Boss::BossStatePhaseTwo::BossJumpAttackFlame);
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
            if (!getGameObject()->getCurrentTarget())
                return Failed;

            if (getGameObject()->getHitbox().intersects(getGameObject()->getCurrentTarget()->getHitbox()))
            {
                getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Attack1);
                return Success;
            }

            getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Run);
            auto target = getGameObject()->getCurrentTarget()->getPlayerPosition();
            auto currentPos = getGameObject()->getSprite().getPosition();

            float moveSpeed = 200.0f;
            sf::Vector2f direction = target - currentPos;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float minSafeDistance = getGameObject()->getHitbox().width / 2 + getGameObject()->getCurrentTarget()->getHitbox().width / 2;

            if (distance > minSafeDistance)
            {
                direction /= distance;
                sf::Vector2f movement = direction * moveSpeed * 0.015f;

                if (direction.x > 0)
                {
                    getGameObject()->isFacingLeft(false);
                    getGameObject()->getSprite().setScale(2.f, 2.f);
                }
                else
                {
                    getGameObject()->isFacingLeft(true);
                    getGameObject()->getSprite().setScale(-2.f, 2.f);
                }

                getGameObject()->getSprite().move(movement);
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

    class RunFlameTowardsTarget : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        bool m_isPlayer;
    public:
        RunFlameTowardsTarget(ICompositeNode* parent, bool isPlayer)
            : BehaviorNodeDecorator(parent), m_isPlayer(isPlayer) {}

        Status tick() override
        {
            if (!getGameObject()->getCurrentTarget())
                return Failed;

            if (getGameObject()->getHitbox().intersects(getGameObject()->getCurrentTarget()->getHitbox()))
                return Success;

            getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::RunFlame);
            auto target = getGameObject()->getCurrentTarget()->getPlayerPosition();
            auto currentPos = getGameObject()->getSprite().getPosition();

            float moveSpeed = 200.0f;
            sf::Vector2f direction = target - currentPos;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            float minSafeDistance = 80.0f;

            if (distance > minSafeDistance)
            {
                direction /= distance;
                sf::Vector2f movement = direction * moveSpeed * 0.015f;

                if (direction.x > 0)
                {
                    getGameObject()->isFacingLeft(false);
                    getGameObject()->getSprite().setScale(2.f, 2.f);
                }
                else
                {
                    getGameObject()->isFacingLeft(true);
                    getGameObject()->getSprite().setScale(-2.f, 2.f);
                }

                getGameObject()->getSprite().move(movement);
            }
            return Running;

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
                reset();
                return Success;
            }

            return Running;
        }

        void reset()
        {
            m_started = false;
            m_timer.restart();
        }
    };

    class FleeFromTarget : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        float m_duration;
        sf::Clock m_timer;
        bool m_started;

    public:
        FleeFromTarget(ICompositeNode* parent, float duration = 2.0f)
            : BehaviorNodeDecorator(parent), m_duration(duration), m_started(false) {}

        Status tick() override
        {
            if (!m_started)
            {
                m_started = true;
                m_timer.restart();
                if (getGameObject()->m_phaseTwoActive)
                    getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::RunFlame);
                else
                    getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Run);
            }

            if (m_timer.getElapsedTime().asSeconds() >= m_duration)
            {
                m_started = false;
                return Success;
            }

            auto targetPos = getGameObject()->getCurrentTarget()->getPlayerPosition();
            auto bossPos = getGameObject()->getSprite().getPosition();

            sf::Vector2f direction = targetPos - bossPos;
            direction = -direction;

            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0)
            {
                direction.x /= length;
                direction.y /= length;
            }

            float moveSpeed = 80.0f;
            float deltaTime = 0.016f;

            getGameObject()->getSprite().move(direction.x * moveSpeed * deltaTime, 0.0f);

            sf::Vector2f currentPos = getGameObject()->getSprite().getPosition();
            if (direction.x > 0)
            {
                getGameObject()->getSprite().setScale(2.f, 2.f);
                getGameObject()->isFacingLeft(false);
            }
            else
            {
                getGameObject()->getSprite().setScale(-2.f, 2.f);
                getGameObject()->isFacingLeft(true);
            }
            getGameObject()->getSprite().setPosition(currentPos);

            return Running;
        }
    };

    class SetInvulnerability : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        bool m_invulnerable;

    public:
        SetInvulnerability(ICompositeNode* parent, bool invulnerable)
            : BehaviorNodeDecorator(parent), m_invulnerable(invulnerable) {}

        Status tick() override
        {
            getGameObject()->setInvulnerable(m_invulnerable);
            return Success;
        }
    };

    class IsInvulnerable : public BehaviorNodeDecorator<class Boss, IConditionalNode>
    {
    public:
        IsInvulnerable(ICompositeNode* node) : BehaviorNodeDecorator(node) {}
        bool condition() override
        {
            return getGameObject()->isInvulnerable();
        }
    };

    class ComboAttackSequence : public ICompositeNode
    {
    private:
        int m_currentAttack;
        std::vector<IActionNode*> m_attackSequence;
        sf::Clock m_attackTimer;
        float m_delayBetweenAttacks;
        bool m_sequenceStarted;

    public:
        ComboAttackSequence(ICompositeNode* parent, float delayBetweenAttacks = 0.5f)
            : ICompositeNode(parent), m_currentAttack(0), m_delayBetweenAttacks(delayBetweenAttacks), m_sequenceStarted(false) {}

        void addAttackToSequence(IActionNode* attack)
        {
            m_attackSequence.push_back(attack);
        }

        Status tick() override
        {
            if (m_attackSequence.empty())
                return Failed;

            if (!m_sequenceStarted)
            {
                m_sequenceStarted = true;
                m_currentAttack = 0;
                m_attackTimer.restart();
            }

            if (m_currentAttack >= m_attackSequence.size())
            {
                m_sequenceStarted = false;
                return Success;
            }

            if (m_attackTimer.getElapsedTime().asSeconds() >= m_delayBetweenAttacks)
            {
                Status attackStatus = m_attackSequence[m_currentAttack]->tick();

                if (attackStatus == Success)
                {
                    m_currentAttack++;
                    m_attackTimer.restart();
                }
            }

            return Running;
        }

        void display() override
        {
            std::cout << "ComboAttackSequence" << std::endl;
        }
    };

    class BossTeleport : public BehaviorNodeDecorator<class Boss, IActionNode>
    {
    private:
        sf::Clock m_teleportTimer;
        bool m_isTeleporting;
        float m_maxDistance;

    public:
        BossTeleport(ICompositeNode* parent, float maxDistance = 300.0f)
            : BehaviorNodeDecorator(parent), m_isTeleporting(false), m_maxDistance(maxDistance) {}

        Status tick() override
        {
            if (!m_isTeleporting)
            {
                if (getGameObject()->m_phaseTwoActive)
                    getGameObject()->setStatePhaseTwo(Boss::BossStatePhaseTwo::IdleFlame);
                else
                    getGameObject()->setStatePhaseOne(Boss::BossStatePhaseOne::Idle);

                m_teleportTimer.restart();
                m_isTeleporting = true;
                return Running;
            }

            if (m_teleportTimer.getElapsedTime().asSeconds() < 0.5f)
                return Running;

            sf::Vector2f currentPos = getGameObject()->getSprite().getPosition();
            sf::Vector2f targetPos = getGameObject()->getCurrentTarget()->getPlayerPosition();

            float angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * 3.14159f;
            float distance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * m_maxDistance;

            sf::Vector2f teleportPos;
            teleportPos.x = targetPos.x + cos(angle) * distance;
            teleportPos.y = targetPos.y + sin(angle) * distance;

            getGameObject()->getSprite().setPosition(teleportPos);

            if (teleportPos.x < targetPos.x)
            {
                getGameObject()->getSprite().setScale(2.f, 2.f);
                getGameObject()->isFacingLeft(false);
            }
            else
            {
                getGameObject()->getSprite().setScale(-2.f, 2.f);
                getGameObject()->isFacingLeft(true);
            }

            m_isTeleporting = false;
            return Success;
        }
    };

    class RandomChance : public BehaviorNodeDecorator<class Boss, IConditionalNode>
    {
    private:
        float m_probability;

    public:
        RandomChance(ICompositeNode* node, float probability = 0.3f)
            : BehaviorNodeDecorator(node), m_probability(probability) {}

        bool condition() override
        {
            float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            return random < m_probability;
        }
    };
}