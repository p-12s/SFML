#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <cmath>

enum struct Direction
{
  NONE,
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Tank
{
  Direction direction;
  sf::RectangleShape gun;
  sf::CircleShape body;
  //sf::Vector2f position;
  sf::Vector2f speed;
  float rotation;

  sf::RectangleShape batteryBgFill;
  sf::RectangleShape batteryLevelFill;
  int levelOfLife;
};

static void updateTankDirection(Tank &tank);
static void updateTankRotation(Tank &tank, sf::Vector2f &mousePosition);
void initializeTank(Tank &tank);
void updateTank(Tank &tank, float elapsedTime, sf::Vector2f &mousePosition);
void drawTank(sf::RenderWindow &window, const Tank &tank);

/*
class Tank
{
private:
  enum class State
  {
    Stand,
    Move,
  };

  State m_state = State::Stand;

  sf::RectangleShape m_gun;
  sf::CircleShape m_body;
  sf::Vector2f m_position;
  sf::Vector2f m_speed;
  float m_rotation;

  sf::RectangleShape m_batteryBgFill;
  sf::RectangleShape m_batteryLevelFill;
  int m_levelOfLife;

public:
  Tank();

  void update(sf::Clock &clock, sf::Vector2f &mousePosition);

  void updateMove(float dt);

  void switchState(State state);

  void updateElements();

  void drow(sf::RenderWindow &window);

  sf::Vector2f getPosition();

  float getRotation();
};
*/