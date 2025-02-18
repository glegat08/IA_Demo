?#include "hero.h"

Hero::Hero() : m_currentStateName(stateName::idle)
{
    m_textures[stateName::idle].loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\hero\\IDLE.png");
    m_textures[stateName::run].loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\hero\\RUN.png");

    //m_sprites.setTexture(m_textures[stateName::idle]);

    //setState(stateName::idle);

    m_sprites.setPosition(100, 900);
}

Hero::~Hero()
{
}

bool Hero::isAlive()
{
    return true;
}

bool Hero::isShooting()
{
    return false;
}

bool Hero::isAttacking()
{
    return false;
}

bool Hero::isInvulnerable()
{
    return false;
}

void Hero::takeDamage(int damage)
{
}

void Hero::setInvulnerable(float duration)
{
}

void Hero::updateInvulnerabilityEffect()
{
}

void Hero::attacking()
{
}

void Hero::setState(stateName newState)
{
    m_currentStateName = newState;
    m_stateManager.setState(this, newState);
    m_sprites.setTexture(m_textures[newState]);
}

void Hero::handleInput()
{
    m_stateManager.handleInput(*this);
}

void Hero::update(float deltaTime)
{
    m_stateManager.update(*this, deltaTime);
}

void Hero::draw(sf::RenderWindow& window)
{
    window.draw(m_sprites);
}

int Hero::getHp()
{
    return m_health;
}

sf::Texture& Hero::getTexture(const stateName& stateName_)
{
    if (m_textures.find(stateName_) == m_textures.end())
        return m_textures[stateName::idle];

    return m_textures[stateName_];
}

sf::Sprite& Hero::getSprite()
{
    return m_sprites;
}