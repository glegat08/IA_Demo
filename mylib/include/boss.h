#ifndef BOSS_H
#define BOSS_H

#include "behaviorTree.h"
#include "gameObject.h"
#include "game.h"


namespace BossStateNames
{
    enum class BossStatePhaseOne
	{
        Idle,
        Run,
        JumpAttack,
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
        JumpAttackFlame,
        HurtFlame,
        Death,
        AttackFlame1,
        AttackFlame2,
        AttackFlame3
    };
}

//class Boss : public gameObject
//{
//public:
//    Boss();
//    ~Boss();
//
//    using BossStatePhaseOne = BossStateNames::BossStatePhaseOne;
//    using BossStatePhaseTwo = BossStateNames::BossStatePhaseTwo;
//
//    // BOOL METHOD
//    bool isAlive() override;
//    bool isShooting() override;
//    bool isAttacking() override;
//    bool isInvulnerable() override;
//
//    void initializeBehaviorTree();
//    void loadTextures();
//    void setState(BossStatePhaseOne newState);
//    void setState2(BossStatePhaseTwo newState);
//    void switchToPhaseTwo();
//    void resetAnimation();
//    void firstBossMove(const sf::Vector2u& windowSize);
//    void takeDamage(int damage) override;
//    void setInvulnerable(float duration) override;
//    void updateInvulnerabilityEffect();
//    void attacking();
//    void handleInput();
//    void update(float deltaTime);
//    void draw(sf::RenderWindow& window);
//
//    int getHp() const;
//    int getShield() const;
//
//    sf::Sprite& getSprite();
//    sf::FloatRect getHitbox() const;
//
//    sf::Texture& getTexture(const BossStatePhaseOne& stateName_);
//    sf::Texture& getTexture2(const BossStatePhaseTwo& stateName_);
//
//    friend class Game;
//
//protected:
//    int m_health = 300;
//    bool m_isIdle;
//    bool m_isAttacking;
//    float m_speed = 200.f;
//
//    sf::Sprite m_cBossSprite;
//
//    sf::Clock m_animationClock;
//    int m_currentFrame = 0;
//
//    bool m_phaseTwoActive = false;
//    BossStatePhaseOne m_currentStateName;
//    BossStatePhaseTwo m_currentStateNameP2;
//
//private:
//
//    // GAMEPLAY
//    sf::Clock m_invulnerableClock;
//    sf::Clock m_blinkClock;
//    float m_invulnerableDuration;
//    bool m_isInvulnerable = false;
//    sf::FloatRect m_hitbox;
//
//    sf::Sprite m_sprites;
//    std::map<BossStatePhaseOne, sf::Texture> m_texturesP1;
//    std::map<BossStatePhaseTwo, sf::Texture> m_texturesP2;
//    BossState m_stateManager;
//};

class Boss : public gameObject
{
public:
    using BossStatePhaseOne = BossStateNames::BossStatePhaseOne;
    using BossStatePhaseTwo = BossStateNames::BossStatePhaseTwo;

    Boss(Game& game);

    void update();
    void findValidTarget();
    void switchToPhaseTwo();

    void setState(BossStatePhaseOne newState);
    void setState2(BossStatePhaseTwo newState);

    bool isAlive() override;
    bool isShooting() override;
    bool isAttacking() override;
    bool isInvulnerable() override;
    int getHp() override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;

    void setHp(int health);

    BT::Status tick();

    //GETTERS
    sf::Sprite& getSprite();
    /*sf::FloatRect getHitbox() const;*/

    sf::Texture& getTexture(const BossStatePhaseOne& stateName_);
    sf::Texture& getTexture2(const BossStatePhaseTwo& stateName_);

    bool m_phaseTwoActive;

private:
    Game& m_game;
    Hero* m_currentTarget;
    int m_health;
    bool m_invulnerable;
    float m_invulnerableDuration;
    BT::RootNode<Boss> m_rootNode;

    sf::Sprite m_sprites;
	std::map<BossStatePhaseOne, sf::Texture> m_texturesP1;
	std::map<BossStatePhaseTwo, sf::Texture> m_texturesP2;
};

#endif // BOSS_H