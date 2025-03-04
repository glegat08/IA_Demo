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
    loadTextures();
    initializeBehaviorTree();
}

void Boss::initializeBehaviorTree()
{
    auto* behavior = new BT::Sequence(&m_rootNode);
    if (!behavior)
        throw std::runtime_error("memory allocation error");

    auto* Sequence1 = new BT::Sequence(behavior);
    new BT::Idle(Sequence1);
    new BT::Wait(Sequence1, 1.0f);
    new BT::RunTowardsTarget(Sequence1, true);
    new BT::BossAttack1(Sequence1, m_game);
    new BT::Wait(Sequence1, 0.5f);
    new BT::BossAttack2(Sequence1, m_game);
    new BT::Wait(Sequence1, 0.5f);
    new BT::BossAttack3(Sequence1, m_game);
    new BT::Wait(Sequence1, 1.0f);

    //auto* ifHealthLow = new BT::IfHealthLow(behavior);
    //auto* transformSequence = new BT::Sequence(ifHealthLow);
    //new BT::TransformToPhaseTwo(transformSequence);

    //auto* ifPhaseTwo = new BT::IfPhaseTwo(behavior);
    //auto* phaseTwoSequence = new BT::Sequence(ifPhaseTwo);
    //new BT::BossAttackFlame1(phaseTwoSequence, m_game);
    //new BT::BossAttackFlame2(phaseTwoSequence, m_game);
    //new BT::BossAttackFlame3(phaseTwoSequence, m_game);
    //new BT::BossJumpAttackFlame(phaseTwoSequence, m_game);
    //new BT::RunFlameTowardsPlayer(phaseTwoSequence);
    //new BT::IdleFlame(phaseTwoSequence);

    //new BT::Hurt(behavior);
    //new BT::HurtFlame(behavior);
    //new BT::Death(behavior);
}

void Boss::update(float deltaTime)
{
    m_rootNode.tick();

    updateAnimation();
    updateInvulnerabilityEffect();
    findValidTarget();
}

void Boss::retreatFromPlayer(float deltaTime)
{
    Hero* hero = m_currentTarget;
    sf::Vector2f bossPos = m_sprites.getPosition();
    sf::Vector2f heroPos = hero->getPlayerPosition();

    if (heroPos.x > bossPos.x)
    {
        m_sprites.move(-m_speed * deltaTime, 0.f);
        m_sprites.setScale(-2.f, 2.f);
        isFacingLeft(true);
    }
    else
    {
        m_sprites.move(m_speed * deltaTime, 0.f);
        m_sprites.setScale(2.f, 2.f);
        isFacingLeft(false);
    }
}

void Boss::performTimedAction(const std::string& action, float interval, std::function<void()> callback)
{
    if (m_actionTimers[action].getElapsedTime().asSeconds() >= interval) 
    {
        callback();
        m_actionTimers[action].restart();
    }
}

bool Boss::isCloseToTarget() const
{
    if (m_currentTarget) 
    {
        sf::Vector2f distance = m_sprites.getPosition() - m_currentTarget->getPlayerPosition();
        return distance.x < 100.f && distance.y < 100.f;
    }
    return false;
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
    if (m_currentStateName != newState)
    {
        m_currentStateName = newState;
        m_sprites.setTexture(getTexture(newState));
        m_currentFrame = 0;
        m_frameCount = phaseOneAnimations[newState].frameCount;
        m_frameDuration = phaseOneAnimations[newState].frameDuration;
        m_animationClock.restart();
    }
}

void Boss::setStatePhaseTwo(BossStatePhaseTwo newState)
{
    if (m_currentStateNameP2 != newState)
    {
        m_currentStateNameP2 = newState;
        m_sprites.setTexture(getTexture2(newState));
        m_currentFrame = 0;
        m_frameCount = phaseTwoAnimations[newState].frameCount;
        m_frameDuration = phaseTwoAnimations[newState].frameDuration;
        m_animationClock.restart();
    }
}

