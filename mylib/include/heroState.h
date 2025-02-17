#pragma once

#include "state.h"

class HeroState
{
public:
	IdleState idle();
	AttackState attack();
	JumpState jump();
	BlockState block();
	RunState run();

private:
	IState* m_currentState;
};