#include "game.h"
#include "boss.h"
#include "resourceManager.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
    : SceneBase(window, framerate),
    m_boss(std::make_unique<Boss>(this))
{
    setBackground(window);
    setGroundTexture(window);
    setPlayer();
    setBoss();
}

void Game::setPlayer()
{
    m_player.getSprite().setPosition(100, 500);

    m_player.setState(HeroStateNames::stateName::jump);

    m_player.setOnGround(false);
}

void Game::setBoss()
{
    m_boss->getSprite().setPosition(600, getGroundHitbox().top);
}

Hero& Game::getPlayer()
{
    return m_player;
}

Boss* Game::getBoss() const
{
    return m_boss.get();
}

void Game::checkCollision()
{
    if (m_player.getHitbox().top + m_player.getHitbox().height > getGroundHitbox().top)
    {
        m_player.getSprite().setPosition(m_player.getPlayerPosition().x, getGroundHitbox().top - m_player.getHitbox().height);
        m_player.setOnGround(true);
    }
    else
        m_player.setOnGround(false);

    if (m_boss->getHitbox().top + m_boss->getHitbox().height > getGroundHitbox().top)
        m_boss->getSprite().setPosition(m_boss->getSprite().getPosition().x, getGroundHitbox().top - m_boss->getHitbox().height);

    sf::FloatRect windowBounds = GetWindowCollision();
    sf::FloatRect playerHitbox = m_player.getHitbox();
    sf::FloatRect bossHitbox = m_boss->getHitbox();

    if (playerHitbox.left < windowBounds.left)
    {
        m_player.getSprite().setPosition
        (
            windowBounds.left + (m_player.getPlayerPosition().x - playerHitbox.left),
            m_player.getPlayerPosition().y
        );
    }

    if (playerHitbox.left + playerHitbox.width > windowBounds.left + windowBounds.width)
    {
        m_player.getSprite().setPosition
        (
            m_player.getPlayerPosition().x - ((playerHitbox.left + playerHitbox.width) - (windowBounds.left + windowBounds.width)),
            m_player.getPlayerPosition().y
        );
    }

    if (bossHitbox.left < windowBounds.left)
    {
        m_boss->getSprite().setPosition
        (
            windowBounds.left + (m_boss->getSprite().getPosition().x - bossHitbox.left),
            m_boss->getSprite().getPosition().y
        );
    }

    if (bossHitbox.left + bossHitbox.width > windowBounds.left + windowBounds.width)
    {
        m_boss->getSprite().setPosition
        (
            m_boss->getSprite().getPosition().x - ((bossHitbox.left + bossHitbox.width) - (windowBounds.left + windowBounds.width)),
            m_boss->getSprite().getPosition().y
        );
    }
}

void Game::setBackground(sf::RenderWindow* window)
{
    m_backgroundTexture.loadFromFile(PathManager::getResourcePath("dungeon\\Tiles\\Bricks1.png"));
    m_backgroundShape.setTexture(&m_backgroundTexture);
    m_backgroundShape.setPosition(0, 0);
    m_backgroundShape.setSize(sf::Vector2f(m_backgroundTexture.getSize().x, m_backgroundTexture.getSize().y));
    if (window->getSize().x > m_backgroundTexture.getSize().x && window->getSize().y > m_backgroundTexture.getSize().y)
    {
        m_backgroundTexture.setRepeated(true);
        m_backgroundShape.setTextureRect(sf::IntRect(0, 0, window->getSize().x + 8000, m_backgroundTexture.getSize().y + 4000));
        m_backgroundShape.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    }
}