void Boss::updateAnimation()
{
    if (m_frameCount > 0 && m_animationClock.getElapsedTime().asSeconds() >= m_frameDuration)
    {
        m_currentFrame = (m_currentFrame + 1) % m_frameCount;
        m_animationClock.restart();
    	m_sprites.setTextureRect(sf::IntRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameHeight));
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

bool Boss::isFacingLeft(bool newBool)
{
	m_isFacingLeft = newBool;
	return m_isFacingLeft;
}

bool Boss::isFacingLeft()
{
	return m_isFacingLeft;
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

sf::FloatRect Boss::getHitbox() const
{
    sf::FloatRect spriteRect = m_sprites.getGlobalBounds();
    float width, height, offsetX, y;

    switch (m_currentStateName)
    {
    case BossStatePhaseOne::Idle:
        width = spriteRect.width * 0.2f;
        height = spriteRect.height * 0.8f;

        if (m_isFacingLeft)
			offsetX = spriteRect.width * 0.5f;
		else
			offsetX = spriteRect.width * 0.35f;

        y = spriteRect.top + (spriteRect.height - height) * 0.2f;

	    break;
    case BossStatePhaseOne::Run:
        width = spriteRect.width * 0.3;
        height = spriteRect.height * 0.8f;

        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.7f;
        else
            offsetX = spriteRect.width * 0.02f;

        y = spriteRect.top + (spriteRect.height - height) * 0.2f;

         break;
    case BossStatePhaseOne::Attack1:
    case BossStatePhaseOne::Attack2:
    case BossStatePhaseOne::Attack3:
        width = spriteRect.width * 0.4f;
        height = spriteRect.height * 0.8f;

        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.18f;
        else
            offsetX = spriteRect.width * 0.42f;

        y = spriteRect.top + (spriteRect.height - height) * 0.2f;

        break;
    case BossStatePhaseOne::BossJumpAttack:
        width = spriteRect.width * 0.55f;
        height = spriteRect.height * 0.8f;

        if (m_isFacingLeft)
            offsetX = spriteRect.width * 0.32f;
        else
            offsetX = spriteRect.width * 0.32f;

        y = spriteRect.top + (spriteRect.height - height) * 0.25f;
        break;
    case BossStatePhaseOne::Hurt:
        width = spriteRect.width * 0.28f;
        height = spriteRect.height * 0.8f;
        offsetX = spriteRect.width * 0.36f;
        break;
    case BossStatePhaseOne::Transformation:
        width = spriteRect.width * 0.4f;
        height = spriteRect.height * 0.8f;
        offsetX = spriteRect.width * 0.3f;
        break;
    }

    float x = spriteRect.left + offsetX;

    return sf::FloatRect(x, y, width, height);
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
    case BossStatePhaseOne::BossJumpAttack:
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
    case BossStatePhaseTwo::BossJumpAttackFlame:
        return jumpAttackFlameDamage;
    default:
        return 0;
    }
}

BT::Status Boss::tick()
{
    findValidTarget();

    return m_rootNode.tick();
}

void Boss::loadTextures()
{
    // First phase
    std::vector<std::pair<BossStatePhaseOne, std::string>> texturesP1 =
    {
        {BossStatePhaseOne::Idle, "IDLE.png"},
        {BossStatePhaseOne::Run, "RUN.png"},
        {BossStatePhaseOne::BossJumpAttack, "JUMP ATTACK.png"},
        {BossStatePhaseOne::Hurt, "HURT.png"},
        {BossStatePhaseOne::Attack1, "ATTACK 1.png"},
        {BossStatePhaseOne::Attack2, "ATTACK 2.png"},
        {BossStatePhaseOne::Attack3, "ATTACK 3.png"},
        {BossStatePhaseOne::Transformation, "SHOUT.png"}
    };

    for (const auto& [state, file] : texturesP1) 
    {
        std::string path = PathManager::getResourcePath("firstBoss_Sprites\\" + file);
        if (!m_texturesP1[state].loadFromFile(path))
            std::cerr << "Error : impossible to find texture " << path << std::endl;
    }

    // Second phase
    std::vector<std::pair<BossStatePhaseTwo, std::string>> texturesP2 = 
    {
        {BossStatePhaseTwo::IdleFlame, "IDLE (FLAMING SWORD).png"},
        {BossStatePhaseTwo::RunFlame, "RUN (FLAMING SWORD).png"},
        {BossStatePhaseTwo::BossJumpAttackFlame, "JUMP ATTACK (FLAMING SWORD).png"},
        {BossStatePhaseTwo::HurtFlame, "HURT (FLAMING SWORD).png"},
        {BossStatePhaseTwo::AttackFlame1, "ATTACK 1 (FLAMING SWORD).png"},
        {BossStatePhaseTwo::AttackFlame2, "ATTACK 2 (FLAMING SWORD).png"},
        {BossStatePhaseTwo::AttackFlame3, "ATTACK 3 (FLAMING SWORD).png"},
        {BossStatePhaseTwo::Death, "DEATH.png"}
    };

    for (const auto& [state, file] : texturesP2) 
    {
        std::string path = PathManager::getResourcePath("firstBoss_Sprites\\" + file);
        if (!m_texturesP2[state].loadFromFile(path)) {
            std::cerr << "Error: can't load texture " << path << std::endl;
        }
    }

    if (m_texturesP1.find(BossStatePhaseOne::Idle) != m_texturesP1.end())
    {
        m_sprites.setTexture(m_texturesP1[BossStatePhaseOne::Idle]);
        m_sprites.setScale(2.f, 2.f);
        m_sprites.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));

        m_currentFrame = 0;
        m_frameCount = phaseOneAnimations[BossStatePhaseOne::Idle].frameCount;
        m_frameDuration = phaseOneAnimations[BossStatePhaseOne::Idle].frameDuration;
        m_animationClock.restart();

        m_currentStateName = BossStatePhaseOne::Idle;
    }
    else
    {
        std::cerr << "Error : no default texture !" << std::endl;
    }
}