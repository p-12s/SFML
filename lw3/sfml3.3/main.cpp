#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>

struct Eye
{
    sf::ConvexShape white;
    sf::Vector2f positionInWindow;
    sf::ConvexShape pupil;
    sf::Vector2f pupilPosition;
    float pupilRotation = 0;
};

sf::Vector2f toEuclidean(float radius, float angle);
void initEye(Eye &eye);
void updateEyeElements(Eye &eye, sf::Vector2f mousePosition);
float toDegrees(float radians);
float toEllipseRadius(float degreeAngle, sf::Vector2f ellipseRadius);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye);
void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye);

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * std::cos(angle),
        radius * std::sin(angle)};
}

// Переводит радианы в градиусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

// Переводит угол в радиус эллипса
float toEllipseRadius(float degreeAngle, sf::Vector2f ellipseRadius)
{
    return ellipseRadius.x * ellipseRadius.y /
           sqrt(
               pow((ellipseRadius.x * sin(degreeAngle)), 2) +
               pow((ellipseRadius.y * cos(degreeAngle)), 2));
}

// Переводит позицию мыши в расстояние до центра
float getDistance(sf::Vector2f eyePositionInWindow, sf::Vector2f mousePosition)
{
    sf::Vector2f positionRelativeToPositionOfEye = mousePosition - eyePositionInWindow;
    return sqrt(pow(positionRelativeToPositionOfEye.x, 2) + pow(positionRelativeToPositionOfEye.y, 2));
}

// Обновляет позиции и повороты частей стрелки согласно текущему состоянию стрелки
void updateEyeElements(Eye &eye, sf::Vector2f mousePosition)
{
    // в случае эллипосов ничего поворачивать не нужно, нужно лишь сместить
    // с помощью угла и радиусов эллипса по осям, найдем радиус

    const sf::Vector2f eyePupilBorderRadius = {15.f, 25.f};
    const float pupilOffsetRadius = toEllipseRadius(eye.pupilRotation, eyePupilBorderRadius);

    // расстояние от центра до мыши
    const float mauseOffsetRadius = getDistance(eye.positionInWindow, mousePosition);

    const sf::Vector2f pupilOffset = toEuclidean(std::min(pupilOffsetRadius, mauseOffsetRadius), eye.pupilRotation);
    eye.pupil.setPosition(eye.pupilPosition + pupilOffset);
}

// Инициализирует фигуру-глаз
void initEye(Eye &eye)
{
    const sf::Vector2f eyeWhiteRadius = {40.f, 80.f};
    const sf::Vector2f eyePupilRadius = {10.f, 20.f};

    // TODO нужно ли defaultPupilPosition
    const sf::Vector2f defaultPupilPosition = {0, 0};

    constexpr int EYE_WHITE_POINT_COUNT = 200;
    constexpr int EYE_PUPIL_POINT_COUNT = 200;

    // цвет белка, зрачка, радиусы яв-ся неизменяемыми свойствами в этом контексте,
    // можно ли их сделать свойством, и обращаться аналогично this. ?
    // хотя это не класс, а функция. тут вместо свойств - константы

    eye.pupilPosition = eye.positionInWindow;

    eye.white.setPosition(eye.positionInWindow);
    eye.white.setFillColor(sf::Color(255, 255, 255));

    eye.white.setPointCount(EYE_WHITE_POINT_COUNT);
    for (int pointNo = 0; pointNo < EYE_WHITE_POINT_COUNT; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(EYE_WHITE_POINT_COUNT);
        sf::Vector2f point = {
            eyeWhiteRadius.x * std::sin(angle),
            eyeWhiteRadius.y * std::cos(angle)};
        eye.white.setPoint(pointNo, point);
    }

    eye.pupil.setPosition(eye.positionInWindow);
    eye.pupil.setFillColor(sf::Color(0, 0, 0));
    eye.pupil.setPointCount(EYE_PUPIL_POINT_COUNT);
    for (int pointNo = 0; pointNo < EYE_PUPIL_POINT_COUNT; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(EYE_PUPIL_POINT_COUNT);
        sf::Vector2f point = {
            eyePupilRadius.x * std::sin(angle),
            eyePupilRadius.y * std::cos(angle)};
        eye.pupil.setPoint(pointNo, point);
    }

    updateEyeElements(eye, defaultPupilPosition);
}

// Обрабатывает событие MouseMove, обновляя позицию мыши
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
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
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye)
{
    // разница позиций мыши и зрачка
    const sf::Vector2f deltaLeftEye = mousePosition - leftEye.pupilPosition;
    leftEye.pupilRotation = atan2(deltaLeftEye.y, deltaLeftEye.x);
    // у меня есть угол, а вот расстояние должно меняться как радиус эллипса
    updateEyeElements(leftEye, mousePosition);

    const sf::Vector2f deltaRightEye = mousePosition - rightEye.pupilPosition;
    rightEye.pupilRotation = atan2(deltaRightEye.y, deltaRightEye.x);
    updateEyeElements(rightEye, mousePosition);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye)
{
    window.clear();

    window.draw(leftEye.white);
    window.draw(leftEye.pupil);

    window.draw(rightEye.white);
    window.draw(rightEye.pupil);

    window.display();
}

// Программа рисует в окне глаза, которые поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eye follows mouse", sf::Style::Default, settings);

    sf::Vector2f mousePosition;

    Eye leftEye, rightEye;
    leftEye.positionInWindow = {350, 300};
    rightEye.positionInWindow = {450, 300};
    initEye(leftEye);
    initEye(rightEye);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}
