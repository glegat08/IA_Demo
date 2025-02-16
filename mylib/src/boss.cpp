#include "boss.h"

enum Corner
{
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

IEnemy::IEnemy() : m_health(100)
{
}

// Base IEnemy Class
IEnemy::IEnemy(sf::RenderWindow* window, Hero* hero)
    : m_renderWindow(window), m_hero(hero), m_health(100)
{
    randomPos(window);
}

bool IEnemy::isAlive() const
{
    return m_health > 0;
}

bool IEnemy::isShooting() const
{
    return false;
}

bool IEnemy::isAttacking() const
{
    return false;
}

bool IEnemy::isInvulnerable() const
{
    return false;
}

void IEnemy::setTexture()
{
}

void IEnemy::updateAnim()
{
}

void IEnemy::movement()
{
}

void IEnemy::randomPos(sf::RenderWindow* window)
{
    sf::Vector2u windowSize = window->getSize();
    float x, y;

    if (auto* boss = dynamic_cast<FirstBoss*>(this))
    {
        const float margin = 50.f;
        int corner = rand() % 4;

        switch (corner)
        {
        case TOP_LEFT:
            x = margin;
            y = margin;
            break;
        case TOP_RIGHT:
            x = windowSize.x - margin - boss->getSprite().getGlobalBounds().width;
            y = margin;
            break;
        case BOTTOM_LEFT:
            x = margin;
            y = windowSize.y - margin - boss->getSprite().getGlobalBounds().height;
            break;
        case BOTTOM_RIGHT:
            x = windowSize.x - margin - boss->getSprite().getGlobalBounds().width;
            y = windowSize.y - margin - boss->getSprite().getGlobalBounds().height;
            break;
        }

        boss->getSprite().setPosition(x, y);
        boss->resetAnimation();
    }
}

FirstBoss::FirstBoss(sf::RenderWindow* window, Hero* hero)
    : IEnemy(window, hero)
{
    m_health = 150000;

    setTexture();
    srand(static_cast<unsigned int>(time(nullptr)));
}

void FirstBoss::setTexture()
{
    m_cBossTexture.loadFromFile("resource\\CrabBoss.png");
    m_cBossSprite.setTexture(m_cBossTexture);
    m_cBossSprite.setScale(0.5f, 0.5f);
    m_cBossSprite.setPosition(100.f, 100.f);
    m_cBossSprite.setRotation(0.f);
}

void FirstBoss::movement()
{
    sf::Vector2u windowSize = m_renderWindow->getSize();
    firstBossMove(windowSize);
}

bool FirstBoss::isAttacking() const
{
    return true;
}

int FirstBoss::getHp() const
{
    return 0;
}

int FirstBoss::getShield() const
{
    return 0;
}

void FirstBoss::takeDamage(int damage)
{
    m_health -= damage;
    if (m_health < 0) 
        m_health = 0;
}

void FirstBoss::setInvulnerable(float duration)
{
}

void FirstBoss::getWeapon()
{
}

void FirstBoss::switchWeapon()
{
}

void FirstBoss::updateAnim()
{
}

sf::Sprite& FirstBoss::getSprite()
{
    return m_cBossSprite;
}

sf::FloatRect FirstBoss::getHitbox() const
{
    return m_cBossSprite.getGlobalBounds();
}

void FirstBoss::firstBossMove(const sf::Vector2u& windowSize)
{
    /*static sf::Clock movementSwitchClock;
    static bool switchMove = true;
    static int move = 1;

    sf::Vector2f position = m_cBossSprite.getPosition();

    if (movementSwitchClock.getElapsedTime().asSeconds() > 3.f) {
        switchMove = (std::rand() % 2 == 0);
        movementSwitchClock.restart();
    }

    if (switchMove) {
        if (position.x <= 0) {
            move = 10;
            m_cBossSprite.setRotation(90.f);
        }
        else if (position.x >= (windowSize.x - 10.f) - m_cBossSprite.getGlobalBounds().width) {
            move = -10;
            m_cBossSprite.setRotation(270.f);
        }
        m_cBossSprite.move(move * 2.f, 0);
    }
    else {
        if (position.y <= 0) {
            move = 10;
            m_cBossSprite.setRotation(180.f);
        }
        else if (position.y >= (windowSize.y - 10.f) - m_cBossSprite.getGlobalBounds().height) {
            move = -10;
            m_cBossSprite.setRotation(0.f);
        }
        m_cBossSprite.move(0, move * 2.f);
    }*/
}