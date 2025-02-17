#pragma once
#include "gameObject.h"
#include "heroState.h"

class Hero : public gameObject
{
public:
	Hero();
	~Hero();


	// BOOL METHOD
	bool isAlive() override;
	bool isShooting() override;
	bool isAttacking() override;
	bool isInvulnerable() override;

	// VOID METHOD
	void setTexture() override;
	void updateAnim() override;
	void movement() override;
	void takeDamage(int damage) override;
	void getWeapon() override;
	void setInvulnerable(float duration) override;
	void updateInvulnerabilityEffect();
	void attacking();
	void setState(IState* newState);
	void handleInput();
	void update();
	void draw(sf::RenderWindow& window);

	int getShield() override;
	int getHp() override;

	sf::Texture& getTexture(const std::string& stateName);
	sf::Sprite& getSprite();


private:
	friend class Game;
	int m_health = 100;

	bool m_isIdle;
	bool m_isAttacking;

	// ANIMATION
	sf::Clock m_movementClock;
	sf::Clock m_movementAnimation;
	sf::Clock m_animationClock;
	const int m_frameWidth = 64;
	const int m_frameHeight = 64;
	const int m_numFrames = 8;
	const int m_numDirections = 4;
	int m_currentFrame = 0;
	int m_currentDirection = 0;
	float m_speed = 200.f;

	// GAMEPLAY
	sf::Clock m_invulnerableClock;
	sf::Clock m_blinkClock;
	float m_invulnerableDuration;
	bool m_isInvulnerable = false;
	sf::FloatRect m_hitbox;

	sf::Sprite m_sprites;
	std::map<std::string, sf::Texture> m_textures;
	IState* m_currentState;
};