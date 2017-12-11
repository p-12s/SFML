#include "Tank.h"
#include "Bomb.h"
#include "Bullet.h"
#include <string>

constexpr unsigned ANTIALIASING_LEVEL = 8;
const sf::Color CONSOLE_FILL_COLOR = sf::Color(255, 255, 255);

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

void createWindow(sf::RenderWindow &window)
{
    const std::string title = "Diep.io 3 stage";

    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(videoMode, title, sf::Style::Default, settings);
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    sf::Clock tankClock;
    sf::Clock bombsClock;

    Tank tank = Tank();
    // список бомб создается бех проблем
    Bomb bomb = Bomb();
    Bullet bullet = Bullet();

    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);

        tank.update(tankClock, mousePosition);

        window.clear(CONSOLE_FILL_COLOR);

        bomb.drow(window);
        tank.drow(window);
        bullet.watch(bombsClock, window);

        window.display();
    }
}
