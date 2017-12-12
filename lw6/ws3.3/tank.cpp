#include "Tank.h"

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * cos(angle)),
        float(radius * sin(angle))};
}

// Переводит радианы в градиусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

static void updateTankDirection(Tank &tank)
{
    tank.direction = Direction::NONE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        tank.direction = Direction::UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        tank.direction = Direction::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        tank.direction = Direction::LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        tank.direction = Direction::RIGHT;
    }
}

static void updateTankRotation(Tank &tank, sf::Vector2f &mousePosition)
{
    const sf::Vector2f delta = mousePosition - tank.body.getPosition();
    tank.rotation = atan2(delta.y, delta.x);

    int gunOffsetFromCenter = tank.body.getRadius();
    const sf::Vector2f gunOffset = toEuclidean(gunOffsetFromCenter, tank.rotation);
    tank.gun.setPosition(tank.body.getPosition() + gunOffset);
    tank.gun.setRotation(toDegrees(tank.rotation));
    tank.batteryBgFill.setPosition({(tank.body.getPosition().x - POWER_BANK_WIDTH / 2), (tank.body.getPosition().y + 30)});
    tank.batteryLevelFill.setPosition({tank.batteryBgFill.getPosition().x, (tank.batteryBgFill.getPosition().y)});
}

void initializeTank(Tank &tank)
{
    // пушка
    tank.gun.setSize({GUN_WIDTN, GUN_HEIGHT});
    tank.gun.setOrigin({(GUN_WIDTN / 2), (GUN_HEIGHT / 2)});
    tank.gun.setFillColor(GUN_FILL_COLOR);
    tank.gun.setOutlineColor(GUN_OUTLINE_COLOR);
    tank.gun.setOutlineThickness(2);
    // корпус
    tank.body.setRadius(TANK_START_SIZE);
    tank.body.setOrigin({TANK_START_SIZE, TANK_START_SIZE});
    tank.body.setFillColor(BODY_FILL_COLOR);
    tank.body.setOutlineColor(GUN_OUTLINE_COLOR);
    tank.body.setOutlineThickness(2);
    // позиция, скорость, поворот
    //tank.position = {400, 300};
    tank.body.setPosition({400, 300});
    tank.rotation = 0;
    tank.direction = Direction::NONE;
    // здоровье
    tank.levelOfLife = POWER_BANK_START_LIFE_LEVEL;

    // фон батареи здоровья
    tank.batteryBgFill.setSize({POWER_BANK_WIDTH, POWER_BANK_HEIGHT});
    tank.batteryBgFill.setOrigin({0, (POWER_BANK_HEIGHT / 2)});
    tank.batteryBgFill.setFillColor(GUN_OUTLINE_COLOR);

    // закрашенный уровень батареи здоровья
    float batteryLevelFillHeight = POWER_BANK_HEIGHT - 2;
    float batteryLevelFillWidth = (POWER_BANK_WIDTH - 2) * tank.levelOfLife / POWER_BANK_START_LIFE_LEVEL;
    tank.batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
    tank.batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
    tank.batteryLevelFill.setFillColor(BATTERY_FILL_COLOR);
}

void updateTank(Tank &tank, float elapsedTime, sf::Vector2f &mousePosition)
{
    const float step = TANK_SPEED * elapsedTime;

    updateTankDirection(tank);
    updateTankRotation(tank, mousePosition);

    sf::Vector2f movement(0.f, 0.f);
    switch (tank.direction)
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
    /*
    if (checkFieldWallsCollision(field, packman.shape.getGlobalBounds(), movement))
    {
        // Останавливаем пакмана при столкновении
        packman.direction = Direction::NONE;
    }
    */
    tank.gun.move(movement);
    tank.body.move(movement);
    tank.batteryBgFill.move(movement);
    tank.batteryLevelFill.move(movement);
}

void drawTank(sf::RenderWindow &window, const Tank &tank)
{
    window.draw(tank.gun);
    window.draw(tank.body);
    window.draw(tank.batteryBgFill);
    window.draw(tank.batteryLevelFill);
}