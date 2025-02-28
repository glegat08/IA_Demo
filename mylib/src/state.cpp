#include "state.h"

#include <SFML/Graphics.hpp>

#include "hero.h"
#include "boss.h"

bool IState::m_dashAvailable = true;
sf::Clock IState::m_dashCooldownClock;
const float IState::m_dashCooldownDuration = 2.0f;
bool IState::m_mouseLeftPressed = false;

// ISTATE
bool IState::isGoingLeft()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
}

bool IState::isGoingRight()
{
    return sf::Keyboard::isKeyPressed((sf::Keyboard::D));
}

bool IState::isJumping()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
}

bool IState::isDodging()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && canDodge();
}

bool IState::canDodge()
{
    if (!m_dashAvailable && m_dashCooldownClock.getElapsedTime().asSeconds() >= m_dashCooldownDuration)
        m_dashAvailable = true;

    return m_dashAvailable;
}

bool IState::isAttacking()
{
    bool currentPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool result = currentPressed && !m_mouseLeftPressed;
    m_mouseLeftPressed = currentPressed;
    return result;
}

bool IState::isJumpAttacking()
{
    if (isJumping())
    {
        bool currentPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool result = currentPressed && !m_mouseLeftPressed;
        m_mouseLeftPressed = currentPressed;
        return result;
    }
}

bool IState::isBlocking()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}

void IState::updateDirection(Hero& hero)
{
    if (isGoingRight() && !isGoingLeft())
    {
        hero.setFacingLeft(false);
        hero.getSprite().setScale(2.f, 2.f);
    }
    else if (isGoingLeft() && !isGoingRight())
    {
        hero.setFacingLeft(true);
        hero.getSprite().setScale(-2.f, 2.f);
    }
}

bool IState::isTemporaryState() const
{
    return false;
}



// IDLE STATE
void IdleState::handleInput(Hero& hero)
{
    if (isGoingLeft() || isGoingRight())
        hero.setState(HeroStateNames::stateName::run);

    updateDirection(hero);

    if (isJumping())
        hero.setState(HeroStateNames::stateName::jump);

    if (isAttacking())
        hero.setState(HeroStateNames::stateName::attack);

    if (isBlocking())
        hero.setState(HeroStateNames::stateName::block);
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
}

// ATTACK STATE
void AttackState::handleInput(Hero& hero)
{
    updateDirection(hero);
}

void AttackState::update(Hero& hero, float deltaTime)
{
    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
    {
        m_currentFrame++;
        m_elapsedTime.restart();

        if (m_currentFrame >= m_frameCount)
        {
            m_currentFrame = 0;

            if (isGoingLeft() || isGoingRight())
                hero.setState(HeroStateNames::stateName::run);
            else
                hero.setState(HeroStateNames::stateName::idle);

            return;
        }

        sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
        hero.getSprite().setTextureRect(frameRect);
    }
}

void AttackState::setTexture(Hero& hero)
{
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::attack));
}

// JUMPING STATE
void JumpState::handleInput(Hero& hero)
{
    updateDirection(hero);

    if (isDodging())
        hero.m_stateManager.pushState(&hero, HeroStateNames::stateName::dodge);

    if (isAttacking())
        hero.setState(HeroStateNames::stateName::jump_attack);

    if (isGoingRight() && !isGoingLeft())
        hero.setHorizontalVelocity(hero.getSpeed());
    else if (isGoingLeft() && !isGoingRight())
        hero.setHorizontalVelocity(-hero.getSpeed());
    else
        hero.setHorizontalVelocity(0);
}

void JumpState::update(Hero& hero, float deltaTime)
{
    float clampedDeltaTime = std::min(deltaTime, 0.1f);

    float verticalVelocity = hero.getVerticalVelocity();
    verticalVelocity += m_gravity * clampedDeltaTime;
    hero.setVerticalVelocity(verticalVelocity);

    hero.move(sf::Vector2f(hero.getHorizontalVelocity() * clampedDeltaTime,
        verticalVelocity * clampedDeltaTime));

    if (hero.isOnGround())
    {
        hero.m_isJumping = false;

        if (isGoingLeft() || isGoingRight())
            hero.setState(HeroStateNames::stateName::run);
        else
            hero.setState(HeroStateNames::stateName::idle);

        return;
    }

    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_elapsedTime.restart();
        sf::IntRect currentFrameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
        hero.getSprite().setTextureRect(currentFrameRect);
    }
}

void JumpState::setTexture(Hero& hero)
{
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::jump));

    if (!hero.m_isJumping)
    {
        hero.m_isJumping = true;
        hero.setVerticalVelocity(-250.f);
    }
}

// JUMPING ATTACK STATE
void JumpAttack::handleInput(Hero& hero)
{
    updateDirection(hero);
}

