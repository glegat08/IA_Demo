#include "boss.h"

Boss::Boss() : m_currentStateName(BossStateNames::BossStatePhaseOne::Idle)
{
    m_texturesP1[BossStateNames::BossStatePhaseOne::Idle].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\IDLE.png");
    m_texturesP1[BossStateNames::BossStatePhaseOne::Run].loadFromFile("C:\\Src\\Proj7-BossAI\\ressources\\firstBoss_Sprites\\RUN.png");

    //m_sprites.setTexture(m_textures[stateName::idle]);

    //setState(stateName::idle);

    m_sprites.setPosition(500, 500);
}

Boss::~Boss()
{
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
    return false;
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
        setState(BossStatePhaseOne::Hurt);
        // TODO : will add the anim
    }
    else
    {
        setState(BossStatePhaseOne::Hurt);
    }

    // 2sec invu after hit
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

sf::Sprite& Boss::getSprite()
{
    return m_sprites;
}

void Boss::switchToPhaseTwo()
{
    if (!m_phaseTwoActive)
    {
        m_phaseTwoActive = true;
        setState(BossStatePhaseTwo::IdleFlame);
    }
}
