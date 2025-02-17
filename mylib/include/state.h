#pragma once

class Hero;

class IState
{
public:
	virtual ~IState() = default;
	virtual void handleInput(Hero& hero) = 0;
	virtual void update(Hero& hero) = 0;
	virtual void setTexture(Hero& hero) = 0;
};

class IdleState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero) override;
	void setTexture(Hero& hero) override;
};

class AttackState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero) override;
	void setTexture(Hero& hero) override;
};

class JumpState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero) override;
	void setTexture(Hero& hero) override;
};

class BlockState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero) override;
	void setTexture(Hero& hero) override;
};

class RunState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero) override;
	void setTexture(Hero& hero) override;
};

class DodgeState : public IState
{
public:
	void handleInput(Hero& hero) override;
	void update(Hero& hero) override;
	void setTexture(Hero& hero) override;
};