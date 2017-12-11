#include "Bomb.h"
#include <cassert>

constexpr float TRIANGLE_BOMB_SIZE = 20;
constexpr float SQUARE_BOMB_SIZE = 20;
constexpr float PANTAGON_BOMB_SIZE = 40;

constexpr float BOMB_POWER_BANK_WIDTH = 36;
constexpr float BOMB_POWER_BANK_HEIGHT = 6;
constexpr int BOMB_POWER_BANK_START_LIFE_LEVEL = 100;

const sf::Color TRIANGLE_FILL_COLOR = sf::Color(252, 118, 119);
const sf::Color TRIANGLE_OUTLINE_COLOR = sf::Color(189, 88, 89);
// TODO добавить цвета других

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