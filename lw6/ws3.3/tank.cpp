#include "Tank.h"

constexpr float TANK_SPEED = 100.f;
constexpr float TANK_START_SIZE = 12;
constexpr float GUN_WIDTN = TANK_START_SIZE * 2;
constexpr float GUN_HEIGHT = TANK_START_SIZE - TANK_START_SIZE / 3;

constexpr float POWER_BANK_WIDTH = 36;
constexpr float POWER_BANK_HEIGHT = 6;
constexpr int POWER_BANK_START_LIFE_LEVEL = 100;

const sf::Color GUN_FILL_COLOR = sf::Color(115, 115, 115);
const sf::Color GUN_OUTLINE_COLOR = sf::Color(53, 53, 53);
const sf::Color BODY_FILL_COLOR = sf::Color(4, 111, 231);
const sf::Color BATTERY_FILL_COLOR = sf::Color(40, 160, 40);


// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * cos(angle)),
        float(radius * sin(angle))};
}

// Переводит радианы в градиусы
float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

Tank::Tank()
{
    // пушка
    m_gun.setSize({GUN_WIDTN, GUN_HEIGHT});
    m_gun.setOrigin({(GUN_WIDTN / 2), (GUN_HEIGHT / 2)});
    m_gun.setFillColor(GUN_FILL_COLOR);
    m_gun.setOutlineColor(GUN_OUTLINE_COLOR);
    m_gun.setOutlineThickness(2);

    // корпус
    m_body.setRadius(TANK_START_SIZE);
    m_body.setOrigin({TANK_START_SIZE, TANK_START_SIZE});
    m_body.setFillColor(BODY_FILL_COLOR);
    m_body.setOutlineColor(GUN_OUTLINE_COLOR);
    m_body.setOutlineThickness(2);

    // позиция, скорость, поворот
    m_position = {400, 300}; // что за дублировнаие положения?
    m_rotation = 0;

    // здоровье
    m_levelOfLife = POWER_BANK_START_LIFE_LEVEL;

    // фон батареи здоровья
    m_batteryBgFill.setSize({POWER_BANK_WIDTH, POWER_BANK_HEIGHT});
    m_batteryBgFill.setOrigin({0, (POWER_BANK_HEIGHT / 2)});
    m_batteryBgFill.setFillColor(GUN_OUTLINE_COLOR);

    // закрашенный уровень батареи здоровья
    float batteryLevelFillHeight = POWER_BANK_HEIGHT - 2;
    float batteryLevelFillWidth = (POWER_BANK_WIDTH - 2) * m_levelOfLife / POWER_BANK_START_LIFE_LEVEL;
    m_batteryLevelFill.setSize({batteryLevelFillWidth, batteryLevelFillHeight});
    m_batteryLevelFill.setOrigin({-1, (batteryLevelFillHeight / 2)});
    m_batteryLevelFill.setFillColor(BATTERY_FILL_COLOR);
}

void Tank::update(sf::Clock &clock, sf::Vector2f &mousePosition)
{
    float dt = clock.restart().asSeconds();
    const sf::Vector2f delta = mousePosition - m_position;
    m_rotation = atan2(delta.y, delta.x);

    updateMove(dt);

    updateElements();
}

void Tank::updateMove(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_speed = {-TANK_SPEED, 0};
        switchState(State::Move);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_speed = {TANK_SPEED, 0};
        switchState(State::Move);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_speed = {0, -TANK_SPEED};
        switchState(State::Move);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_speed = {0, TANK_SPEED};
        switchState(State::Move);
    }
    else
    {
        m_speed = {0, 0};
        switchState(State::Stand);
    }

    // Передвигаем танк
    float positionX = m_position.x + m_speed.x * dt;
    if (positionX < WINDOW_WIDTH && positionX > 0)
    {
        m_position.x = positionX;
    }

    float positionY = m_position.y + m_speed.y * dt;
    if (positionY < WINDOW_HEIGHT && positionY > 0)
    {
        m_position.y = positionY;
    }
}

void Tank::switchState(State state)
{
    if (m_state == state)
    {
        // Состояние не изменилось
        return;
    }

    switch (state)
    {
    case State::Stand:
        //assert(!"cannot switch to Stand");
        break;

    case State::Move:
        // передвижение
        break;
    }

    // Меняем состояние
    m_state = state;
}

// Обновляет позиции и повороты частей стрелки согласно текущему состоянию стрелки
void Tank::updateElements()
{
    int gunOffsetFromCenter = m_body.getRadius();
    const sf::Vector2f gunOffset = toEuclidean(gunOffsetFromCenter, m_rotation);
    m_gun.setPosition(m_position + gunOffset);
    m_gun.setRotation(toDegrees(m_rotation));

    int bodyOffsetFromCenter = 0;
    const sf::Vector2f bodyOffset = toEuclidean(bodyOffsetFromCenter, m_rotation);
    m_body.setPosition(m_position);
    m_body.setRotation(toDegrees(m_rotation));
    m_batteryBgFill.setPosition({(m_position.x - POWER_BANK_WIDTH / 2), (m_position.y + 30)});
    m_batteryLevelFill.setPosition({m_batteryBgFill.getPosition().x, (m_batteryBgFill.getPosition().y)});
}

void Tank::drow(sf::RenderWindow &window)
{
    window.draw(m_gun);
    window.draw(m_body);
    window.draw(m_batteryBgFill);
    window.draw(m_batteryLevelFill);
}

sf::Vector2f getPosition()
{
    
}

float getRotation()
{
    
}