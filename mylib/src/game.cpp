#include "game.h"

Game::Game(sf::RenderWindow* window, const float& framerate)
	: SceneBase(window, framerate)
{
    setMapTexture(window);
    setPlayer();
}

//Game::~Game()
//{
//}

void Game::setPlayer()
{
    m_player = Hero();
}

void Game::setMapTexture(sf::RenderWindow* window)
{
    // BACKGROUND
    m_backgroundTexture.loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\dungeon\\Tiles\\Bricks1.png");
    m_backgroundShape.setTexture(&m_backgroundTexture);
    m_backgroundShape.setPosition(0, 0);
    m_backgroundShape.setSize(sf::Vector2f(m_backgroundTexture.getSize().x, m_backgroundTexture.getSize().y));
    if (window->getSize().x > m_backgroundTexture.getSize().x && window->getSize().y > m_backgroundTexture.getSize().y)
    {
        m_backgroundTexture.setRepeated(true);
        m_backgroundShape.setTextureRect(sf::IntRect(0, 0, window->getSize().x + 8000, m_backgroundTexture.getSize().y + 4000));
        m_backgroundShape.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    }

    // GROUND
    m_mapTexture.loadFromFile("C:\\Users\\guill\\source\\repos\\IAGame\\resources\\dungeon\\Tiles\\Floor1.png");
    m_rectangle_shape.setTexture(&m_mapTexture);
    float groundY = window->getSize().y - m_mapTexture.getSize().y;
    m_rectangle_shape.setPosition(0, groundY + 500);
    m_rectangle_shape.setSize(sf::Vector2f(m_mapTexture.getSize().x, m_mapTexture.getSize().y));
    if (window->getSize().x > m_mapTexture.getSize().x)
    {
        m_mapTexture.setRepeated(true);
        m_rectangle_shape.setTextureRect(sf::IntRect(0, 0, window->getSize().x - 8000, m_mapTexture.getSize().y + 200));
        m_rectangle_shape.setSize(sf::Vector2f(window->getSize().x, m_mapTexture.getSize().y));
    }

}

void Game::processInput(const sf::Event& event)
{
    m_player.handleInput();
}

void Game::update(const float& deltaTime)
{
    if (!m_isGameOver)
    {
        m_player.update(deltaTime);
    }

    float currentTime = m_fpsClock.getElapsedTime().asMilliseconds();
    if (currentTime - m_fpsStartTime > 1000)
    {
        m_fpsText.setString("FPS: " + std::to_string(m_fpsCounter));
        m_fpsStartTime = currentTime;
        m_fpsCounter = 0;
    }
    m_fpsCounter++;

    if (m_isGameOver)
        return;
}

void Game::render()
{
    if (!m_renderWindow) 
        return;

    m_renderWindow->draw(m_backgroundShape);
    m_renderWindow->draw(m_player.getSprite());
    m_renderWindow->draw(m_rectangle_shape);
}
