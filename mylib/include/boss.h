#ifndef BOSS_H
#define BOSS_H

#include "behaviorTree.h"
#include "gameObject.h"
#include "game.h"
#include <unordered_map>
#include <functional>

struct AnimationData
{
    int frameCount;
    float frameDuration;
};

namespace BossStateNames
{
    enum class BossStatePhaseOne
    {
        Idle,
        Run,
        BossJumpAttack,
        Hurt,
        Attack1,
        Attack2,
        Attack3,
        Transformation
    };

    enum class BossStatePhaseTwo
    {
        IdleFlame,
        RunFlame,
        BossJumpAttackFlame,
        HurtFlame,
        Death,
        AttackFlame1,
        AttackFlame2,
        AttackFlame3
    };
}

class Boss : public IGameObject
{
public:
    using BossStatePhaseOne = BossStateNames::BossStatePhaseOne;
    using BossStatePhaseTwo = BossStateNames::BossStatePhaseTwo;

    // default constructor
    Boss() : m_game(nullptr), m_currentTarget(nullptr), m_health(100),
        m_isInvulnerable(false), m_isAttacking(false), m_invulnerableDuration(0.f),
        m_phaseTwoActive(false), m_currentStateName(BossStatePhaseOne::Idle),
        m_currentStateNameP2(BossStatePhaseTwo::IdleFlame), m_rootNode(nullptr)
    {}

    Boss(Game* game);
    void initializeBehaviorTree();

    void update(float deltaTime);
    void updateTimedActions();
    void updateMovementAndAttack(float deltaTime);
    void findValidTarget();
    void switchToPhaseTwo();
    void loadTextures();
    void updateInvulnerabilityEffect();
    void attacking();

    void setStatePhaseOne(BossStatePhaseOne newState);
    void setStatePhaseTwo(BossStatePhaseTwo newState);
    void updateAnimation();

    bool isAlive() override;
    bool isShooting() override;
    bool isAttacking() override;
    bool isInvulnerable() override;
    bool isCloseToTarget() const;
    int getHp() override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;

    void performTimedAction(const std::string& action, float interval, std::function<void()> callback);

    void setHp(int health);
    int getHp() const;
    sf::FloatRect getHitbox() const;
    sf::FloatRect getHitboxPhaseOne(const sf::FloatRect& spriteRect) const;
    sf::FloatRect getHitboxPhaseTwo(const sf::FloatRect& spriteRect) const;
    bool isInPhaseOne() const;
    Hero* getCurrentTarget() const;
    void moveTowardsPlayer(float deltaTime);
    void retreatFromPlayer(float deltaTime);

    //attack
    int getAttackDamage(BossStatePhaseOne attackType) const;
    int getAttackDamage(BossStatePhaseTwo attackType) const;

    void draw(sf::RenderWindow& window) const;

    BT::Status tick();

    //GETTERS
    sf::Sprite& getSprite();

    sf::Texture& getTexture(const BossStatePhaseOne& stateName_);
    sf::Texture& getTexture2(const BossStatePhaseTwo& stateName_);

    bool m_phaseTwoActive;
    bool isFacingLeft(bool newBool);
    bool isFacingLeft();

private:
    Game* m_game;
    Hero* m_currentTarget;
    int m_health;
    sf::Clock m_invulnerableClock;
    sf::Clock m_blinkClock;
    bool m_isInvulnerable;
    bool m_isAttacking;
    float m_invulnerableDuration;
    BT::RootNode m_rootNode;
    int m_currentFrame = 0;
    int m_frameCount = 0;
    float m_frameDuration = 0.0f;
    float m_speed = 70.f;
    sf::Clock m_animationClock;
    sf::Clock m_runAnimationClock;
    sf::Clock m_attackDelayClock;
    bool m_isFacingLeft = false;
    const int m_frameWidth = 128;
    const int m_frameHeight = 64;

    //attack ratio
    int attack1Damage = 10;
    int attack2Damage = 10;
    int attack3Damage = 10;
    int jumpAttackDamage = 20;
    int attackFlame1Damage = 20;
    int attackFlame2Damage = 20;
    int attackFlame3Damage = 20;
    int jumpAttackFlameDamage = 30;

    sf::Sprite m_sprites;
    std::unordered_map<std::string, sf::Clock> m_actionTimers;
    std::unordered_map<std::string, float> m_actionIntervals;
    BossStatePhaseOne m_currentStateName;
    BossStatePhaseTwo m_currentStateNameP2;

    std::map<BossStatePhaseOne, AnimationData> phaseOneAnimations = {
    {BossStatePhaseOne::Idle, {6, 0.2f}},
    {BossStatePhaseOne::Run, {8, 0.1f}},
    {BossStatePhaseOne::Hurt, {4, 0.3f}},
    {BossStatePhaseOne::Attack1, {7, 0.12f}},
    {BossStatePhaseOne::Attack2, {6, 0.15f}},
    {BossStatePhaseOne::Attack3, {7, 0.1f}},
    {BossStatePhaseOne::BossJumpAttack, {12, 0.08f}},
    {BossStatePhaseOne::Transformation, {17, 0.12f}}
    };

    std::map<BossStatePhaseTwo, AnimationData> phaseTwoAnimations = {
    {BossStatePhaseTwo::IdleFlame, {6, 0.18f}},
    {BossStatePhaseTwo::RunFlame, {8, 0.1f}},
    {BossStatePhaseTwo::HurtFlame, {4, 0.3f}},
    {BossStatePhaseTwo::AttackFlame1, {7, 0.1f}},
    {BossStatePhaseTwo::AttackFlame2, {6, 0.12f}},
    {BossStatePhaseTwo::AttackFlame3, {7, 0.1f}},
    {BossStatePhaseTwo::BossJumpAttackFlame, {12, 0.07f}},
    {BossStatePhaseTwo::Death, {10, 0.2f}},
    };

    std::unordered_map<BossStatePhaseOne, sf::Clock> attackCooldowns;
    std::unordered_map<BossStatePhaseOne, float> attackIntervals =
    {
        {BossStatePhaseOne::Attack1, 2.0f},
        {BossStatePhaseOne::Attack2, 4.0f},
        {BossStatePhaseOne::Attack3, 6.0f},
        {BossStatePhaseOne::BossJumpAttack, 8.0f}
    };

    std::map<BossStatePhaseOne, sf::Texture> m_texturesP1;
    std::map<BossStatePhaseTwo, sf::Texture> m_texturesP2;
};

#endif // BOSS_H