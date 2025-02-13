#ifndef BOSS_H
#define BOSS_H

#include "gameObject.h"
#include "hero.h"

struct AnimationData {
    int frameWidth;
    int frameHeight;
    int numFrames;
};

class IEnemy : public GameObject
{
public:
    IEnemy();
    IEnemy(sf::RenderWindow* window, Player* player);
    virtual ~IEnemy() = default;

    // Pure virtual methods
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
    Player* m_player;

    int m_health = 100;
    int m_shield = 0;
};

class FirstBoss : public IEnemy
{
public:
    FirstBoss(sf::RenderWindow* window, Player* player);

    void setTexture() override;
    void movement() override;
    bool isAttacking() override;
    int getHp() const override;
    int getShield() const override;
    void takeDamage(int damage) override;
    void setInvulnerable(float duration) override;
    void getWeapon() override;
    void switchWeapon() override;
    void updateAnim() override;

    sf::Sprite& getSprite() override;
    sf::FloatRect getHitbox() const;

private:
    sf::Texture m_cBossTexture;
    sf::Sprite m_cBossSprite;

    void moveLikeACrab(const sf::Vector2u& windowSize);
};

#endif // BOSS_H