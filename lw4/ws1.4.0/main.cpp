#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

// Инициализируем спрайт
void init(sf::Texture &texture, sf::Sprite &sprite)
{
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    sprite.setPosition(0, 0);
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
        // кейс на клик левой кнопкой мыши
        default:
            break;
        }
    }
}

float getLength()
{
    // найдем длину вектора перемещения от центра стрелки до позиции курсора, |delta| >= 0
    // при достижении стрелкой позиции курсора, считаем оставшееся расстояние = 0
    return 0;
}

float getRotationAngleInDegrees()
{
    // найдем угол между положением курсора (после клика) и спрайтом
    return 0;
}

void setRotation()
{
    // повернем спрайт влево или вправо, в зависимости от угла
}

void setMove()
{
    // найдем направление движения, с помощью нормализации вектора
    // и вычислим, какие она будет иметь координаты
    // установим обновленные координаты
}

void update(const sf::Vector2f &mousePosition, sf::Sprite &cat, sf::Sprite &pointer, float dt)
{
    static const float maxSpeedOfMove = 20;
    // вектор полного перемещения
    // обновим положение спрайта
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    window.clear({255, 255, 255});
    window.draw(cat);
    window.draw(pointer);
    window.display();
}

void initCat(sf::Texture &texture, sf::Sprite &cat)
{
    cat.setTexture(texture);
    cat.setTextureRect(sf::IntRect(0, 0, 38, 35));
    cat.setColor(sf::Color(255, 255, 255, 200));
    cat.setPosition(0, 0);
}

void initPointer(sf::Texture &texture, sf::Sprite &pointer)
{
    pointer.setTexture(texture);
    pointer.setTextureRect(sf::IntRect(0, 0, 38, 35));
    pointer.setColor(sf::Color(255, 255, 255, 200));
    pointer.setPosition(0, 0);
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
        "Cat follows pointer",
        sf::Style::Default,
        settings);

    // Declare and load a texture
    sf::Texture catTexture;
    sf::Texture pointerTexture;

    if (!catTexture.loadFromFile("ws1.4/resources/cat.png", sf::IntRect(0, 0, 38, 35)))
        exit(EXIT_FAILURE);
    if (!pointerTexture.loadFromFile("ws1.4/resources/pointer.png", sf::IntRect(0, 0, 32, 32)))
        exit(EXIT_FAILURE);

    sf::Sprite cat;
    sf::Sprite pointer;

    sf::Vector2f mousePosition;
    sf::Clock clock;

    init(catTexture, cat);
    init(pointerTexture, pointer);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, cat, pointer, dt);
        redrawFrame(window, cat, pointer);
    }
}
