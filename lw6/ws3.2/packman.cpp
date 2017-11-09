
bool handlePackmanKeyRelease(const sf::Event::KeyEvent &event, Packman &packman)
{
    bool handled = true;
    switch (event.code)
    {
    case sf::Keyboard::Up:
        if (packman.direction == Direction::UP)
        {
            packman.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::Down:
        if (packman.direction == Direction::DOWN)
        {
            packman.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::Left:
        if (packman.direction == Direction::LEFT)
        {
            packman.direction = Direction::NONE;
        }
        break;
    case sf::Keyboard::Right:
        if (packman.direction == Direction::RIGHT)
        {
            packman.direction = Direction::NONE;
        }
        break;
    default:
        handled = false;
        break;
    }

    return handled;
}

void updatePackman(Packman &packman, float elapsedTime)
{
    const float PACKMAN_SPEED = 20.f; // pixels per second.
    const float step = PACKMAN_SPEED * elapsedTime;
    sf::Vector2f position = packman.shape.getPosition();
    switch (packman.direction)
    {
    case Direction::UP:s
        position.y -= step;
        break;
    case Direction::DOWN:
        position.y += step;
        break;
    case Direction::LEFT:
        position.x -= step;
        break;
    case Direction::RIGHT:
        position.x += step;
        break;
    case Direction::NONE:
        break;
    }
    packman.shape.setPosition(position);
}
