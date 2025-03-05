#include "boss.h"
#include "behaviorTree.h"
#include "bossBehavior.h"
#include "resourceManager.h"
#include "game.h"
#include "hero.h"

Boss::Boss(Game* game)
    : m_game(game)
    , m_currentTarget(nullptr)
    , m_health(100)
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

    auto* inAttackRange = new BT::CheckTargetInRange(behavior, 150.f);

    auto* attackSequence = new BT::Sequence(inAttackRange);
    new BT::BossAttack1(attackSequence, m_game);
    new BT::Wait(attackSequence, 2.f);
    new BT::BossAttack2(attackSequence, m_game);
    new BT::Wait(attackSequence, 2.f);
    new BT::BossAttack3(attackSequence, m_game);
    new BT::Wait(attackSequence, 5.f);

    new BT::RunTowardsTarget(behavior, true);
    new BT::Hurt(behavior);

    /*auto* ifHealthLow = new BT::IfHealthLow(behavior);
    auto* transformSequence = new BT::Sequence(ifHealthLow);
    new BT::TransformToPhaseTwo(transformSequence);

    auto* ifPhaseTwo = new BT::IfPhaseTwo(behavior);
    auto* phaseTwoSequence = new BT::Sequence(ifPhaseTwo);
    new BT::BossAttackFlame1(phaseTwoSequence, m_game);
    new BT::Wait(phaseTwoSequence, 0.5f);
    new BT::BossAttackFlame2(phaseTwoSequence, m_game);
    new BT::Wait(phaseTwoSequence, 0.5f);
    new BT::BossAttackFlame3(phaseTwoSequence, m_game);
    new BT::Wait(phaseTwoSequence, 0.1f);
    new BT::BossJumpAttackFlame(phaseTwoSequence, m_game);
    new BT::RunFlameTowardsTarget(phaseTwoSequence, true);
    new BT::IdleFlame(phaseTwoSequence);

    new BT::HurtFlame(behavior);
    new BT::Death(behavior);*/
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

    if (isInPhaseOne())
        return getHitboxPhaseOne(spriteRect);
    else
        return getHitboxPhaseTwo(spriteRect);
}

sf::FloatRect Boss::getHitboxPhaseOne(const sf::FloatRect& spriteRect) const
{
    float width, height, offsetX, y;

    switch (m_currentStateName)
    {
    case BossStatePhaseOne::Idle:
        width = spriteRect.width * 0.2f;
        height = spriteRect.height * 0.8f;
        offsetX = m_isFacingLeft ? spriteRect.width * 0.5f : spriteRect.width * 0.35f;
        y = spriteRect.top + (spriteRect.height - height) * 0.2f;
        break;

    case BossStatePhaseOne::Run:
        width = spriteRect.width * 0.3f;
        height = spriteRect.height * 0.8f;
        offsetX = m_isFacingLeft ? spriteRect.width * 0.7f : spriteRect.width * 0.02f;
        y = spriteRect.top + (spriteRect.height - height) * 0.2f;
        break;

    case BossStatePhaseOne::Attack1:
    case BossStatePhaseOne::Attack2:
    case BossStatePhaseOne::Attack3:
        width = spriteRect.width * 0.4f;
        height = spriteRect.height * 0.8f;
        offsetX = m_isFacingLeft ? spriteRect.width * 0.45f : spriteRect.width * 0.16f;
        y = spriteRect.top + (spriteRect.height - height) * 0.2f;
        break;

    case BossStatePhaseOne::BossJumpAttack:
        width = spriteRect.width * 0.55f;
        height = spriteRect.height * 0.8f;
        offsetX = spriteRect.width * 0.32f;
        y = spriteRect.top + (spriteRect.height - height) * 0.25f;
        break;

    case BossStatePhaseOne::Hurt:
        width = spriteRect.width * 0.28f;
        height = spriteRect.height * 0.8f;
        offsetX = spriteRect.width * 0.36f;
        y = spriteRect.top + (spriteRect.height - height) * 0.2f;
        break;

    case BossStatePhaseOne::Transformation:
        width = spriteRect.width * 0.4f;
        height = spriteRect.height * 0.8f;
        offsetX = spriteRect.width * 0.3f;
        y = spriteRect.top + (spriteRect.height - height) * 0.2f;
        break;
    }

    return sf::FloatRect(spriteRect.left + offsetX, y, width, height);
}

