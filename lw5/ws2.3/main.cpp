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

#include "generator.h"
//#include "color.h"

/*
struct PRNG
{
    std::mt19937 engine;
};
*/

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
};
/*
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
*/
void updateSpeed(std::vector<Ball> &elements, const int windowWidth, const int windowHeight)
{
    for (size_t fi = 0; fi < elements.size(); ++fi)
    {
        int ballRadius = elements[fi].ball.getRadius();
        float &speedX = elements[fi].speed.x;
        float &speedY = elements[fi].speed.y;
        int positionX = elements[fi].ball.getPosition().x;
        int positionY = elements[fi].ball.getPosition().y;

        if ((positionX + ballRadius >= windowWidth) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((positionX - ballRadius < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        if ((positionY + ballRadius >= windowHeight) && (speedY > 0))
        {
            speedY = -speedY;
        }
        if ((positionY - ballRadius < 0) && (speedY < 0))
        {
            speedY = -speedY;
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

// Возвращает результат скалрного произведения 2-х векторов
double vectorsScalarComposition(const sf::Vector2f &vec1, const sf::Vector2f &vec2)
{
    sf::Vector2f temp;
    temp.x = vec1.x * vec2.x;
    temp.y = vec1.y * vec2.y;
    return double(temp.x + temp.y);
}

// Возвращает вектора скоростей после удара
void ballStateRecalculation(Ball &first, Ball &second)
{
    sf::Vector2f firstPosition = first.ball.getPosition();
    sf::Vector2f secondPosition = second.ball.getPosition();

    sf::Vector2f deltaToW1 = firstPosition - secondPosition;
    sf::Vector2f speedDifferenceToW1 = first.speed - second.speed;

    double tempItem1 = vectorsScalarComposition(speedDifferenceToW1, deltaToW1) / pow(getLength(deltaToW1), 2);
    sf::Vector2f tempItem11 = {float(tempItem1 * deltaToW1.x), float(tempItem1 * deltaToW1.y)};
    sf::Vector2f w1 = first.speed - tempItem11;
    //sf::Vector2f w1 = first.speed - (vectorsScalarComposition(speedDifferenceToW1, deltaToW1) / pow(deltaToW1, 2)) * deltaToW1;

    sf::Vector2f deltaToW2 = secondPosition - firstPosition;
    sf::Vector2f speedDifferenceToW2 = second.speed - first.speed;

    double tempItem2 = vectorsScalarComposition(speedDifferenceToW2, deltaToW2) / pow(getLength(deltaToW2), 2);
    sf::Vector2f tempItem22 = {float(tempItem2 * deltaToW2.x), float(tempItem2 * deltaToW2.y)};
    //sf::Vector2f w2 = second.speed - tempItem2 * deltaToW2;
    sf::Vector2f w2 = second.speed - tempItem22;
    //sf::Vector2f w2 = second.speed - (vectorsScalarComposition(speedDifferenceToW2, deltaToW2) / pow(deltaToW2, 2)) * deltaToW2;

    first.speed = w1;
    second.speed = w2;
}

void checkOutCollisions(std::vector<Ball> &elements)
{
    // Перебираем каждую пару объектов
    //  - ни одну пару не используем дважды
    //  - не используем пары из одного объекта (т.е. объект не сталкивается сам с собой)
    for (size_t fi = 0; fi < elements.size(); ++fi)
    {
        for (size_t si = fi + 1; si < elements.size(); ++si)
        {
            // вектор полного перемещения от центра одного круга до центра второго
            sf::Vector2f delta = elements[fi].ball.getPosition() - elements[si].ball.getPosition();
            // расстояние
            int centerToCenterDistance = getLength(delta);

            // сумма радиусов 2 сравниваемых шаров
            int sumOfRadiusesOfBalls = elements[fi].ball.getRadius() + elements[si].ball.getRadius();
            // если расстояние между центрами меньше суммы радиусов

            if (centerToCenterDistance <= sumOfRadiusesOfBalls)
            {
                // меняем скорость и направление
                ballStateRecalculation(elements[fi], elements[si]);
                // иногда происходит заталкивание, и шары "слипаются", пока достаточно сильный внешний импульс не позволит им "разъединиться"
            }
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
    constexpr float minSpeedNumber = -200.f;
    constexpr float maxSpeedNumber = 200.f;

    PRNG *generator = newGenerator(); //newGenerator(generator)
    sf::Vector2f result = {
        randomFloat(generator, minSpeedNumber, maxSpeedNumber),
        randomFloat(generator, minSpeedNumber, maxSpeedNumber)};
    delete generator;
    return result;
}

// Получаем цвет от (0, 0, 0) до (255, 255, 255)
sf::Color getColor()
{
    constexpr int minColorNumber = 0;
    constexpr int maxColorNumber = 255;

    PRNG generator;
    initGenerator(generator);

    return sf::Color(
        random(generator, minColorNumber, maxColorNumber),
        random(generator, minColorNumber, maxColorNumber),
        random(generator, minColorNumber, maxColorNumber));
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
    constexpr unsigned minBallSize = 20;

    std::vector<Ball> balls(ballsCount);

    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        int ballRadius = minBallSize + fi;
        balls[fi].ball.setRadius(ballRadius);
        balls[fi].ball.setPosition({float(30 + (fi * 65)), float(30 + (fi * 65))});
        balls[fi].speed = getSpeed(); //{50.f, 50.f}; //getSpeed();
        balls[fi].ball.setFillColor(getColor());
        // Устанавливаем начало координат каждого шара в его центр
        balls[fi].ball.setOrigin(ballRadius, ballRadius);
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
        checkOutCollisions(balls);
        window.clear();
        drow(window, balls);
        window.display();
    }
}