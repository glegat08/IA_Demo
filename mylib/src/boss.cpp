#include "boss.h"
#include "behaviorTree.h"
#include "bossBehavior.h"
#include "resourceManager.h"
#include "game.h"

Boss::Boss(Game& game)
    : m_game(game)
    , m_currentTarget(nullptr)
    , m_health(300)
    , m_phaseTwoActive(false)
    , m_isInvulnerable(false)
	, m_isAttacking(false)
    , m_invulnerableDuration(0.0f)
	, m_rootNode(this)
{
    loadTextures();
    m_sprites.setPosition(500, 500);

    auto* behavior = new BT::Sequence(&m_rootNode);
    if (!behavior)
        throw std::runtime_error("memory allocation error");

    // Phase 1 actions
    new BT::BossAttack1(behavior);
    new BT::BossAttack2(behavior);
    new BT::BossAttack3(behavior);
    new BT::JumpAttack(behavior);
    new BT::RunTowardsPlayer(behavior);
    new BT::Idle(behavior);

    auto* ifHealthLow = new BT::IfHealthLow(behavior);
    new BT::TransformToPhaseTwo(ifHealthLow);

    // Phase 2 actions
    auto* ifPhaseTwo = new BT::IfPhaseTwo(behavior);
    new BT::BossAttackFlame1(ifPhaseTwo);
    new BT::BossAttackFlame2(ifPhaseTwo);
    new BT::BossAttackFlame3(ifPhaseTwo);
    new BT::FlameJumpAttack(ifPhaseTwo);
    new BT::RunFlameTowardsPlayer(ifPhaseTwo);
    new BT::IdleFlame(ifPhaseTwo);

    new BT::Hurt(behavior);
    new BT::HurtFlame(behavior);
    new BT::Death(behavior);
}

void Boss::update()
{
    m_rootNode.tick();
}

void Boss::findValidTarget()
{
}

void Boss::switchToPhaseTwo()
{
    if (!m_phaseTwoActive)
    {
        m_phaseTwoActive = true;
        setState2(BossStatePhaseTwo::IdleFlame);
    }
}

//void Boss::setState(BossStatePhaseOne newState)
//{
//    if (m_currentStateName == newState)
//        return;
//
//    m_currentStateName = newState;
//    m_stateManager.setState(this, newState);
//
//    if (m_texturesP1.find(newState) != m_texturesP1.end())
//        m_sprites.setTexture(m_texturesP1[newState]);
//}
//
//void Boss::setState2(BossStatePhaseTwo newState)
//{
//    if (m_currentStateNameP2 == newState)
//        return;
//
//    m_currentStateNameP2 = newState;
//    m_stateManager.setState2(this, newState);
//
//    if (m_texturesP2.find(newState) != m_texturesP2.end())
//        m_sprites.setTexture(m_texturesP2[newState]);
//}

int Boss::getHp()
{
    return m_health;
}

void Boss::setHp(int health)
{
    m_health = health;
    if (m_health <= 0)
    {
        m_rootNode.tick();
        // death
    }
}

sf::Texture& Boss::getTexture(const BossStatePhaseOne& stateName_)
{
    auto it = m_texturesP1.find(stateName_);
    if (it != m_texturesP1.end())
        return it->second;

    static sf::Texture defaultTexture;
    return defaultTexture;
}

sf::Texture& Boss::getTexture2(const BossStatePhaseTwo& stateName_)
{
    auto it = m_texturesP2.find(stateName_);
    if (it != m_texturesP2.end())
        return it->second;

    static sf::Texture defaultTexture;
    return defaultTexture;
}

sf::Sprite& Boss::getSprite()
{
    return m_sprites;
}

void Boss::takeDamage(int damage)
{
    if (m_isInvulnerable) return;

    m_health -= damage;
    if (m_health <= 0)
    {
        setState2(BossStatePhaseTwo::Death);
    }
    else
    {
        setState(BossStatePhaseOne::Hurt);
    }

    // 2sec invu
    setInvulnerable(2.0f);
}

bool Boss::isAlive()
{
    return m_health > 0;
}

bool Boss::isShooting()
{
    return false;
}

bool Boss::isAttacking()
{
    return m_isAttacking;
}

bool Boss::isInvulnerable()
{
    return m_isInvulnerable;
}

void Boss::setInvulnerable(float duration)
{
    m_isInvulnerable = true;
    m_invulnerableClock.restart();
    m_invulnerableDuration = duration;
}

void Boss::updateInvulnerabilityEffect()
{
}

void Boss::attacking()
{
}

void Boss::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprites);
}

int Boss::getHp() const
{
    return m_health;
}

BT::Status Boss::tick()
{
    return m_rootNode.tick();
}

void Boss::loadTextures()
{
    // First phase
    m_texturesP1[BossStatePhaseOne::Idle].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\IDLE.png"));
    m_texturesP1[BossStatePhaseOne::Run].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\RUN.png"));
    m_texturesP1[BossStatePhaseOne::JumpAttack].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\JUMP ATTACK.png"));
    m_texturesP1[BossStatePhaseOne::Hurt].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\HURT.png"));
    m_texturesP1[BossStatePhaseOne::Attack1].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 1.png"));
    m_texturesP1[BossStatePhaseOne::Attack2].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 2.png"));
    m_texturesP1[BossStatePhaseOne::Attack3].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 3.png"));
    m_texturesP1[BossStatePhaseOne::Transformation].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\SHOUT.png"));

    // Second phase
    m_texturesP2[BossStatePhaseTwo::IdleFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\IDLE (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::RunFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\RUN (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::JumpAttackFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\JUMP ATTACK (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::HurtFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\HURT (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::AttackFlame1].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 1 (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::AttackFlame2].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 2 (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::AttackFlame3].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 3 (FLAMING SWORD).png"));
    m_texturesP2[BossStatePhaseTwo::Death].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\SHOUT (FLAMING SWORD).png"));

    m_sprites.setTexture(m_texturesP1[BossStatePhaseOne::Idle]);
    m_sprites.setScale(2.f, 2.f);
}