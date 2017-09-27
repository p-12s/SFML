#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
#define WALLS_COLOR "77, 46, 11"
#define DOOR_COLOR "24, 23, 23"
#define ROOF_COLOR "93, 30, 23"
#define TRUMPET_COLOR "59, 56, 56"
#define SMOKE_COLOR "191, 191, 191"

    sf::RectangleShape walls;
    walls.setSize({457, 241});
    walls.setPosition({162, 300});
    walls.setFillColor(sf::Color(77, 46, 11));

    sf::RectangleShape door;
    door.setSize({76, 165});
    door.setPosition({206, 377});
    door.setFillColor(sf::Color(24, 23, 23));

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(93, 30, 23));
    roof.setPosition({110, 187});
    roof.setPointCount(4);
    roof.setPoint(0, {166, 0});
    roof.setPoint(1, {397, 0});
    roof.setPoint(2, {561, 120});
    roof.setPoint(3, {0, 120});

    sf::CircleShape smokePart1(25);
    smokePart1.setPosition({507, 31});
    smokePart1.setFillColor(sf::Color(191, 191, 191));

    sf::CircleShape smokePart2(22);
    smokePart2.setPosition({496, 63});
    smokePart2.setFillColor(sf::Color(191, 191, 191));

    sf::CircleShape smokePart3(18);
    smokePart3.setPosition({482, 89});
    smokePart3.setFillColor(sf::Color(191, 191, 191));

    sf::CircleShape smokePart4(16);
    smokePart4.setPosition({473, 116});
    smokePart4.setFillColor(sf::Color(191, 191, 191));

    sf::ConvexShape trumpet;
    trumpet.setFillColor(sf::Color(59, 56, 56));
    trumpet.setPosition({449, 140});
    trumpet.setPointCount(8);
    trumpet.setPoint(0, {0, 0});
    trumpet.setPoint(1, {58, 0});
    trumpet.setPoint(2, {58, 42});
    trumpet.setPoint(3, {47, 42});
    trumpet.setPoint(4, {47, 105});
    trumpet.setPoint(5, {13, 105});
    trumpet.setPoint(6, {13, 42});
    trumpet.setPoint(7, {0, 42});

    sf::RenderWindow window(sf::VideoMode({800, 600}), "House");
    window.clear();

    window.draw(walls);
    window.draw(door);
    window.draw(roof);
    window.draw(smokePart1);
    window.draw(smokePart2);
    window.draw(smokePart3);
    window.draw(smokePart4);
    window.draw(trumpet);

    window.display();

    sf::sleep(sf::seconds(5));
}
