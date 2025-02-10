#include "engine.h"

int main()
{
    SceneManager sceneManager(1920, 1080, "Tahiti Rising");
    Engine game(sceneManager);

    game.exec();

    return 0;
}