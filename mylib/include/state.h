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
	virtual void setBossTexture(Boss& boss) = 0;
};

///////////////////////   PHASE 1  //////////////////////////////////////

class BossIdleState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 6;
    int m_currentFrame = 0;
    float m_frameTime = 0.1f;
    sf::Clock m_elapsedTime;
};

class BossRunState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 8;
    int m_currentFrame = 0;
    float m_frameTime = 0.08f;
    sf::Clock m_elapsedTime;
};

class BossHurtState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 4;
    int m_currentFrame = 0;
    float m_frameTime = 0.12f;
    sf::Clock m_elapsedTime;
};

class BossFirstAttackState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 7;
    int m_currentFrame = 0;
    float m_frameTime = 0.09f;
    sf::Clock m_elapsedTime;
};

class BossSecondAttackState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 6;
    int m_currentFrame = 0;
    float m_frameTime = 0.1f;
    sf::Clock m_elapsedTime;
};

class BossThirdAttackState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 7;
    int m_currentFrame = 0;
    float m_frameTime = 0.09f;
    sf::Clock m_elapsedTime;
};

class BossJumpState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 12;
    int m_currentFrame = 0;
    float m_frameTime = 0.07f;
    sf::Clock m_elapsedTime;
};

class BossTransformationState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 17;
    int m_currentFrame = 0;
    float m_frameTime = 0.08f;
    sf::Clock m_elapsedTime;
};

////////////////////////////////////////////////////////////////

class BossIdleFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 6;
    int m_currentFrame = 0;
    float m_frameTime = 0.1f;
    sf::Clock m_elapsedTime;
};

class BossRunFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 8;
    int m_currentFrame = 0;
    float m_frameTime = 0.08f;
    sf::Clock m_elapsedTime;
};

class BossHurtFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 4;
    int m_currentFrame = 0;
    float m_frameTime = 0.12f;
    sf::Clock m_elapsedTime;
};

class BossFirstAttackFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 7;
    int m_currentFrame = 0;
    float m_frameTime = 0.09f;
    sf::Clock m_elapsedTime;
};

class BossSecondAttackFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 6;
    int m_currentFrame = 0;
    float m_frameTime = 0.1f;
    sf::Clock m_elapsedTime;
};

class BossThirdAttackFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 7;
    int m_currentFrame = 0;
    float m_frameTime = 0.09f;
    sf::Clock m_elapsedTime;
};

class BossJumpFlameState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 12;
    int m_currentFrame = 0;
    float m_frameTime = 0.07f;
    sf::Clock m_elapsedTime;
};

class BossDeathState : public IBossState
{
public:
    void update(Boss& boss, float deltaTime) override;
    void setBossTexture(Boss& boss) override;

protected:
    const int m_frameWidth = 128;
    const int m_frameHeight = 108;
    int m_frameCount = 10;
    int m_currentFrame = 0;
    float m_frameTime = 0.1f;
    sf::Clock m_elapsedTime;
};