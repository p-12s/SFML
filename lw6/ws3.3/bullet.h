#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "tank.h"

struct Bullet
{
  sf::CircleShape body;
  sf::Vector2f speed;
};

Bullet createBullet(Tank &tank, sf::Vector2f &mousePosition);
void updateBullet(Bullet &bullet, float elapsedTime);
void drawBullet(sf::RenderWindow &window, const Bullet &bullets);

// пустой вектор пуль
// по пробелу добавляем
// по достижении стены удаляем
