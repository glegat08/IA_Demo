#include "state.h"
#include <SFML/Graphics.hpp>

#include "hero.h"

// IDLE STATE
void IdleState::handleInput(Hero& hero)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		hero.setState(new RunState());
	}
}

void IdleState::update(Hero& hero)
{
}

void IdleState::setTexture(Hero& hero)
{
	hero.getSprite().setTexture(hero.getTexture("idle"));
}

// ATTACK STATE
void AttackState::handleInput(Hero& hero)
{
}

void AttackState::update(Hero& hero)
{
}

void AttackState::setTexture(Hero& hero)
{
}

// JUMPING STATE
void JumpState::handleInput(Hero& hero)
{
}

void JumpState::update(Hero& hero)
{
}

void JumpState::setTexture(Hero& hero)
{
}

// BLOCK STATE
void BlockState::handleInput(Hero& hero)
{
}

void BlockState::update(Hero& hero)
{
}

void BlockState::setTexture(Hero& hero)
{
}

// RUN STATE
void RunState::handleInput(Hero& hero)
{
}

void RunState::update(Hero& hero)
{
}

void RunState::setTexture(Hero& hero)
{
}

// DODGE STATE
void DodgeState::handleInput(Hero& hero)
{
}

void DodgeState::update(Hero& hero)
{
}

void DodgeState::setTexture(Hero& hero)
{
}
