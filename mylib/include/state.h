#pragma once
#include <SFML/System.hpp>

class Hero;
class Boss;

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
	sf::Vector2i m_frameSize;
	int m_frameCount;
	int m_currentFrame;
	float m_frameTime;
	float m_elapsedTime;
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
	const int m_frameWidth = 96;
	const int m_frameHeight = 64;
	int m_frameCount = 16;
	int m_currentFrame = 0;
	float m_frameTime = 0.04f;
	sf::Clock m_elapsedTime;
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


//////////////////////////////////////////////////////////////////////////

class IBossState
{
public:
	virtual ~IBossState() = default;
	virtual void update(Boss& boss, float deltaTime) = 0;
	virtual void setTexture(Boss& boss) = 0;
};

class BossIdleState : public IBossState
{
public:
	void update(Boss& boss, float deltaTime) override;
	void setTexture(Boss& boss) override;

protected:
	const int m_frameWidth = 128;
	const int m_frameHeight = 108;
	int m_frameCount = 6;
	int m_currentFrame = 0;
	float m_frameTime = 0.1f;
	sf::Clock m_elapsedTime;
};