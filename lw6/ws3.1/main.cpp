#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

//TODO удалить комментарии
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned ANTIALIASING_LEVEL = 8;

/*
2 этап:

- реализовать перемещение танка с помошью клавиш, не далее чем рамки экрана
    - посмотреть реализацию с клавишами в воркшопе последнем
    - научить танк двигаться



- реализовать ограничение для перемещения такна в виде рамок окна
- научить танк стрелять (создание оъектов с размерами и начальной скоростью)
- установить ограничение по выпуску снарядов за единицу времени

- создать 5-6 мин. Каждая из них имеет:
 - вид (треугольник, квадрат, 6-ти угольник)
  - размер
  - цвет
  - уровень "здоровья", который будет кратен урону от снаряда моего танка (или бота)
  - рандомное расположение, не занятое положением моего танка

Что можно еще добавить минам:
 - скорость и направление движения
 - авто-наведение на танк (однако танк может получить бонус - холодильник, и мины перестанут "наводиться")
 
 Что можно еще добавить танку:
 - движение по диагонали
*/

// будет сущность танка, то что на экране
struct Tank
{
    sf::RectangleShape gun;
    sf::CircleShape body;
    sf::Vector2f position;
    sf::Vector2f speed;
    float rotation;
};

// и сущность учета здоровья и бонусов
struct PowerBank
{
    // TODO можно устанавливать его размер в зависимости от уровня (рост)
    sf::RectangleShape batteryBackground;
    sf::RectangleShape batteryLevelFill;
    int life;
};

sf::Vector2f toEuclidean(float radius, float angle);
void updateTankElements(Tank &tank);
void initTank(Tank &tank);
float toDegrees(float radians);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);

void update(const sf::Vector2f &mousePosition, Tank &tank);

void redrawFrame(sf::RenderWindow &window, Tank &tank);

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * cos(angle)),
        float(radius * sin(angle))};
}

// Обновляет позиции и повороты частей стрелки согласно текущему состоянию стрелки
void updateTankElements(Tank &tank)
{
    int gunOffsetFromCenter = tank.body.getRadius();
    const sf::Vector2f gunOffset = toEuclidean(gunOffsetFromCenter, tank.rotation);
    tank.gun.setPosition(tank.position + gunOffset);
    tank.gun.setRotation(toDegrees(tank.rotation));

    int bodyOffsetFromCenter = 0;
    const sf::Vector2f bodyOffset = toEuclidean(bodyOffsetFromCenter, tank.rotation);
    tank.body.setPosition(tank.position);
    tank.body.setRotation(toDegrees(tank.rotation));
}

// Инициализирует Tank
void initTank(Tank &tank)
{
    constexpr float TANK_SIZE = 12;
    constexpr float GUN_WIDTN = TANK_SIZE * 2;
    constexpr float GUN_HEIGHT = TANK_SIZE - TANK_SIZE / 3;

    // пушка
    tank.gun.setSize({GUN_WIDTN, GUN_HEIGHT});
    tank.gun.setOrigin({(GUN_WIDTN / 2), (GUN_HEIGHT / 2)});
    tank.gun.setFillColor(sf::Color(115, 115, 115));
    tank.gun.setOutlineColor(sf::Color(53, 53, 53));
    tank.gun.setOutlineThickness(2);

    // корпус
    tank.body.setRadius(TANK_SIZE);
    tank.body.setPosition({200, 120});
    tank.body.setOrigin({TANK_SIZE, TANK_SIZE});
    tank.body.setFillColor(sf::Color(4, 111, 231));
    tank.body.setOutlineColor(sf::Color(53, 53, 53));
    tank.body.setOutlineThickness(2);

    // позиция, скорость, поворот
    tank.position = {400, 300};
    tank.speed = {100.f, 100.f};
    tank.rotation = 0;

    //updateTankElements(tank);
}

// Инициализирует PowerBank
void initPowerBank(PowerBank &powerBank, Tank &tank)
{
    float POWER_BANK_WIDTH = tank.body.getRadius() * 3;
    float POWER_BANK_HEIGHT = 6;
    int POWER_BANK_START_LIFE_LEVEL = 100;

    // здоровье
    powerBank.life = POWER_BANK_START_LIFE_LEVEL;

    // фон батареи здоровья
    powerBank.batteryBackground.setSize({POWER_BANK_WIDTH, POWER_BANK_HEIGHT});
    powerBank.batteryBackground.setOrigin({0, (POWER_BANK_HEIGHT / 2)});
    powerBank.batteryBackground.setFillColor(sf::Color(53, 53, 53));
    powerBank.batteryBackground.setPosition({(tank.position.x - POWER_BANK_WIDTH / 2),
                                             (tank.position.y + 30)});

    // закрашенный уровень батареи здоровья
    float batteryLevelFillHeight = POWER_BANK_HEIGHT - 2;
    float batteryLevelFillWidth = (POWER_BANK_WIDTH - 2) * powerBank.life / POWER_BANK_START_LIFE_LEVEL;
    powerBank.batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
    powerBank.batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
    powerBank.batteryLevelFill.setFillColor(sf::Color(40, 160, 40));

    powerBank.batteryLevelFill.setPosition({powerBank.batteryBackground.getPosition().x,
                                            (powerBank.batteryBackground.getPosition().y)});

    //updateTankElements(tank);
}

// Переводит радианы в градиусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    // std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, Tank &tank, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                std::cout << "Move to Left" << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                std::cout << "Move to Right" << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                std::cout << "Move to Up" << std::endl;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                std::cout << "Move to Down" << std::endl;
            }
            // передвинься сюда
            break;

        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, Tank &tank)
{
    std::cout << "inner update mouse x=" << mousePosition.x << ", y=" << mousePosition.y << std::endl;

    const sf::Vector2f delta = mousePosition - tank.position;
    tank.rotation = atan2(delta.y, delta.x);
    updateTankElements(tank);

    //float dt = clock.restart().asSeconds();
    //puppeteer.update(dt);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Tank &tank, PowerBank &powerBank)
{
    window.clear({255, 255, 255});
    window.draw(tank.gun);
    window.draw(tank.body);
    window.draw(powerBank.batteryBackground);
    window.draw(powerBank.batteryLevelFill);
    window.display();
}

void createWindow(sf::RenderWindow &window)
{
    const std::string title = "Diep.io 2 stage";

    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(videoMode, title, sf::Style::Default, settings);
}

int main()
{

    sf::RenderWindow window;
    createWindow(window);

    // время понадобится позже, для плавного поворота и ?перемещения
    sf::Clock clock;

    /* понадрбится при столкновении со стенками
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();

        sf::Vector2f position = shape.getPosition();
        // position += speed * dt;

        // при перемещении проверять, не граница и окна. но это потом, я же собираюсь расширить видимую область
        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }

        shape.setPosition(position);

        // Рисование текущего состояния
        window.clear({255, 255, 255});
        window.draw(shape);
        window.display();
    }
    */

    Tank tank;
    PowerBank powerBank;
    sf::Vector2f mousePosition;

    initTank(tank);
    initPowerBank(powerBank, tank);

    while (window.isOpen())
    {
        pollEvents(window, tank, mousePosition);
        std::cout << "after pollEvents mouse x=" << mousePosition.x << ", y=" << mousePosition.y << std::endl;
        update(mousePosition, tank);
        redrawFrame(window, tank, powerBank);
    }
}
