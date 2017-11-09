#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

void init(sf::Texture &texture, sf::Sprite &cat)
{
    cat.setTexture(texture);
    cat.setTextureRect(sf::IntRect(0, 0, 38, 35));
    cat.setColor(sf::Color(255, 255, 255, 200));
    cat.setPosition(0, 0);
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear({255, 255, 255});
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    static const int ANTIALIASING_LEVEL = 8;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Cat",
        sf::Style::Default,
        settings);

    sf::Texture texture;
    if (!texture.loadFromFile("ws1.3/resources/cat.png"))
        exit(EXIT_FAILURE);
    sf::Sprite cat;

    init(texture, cat);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}
