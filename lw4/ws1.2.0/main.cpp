#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

// Инициализируем фигуру-указатель
void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(7);
    pointer.setPoint(0, {52, 0});
    pointer.setPoint(1, {0, -52});
    pointer.setPoint(2, {0, -26});
    pointer.setPoint(3, {-52, -26});
    pointer.setPoint(4, {-52, 26});
    pointer.setPoint(5, {0, 26});
    pointer.setPoint(6, {0, 52});

    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(255, 255, 0));
    pointer.setOutlineColor(sf::Color(0, 0, 0));
    pointer.setOutlineThickness(2);
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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
        default:
            break;
        }
    }
}

float getDirectionOfMove()
{
    // найдем длину вектора перемещения от центра стрелки до позиции курсора
    // |delta| >= 0
    // при достижении стрелкой позиции курсора, считаем оставшееся расстояние = 0
    return 0;
}

float getRotationAngleInDegrees()
{
    // найдем угол поворота,на который нужно повренуть фигуру
    // для направления на позицию мышки
    return 0;
}

void setRotation()
{
    static const float maxSpeedOfRotation = 90;
    // повернем фигуру на требуемый угол с учетом ограничения
}

void setMove()
{
    // найдем направление движения, с помощью нормализации вектора
    // и утсановим новые координаты координаты
}

float getMinDistance()
{
    return 0;
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float dt)
{
    // найдем:
    // 1. расстояние от фигуры до курсора
    // 2. перемещение фигуры за время dt
    // 3. выберем из этих двух значений минимальное и если оно > 0
    // 4. обновим координаты и угол поворота фигуры
    getMinDistance();
    getRotationAngleInDegrees();
    setRotation();
    setMove();
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear({255, 255, 255});
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr int ANTIALIASING_LEVEL = 8;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse",
        sf::Style::Default,
        settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    sf::Clock clock;

    init(pointer);
    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, dt);
        redrawFrame(window, pointer);
    }
}
