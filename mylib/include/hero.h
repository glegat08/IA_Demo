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
		jump_attack,
		block,
		dodge,
		hurt,
		death
	};
}

class Hero : public IGameObject
{
public:
	Hero();
	~Hero() override = default;

	using stateName = HeroStateNames::stateName;

	bool isAlive() override;
	bool isShooting() override;
	bool isAttacking() override;
	bool isInvulnerable() override;
	bool isFacingLeft() const;
	bool isJumping() const;
	bool isOnGround() const;


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
	void pushState(stateName newState);
	void popState();
	void setOnGround(bool);


	sf::Texture& getTexture(const stateName& stateName_);
	sf::Sprite& getSprite();
	stateName getCurrentState() const;
	HeroState& getStateManager();

	void setStateTexture();


	int getDamage() const;
	int getHp() override;
	float getSpeed() const;
	float getJumpVelocity() const;

	void setHorizontalVelocity(float velocity);
	float getHorizontalVelocity() const;
	void setVerticalVelocity(float velocity);
	float getVerticalVelocity() const;

	sf::FloatRect getHitbox() const;
	sf::Vector2f getPlayerPosition();
	sf::Vector2f getPlayerCenter();

	bool getAirDodge(bool newResult);
	bool getIsJumping(bool newResult);
	bool getIsJumping();
	bool getIsHurt(bool newResult);
	bool getIsHurt();
	bool getIsDead();
	bool getIsDead(bool newResult);

protected:
	int m_health = 40;
	int m_attackDmg = 51;

	bool m_isIdle;
	bool m_isAttacking;
	bool m_isFacingLeft = false;
	bool m_isJumping;
	bool m_isOnGround = false;
	bool m_isAirDodging = false;
	bool m_isHurt = false;
	bool m_isDead = false;

	float m_speed = 70.f;
	float m_horizontalVelocity = 0.f;
	float m_verticalVelocity = 0.f;
	float m_jumpVelocity = 0.f;

protected:
	// GAMEPLAY
	bool m_isInvulnerable = false;
	sf::Clock m_invulnerabilityTimer;
	float m_invulnerabilityDuration = 0.f;

	sf::Sprite m_sprites;
	std::map<stateName, sf::Texture> m_textures;
	HeroState m_stateManager;
	stateName m_currentStateName;
};