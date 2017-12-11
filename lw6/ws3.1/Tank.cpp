#include "Tank.h"
#include <cmath>
#include <float.h>
#include <cassert>
#include <iostream>

constexpr float TANK_SIZE = 12;
constexpr float GUN_WIDTN = TANK_SIZE * 2;
constexpr float GUN_HEIGHT = TANK_SIZE - TANK_SIZE / 3;




// Скорость персонажа, пикселей в секунду.
constexpr float HERO_SPEED = 100.f;
constexpr float JUMP_START_SPEED = 250.f;
// Ускорение свободного падения, пикселей в секунду.
const sf::Vector2f GRAVITY_ACCELERATION = {0, 800.f};
// Длительность кадра анимации, в секундах.
constexpr float FRAME_DURATION = 0.1f;




static float length(const sf::Vector2f& value)
{
    return std::hypotf(value.x, value.y);
}

static sf::Vector2f normalize(const sf::Vector2f& value)
{
    const float valueLength = length(value);
    if (valueLength < FLT_EPSILON)
    {
        return { 0, 0 };
    }
    return value / valueLength;
}

Tank::Tank(AnimatedSprite& sprite)
    : m_sprite(sprite)
{
}

void Tank::update(float dt)
{
    // в зависимости от статуса обновлять движение
    switch (m_state)
    {
        /*
        case State::NotStarted:
        case State::Idle:
        case State::Walking:
            updateIdleOrWalking(dt);
            break;
        case State::Jumping:
            updateJumping(dt);
            break;
        */
        case State::StandsStill:
        case State::MovesToLeft:
            updateMoves(dt);// еще параметр напрв. движ в виде вектора
            break;
        case State::MovesToRight:
            updateMoves(dt);
            break;
        case State::MovesToUp:
            updateMoves(dt);
            break;
        case State::MovesToDown:
            updateMoves(dt);
            break;
    }
/*
    if (m_updateAnimation)
    {
        m_updateAnimation(dt);
    }
*/
}

// можно просто переделать движение влево-вправо для меня
void Tank::updateIdleOrWalking(float dt)
{
    // Герой двигается, влево, вправо либо стоит на месте.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_sprite.setScale(-1, 1);
        m_speed.x = -HERO_SPEED;
        switchState(State::Walking);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_sprite.setScale(1, 1);
        m_speed.x = HERO_SPEED;
        switchState(State::Walking);
    }
    else
    {
        m_speed = { 0, 0 };
        switchState(State::Idle);
    }

    // Герой начинает прыжок.
/*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        m_jumpStartY = m_sprite.getPosition().y;
        m_speed.y = -JUMP_START_SPEED;
        switchState(State::Jumping);
    }
*/
    // Передвигаем куклу-персонажа.
    m_sprite.setPosition(m_sprite.getPosition() + m_speed * dt);
}

void Tank::switchState(State state)
{
    if (m_state == state)
    {
        // Состояние не изменилось - эффекта перехода нет.
        return;
    }

    // Меняем состояние
    m_state = state;
    std::cout << "state switched to: " + m_state << std::endl;
}