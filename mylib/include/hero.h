#pragma once
#include "gameObject.h"
#include "heroState.h"

namespace HeroStateNames
{
	enum class stateName
	{
		idle,
		run,
		jump,
		attack,
		dodge,
		hurt,
		death
	};
}

class Hero : public gameObject
{
public:
	Hero();
	~Hero();

	using stateName = HeroStateNames::stateName;

	// BOOL METHOD
	bool isAlive() override;
	bool isShooting() override;
	bool isAttacking() override;
	bool isInvulnerable() override;

	// VOID METHOD
	void takeDamage(int damage) override;
	void setInvulnerable(float duration) override;
	void updateInvulnerabilityEffect();
	void attacking();
	void setState(stateName newState);
	void handleInput();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	int getHp() override;

	sf::Texture& getTexture(const stateName& stateName_);
	sf::Sprite& getSprite();

	friend class Game;
private:
	int m_health = 100;

	bool m_isIdle;
	bool m_isAttacking;

	float m_speed = 200.f;

	// GAMEPLAY
	sf::Clock m_invulnerableClock;
	sf::Clock m_blinkClock;
	float m_invulnerableDuration;
	bool m_isInvulnerable = false;
	sf::FloatRect m_hitbox;

	sf::Sprite m_sprites;
	std::map<stateName, sf::Texture> m_textures;
	HeroState m_stateManager;
	stateName m_currentStateName;
};