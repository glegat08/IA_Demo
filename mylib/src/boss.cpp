#include "boss.h"

Boss::Boss()
    : m_currentStateName(BossStateNames::BossStatePhaseOne::Idle),
    m_currentStateNameP2(BossStateNames::BossStatePhaseTwo::IdleFlame),
    m_health(300), m_isInvulnerable(false), m_phaseTwoActive(false)
{
    loadTextures();
    m_sprites.setPosition(500, 500);
}

Boss::~Boss()
{}

void Boss::loadTextures()
{
    // First phase
    m_texturesP1[BossStateNames::BossStatePhaseOne::Idle].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\IDLE.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Run].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\RUN.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::JumpAttack].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\JUMP ATTACK.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Hurt].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\HURT.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Attack1].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\ATTACK 1.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Attack2].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\ATTACK 2.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Attack3].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\ATTACK 3.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Transformation].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\SHOUT.png");

    // Second phase
    m_texturesP2[BossStateNames::BossStatePhaseTwo::IdleFlame].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\IDLE (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::RunFlame].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\RUN (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::JumpAttackFlame].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\JUMP ATTACK (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::HurtFlame].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\HURT (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::AttackFlame1].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\ATTACK 1 (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::AttackFlame2].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\ATTACK 2 (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::AttackFlame3].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\ATTACK 3 (FLAMING SWORD).png");
    m_texturesP2[BossStateNames::BossStatePhaseTwo::Death].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\SHOUT (FLAMING SWORD).png");
}

bool Boss::isAlive()
{
    return m_health > 0;
}

bool Boss::isShooting()
{
    return false;
}

bool Boss::isAttacking()
{
    return m_isAttacking;
}

bool Boss::isInvulnerable()
{
    return m_isInvulnerable;
}

void Boss::takeDamage(int damage)
{
    if (m_isInvulnerable) return;

    m_health -= damage;
    if (m_health <= 0)
    {
        setState2(BossStatePhaseTwo::Death);
    }
    else
    {
        setState(BossStatePhaseOne::Hurt);
    }

    // 2sec invu
    setInvulnerable(2.0f);
}

void Boss::setInvulnerable(float duration)
{
    m_isInvulnerable = true;
    m_invulnerableClock.restart();
    m_invulnerableDuration = duration;
}

void Boss::updateInvulnerabilityEffect()
{
}

void Boss::attacking()
{
}

void Boss::setState(BossStatePhaseOne newState)
{
    if (m_currentStateName == newState)
        return;

    m_currentStateName = newState;
    m_stateManager.setState(this, newState);

    if (m_texturesP1.find(newState) != m_texturesP1.end())
        m_sprites.setTexture(m_texturesP1[newState]);
}

void Boss::setState2(BossStatePhaseTwo newState)
{
    if (m_currentStateNameP2 == newState)
        return;

    m_currentStateNameP2 = newState;
    m_stateManager.setState(this, newState);

    if (m_texturesP2.find(newState) != m_texturesP2.end())
        m_sprites.setTexture(m_texturesP2[newState]);
}

void Boss::switchToPhaseTwo()
{
    if (!m_phaseTwoActive)
    {
        m_phaseTwoActive = true;
        setState2(BossStatePhaseTwo::IdleFlame);
    }
}

void Boss::update(float deltaTime)
{
    if (m_isInvulnerable && m_invulnerableClock.getElapsedTime().asSeconds() >= m_invulnerableDuration)
        m_isInvulnerable = false;

    m_stateManager.update(*this, deltaTime);
}

void Boss::draw(sf::RenderWindow& window)
{
    window.draw(m_sprites);
}

int Boss::getHp() const
{
    return m_health;
}

sf::Texture& Boss::getTexture(const BossStatePhaseOne& stateName_)
{
    auto it = m_texturesP1.find(stateName_);
    if (it != m_texturesP1.end())
        return it->second;

    static sf::Texture defaultTexture;
    return defaultTexture;
}

sf::Texture& Boss::getTexture2(const BossStatePhaseTwo& stateName_)
{
    auto it = m_texturesP2.find(stateName_);
    if (it != m_texturesP2.end())
        return it->second;

    static sf::Texture defaultTexture;
    return defaultTexture;
}

sf::Sprite& Boss::getSprite()
{
    return m_sprites;
}
