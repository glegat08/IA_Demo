#ifndef BOSS_H
#define BOSS_H

#include "gameObject.h"
#include "hero.h"

enum class BossStatePhaseOne {
    Idle,
    Run,
    JumpAttack,
    Hurt,
    Attack1,
    Attack2,
    Attack3,
    Transformation
};

enum class BossStatePhaseTwo {
    IdleFlame,
    RunFlame,
    JumpAttackFlame,
    HurtFlame,
    Death,
    AttackFlame1,
    AttackFlame2,
    AttackFlame3
};

struct AnimationData {
    int frameWidth;
    int frameHeight;
    int numFrames;
    float frameDuration;
    sf::Texture texture;
};

class IEnemy : public GameObject
{
public:
    IEnemy();
    IEnemy(sf::RenderWindow* window, Hero* hero);
    virtual ~IEnemy() override = default;

    virtual sf::Sprite& getSprite() = 0;
    virtual sf::FloatRect getHitbox() const = 0;

    virtual bool isAlive() const override;
    virtual bool isShooting() const override;
    virtual bool isAttacking() const override;
    virtual bool isInvulnerable() const override;

    virtual void setTexture() override;
    virtual void updateAnim() override;
    virtual void movement() override;
    virtual void randomPos(sf::RenderWindow* window);

protected:
    sf::RenderWindow* m_renderWindow;
    Hero* m_hero;

    int m_health = 100;
    int m_shield = 0;
};

class FirstBoss : public IEnemy
{
public:
    FirstBoss(sf::RenderWindow* window, Hero* hero);

    void setTexture() override;
    void movement() override;
    bool isAttacking() const override;
    void setState(BossStatePhaseOne newState);
    void setState(BossStatePhaseTwo newState);
    void switchToPhaseTwo();
    int getHp() const override;
    int getShield() const override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;
    void getWeapon() override;
    void switchWeapon() override;
    void updateAnim() override;
    void resetAnimation();
    void firstBossMove(const sf::Vector2u& windowSize);

    sf::Sprite& getSprite() override;
    sf::FloatRect getHitbox() const override;

private:
    // Phase 1 Textures
    sf::Texture m_textureIdle;
    sf::Texture m_textureRun;
    sf::Texture m_textureJumpAttack;
    sf::Texture m_textureHurt;
    sf::Texture m_textureTransformation;
    sf::Texture m_textureAttack1;
    sf::Texture m_textureAttack2;
    sf::Texture m_textureAttack3;

    // Phase 2 Textures
    sf::Texture m_textureIdleFlame;
    sf::Texture m_textureRunFlame;
    sf::Texture m_textureJumpAttackFlame;
    sf::Texture m_textureHurtFlame;
    sf::Texture m_textureDeath;
    sf::Texture m_textureAttackFlame1;
    sf::Texture m_textureAttackFlame2;
    sf::Texture m_textureAttackFlame3;

    sf::Sprite m_cBossSprite;

    AnimationData m_currentAnimation;
    sf::Clock m_animationClock;
    int m_currentFrame = 0;

    BossStatePhaseOne m_statePhaseOne = BossStatePhaseOne::Idle;
    BossStatePhaseTwo m_statePhaseTwo = BossStatePhaseTwo::IdleFlame;
    bool m_phaseTwoActive = false;
};

#endif // BOSS_H
