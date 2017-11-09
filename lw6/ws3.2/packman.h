

// Новый синтаксис C++ 2011, позволяет избегать конфликтов
// добавляет во внешнюю область видимости константы Direction::NONE == 0,
// Direction::UP == 1 и так далее. Имя Direction::NONE ни с чем не конфликтует.
enum struct Direction
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

bool handlePackmanKeyPress(const sf::Event::KeyEvent &event, Packman &packman);

void updatePackman(Packman &packman, float elapsedTime);