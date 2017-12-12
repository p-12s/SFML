#pragma once

#include "constants.h"
#include "tank.h"
#include "bomb.h"
#include "utils.h"
#include "bullet.h"
#include <map>

enum class GameState
{
    Playing,
    PlayerLosed,
    PlayerWon,
};

struct GameScene
{
    //Field field;    // TODO можно нарисовать поле вместо текстуры
    Tank tank;
    //Bomb bomb; // потом список
    std::vector<Bomb> bombs;
    //std::map<GhostId, Ghost> ghosts;
    std::vector<Bullet> bullets;
    GameState gameState;
    //unsigned totalCookieCount;

    sf::Font arial;
    sf::RectangleShape gameOverBackground;
    sf::Text gameOverLabel;
};

void initializeGameScene(GameScene &scene, const sf::Vector2f &sceneSize);
void updateGameScene(GameScene &scene, float elapsedTime, sf::Clock &rechargeClock, sf::Vector2f &mousePosition);
//std::string getGameSceneWindowTitle(const GameScene &scene);
void drawGameScene(sf::RenderWindow &window, const GameScene &scene);
void destroyGameScene(GameScene &scene);