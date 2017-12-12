#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "generator.h"

// Получаем цвет от (0, 0, 0) до (255, 255, 255)
sf::Color getColor(PRNG &generator);
