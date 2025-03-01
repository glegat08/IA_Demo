#include "boss.h"
#include "behaviorTree.h"
#include "bossBehavior.h"
#include "resourceManager.h"
#include "game.h"
#include "hero.h"

Boss::Boss(Game* game)
    : m_game(game)
    , m_currentTarget(nullptr)
    , m_health(300)
    , m_phaseTwoActive(false)
    , m_isInvulnerable(false)
	, m_isAttacking(false)
    , m_invulnerableDuration(0.0f)
	, m_rootNode(this)
{
    std::cout << "Boss created!" << std::endl;

    loadTextures();
    /*m_sprites.setPosition(500, 500);*/

    auto* behavior = new BT::Sequence(&m_rootNode);
    if (!behavior)
        throw std::runtime_error("memory allocation error");

    // Phase 1 actions
    new BT::BossAttack1(behavior, m_game);
    new BT::BossAttack2(behavior, m_game);
    new BT::BossAttack3(behavior, m_game);
    new BT::JumpAttack(behavior, m_game);
    new BT::RunTowardsPlayer(behavior);
    new BT::Idle(behavior);

    auto* ifHealthLow = new BT::IfHealthLow(behavior);
    new BT::TransformToPhaseTwo(ifHealthLow);

    // Phase 2 actions
    auto* ifPhaseTwo = new BT::IfPhaseTwo(behavior);
    new BT::BossAttackFlame1(ifPhaseTwo, m_game);
    new BT::BossAttackFlame2(ifPhaseTwo, m_game);
    new BT::BossAttackFlame3(ifPhaseTwo, m_game);
    new BT::FlameJumpAttack(ifPhaseTwo, m_game);
    new BT::RunFlameTowardsPlayer(ifPhaseTwo);
    new BT::IdleFlame(ifPhaseTwo);

    new BT::Hurt(behavior);
    new BT::HurtFlame(behavior);
    new BT::Death(behavior);
}

void Boss::update(float deltaTime)
{
    m_rootNode.tick();

    updateAnimation();
    updateInvulnerabilityEffect();
    findValidTarget();
    m_isAttacking = false;

    if (m_currentTarget)
    {
        Hero* hero = m_currentTarget;
        if (isAttacking() && hero->getHitbox().intersects(m_sprites.getGlobalBounds()))
        {
            int damage = getAttackDamage(m_currentStateName);
            hero->takeDamage(damage);
        }
    }
}

void Boss::findValidTarget()
{
    if (m_game)
    {
        Hero& hero = m_game->getPlayer();
        if (hero.isAlive())
            m_currentTarget = &hero;
        else
            m_currentTarget = nullptr;
    }
    else
    {
        m_currentTarget = nullptr;
    }
}


void Boss::switchToPhaseTwo()
{
    if (!m_phaseTwoActive)
    {
        m_phaseTwoActive = true;
        setStatePhaseTwo(BossStatePhaseTwo::IdleFlame);
    }
}

void Boss::setStatePhaseOne(BossStatePhaseOne newState)
{
    if (m_currentStateName == newState)
        return;

    m_currentStateName = newState;
    m_sprites.setTexture(getTexture(newState));

    m_currentFrame = 0;
    m_frameCount = phaseOneAnimations[newState].frameCount;
    m_frameDuration = phaseOneAnimations[newState].frameDuration;
    m_animationClock.restart();
}


void Boss::setStatePhaseTwo(BossStatePhaseTwo newState)
{
    if (m_currentStateNameP2 == newState)
        return;

    m_currentStateNameP2 = newState;
    m_sprites.setTexture(getTexture2(newState));

    m_currentFrame = 0;
    m_frameCount = phaseTwoAnimations[newState].frameCount;
    m_frameDuration = phaseTwoAnimations[newState].frameDuration;
    m_animationClock.restart();
}

void Boss::updateAnimation()
{
    if (m_frameCount > 0 && m_animationClock.getElapsedTime().asSeconds() >= m_frameDuration)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_animationClock.restart();

        int frameWidth = 128;
        int frameHeight = 108;
        m_sprites.setTextureRect(sf::IntRect(m_currentFrame * frameWidth, 0, frameWidth, frameHeight));
    }
}

int Boss::getHp()
{
    return m_health;
}

void Boss::setHp(int health)
{
    m_health = health;
    if (m_health <= 0)
        setStatePhaseTwo(BossStatePhaseTwo::Death);
}

Hero* Boss::getCurrentTarget() const
{
	return m_currentTarget;
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
    if (m_isInvulnerable)
        return;

    m_health -= damage;
    if (m_health <= 0)
        setStatePhaseTwo(BossStatePhaseTwo::Death);
    else
        setStatePhaseOne(BossStatePhaseOne::Hurt);

    // 2 sec invu
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
    if (m_isInvulnerable && m_invulnerableClock.getElapsedTime().asSeconds() >= m_invulnerableDuration)
        m_isInvulnerable = false;
}

void Boss::attacking()
{
    m_isAttacking = true;
}

void Boss::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprites);
}

int Boss::getHp() const
{
    return m_health;
}

