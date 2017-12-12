#include "constants.h"
#include "gamescene.h"
#include <string>

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

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
    const std::string title = "Diep.io Game Clone - 3th stage";
    sf::VideoMode videoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    window.create(videoMode, title, sf::Style::Default, settings);
}

void update(sf::Clock &clock, sf::Clock &rechargeClock, GameScene &scene, sf::Vector2f &mousePosition)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();    
    clock.restart();
    updateGameScene(scene, elapsedTime, rechargeClock, mousePosition);
}

void render(sf::RenderWindow &window, const GameScene &scene)
{
    window.clear(GAME_BG_COLOR);
    drawGameScene(window, scene);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    sf::Vector2f mousePosition;
    sf::Clock clock;
    sf::Clock rechargeTime;
    GameScene scene;
    initializeGameScene(scene, sf::Vector2f(window.getSize()));

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(clock, rechargeTime, scene, mousePosition);
        //window.setTitle(getGameSceneWindowTitle(scene));
        render(window, scene);
    }
}
