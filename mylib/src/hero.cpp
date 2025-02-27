#include "hero.h"

#include "resourceManager.h"

Hero::Hero()
{
    m_textures[stateName::idle].loadFromFile(PathManager::getResourcePath("hero\\IDLE.png"));
    m_textures[stateName::run].loadFromFile(PathManager::getResourcePath("hero\\RUN.png"));
    m_textures[stateName::jump].loadFromFile(PathManager::getResourcePath("hero\\JUMP.png"));
    m_textures[stateName::dodge].loadFromFile(PathManager::getResourcePath("hero\\DASH.png"));
    m_textures[stateName::attack].loadFromFile(PathManager::getResourcePath("hero\\ATTACK1.png"));
	m_textures[stateName::jump_attack].loadFromFile(PathManager::getResourcePath("hero\\AIR_ATTACK.png"));
	m_textures[stateName::block].loadFromFile(PathManager::getResourcePath("hero\\BLOCK.png"));

	m_sprites.setTexture(m_textures[stateName::idle]);
    m_sprites.setScale(2.f, 2.f);
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

bool Hero::isOnGround() const
{
    return m_isOnGround;
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
    sf::FloatRect spriteRect = m_sprites.getGlobalBounds();
    float width, height, offsetX, y;

    // IDLE STATE
    width = spriteRect.width * 0.2f;
    height = spriteRect.height * 1.0f;

    if (m_isFacingLeft)
        offsetX = spriteRect.width * 0.75f;
    else
        offsetX = spriteRect.width * 0.05f;

    y = spriteRect.top + (spriteRect.height - height) * 0.35f;

    switch (m_currentStateName)
    {
	case stateName::run:
		width = spriteRect.width * 0.3f;
        if (m_isFacingLeft)
			offsetX = spriteRect.width * 0.65f;
		else
			offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::attack:
        width = spriteRect.width * 0.47f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.47f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::jump_attack:
        width = spriteRect.width * 0.54f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.4f;
        else
            offsetX = spriteRect.width * 0.05f;
        break;
    case stateName::dodge:
        width = spriteRect.width * 0.18f;
        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.2f;
        else
            offsetX = spriteRect.width * 0.66f;
        break;
	case stateName::block:
		width = spriteRect.width * 0.3f;
		if (m_isFacingLeft)
			offsetX = spriteRect.width * 0.65f;
		else
			offsetX = spriteRect.width * 0.05f;
		break;
    }

    float x = spriteRect.left + offsetX;

    return sf::FloatRect(x, y, width, height);
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

void Hero::pushState(stateName newState)
{
    m_currentStateName = newState;
    m_stateManager.pushState(this, newState);
    m_sprites.setTexture(m_textures[newState]);
}

void Hero::popState()
{
    m_stateManager.popState(this);
    m_currentStateName = m_stateManager.getCurrentStateName();
}

void Hero::setOnGround(bool onGround)
{
    m_isOnGround = onGround;
}
