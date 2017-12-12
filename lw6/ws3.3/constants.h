#pragma once
#include <SFML/Graphics.hpp>

//  General
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned ANTIALIASING_LEVEL = 8;
const sf::Color GAME_BG_COLOR = sf::Color(205, 205, 205);

// Tank
constexpr float TANK_SPEED = 100.f;
constexpr float TANK_START_SIZE = 12;
constexpr float GUN_WIDTN = TANK_START_SIZE * 2;
constexpr float GUN_HEIGHT = TANK_START_SIZE - TANK_START_SIZE / 3;

constexpr float POWER_BANK_WIDTH = 36;
constexpr float POWER_BANK_HEIGHT = 6;
constexpr int POWER_BANK_START_LIFE_LEVEL = 100;

const sf::Color GUN_FILL_COLOR = sf::Color(115, 115, 115);
const sf::Color GUN_OUTLINE_COLOR = sf::Color(53, 53, 53);
const sf::Color BODY_FILL_COLOR = sf::Color(4, 111, 231);
const sf::Color BATTERY_FILL_COLOR = sf::Color(40, 160, 40);
const sf::Color BATTERY_OUTLINE_COLOR = GUN_OUTLINE_COLOR;

constexpr int LIVE_DAMAGE_LEVEL = 50;

// Bullets
constexpr float BULLET_SPEED = 250.f;
constexpr float BULLET_SIZE = 5;
constexpr float BULLET_OUTLINE_SIZE = 3;
constexpr float RECHARGE_TIME_IN_SECOND = 0.5;

const sf::Color BULLET_FILL_COLOR = sf::Color(241, 78, 84);
const sf::Color BULLET_OUTLINE_COLOR = sf::Color(180, 58, 63);

// Bomb
constexpr float TRIANGLE_BOMB_SIZE = 20;
constexpr float SQUARE_BOMB_SIZE = 20;
constexpr float PANTAGON_BOMB_SIZE = 40;

constexpr float BOMB_POWER_BANK_WIDTH = 36;
constexpr float BOMB_POWER_BANK_HEIGHT = 6;
constexpr int BOMB_POWER_BANK_START_LIFE_LEVEL = 100;

constexpr int START_TRIANGLE_BOMB_COUNT = 10;
const sf::Color TRIANGLE_FILL_COLOR = sf::Color(252, 118, 119);
const sf::Color TRIANGLE_OUTLINE_COLOR = sf::Color(189, 88, 89);

const sf::Color SQUARE_FILL_COLOR = sf::Color(255, 232, 105);
const sf::Color SQUARE_OUTLINE_COLOR = sf::Color(191, 174, 78);

const sf::Color PENTAGON_FILL_COLOR = sf::Color(118, 141, 252);
const sf::Color PENTAGON_OUTLINE_COLOR = sf::Color(88, 105, 189);

// Game scene
static const sf::Color TRANSPARENT_GRAY = sf::Color(200, 200, 200, 200);