#include "packman.h"
#include "field.h"

static const sf::Color PACKMAN_COLOR = sf::Color(255, 216, 0);
static const float PACKMAN_SPEED = 120.f; // pixels per second.
static const float PACKMAN_RADIUS = 12.5f; // pixels

static void updatePackmanDirection(Packman &packman)
{
    packman.direction = Direction::NONE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        packman.direction = Direction::UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        packman.direction = Direction::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        packman.direction = Direction::LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        packman.direction = Direction::RIGHT;
    }
}

void initializePackman(Packman &packman)
{
    packman.direction = Direction::NONE;
    packman.shape.setRadius(PACKMAN_RADIUS);
    packman.shape.setFillColor(PACKMAN_COLOR);
    packman.shape.setPosition(getPackmanStartPosition());
}

void updatePackman(Packman &packman, float elapsedTime, const Field &field)
{
    const float step = PACKMAN_SPEED * elapsedTime;

    updatePackmanDirection(packman);

    sf::Vector2f movement(0.f, 0.f);
    switch (packman.direction)
    {
    case Direction::UP:
        movement.y -= step;
        break;
    case Direction::DOWN:
        movement.y += step;
        break;
    case Direction::LEFT:
        movement.x -= step;
        break;
    case Direction::RIGHT:
        movement.x += step;
        break;
    case Direction::NONE:
        break;
    }
    const sf::FloatRect packmanBounds = packman.shape.getGlobalBounds();
    if (checkFieldWallsCollision(field, packmanBounds, movement))
    {
        // Останавливаем пакмана при столкновении
        packman.direction = Direction::NONE;
    }
    packman.shape.move(movement);
}