void Game::setGroundTexture(sf::RenderWindow* window)
{
    m_mapTexture.loadFromFile(PathManager::getResourcePath("dungeon\\Tiles\\Floor1.png"));
    m_rectangle_shape.setTexture(&m_mapTexture);

    float groundY = window->getSize().y - 60;
    m_rectangle_shape.setPosition(0, groundY);
    m_rectangle_shape.setSize(sf::Vector2f(m_mapTexture.getSize().x, m_mapTexture.getSize().y));

    if (window->getSize().x > m_mapTexture.getSize().x)
    {
        m_mapTexture.setRepeated(true);
        m_rectangle_shape.setTextureRect(sf::IntRect(0, 0, window->getSize().x + 3000, m_mapTexture.getSize().y + 100));
        m_rectangle_shape.setSize(sf::Vector2f(window->getSize().x, m_mapTexture.getSize().y));
    }
}

sf::FloatRect Game::GetWindowCollision()
{
    return sf::FloatRect(0, 0, m_renderWindow->getSize().x, m_renderWindow->getSize().y);
}

sf::FloatRect Game::getGroundHitbox()
{
    return m_rectangle_shape.getGlobalBounds();
}

sf::FloatRect Game::getPlatformHitbox()
{
    return m_platform.getGlobalBounds();
}

void Game::processInput(const sf::Event& event)
{
    m_player.handleInput();
}

void Game::update(const float& deltaTime)
{
    if (!m_player.isAlive())
        m_isGameOver = true;

    m_player.update(deltaTime);
    m_boss->update(deltaTime);
    checkCollision();

    if (m_isGameOver)
        return;
}

void Game::render()
{
    if (!m_renderWindow)
        return;

    if (m_isGameOver == true)
		displayGameOver();

    m_renderWindow->draw(m_backgroundShape);
    m_renderWindow->draw(m_rectangle_shape);
    m_renderWindow->draw(m_player.getSprite());
    m_renderWindow->draw(m_boss->getSprite());

    drawHitboxes();
}

void Game::drawHitboxes()
{
    sf::FloatRect groundRect = getGroundHitbox();
    sf::RectangleShape groundHitboxShape;
    groundHitboxShape.setPosition(groundRect.left, groundRect.top);
    groundHitboxShape.setSize(sf::Vector2f(groundRect.width, groundRect.height));
    groundHitboxShape.setFillColor(sf::Color::Transparent);
    groundHitboxShape.setOutlineColor(sf::Color::Red);
    groundHitboxShape.setOutlineThickness(2.f);

    sf::FloatRect playerRect = m_player.getHitbox();
    sf::RectangleShape playerHitboxShape;
    playerHitboxShape.setPosition(playerRect.left, playerRect.top);
    playerHitboxShape.setSize(sf::Vector2f(playerRect.width, playerRect.height));
    playerHitboxShape.setFillColor(sf::Color::Transparent);
    playerHitboxShape.setOutlineColor(sf::Color::Green);
    playerHitboxShape.setOutlineThickness(2.f);

	sf::FloatRect bossRect = m_boss->getHitbox();
	sf::RectangleShape bossHitboxShape;
	bossHitboxShape.setPosition(bossRect.left, bossRect.top);
	bossHitboxShape.setSize(sf::Vector2f(bossRect.width, bossRect.height));
	bossHitboxShape.setFillColor(sf::Color::Transparent);
	bossHitboxShape.setOutlineColor(sf::Color::Blue);
	bossHitboxShape.setOutlineThickness(2.f);

    m_renderWindow->draw(groundHitboxShape);
    m_renderWindow->draw(playerHitboxShape);
	m_renderWindow->draw(bossHitboxShape);
}

void Game::displayGameOver()
{
    sf::RectangleShape overlay(sf::Vector2f(m_renderWindow->getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 128));

    m_gameOverText.setFont(m_scoreFont);
    m_gameOverText.setString("GAME OVER");
    m_gameOverText.setCharacterSize(72);
    m_gameOverText.setFillColor(sf::Color::Red);

    sf::FloatRect textBounds = m_gameOverText.getLocalBounds();
    m_gameOverText.setPosition(
        (m_renderWindow->getSize().x - textBounds.width) / 2,
        (m_renderWindow->getSize().y - textBounds.height) / 2
    );

    m_renderWindow->draw(overlay);
    m_renderWindow->draw(m_gameOverText);
}
