#include "Bomb.h"
#include <cassert>

void initializeBombs(std::vector<Bomb> &bombs)
{
    PRNG generator;
    initGenerator(generator);

    for (auto i = 0; i < START_TRIANGLE_BOMB_COUNT; i++)
    {
        Bomb *bomb = new Bomb;
        bomb->body.setFillColor(TRIANGLE_FILL_COLOR);
        bomb->body.setOutlineColor(TRIANGLE_OUTLINE_COLOR);
        bomb->body.setOutlineThickness(3);

        //bomb->body.setPosition({float(200 + i * 10), float(120 + i * 10)}); // 0-800, 0-600
        bomb->body.setPosition({randomFloat(generator, 0, WINDOW_WIDTH),
                                randomFloat(generator, 0, WINDOW_HEIGHT)});
        bomb->body.setPointCount(3);
        bomb->body.setPoint(0, {5, -10});
        bomb->body.setPoint(1, {5, 10});
        bomb->body.setPoint(2, {-15, 0});

        // здоровье
        bomb->levelOfLife = BOMB_POWER_BANK_START_LIFE_LEVEL;

        // фон батареи здоровья
        bomb->batteryBgFill.setSize({BOMB_POWER_BANK_WIDTH, BOMB_POWER_BANK_HEIGHT});
        bomb->batteryBgFill.setOrigin({0, (BOMB_POWER_BANK_HEIGHT / 2)});
        bomb->batteryBgFill.setFillColor(BATTERY_OUTLINE_COLOR);

        // закрашенный уровень батареи здоровья
        float batteryLevelFillHeight = BOMB_POWER_BANK_HEIGHT - 2;
        float batteryLevelFillWidth = (BOMB_POWER_BANK_WIDTH - 2) * bomb->levelOfLife / BOMB_POWER_BANK_START_LIFE_LEVEL;
        bomb->batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
        bomb->batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
        bomb->batteryLevelFill.setFillColor(BATTERY_FILL_COLOR);

        // положение уровная жизни
        bomb->batteryBgFill.setPosition({(bomb->body.getPosition().x - BOMB_POWER_BANK_WIDTH / 2), (bomb->body.getPosition().y + 30)});
        bomb->batteryLevelFill.setPosition({bomb->batteryBgFill.getPosition().x, (bomb->batteryBgFill.getPosition().y)});

        bombs.push_back(*bomb);
    }
}

void drawBomb(sf::RenderWindow &window, const Bomb &bomb)
{
    window.draw(bomb.body);
    window.draw(bomb.batteryBgFill);
    window.draw(bomb.batteryLevelFill);
}

sf::FloatRect getBombBounds(const Bomb &bomb)
{
    return bomb.body.getGlobalBounds();
}

void recountLevelOfHealth(Bomb &bomb)
{
    // закрашенный уровень батареи здоровья
    float batteryLevelFillHeight = BOMB_POWER_BANK_HEIGHT - 2;
    float batteryLevelFillWidth = (BOMB_POWER_BANK_WIDTH - 2) * bomb.levelOfLife / BOMB_POWER_BANK_START_LIFE_LEVEL;
    bomb.batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
    bomb.batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
    bomb.batteryLevelFill.setFillColor(BATTERY_FILL_COLOR);
}

void injureBomb(Bomb &bomb)
{
    bomb.levelOfLife -= LIVE_DAMAGE_LEVEL;
    std::cout << "[bomb.cpp] bomb.levelOfLife: " << bomb.levelOfLife << std::endl;
    if (bomb.levelOfLife >= 0)
    {
        recountLevelOfHealth(bomb);
    }
}