#include "bullet.h"
#include <vector>
#include <list>
#include <cmath>

float length(const sf::Vector2f direction)
{
    // найдем длину вектора перемещения от центра стрелки до позиции курсора, |delta| >= 0
    const float sumOfSquaresOfCoordinates = pow(direction.x, 2) + pow(direction.y, 2);
    float directionOfMove;
    if (sumOfSquaresOfCoordinates >= 0)
    {
        directionOfMove = sqrt(sumOfSquaresOfCoordinates);
    }
    else
    {
        directionOfMove = 0;
    }
    return directionOfMove;
}

sf::Vector2f normal(const sf::Vector2f direction)
{
    float directionLength = length(direction);
    return {(direction.x / directionLength), (direction.y / directionLength)};
}

Bullet createBullet(Tank &tank, sf::Vector2f &mousePosition)
{
    Bullet *bullet = new Bullet;
    bullet->body.setRadius(BULLET_SIZE);
    bullet->body.setOrigin(BULLET_SIZE, BULLET_SIZE);
    bullet->body.setFillColor(BULLET_FILL_COLOR);
    bullet->body.setOutlineColor(BULLET_OUTLINE_COLOR);
    bullet->body.setOutlineThickness(BULLET_OUTLINE_SIZE);
    bullet->body.setPosition(tank.body.getPosition());

    const sf::Vector2f delta = mousePosition - tank.body.getPosition();
    const sf::Vector2f normalizedVector = normal(delta);
    bullet->speed = {(BULLET_SPEED * normalizedVector.x),
                     (BULLET_SPEED * normalizedVector.y)};

    return *bullet;
}

void updateBullet(Bullet &bullet, float elapsedTime)
{
    const float positionX = bullet.body.getPosition().x + bullet.speed.x * elapsedTime;
    const float positionY = bullet.body.getPosition().y + bullet.speed.y * elapsedTime;

    if (positionX < WINDOW_WIDTH && positionX > 0 && positionY < WINDOW_HEIGHT && positionY > 0)
    {
        bullet.body.setPosition({positionX, positionY});
    }
    else
    {
        //delete bullet;
    }
}

void drawBullet(sf::RenderWindow &window, const Bullet &bullet)
{
    window.draw(bullet.body);
}

sf::FloatRect getBulletBounds(const Bullet &bullet)
{
    return bullet.body.getGlobalBounds();
}