#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

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