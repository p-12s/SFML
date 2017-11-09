#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr int pointCount = 200;
    const int halfRadius = 200;
    const sf::Vector2f ellipseRadius = {200.f, 80.f};

    sf::Clock clock;
    sf::Vector2f speed = {100.f, 100.f};

    // Создаем окно с параметрами сглаживания
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Polar Rose",
        sf::Style::Default, settings);

    // Объявляем фигуру, которая будет выглядеть как эллипс
    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 200});
    ellipse.setFillColor(sf::Color(41, 112, 255));

    ellipse.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = halfRadius * sin(6 * angle);

        sf::Vector2f point = {
            radius * std::sin(angle),
            radius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

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

        sf::Vector2f position = ellipse.getPosition();
        position += speed * dt;

        if ((position.x + halfRadius >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x - halfRadius < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + halfRadius >= WINDOW_HEIGHT) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y - halfRadius < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }

        ellipse.setPosition(position);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}