#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void initializePackman(sf::CircleShape &shape)
{
    shape.setRadius(20);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100, 0);
}

void handleEvents(sf::RenderWindow & window, Packman &packman)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Кнопка закрытия окна
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        // Клавиши управления пакманом
        else if (event.type == sf::Event::KeyPressed)
        {
            handlePackmanKeyPress(event.key, packman);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            handlePackmanKeyRelease(event.key, packman);
        }
    }
}

void update(sf::Clock &clock, Packman &packman)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    updatePackman(packman, elapsedTime);
}

int main(int, char *[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window Title");
    Packman packman;
    initializePackman(packman);

    sf::Clock clock;

    while (window.isOpen())
    {
        handleEvents(window, packman);
        update(packman, clock);
        render(window, packman);
    }

    return 0;
}