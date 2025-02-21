#include "state.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "hero.h"

// IDLE STATE
void IdleState::handleInput(Hero& hero)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		hero.setState(HeroStateNames::stateName::run);

	if (hero.isFacingLeft())
		hero.getSprite().setScale(-2.f, 2.f);
	else
		hero.getSprite().setScale(2.f, 2.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		hero.setState(HeroStateNames::stateName::jump);
}

void IdleState::update(Hero& hero, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime) 
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		m_elapsedTime.restart();

		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		hero.getSprite().setTextureRect(frameRect);
	}
}

void IdleState::setTexture(Hero& hero)
{
	hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::idle));
}

// ATTACK STATE
void AttackState::handleInput(Hero& hero)
{
}

void AttackState::update(Hero& hero, float deltaTime)
{
}

void AttackState::setTexture(Hero& hero)
{
}

// JUMPING STATE
void JumpState::handleInput(Hero& hero)
{
}

void JumpState::update(Hero& hero, float deltaTime)
{
    float clampedDeltaTime = std::min(deltaTime, 0.1f);

    m_verticalVelocity += m_gravity * clampedDeltaTime;

    hero.move(sf::Vector2f(hero.getHorizontalVelocity() * clampedDeltaTime, m_verticalVelocity * clampedDeltaTime));

    if (hero.getSprite().getPosition().y >= m_groundLevel)
    {
        hero.getSprite().setPosition(hero.getSprite().getPosition().x, m_groundLevel);

        m_verticalVelocity = -250.f;

        if (hero.getHorizontalVelocity() > 0.1f)
            hero.setState(HeroStateNames::stateName::run);
        else
            hero.setState(HeroStateNames::stateName::idle);
    }

    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_elapsedTime.restart();
        sf::IntRect currentFrameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
        hero.getSprite().setTextureRect(currentFrameRect);
    }
}

void JumpState::setTexture(Hero& hero)
{
	hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::jump));
}

// BLOCK STATE
void BlockState::handleInput(Hero& hero)
{
}

void BlockState::update(Hero& hero, float deltaTime)
{
}

void BlockState::setTexture(Hero& hero)
{
}

// RUN STATE

void RunState::handleInput(Hero& hero)
{
    bool goingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool goingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    bool jumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (!goingRight && !goingLeft || goingRight && goingLeft)
        hero.setState(HeroStateNames::stateName::idle);
    else if (jumping)
    {
        hero.setHorizontalVelocity(goingRight ? hero.getSpeed() : -hero.getSpeed());
        hero.setState(HeroStateNames::stateName::jump);
    }
    else if (goingRight)
        hero.setFacingLeft(false);
    else if (goingLeft)
        hero.setFacingLeft(true);
}

void RunState::update(Hero& hero, float deltaTime)
{
    handleInput(hero);

    if (hero.getCurrentState() == HeroStateNames::stateName::run) 
	{
        bool goingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        bool goingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);

        float clampedDeltaTime = std::min(deltaTime, 0.1f);

        if (goingRight && !goingLeft) 
		{
            hero.move(sf::Vector2f(hero.getSpeed() * clampedDeltaTime, 0));
			hero.getSprite().setScale(2.f, 2.f);
			hero.setFacingLeft(false);
        }
        else if (goingLeft && !goingRight) 
		{
            hero.move(sf::Vector2f(-hero.getSpeed() * clampedDeltaTime, 0));
			hero.getSprite().setScale(-2.f, 2.f);
			hero.setFacingLeft(true);
        }

        if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime) 
		{
            m_currentFrame = (m_currentFrame + 1) % m_frameCount;
            m_elapsedTime.restart();
            sf::IntRect currentFrameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
            hero.getSprite().setTextureRect(currentFrameRect);
        }
    }
}

void RunState::setTexture(Hero& hero)
{
	hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::run));
}

// DODGE STATE
void DodgeState::handleInput(Hero& hero)
{
}

void DodgeState::update(Hero& hero, float deltaTime)
{
}

void DodgeState::setTexture(Hero& hero)
{
}
