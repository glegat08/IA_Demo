#include "state.h"
#include <SFML/Graphics.hpp>

#include "hero.h"
#include "boss.h"

// IDLE STATE
void IdleState::handleInput(Hero& hero)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		hero.setState(HeroStateNames::stateName::run);
}

void IdleState::update(Hero& hero, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		m_elapsedTime.restart();

		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		hero.getSprite().setTextureRect(frameRect);
	}
}

void IdleState::setTexture(Hero& hero)
{
	hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::idle));
	hero.getSprite().setScale(2.f, 2.f);
}

// ATTACK STATE
void AttackState::handleInput(Hero& hero)
{
}

void AttackState::update(Hero& hero, float deltaTime)
{
}

void AttackState::setTexture(Hero& hero)
{
}

// JUMPING STATE
void JumpState::handleInput(Hero& hero)
{
}

void JumpState::update(Hero& hero, float deltaTime)
{
}

void JumpState::setTexture(Hero& hero)
{
}

// BLOCK STATE
void BlockState::handleInput(Hero& hero)
{
}

void BlockState::update(Hero& hero, float deltaTime)
{
}

void BlockState::setTexture(Hero& hero)
{
}

// RUN STATE

void RunState::handleInput(Hero& hero)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		hero.setState(HeroStateNames::stateName::idle);
	}
}

void RunState::update(Hero& hero, float deltaTime)
{
	sf::Vector2f position = hero.getSprite().getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position.x += 4.f * deltaTime;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position.x -= 4.f * deltaTime;
	}

	hero.getSprite().setPosition(position);

	// Animation
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		m_elapsedTime.restart();

		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		hero.getSprite().setTextureRect(frameRect);
	}
}

void RunState::setTexture(Hero& hero)
{
	hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::run));
	hero.getSprite().setScale(2.f, 2.f);
}

// DODGE STATE
void DodgeState::handleInput(Hero& hero)
{
}

void DodgeState::update(Hero& hero, float deltaTime)
{
}

void DodgeState::setTexture(Hero& hero)
{
}

  ///////////////////////////////////////////////////////////////////
 /////////////////////// PHASE 1 ///////////////////////////////////
///////////////////////////////////////////////////////////////////

void BossIdleState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossIdleState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Idle));
	boss.getSprite().setScale(2.f, 2.f);
}

void BossRunState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossRunState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Run));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossHurtState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime) 
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossHurtState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Hurt));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossFirstAttackState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime) 
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossFirstAttackState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack1));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossSecondAttackState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossSecondAttackState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack2));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossThirdAttackState::update(Boss& boss, float deltaTime) {
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime) 
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossThirdAttackState::setBossTexture(Boss& boss) {
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack3));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossTransformationState::update(Boss& boss, float deltaTime) {
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossTransformationState::setBossTexture(Boss& boss) {
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack3));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

  ///////////////////////////////////////////////////////////////////
 /////////////////////// PHASE 2 ///////////////////////////////////
///////////////////////////////////////////////////////////////////


void BossIdleFlameState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossIdleFlameState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Idle));
	boss.getSprite().setScale(2.f, 2.f);
}

void BossRunFlameState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossRunFlameState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Run));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossHurtFlameState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossHurtFlameState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Hurt));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossFirstAttackFlameState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossFirstAttackFlameState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack1));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossSecondAttackFlameState::update(Boss& boss, float deltaTime)
{
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossSecondAttackFlameState::setBossTexture(Boss& boss)
{
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack2));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossThirdAttackFlameState::update(Boss& boss, float deltaTime) {
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossThirdAttackFlameState::setBossTexture(Boss& boss) {
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack3));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}

void BossDeathState::update(Boss& boss, float deltaTime) {
	if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
	{
		m_currentFrame = (m_currentFrame + 1) % m_frameCount;
		sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
		boss.getSprite().setTextureRect(frameRect);
		m_elapsedTime.restart();
	}
}

void BossDeathState::setBossTexture(Boss& boss) {
	boss.getSprite().setTexture(boss.getTexture(BossStateNames::BossStatePhaseOne::Attack3));
	boss.getSprite().setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
}