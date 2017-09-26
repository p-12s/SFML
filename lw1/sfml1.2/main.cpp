#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Initials");

    window.clear();

    // My initials - VPI

    // V letter
    sf::RectangleShape vLetterPart1;
    vLetterPart1.setSize({45, 372});
    vLetterPart1.setPosition({84, 124});
    vLetterPart1.setRotation(-15);
    vLetterPart1.setFillColor(sf::Color(193, 73, 83));
    window.draw(vLetterPart1);

    sf::RectangleShape vLetterPart2;
    vLetterPart2.setSize({45, 372});
    vLetterPart2.setPosition({276, 114});
    vLetterPart2.setRotation(15);
    vLetterPart2.setFillColor(sf::Color(193, 73, 83));
    window.draw(vLetterPart2);

    // P letter
    sf::RectangleShape pLetterPart1;
    pLetterPart1.setSize({45, 372});
    pLetterPart1.setPosition({363, 116});
    pLetterPart1.setFillColor(sf::Color(193, 73, 83));
    window.draw(pLetterPart1);

    sf::RectangleShape pLetterPart2;
    pLetterPart2.setSize({45, 196});
    pLetterPart2.setPosition({363, 159});
    pLetterPart2.setRotation(-90);
    pLetterPart2.setFillColor(sf::Color(193, 73, 83));
    window.draw(pLetterPart2);

    sf::RectangleShape pLetterPart3;
    pLetterPart3.setSize({45, 196});
    pLetterPart3.setPosition({363, 324});
    pLetterPart3.setRotation(-90);
    pLetterPart3.setFillColor(sf::Color(193, 73, 83));
    window.draw(pLetterPart3);

    sf::RectangleShape pLetterPart4;
    pLetterPart4.setSize({45, 209});
    pLetterPart4.setPosition({514, 116});
    pLetterPart4.setFillColor(sf::Color(193, 73, 83));
    window.draw(pLetterPart4);

    // I letter
    sf::RectangleShape iLetterPart1;
    iLetterPart1.setSize({45, 372});
    iLetterPart1.setPosition({672, 116});
    iLetterPart1.setFillColor(sf::Color(193, 73, 83));
    window.draw(iLetterPart1);

    window.display();

    sf::sleep(sf::seconds(5));
}