sf::FloatRect Boss::getHitboxPhaseTwo(const sf::FloatRect& spriteRect) const
{
    float width, height, offsetX, y;

    switch (m_currentStateNameP2)
    {
    case BossStatePhaseTwo::IdleFlame:
        width = spriteRect.width * 0.25f;
        height = spriteRect.height * 0.9f;
        offsetX = m_isFacingLeft ? spriteRect.width * 0.4f : spriteRect.width * 0.3f;
        y = spriteRect.top + (spriteRect.height - height) * 0.1f;
        break;

    case BossStatePhaseTwo::RunFlame:
        width = spriteRect.width * 0.35f;
        height = spriteRect.height * 0.85f;
        offsetX = m_isFacingLeft ? spriteRect.width * 0.75f : spriteRect.width * 0.05f;
        y = spriteRect.top + (spriteRect.height - height) * 0.1f;
        break;

    case BossStatePhaseTwo::AttackFlame1:
    case BossStatePhaseTwo::AttackFlame2:
    case BossStatePhaseTwo::AttackFlame3:
        width = spriteRect.width * 0.45f;
        height = spriteRect.height * 0.9f;
        offsetX = m_isFacingLeft ? spriteRect.width * 0.5f : spriteRect.width * 0.2f;
        y = spriteRect.top + (spriteRect.height - height) * 0.1f;
        break;

    case BossStatePhaseTwo::BossJumpAttackFlame:
        width = spriteRect.width * 0.55f;
        height = spriteRect.height * 1.0f;
        offsetX = spriteRect.width * 0.3f;
        y = spriteRect.top + (spriteRect.height - height) * 0.2f;
        break;

    case BossStatePhaseTwo::HurtFlame:
        width = spriteRect.width * 0.3f;
        height = spriteRect.height * 0.85f;
        offsetX = spriteRect.width * 0.4f;
        y = spriteRect.top + (spriteRect.height - height) * 0.1f;
        break;

    case BossStatePhaseTwo::Death:
        width = spriteRect.width * 0.5f;
        height = spriteRect.height * 0.85f;
        offsetX = spriteRect.width * 0.35f;
        y = spriteRect.top + (spriteRect.height - height) * 0.15f;
        break;
    }

    return sf::FloatRect(spriteRect.left + offsetX, y, width, height);
}

bool Boss::isInPhaseOne() const
{
    switch (m_currentStateName)
    {
    case BossStatePhaseOne::Idle:
    case BossStatePhaseOne::Run:
    case BossStatePhaseOne::Attack1:
    case BossStatePhaseOne::Attack2:
    case BossStatePhaseOne::Attack3:
    case BossStatePhaseOne::BossJumpAttack:
    case BossStatePhaseOne::Hurt:
    case BossStatePhaseOne::Transformation:
        return true;
    default:
        return false;
    }
}


int Boss::getAttackDamage(BossStatePhaseOne attackType) const
{
    int dmg = 0;
    switch (attackType)
    {
    case BossStatePhaseOne::Attack1:
        dmg = attack1Damage;
        break;
    case BossStatePhaseOne::Attack2:
        dmg = attack2Damage;
        break;
    case BossStatePhaseOne::Attack3:
        dmg = attack3Damage;
        break;
    case BossStatePhaseOne::BossJumpAttack:
        dmg = jumpAttackDamage;
        break;
    default:
        dmg = 0;
    }

    std::cout << "Damage delt : " << dmg << std::endl;
    return dmg;
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