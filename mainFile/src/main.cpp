#include "engine.h"

int main()
{
    SceneManager sceneManager(1920, 1080, "IA Demo");
    Engine game(sceneManager);

    game.exec();

    return 0;
}