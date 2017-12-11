#include "Bullet.h"
#include "Tank.h"

constexpr float BULLET_SPEED = 250.f;
constexpr float BULLET_SIZE = 5;
constexpr float BULLET_OUTLINE_SIZE = 3;

const sf::Color BULLET_FILL_COLOR = sf::Color(241, 78, 84);
const sf::Color BULLET_OUTLINE_COLOR = sf::Color(180, 58, 63);

Bullet::Bullet()
{
    m_body.setRadius(BULLET_SIZE);
    m_body.setOrigin({BULLET_SIZE, BULLET_SIZE});
    m_body.setFillColor(BULLET_FILL_COLOR);
    m_body.setOutlineColor(BULLET_OUTLINE_COLOR);
    m_body.setOutlineThickness(BULLET_OUTLINE_SIZE);
}

void Bullet::update(sf::Clock &clock)
{
    const float elapsedTime = clock.restart().asSeconds();
    // Передвигаем ракету
    // не останавливать снаряд, а удалять
    float positionX = m_body.getPosition().x + m_speed.x * elapsedTime;
    float positionY = m_body.getPosition().y + m_speed.y * elapsedTime;

    if (positionX < 800 && positionX > 0 &&
        positionY < 600 && positionY > 0)
    {
        m_body.setPosition({positionX, positionY});
    }
}

// по нажатию пробела создавать
void Bullet::updateMove(float dt)
{
    /*
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
    }*/
}

void Bullet::watch(sf::Clock &clock, sf::RenderWindow &window)
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    if (elapsedTime > 1)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            // удобно взять положение и напрваление танка
            // выстрел

            // позиция, скорость, поворот
            m_body.setPosition({300, 300}); // брать у танка
            m_speed = {-100.f, -100.f};     // зависит от направления пушки танка

            window.draw(m_body);
            std::cout << "bum!!" << std::endl;

            clock.restart();
        }
    }
}