int Boss::getAttackDamage(BossStatePhaseOne attackType) const
{
    switch (attackType)
	{
		case BossStatePhaseOne::Attack1:
            return attack1Damage;
		case BossStatePhaseOne::Attack2:
            return attack2Damage;
		case BossStatePhaseOne::Attack3:
            return attack3Damage;
		case BossStatePhaseOne::JumpAttack:
            return jumpAttackDamage;
		default:
            return 0;
    }
}

int Boss::getAttackDamage(BossStatePhaseTwo attackType) const
{
    switch (attackType)
	{
		case BossStatePhaseTwo::AttackFlame1:
            return attackFlame1Damage;
		case BossStatePhaseTwo::AttackFlame2:
            return attackFlame2Damage;
		case BossStatePhaseTwo::AttackFlame3:
            return attackFlame3Damage;
		case BossStatePhaseTwo::JumpAttackFlame:
            return jumpAttackFlameDamage;
		default: 
            return 0;
    }
}

BT::Status Boss::tick()
{
    return m_rootNode.tick();
}

//void Boss::loadTextures()
//{
//    // First phase
//    std::cout << "Loading textures..." << std::endl;
//    m_texturesP1[BossStatePhaseOne::Idle].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\IDLE.png"));
//    std::cout << PathManager::getResourcePath("firstBoss_Sprites\\IDLE.png") << std::endl;
//
//    m_texturesP1[BossStatePhaseOne::Run].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\RUN.png"));
//    m_texturesP1[BossStatePhaseOne::JumpAttack].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\JUMP ATTACK.png"));
//    m_texturesP1[BossStatePhaseOne::Hurt].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\HURT.png"));
//    m_texturesP1[BossStatePhaseOne::Attack1].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 1.png"));
//    m_texturesP1[BossStatePhaseOne::Attack2].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 2.png"));
//    m_texturesP1[BossStatePhaseOne::Attack3].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 3.png"));
//    m_texturesP1[BossStatePhaseOne::Transformation].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\SHOUT.png"));
//
//    for (const auto& pair : m_texturesP1) {
//        std::cout << "Texture loaded for state: " << static_cast<int>(pair.first) << std::endl;
//    }
//
//
//    // Second phase
//    m_texturesP2[BossStatePhaseTwo::IdleFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\IDLE (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::RunFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\RUN (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::JumpAttackFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\JUMP ATTACK (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::HurtFlame].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\HURT (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::AttackFlame1].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 1 (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::AttackFlame2].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 2 (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::AttackFlame3].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\ATTACK 3 (FLAMING SWORD).png"));
//    m_texturesP2[BossStatePhaseTwo::Death].loadFromFile(PathManager::getResourcePath("firstBoss_Sprites\\DEATH.png"));
//
//    m_sprites.setTexture(m_texturesP1[BossStatePhaseOne::Idle]);
//    m_sprites.setScale(2.f, 2.f);
//}

void Boss::loadTextures()
{
    // First phase
    std::vector<std::pair<BossStatePhaseOne, std::string>> texturesP1 = 
    {
        {BossStatePhaseOne::Idle, "IDLE.png"},
        {BossStatePhaseOne::Run, "RUN.png"},
        {BossStatePhaseOne::JumpAttack, "JUMP ATTACK.png"},
        {BossStatePhaseOne::Hurt, "HURT.png"},
        {BossStatePhaseOne::Attack1, "ATTACK 1.png"},
        {BossStatePhaseOne::Attack2, "ATTACK 2.png"},
        {BossStatePhaseOne::Attack3, "ATTACK 3.png"},
        {BossStatePhaseOne::Transformation, "SHOUT.png"}
    };

    for (const auto& [state, file] : texturesP1) {
        std::string path = PathManager::getResourcePath("firstBoss_Sprites\\" + file);
        if (!m_texturesP1[state].loadFromFile(path))
            std::cerr << "Error : impossible to find texture " << path << std::endl;
    }

    // Second phase
    std::vector<std::pair<BossStatePhaseTwo, std::string>> texturesP2 = {
        {BossStatePhaseTwo::IdleFlame, "IDLE (FLAMING SWORD).png"},
        {BossStatePhaseTwo::RunFlame, "RUN (FLAMING SWORD).png"},
        {BossStatePhaseTwo::JumpAttackFlame, "JUMP ATTACK (FLAMING SWORD).png"},
        {BossStatePhaseTwo::HurtFlame, "HURT (FLAMING SWORD).png"},
        {BossStatePhaseTwo::AttackFlame1, "ATTACK 1 (FLAMING SWORD).png"},
        {BossStatePhaseTwo::AttackFlame2, "ATTACK 2 (FLAMING SWORD).png"},
        {BossStatePhaseTwo::AttackFlame3, "ATTACK 3 (FLAMING SWORD).png"},
        {BossStatePhaseTwo::Death, "DEATH.png"}
    };

    for (const auto& [state, file] : texturesP2) {
        std::string path = PathManager::getResourcePath("firstBoss_Sprites\\" + file);
        if (!m_texturesP2[state].loadFromFile(path)) {
            std::cerr << "Error: can't load texture " << path << std::endl;
        }
    }

    if (m_texturesP1.find(BossStatePhaseOne::Idle) != m_texturesP1.end()) {
        m_sprites.setTexture(m_texturesP1[BossStatePhaseOne::Idle]);
        m_sprites.setScale(2.f, 2.f);
    }
    else 
    {
        std::cerr << "Error : no default texture !" << std::endl;
    }
}
