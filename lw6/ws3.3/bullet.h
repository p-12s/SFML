#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
  private:
    sf::CircleShape m_body;
    sf::Vector2f m_speed;

  public:
    Bullet();

    void update(sf::Clock &clock);

    void updateMove(float dt);

    void watch(sf::Clock &clock, sf::RenderWindow &window);

};