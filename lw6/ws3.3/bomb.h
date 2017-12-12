#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <cmath>

struct Bomb
{
  sf::ConvexShape body;
  sf::RectangleShape batteryBgFill;
  sf::RectangleShape batteryLevelFill;
  int levelOfLife;
};

void initializeBomb(Bomb &bomb);
void drawBomb(sf::RenderWindow &window, const Bomb &bomb);
/*
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
*/