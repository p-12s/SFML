#include "generator.h"
#include "color.h"
#include <iostream>

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f speed;
};

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

    sf::Vector2f deltaToW2 = secondPosition - firstPosition;
    sf::Vector2f speedDifferenceToW2 = second.speed - first.speed;

    double tempItem2 = vectorsScalarComposition(speedDifferenceToW2, deltaToW2) / pow(getLength(deltaToW2), 2);
    sf::Vector2f tempItem22 = {float(tempItem2 * deltaToW2.x), float(tempItem2 * deltaToW2.y)};
    sf::Vector2f w2 = second.speed - tempItem22;

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

// Получаем скорость
sf::Vector2f getSpeed(PRNG &generator)
{
    constexpr float minSpeedNumber = -250.f;
    constexpr float maxSpeedNumber = 250.f;

    return {
        randomFloat(generator, minSpeedNumber, maxSpeedNumber),
        randomFloat(generator, minSpeedNumber, maxSpeedNumber)};
}

void calculationWithConstantMinimumTime(
    float dt,
    std::vector<Ball> &elements,
    const int windowWidth,
    const int windowHeight,
    sf::RenderWindow &window)
{
    const unsigned additionalCalculationsCount = 10;
    for (auto i = 0; i < additionalCalculationsCount; ++i)
    {
        updatePosition(elements, (dt / additionalCalculationsCount));
        updateSpeed(elements, windowWidth, windowHeight);
        checkOutCollisions(elements);
        window.clear();
        drow(window, elements);
        window.display();
    }
}

Ball createBall()
{
    Ball *ball = new Ball;
    int fi = 5;
    int ballRadius = 25 + fi;
    ball->ball.setRadius(ballRadius);
    ball->ball.setPosition({float(30 + (fi * 65)), float(30 + (fi * 65))});
    ball->speed = {210.f, -200.f};                     //getSpeed(generator);
    ball->ball.setFillColor(sf::Color(100, 200, 150)); //getColor(generator)
    // Устанавливаем начало координат каждого шара в его центр
    ball->ball.setOrigin(ballRadius, ballRadius);
    return *ball;
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

    constexpr unsigned ballsCount = 2;
    constexpr unsigned minBallSize = 25;

    std::vector<Ball> balls(ballsCount);

    PRNG generator;
    initGenerator(generator);

    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        int ballRadius = minBallSize + fi;

        balls[fi].ball.setRadius(ballRadius);
        balls[fi].ball.setPosition({float(30 + (fi * 65)), float(30 + (fi * 65))});
        balls[fi].speed = {210.f, -200.f}; //getSpeed(generator);
        balls[fi].ball.setFillColor(sf::Color(100, 200, 150));
        // Устанавливаем начало координат каждого шара в его центр
        balls[fi].ball.setOrigin(ballRadius, ballRadius);
    }

    sf::Clock clock;

    while (window.isOpen())
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Ball newBall = createBall();
            balls.push_back(newBall);
            std::cout << "space!" << std::endl;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            int lastBallPosition = balls.size() - 1;
            std::cout << "length before: " << balls.size() << std::endl;
            //delete balls[lastBallPosition];
            std::cout << "length after: " << balls.size() << std::endl;
        }

        float dt = clock.restart().asSeconds();
        calculationWithConstantMinimumTime(dt, balls, WINDOW_WIDTH, WINDOW_HEIGHT, window);
    }
}