void JumpAttack::update(Hero& hero, float deltaTime)
{
    float clampedDeltaTime = std::min(deltaTime, 0.1f);

    float verticalVelocity = hero.getVerticalVelocity();
    verticalVelocity += m_gravity * clampedDeltaTime;
    hero.setVerticalVelocity(verticalVelocity);

    hero.move(sf::Vector2f(hero.getHorizontalVelocity() * clampedDeltaTime,
        verticalVelocity * clampedDeltaTime));

    if (hero.isOnGround())
    {
        hero.m_isJumping = false;

        if (isGoingLeft() || isGoingRight())
            hero.setState(HeroStateNames::stateName::run);
        else
            hero.setState(HeroStateNames::stateName::idle);

        return;
    }

    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
    {
        m_currentFrame++;
        m_elapsedTime.restart();

        if (m_currentFrame >= m_frameCount)
        {
            m_currentFrame = 0;
            hero.setState(HeroStateNames::stateName::jump);
            return;
        }

        sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
        hero.getSprite().setTextureRect(frameRect);
    }
}

void JumpAttack::setTexture(Hero& hero)
{
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::jump_attack));
}

// BLOCK STATE
void BlockState::handleInput(Hero& hero)
{
    if (isJumping())
        hero.setState(HeroStateNames::stateName::jump);
    if (isDodging())
        hero.setState(HeroStateNames::stateName::dodge);
    if (isAttacking())
        hero.setState(HeroStateNames::stateName::attack);

    updateDirection(hero);
}

void BlockState::update(Hero& hero, float deltaTime)
{
    if (!isBlocking())
    {
        if (isGoingLeft() || isGoingRight())
            hero.setState(HeroStateNames::stateName::run);
        else
            hero.setState(HeroStateNames::stateName::idle);
        return;
    }

    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_elapsedTime.restart();
        sf::IntRect frameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
        hero.getSprite().setTextureRect(frameRect);
    }
}

void BlockState::setTexture(Hero& hero)
{
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::block));
}

// RUN STATE
void RunState::handleInput(Hero& hero)
{
    if ((!isGoingRight() && !isGoingLeft()) || (isGoingRight() && isGoingLeft()))
        hero.setState(HeroStateNames::stateName::idle);

    if (isJumping())
        hero.setState(HeroStateNames::stateName::jump);

    if (isDodging())
        hero.setState(HeroStateNames::stateName::dodge);

    if (isAttacking())
        hero.setState(HeroStateNames::stateName::attack);

    updateDirection(hero);
}

void RunState::update(Hero& hero, float deltaTime)
{
    if (hero.getCurrentState() == HeroStateNames::stateName::run)
    {
        float clampedDeltaTime = std::min(deltaTime, 0.1f);

        if (isGoingRight() && !isGoingLeft())
        {
            hero.move(sf::Vector2f(hero.getSpeed() * clampedDeltaTime, 0));
            updateDirection(hero);
        }
        else if (isGoingLeft() && !isGoingRight())
        {
            hero.move(sf::Vector2f(-hero.getSpeed() * clampedDeltaTime, 0));
            updateDirection(hero);
        }

        if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
        {
            m_currentFrame = (m_currentFrame + 1) % m_frameCount;
            m_elapsedTime.restart();
            sf::IntRect currentFrameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
            hero.getSprite().setTextureRect(currentFrameRect);
        }
    }
}

void RunState::setTexture(Hero& hero)
{
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::run));
}

// DODGE STATE
void DodgeState::handleInput(Hero& hero)
{
    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_dodgeDuration)
    {
        if (!hero.m_stateManager.isStateStackEmpty())
            hero.m_stateManager.popState(&hero);
        else
        {
            if (isGoingLeft() || isGoingRight())
                hero.setState(HeroStateNames::stateName::run);
            else
                hero.setState(HeroStateNames::stateName::idle);
        }
    }
}

void DodgeState::update(Hero& hero, float deltaTime)
{
    float clampedDeltaTime = std::min(deltaTime, 0.1f);
    float dashDirection = hero.isFacingLeft() ? -1.0f : 1.0f;

    IState::m_dashCooldownClock.restart();
    IState::m_dashAvailable = false;

    hero.move(sf::Vector2f(m_dodgeSpeed * dashDirection * clampedDeltaTime, 0));

    if (m_elapsedTime.getElapsedTime().asSeconds() >= m_frameTime)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_elapsedTime.restart();
        sf::IntRect currentFrameRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight);
        hero.getSprite().setTextureRect(currentFrameRect);
    }
}

void DodgeState::setTexture(Hero& hero)
{
    hero.getSprite().setTexture(hero.getTexture(HeroStateNames::stateName::dodge));
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