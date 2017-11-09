#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

// Инициализируем спрайт
void init(sf::Texture &texture, sf::Sprite &sprite)
{
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(255, 255, 255, 200));
    const sf::Vector2u textureSize = texture.getSize();
    sprite.setPosition(float(textureSize.x), float(textureSize.y));
    sprite.setOrigin(float(textureSize.x / 2), float(textureSize.y / 2));
}

// Переводит радианы в градусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

float getRotationAngleInDegrees(const sf::Vector2f coordinateDifference)
{
    float angle = atan2(coordinateDifference.y, coordinateDifference.x);
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    return toDegrees(angle);
}

// Берет координаты клика, усанавливает позицию красной точки
void updatePointerPosition(sf::Sprite &pointer, const sf::Vector2f &positionForInstallation)
{
    pointer.setPosition({positionForInstallation.x, positionForInstallation.y});
}

// Поворачивает кота в сторону красной точки
void updateCatLooking(sf::Sprite &cat, sf::Sprite &pointer)
{
    // вектор полного перемещения
    const sf::Vector2f delta = pointer.getPosition() - cat.getPosition();
    const float angle = getRotationAngleInDegrees(delta);

    // в какую сторону смотрит кот - зависит от угла направления движения
    if ((90 <= angle) && (angle <= 270))
    {
        cat.setScale(-1, 1);
    }
    else
    {
        cat.setScale(1, 1);
    }
}

// Опрашивает и обрабатывает доступные события в цикле
void pollEvents(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f newPointerPosition = {float(event.mouseButton.x), float(event.mouseButton.y)};
                // обновили позицию красной точки
                updatePointerPosition(pointer, newPointerPosition);
                // повернули кота в нужную сторону
                updateCatLooking(cat, pointer);
            }
            break;
        default:
            break;
        }
    }
}

// найдем длину вектора перемещения от центра стрелки до позиции курсора, |delta| >= 0
float getLength(const sf::Vector2f coordinateDifference)
{
    const float sumOfSquaresOfCoordinates = pow(coordinateDifference.x, 2) + pow(coordinateDifference.y, 2);
    float directionOfMove;
    if (sumOfSquaresOfCoordinates >= 0)
    {
        directionOfMove = sqrt(sumOfSquaresOfCoordinates); // |delta|
    }
    else
    {
        // при достижении стрелкой позиции курсора, считаем оставшееся расстояние = 0
        directionOfMove = 0;
    }
    return directionOfMove;
}

void setMove(const float directionOfMove, const sf::Vector2f delta, const float minMove, sf::Sprite &cat)
{
    // найдем направление движения, с помощью нормализации вектора
    const sf::Vector2f direction = {float(delta.x / directionOfMove), float(delta.y / directionOfMove)};

    // и вычислим, какие она будет иметь координаты
    const sf::Vector2f dtPosition = {
        direction.x * minMove,
        direction.y * minMove};

    cat.setPosition(cat.getPosition() + dtPosition);
}

void update(sf::Sprite &cat, sf::Sprite &pointer, const float dt)
{
    static const float maxSpeedOfMove = 100;

    // вектор полного перемещения
    const sf::Vector2f delta = pointer.getPosition() - cat.getPosition();
    // расстояние от кота до красной точки, directionOfMove >= 0
    const float directionOfMove = getLength(delta);

    // на какое расстояние переместиться фигура за время dt
    const float maxMovePerTimePeriod = maxSpeedOfMove * dt;
    // выберем минимальное из этих двух
    const float minMove = std::min(directionOfMove, maxMovePerTimePeriod);

    if (minMove != 0)
    {
        setMove(directionOfMove, delta, minMove, cat);
    }
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    window.clear({255, 255, 255});
    window.draw(cat);
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    static const int ANTIALIASING_LEVEL = 8;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    // инициализацию окна в отдельную функцию (метод .init, с параметрами)
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Cat follows pointer",
        sf::Style::Default,
        settings);

    // 2 картинки одним спрайтом
    // объявление спрайта тоже в функцию, пармтеры вырезания спрайта передавать в sf::IntRect
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

    // init вызывать в конце функции инициализации
    init(catTexture, cat);
    init(pointerTexture, pointer);

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();
        pollEvents(window, cat, pointer);
        update(cat, pointer, dt);
        redrawFrame(window, cat, pointer);
    }
}
