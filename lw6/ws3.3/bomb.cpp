#include "Bomb.h"
#include <cassert>

void initializeBomb(Bomb &bomb)
{
    bomb.body.setFillColor(TRIANGLE_FILL_COLOR);
    bomb.body.setOutlineColor(TRIANGLE_OUTLINE_COLOR);
    bomb.body.setOutlineThickness(3);

    bomb.body.setPosition({200, 120}); //TODO рандомом получать
    bomb.body.setPointCount(3);
    bomb.body.setPoint(0, {5, -10});
    bomb.body.setPoint(1, {5, 10});
    bomb.body.setPoint(2, {-15, 0});

    // здоровье
    bomb.levelOfLife = BOMB_POWER_BANK_START_LIFE_LEVEL;

    // фон батареи здоровья
    bomb.batteryBgFill.setSize({BOMB_POWER_BANK_WIDTH, BOMB_POWER_BANK_HEIGHT});
    bomb.batteryBgFill.setOrigin({0, (BOMB_POWER_BANK_HEIGHT / 2)});
    bomb.batteryBgFill.setFillColor(BATTERY_OUTLINE_COLOR);

    // закрашенный уровень батареи здоровья
    float batteryLevelFillHeight = BOMB_POWER_BANK_HEIGHT - 2;
    float batteryLevelFillWidth = (BOMB_POWER_BANK_WIDTH - 2) * bomb.levelOfLife / BOMB_POWER_BANK_START_LIFE_LEVEL;
    bomb.batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
    bomb.batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
    bomb.batteryLevelFill.setFillColor(BATTERY_FILL_COLOR);

    // положение уровная жизни
    bomb.batteryBgFill.setPosition({(bomb.body.getPosition().x - BOMB_POWER_BANK_WIDTH / 2), (bomb.body.getPosition().y + 30)});
    bomb.batteryLevelFill.setPosition({bomb.batteryBgFill.getPosition().x, (bomb.batteryBgFill.getPosition().y)});
}

void drawBomb(sf::RenderWindow &window, const Bomb &bomb)
{
    window.draw(bomb.body);
    window.draw(bomb.batteryBgFill);
    window.draw(bomb.batteryLevelFill);
}

/*
Bomb::Bomb()
{
    m_bomb.setFillColor(TRIANGLE_FILL_COLOR);
    m_bomb.setOutlineColor(TRIANGLE_OUTLINE_COLOR);
    m_bomb.setOutlineThickness(3);

    m_bomb.setPosition({200, 120}); //TODO рандомом получать
    m_bomb.setPointCount(3);
    m_bomb.setPoint(0, {5, -10});
    m_bomb.setPoint(1, {5, 10});
    m_bomb.setPoint(2, {-15, 0});

    // здоровье
    m_levelOfLife = BOMB_POWER_BANK_START_LIFE_LEVEL;

    // фон батареи здоровья
    m_batteryBgFill.setSize({BOMB_POWER_BANK_WIDTH, BOMB_POWER_BANK_HEIGHT});
    m_batteryBgFill.setOrigin({0, (BOMB_POWER_BANK_HEIGHT / 2)});
    m_batteryBgFill.setFillColor(sf::Color(53, 53, 53));

    // закрашенный уровень батареи здоровья
    float batteryLevelFillHeight = BOMB_POWER_BANK_HEIGHT - 2;
    float batteryLevelFillWidth = (BOMB_POWER_BANK_WIDTH - 2) * m_levelOfLife / BOMB_POWER_BANK_START_LIFE_LEVEL;
    m_batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
    m_batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
    m_batteryLevelFill.setFillColor(sf::Color(40, 160, 40));

    // положение уровная жизни
    m_batteryBgFill.setPosition({(m_bomb.getPosition().x - BOMB_POWER_BANK_WIDTH / 2), (m_bomb.getPosition().y + 30)});
    m_batteryLevelFill.setPosition({m_batteryBgFill.getPosition().x, (m_batteryBgFill.getPosition().y)});
}

void Bomb::drow(sf::RenderWindow &window)
{
    window.draw(m_bomb);
    window.draw(m_batteryBgFill);
    window.draw(m_batteryLevelFill);
}
*/