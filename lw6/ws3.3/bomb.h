#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Bomb
{
private:
  sf::ConvexShape m_bomb;

  sf::RectangleShape m_batteryBgFill;
  sf::RectangleShape m_batteryLevelFill;
  int m_levelOfLife;

public:
  Bomb();

  void drow(sf::RenderWindow &window);
};