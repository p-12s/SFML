#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <random>
#include <ctime>
#include <random>
#include <cassert>

struct PRNG
{
    std::mt19937 engine;
};

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
};

void initGenerator(PRNG &generator)
{
    // Используем время с 1 января 1970 года в секундах как случайное зерно
    unsigned seed = unsigned(std::time(nullptr));
    // Делим по модулю на псевдо-случайное число
    seed = seed % (std::rand() + 1);
    generator.engine.seed(seed);
}

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

// Генерирует число с плавающей точкой в диапазоне [minValue, maxValue)
float randomFloat(PRNG &generator, float minValue, float maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

void updateSpeed(std::vector<Ball> &elements, const int windowWidth, const int windowHeight)
{
    for (size_t fi = 0; fi < elements.size(); ++fi)
    {
        if ((elements[fi].ball.getPosition().x + 2 * elements[fi].ball.getRadius() >= windowWidth) && (elements[fi].speed.x > 0))
        {
            elements[fi].speed.x = -elements[fi].speed.x;
        }
        if ((elements[fi].ball.getPosition().x < 0) && (elements[fi].speed.x < 0))
        {
            elements[fi].speed.x = -elements[fi].speed.x;
        }
        if ((elements[fi].ball.getPosition().y + 2 * elements[fi].ball.getRadius() >= windowHeight) && (elements[fi].speed.y > 0))
        {
            elements[fi].speed.y = -elements[fi].speed.y;
        }
        if ((elements[fi].ball.getPosition().y < 0) && (elements[fi].speed.y < 0))
        {
            elements[fi].speed.y = -elements[fi].speed.y;
        }
    }
}

void drow(sf::RenderWindow &window, std::vector<Ball> elements)
{
    for (size_t fi = 0; fi < elements.size(); ++fi)
    {
        window.draw(elements[fi].ball);
    }
}

void updatePosition(std::vector<Ball> &elements, const float dt)
{
    for (size_t fi = 0; fi < elements.size(); ++fi)
    {
        sf::Vector2f position = elements[fi].ball.getPosition();
        position += elements[fi].speed * dt;
        elements[fi].ball.setPosition(position);
    }
}

// Получаем скорость от (-150f, -150f) до (150f, 150f)
sf::Vector2f getSpeed()
{
    PRNG generator;
    initGenerator(generator);
    return {randomFloat(generator, -150.f, 150.f), randomFloat(generator, -150.f, 150.f)};
}

// Получаем цвет от (0, 0, 0) до (255, 255, 255)
sf::Color getColor()
{
    PRNG generator;
    initGenerator(generator);
    return sf::Color(random(generator, 0, 255), random(generator, 0, 255), random(generator, 0, 255));
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned ANTIALIASING_LEVEL = 8;

    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    // инициализацию окна в отдельную функцию (метод .init, с параметрами)
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Bouncing Balls",
        sf::Style::Default,
        settings);

    constexpr unsigned ballsCount = 10;

    std::vector<Ball> balls(ballsCount);

    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        balls[fi].ball.setRadius(20 + fi);
        balls[fi].ball.setPosition({(WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2)});
        balls[fi].speed = getSpeed();
        balls[fi].ball.setFillColor(getColor());
    }

    sf::Clock clock;

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

        updatePosition(balls, dt);
        updateSpeed(balls, WINDOW_WIDTH, WINDOW_HEIGHT);
        window.clear();
        drow(window, balls);
        window.display();
    }
}