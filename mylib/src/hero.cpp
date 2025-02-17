#include "hero.h"

Hero::Hero()
{
}

Hero::~Hero()
{
	delete m_currentState;
}

void Hero::setState(IState* newState)
{
	delete m_currentState;
	m_currentState = newState;
	m_currentState->setTexture(*this);
}

void Hero::handleInput()
{
	m_currentState->handleInput(*this);
}

void Hero::update()
{
	m_currentState->update(*this);
}

void Hero::draw(sf::RenderWindow& window)
{
	window.draw(m_sprites);
}

sf::Texture& Hero::getTexture(const std::string& stateName)
{
	return m_textures[stateName];
}

sf::Sprite& Hero::getSprite()
{
	return m_sprites;
}
