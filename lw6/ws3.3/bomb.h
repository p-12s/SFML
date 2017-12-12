#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "generator.h"
#include <cmath>

struct Bomb
{
  sf::ConvexShape body;
  sf::RectangleShape batteryBgFill;
  sf::RectangleShape batteryLevelFill;
  int levelOfLife;
};

void initializeBombs(std::vector<Bomb> &bombs);
void drawBomb(sf::RenderWindow &window, const Bomb &bomb);
sf::FloatRect getBombBounds(const Bomb &bomb);
void injureBomb(Bomb &bomb);