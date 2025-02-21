#pragma once
#include <SFML/Graphics.hpp>

class Hero;

class IState
{
public:
	virtual ~IState() = default;
	virtual void handleInput(Hero& hero) = 0;
	virtual void update(Hero& hero, float deltaTime) = 0;
	virtual void setTexture(Hero& hero) = 0;
};

class IdleState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	const int m_frameWidth = 96;
	const int m_frameHeight = 64;
	int m_frameCount = 10;
	int m_currentFrame = 0;
	float m_frameTime = 0.1f;
	sf::Clock m_elapsedTime;
};

class AttackState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Vector2i m_frameSize;
	int m_frameCount;
	int m_currentFrame;
	float m_frameTime;
	float m_elapsedTime;
};

class JumpState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.2f;
	int m_currentFrame = 0;
	const int m_frameCount = 3;
	const int m_frameWidth = 96;
	const int m_frameHeight = 64;

	float m_verticalVelocity = -250.0f;
	float m_gravity = 80.0f;
	float m_groundLevel = 900.0f;
};

class BlockState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Vector2i m_frameSize;
	int m_frameCount;
	int m_currentFrame;
	float m_frameTime;
	float m_elapsedTime;
};

class RunState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Clock m_elapsedTime;
	const float m_frameTime = 0.03f;
	int m_currentFrame = 0;
	const int m_frameCount = 16;
	const int m_frameWidth = 96;
	const int m_frameHeight = 64;
};

class DodgeState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero, float deltaTime) override;
	void setTexture(Hero& hero) override;

protected:
	sf::Vector2i m_frameSize;
	int m_frameCount;
	int m_currentFrame;
	float m_frameTime;
	float m_elapsedTime;
};