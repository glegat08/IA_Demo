#include "boss.h"
#include <stdexcept>

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
    if (!m_textureIdle.loadFromFile("idle.png") ||
        !m_textureRun.loadFromFile("run.png") ||
        !m_textureJumpAttack.loadFromFile("jumpAttack.png") ||
        !m_textureHurt.loadFromFile("hurt.png") ||
        !m_textureTransformation.loadFromFile("transformation.png") ||
        !m_textureAttack1.loadFromFile("attack1.png") ||
        !m_textureAttack2.loadFromFile("attack2.png") ||
        !m_textureAttack3.loadFromFile("attack3.png") ||

        !m_textureIdleFlame.loadFromFile("idle_flame.png") ||
        !m_textureRunFlame.loadFromFile("run_flame.png") ||
        !m_textureJumpAttackFlame.loadFromFile("jumpAttack_flame.png") ||
        !m_textureHurtFlame.loadFromFile("hurt_flame.png") ||
        !m_textureDeath.loadFromFile("death.png") ||
        !m_textureAttackFlame1.loadFromFile("attack_flame1.png") ||
        !m_textureAttackFlame2.loadFromFile("attack_flame2.png") ||
        !m_textureAttackFlame3.loadFromFile("attack_flame3.png"))
    {
        throw "Erreur de chargement des textures du boss";
    }

    m_cBossSprite.setTexture(m_textureIdle);
}

void FirstBoss::setTexture()
{
    /*m_cBossTexture.loadFromFile("resource\\.png");
    m_cBossSprite.setTexture(m_cBossTexture);
    m_cBossSprite.setScale(0.5f, 0.5f);
    m_cBossSprite.setPosition(100.f, 100.f);
    m_cBossSprite.setRotation(0.f);*/
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
    if (damage <= 0)
        return;

    m_health -= damage;

    if (m_health <= 0)
    {
        setState(BossStatePhaseTwo::Death);
        return;
    }

    if (m_health <= 50 && !m_phaseTwoActive)
        setState(BossStatePhaseOne::Transformation);
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

    if (movementSwitchClock.getElapsedTime().asSeconds() > 3.f) 
    {
        switchMove = (std::rand() % 2 == 0);
        movementSwitchClock.restart();
    }

    if (switchMove) {
        if (position.x <= 0)
        {
            move = 10;
            m_cBossSprite.setRotation(90.f);
        }
        else if (position.x >= (windowSize.x - 10.f) - m_cBossSprite.getGlobalBounds().width)
        {
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

void FirstBoss::setState(BossStatePhaseOne newState)
{
    if (m_phaseTwoActive)
        return;

    m_statePhaseOne = newState;
    m_currentFrame = 0;
    m_animationClock.restart();

    switch (m_statePhaseOne)
    {
    case BossStatePhaseOne::Idle:
        m_cBossSprite.setTexture(m_textureIdle);
        break;
    case BossStatePhaseOne::Run:
        m_cBossSprite.setTexture(m_textureRun);
        break;
    case BossStatePhaseOne::JumpAttack:
        m_cBossSprite.setTexture(m_textureJumpAttack);
        break;
    case BossStatePhaseOne::Hurt:
        m_cBossSprite.setTexture(m_textureHurt);
        break;
    case BossStatePhaseOne::Attack1:
        m_cBossSprite.setTexture(m_textureAttack1);
        break;
    case BossStatePhaseOne::Attack2:
        m_cBossSprite.setTexture(m_textureAttack2);
        break;
    case BossStatePhaseOne::Attack3:
        m_cBossSprite.setTexture(m_textureAttack3);
        break;
    case BossStatePhaseOne::Transformation:
        m_cBossSprite.setTexture(m_textureTransformation);
        m_animationClock.restart();
        break;
    }
}

void FirstBoss::setState(BossStatePhaseTwo newState)
{
    if (!m_phaseTwoActive)
        return;

    m_statePhaseTwo = newState;
    m_currentFrame = 0;
    m_animationClock.restart();

    switch (m_statePhaseTwo)
    {
    case BossStatePhaseTwo::IdleFlame:
        m_cBossSprite.setTexture(m_textureIdleFlame);
        break;
    case BossStatePhaseTwo::RunFlame:
        m_cBossSprite.setTexture(m_textureRunFlame);
        break;
    case BossStatePhaseTwo::JumpAttackFlame:
        m_cBossSprite.setTexture(m_textureJumpAttackFlame);
        break;
    case BossStatePhaseTwo::HurtFlame:
        m_cBossSprite.setTexture(m_textureHurtFlame);
        break;
    case BossStatePhaseTwo::Death:
        m_cBossSprite.setTexture(m_textureDeath);
        break;
    case BossStatePhaseTwo::AttackFlame1:
        m_cBossSprite.setTexture(m_textureAttackFlame1);
        break;
    case BossStatePhaseTwo::AttackFlame2:
        m_cBossSprite.setTexture(m_textureAttackFlame2);
        break;
    case BossStatePhaseTwo::AttackFlame3:
        m_cBossSprite.setTexture(m_textureAttackFlame3);
        break;
    }
}

void FirstBoss::switchToPhaseTwo()
{
    if (m_phaseTwoActive)
        return;

    m_phaseTwoActive = true;

    sf::Clock transformationClock;
    while (transformationClock.getElapsedTime().asSeconds() < 2.0f)
    {
    }

    setState(BossStatePhaseTwo::IdleFlame);
}

