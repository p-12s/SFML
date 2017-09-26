#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({125, 304}), "Traffic lights");

    window.clear();

    sf::RectangleShape trafficBackground;
    trafficBackground.setSize({85, 264});
    trafficBackground.setPosition({20, 20});
    trafficBackground.setFillColor(sf::Color(67, 67, 67));
    window.draw(trafficBackground);

    sf::CircleShape greenCircle(36);
    greenCircle.setPosition({26, 32});
    greenCircle.setFillColor(sf::Color(0, 141, 15));
    window.draw(greenCircle);

    sf::CircleShape yellowCircle(36);
    yellowCircle.setPosition({26, 115});
    yellowCircle.setFillColor(sf::Color(255, 234, 38));
    window.draw(yellowCircle);

    sf::CircleShape redCircle(36);
    redCircle.setPosition({26, 199});
    redCircle.setFillColor(sf::Color(242, 0, 0));
    window.draw(redCircle);

    window.display();

    sf::sleep(sf::seconds(5));
}
