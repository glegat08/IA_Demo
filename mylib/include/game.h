#pragma once

#include "hero.h"
#include "sceneBase.h"

class Game : public SceneBase
{
public:
    Game(sf::RenderWindow* window, const float& framerate);
    ~Game() = default;

    // PLAYER
    void setPlayer();
    void removeProjectiles();

    // ENEMIES
    void setEnemiesCount(int count);
    void spawnEnemy(sf::RenderWindow* window);
    void removeDeadEnemies();

    // GAME MAP
    void setBackground(sf::RenderWindow* window);
    void setMapTexture(sf::RenderWindow* window);
    void setAudio();
    void processInput(const sf::Event& event) override;
    void update(const float& deltaTime) override;
    void render() override;
    void displayFPS();
    void displayScore();

private:
    int m_enemiesCount;
    Hero m_player;

    // MAP
    sf::RectangleShape m_rectangle_shape;
    sf::Texture m_mapTexture;

    // PLATFORM
    sf::RectangleShape m_platform;
    sf::Texture m_platformTexture;
    sf::Sprite m_platformSprite;

    // BACKGROUND
    sf::Texture m_backgroundTexture;
    sf::RectangleShape m_backgroundShape;
    sf::Music m_gameMusic;

    // SCORE
    sf::Font m_scoreFont;
    sf::Text m_scoreText;
    int m_score = 0;

    // FPS COUNTER
    sf::Font m_fpsFont;
    sf::Text m_fpsText;
    SceneBase* m_currentScene;
    sf::Clock m_fpsClock;
    int m_fpsCounter = 0;
    float m_fpsStartTime = 0.f;

    // GAME OVER
    void displayGameOver();
    sf::Text m_gameOverText;
    sf::Text m_winText;
    bool m_isGameOver = false;
};