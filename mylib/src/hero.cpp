#include "hero.h"

Hero::Hero() : m_currentStateName(stateName::idle)
{
    m_textures[stateName::idle].loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\hero\\IDLE.png");
    m_textures[stateName::run].loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\hero\\RUN.png");
    m_textures[stateName::jump].loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\hero\\JUMP.png");

	m_sprites.setTexture(m_textures[stateName::idle]);
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

bool Hero::isFacingLeft() const
{
    return m_isFacingLeft;
}

bool Hero::isJumping() const
{
    return m_isJumping;
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

void Hero::setSpeed(float speed)
{
    m_speed = speed;
}

int Hero::getHp()
{
    return m_health;
}

float Hero::getSpeed() const
{
    return m_speed;
}

float Hero::getJumpVelocity() const
{
    return m_jumpVelocity;
}

sf::FloatRect Hero::getHitbox() const
{
    sf::FloatRect m_hitbox = m_sprites.getGlobalBounds();

    float offsetX = m_hitbox.width * 0.4f;
	float offsetY = m_hitbox.height * 0.35f;
    float reducedWidth = m_hitbox.width - 2 * offsetX;
	float reducedHeight = m_hitbox.height - 2 * offsetY;

    return sf::FloatRect
    (
        m_hitbox.left + offsetX,
        m_hitbox.top + offsetY,
        reducedWidth,
        reducedHeight
    );
}

sf::Vector2f Hero::getPlayerPosition()
{
    return m_sprites.getPosition();
}

sf::Vector2f Hero::getPlayerCenter()
{
	return { getHitbox().left + getHitbox().width / 2.f, getHitbox().top + getHitbox().height / 2.f };
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

Hero::stateName Hero::getCurrentState() const
{
    return m_currentStateName;
}

void Hero::move(const sf::Vector2f& offset)
{
    m_sprites.move(offset);
}

void Hero::setFacingLeft(bool left)
{
    m_isFacingLeft = left;
}
