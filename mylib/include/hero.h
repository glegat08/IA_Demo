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
	bool isFacingLeft() const;
	bool isJumping() const;

	// VOID METHOD
	void takeDamage(int damage) override;
	void setInvulnerable(float duration) override;
	void updateInvulnerabilityEffect();
	void attacking();
	void setState(stateName newState);
	void handleInput();
	void update(float deltaTime);
	void setSpeed(float speed);
	void move(const sf::Vector2f& offset);
	void setFacingLeft(bool left);


	sf::Texture& getTexture(const stateName& stateName_);
	sf::Sprite& getSprite();
	stateName getCurrentState() const;


	int getHp() override;
	float getSpeed() const;
	float getJumpVelocity() const;

	friend class Game;

	void setHorizontalVelocity(float velocity) { m_horizontalVelocity = velocity; }
	float getHorizontalVelocity() const { return m_horizontalVelocity; }
	sf::FloatRect getHitbox() const;
	sf::Vector2f getPlayerPosition();
	sf::Vector2f getPlayerCenter();

private:
	int m_health = 100;

	bool m_isIdle;
	bool m_isAttacking;
	bool m_isFacingLeft = false;
	float m_jumpVelocity = 0.f;
	bool m_isJumping;

	float m_speed = 70.f;
	float m_horizontalVelocity = 0.f;

	// GAMEPLAY
	sf::Clock m_invulnerableClock;
	sf::Clock m_blinkClock;
	float m_invulnerableDuration;
	bool m_isInvulnerable = false;

	sf::Sprite m_sprites;
	std::map<stateName, sf::Texture> m_textures;
	HeroState m_stateManager;
	stateName m_currentStateName;
};