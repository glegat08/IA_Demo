#pragma once
#include <memory>
#include <vector>

#include "sceneBase.h"

class SceneManager
{
public:
	SceneManager(const int& width, const int& height, std::string title);

	sf::RenderWindow* getWindow();
	SceneBase getCurrentScene();
	void setCurrentScene(const int& index);
	void processInput();
	void exec();

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::unique_ptr<SceneBase>> m_scenes;
};
