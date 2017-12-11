#include "field.h"

static const float BLOCK_SIZE = 25.f;
static const size_t FIELD_WIDTH = 32;
static const size_t FIELD_HEIGHT = 24;

static const char FIELD_MAZE[] = "################################"
                                 "#     #                        #"
                                 "#     #                        #"
                                 "#     #                        #"
                                 "#  @  #                        #"
                                 "#                              #"
                                 "#           ####################"
                                 "#                              #"
                                 "#                              #"
                                 "#                  #           #"
                                 "#                  #           #"
                                 "############       #           #"
                                 "#                  #           #"
                                 "#                  #           #"
                                 "#                  #           #"
                                 "#                  #           #"
                                 "#                  #           #"
                                 "#                  #           #"
                                 "#             ############     #"
                                 "#                              #"
                                 "#                              #"
                                 "#                              #"
                                 "#                              #"
                                 "################################";

static const sf::Color WALL_COLOR = sf::Color(52, 93, 199);
static const sf::Color ROAD_COLOR = sf::Color(40, 40, 40);

static sf::FloatRect moveRect(const sf::FloatRect &rect, sf::Vector2f &offset)
{
    return {rect.left + offset.x, rect.top + offset.y, rect.width, rect.height};
}

// Находит символ '@' в исходной карте лабиринта.
sf::Vector2f getPackmanStartPosition()
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            const size_t offset = x + y * FIELD_WIDTH;
            if (FIELD_MAZE[offset] == '@')
            {
                return {x * BLOCK_SIZE, y * BLOCK_SIZE};
            }
        }
    }
    return {0, 0};
}

void initializeField(Field &field)
{
    field.width = FIELD_WIDTH;
    field.height = FIELD_HEIGHT;
    field.cells = new Cell[field.width * field.height];
    for (size_t y = 0; y < field.height; y++)
    {
        for (size_t x = 0; x < field.width; x++)
        {
            const size_t offset = x + y * field.width;
            CellCategory category;
            sf::Color color;
            if (FIELD_MAZE[offset] == '#')
            {
                category = CellCategory::WALL;
                color = WALL_COLOR;
            }
            else
            {
                category = CellCategory::ROAD;
                color = ROAD_COLOR;
            }
            Cell &cell = field.cells[offset];
            cell.category = category;
            cell.bounds.setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
            cell.bounds.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            cell.bounds.setFillColor(color);
        }
    }
}

void drawField(sf::RenderWindow &window, const Field &field)
{
    for (size_t i = 0; i < field.width * field.height; i++)
    {
        window.draw(field.cells[i].bounds);
    }
}

// Модифицирует вектор перемещения, избегая столкновения
// прямоугольника `rect` со стенами лабиринта в поле `field`.
// Возвращает `true`, если вектор перемещения изменён.
bool checkFieldWallsCollision(const Field &field, const sf::FloatRect &oldBounds, sf::Vector2f &movement)
{
    sf::FloatRect newBounds = moveRect(oldBounds, movement);
    bool changed = false;
    for (size_t i = 0, n = field.width * field.height; i < n; i++)
    {
        const Cell &cell = field.cells[i];
        if (cell.category == CellCategory::ROAD)
        {
            continue;
        }

        sf::FloatRect blockBound = cell.bounds.getGlobalBounds();
        if (newBounds.intersects(blockBound))
        {
            if (movement.y < 0)
            {
                movement.y += blockBound.top + blockBound.height - newBounds.top;
            }
            else if (movement.y > 0)
            {
                movement.y -= newBounds.top + newBounds.height - blockBound.top;
            }
            if (movement.x < 0)
            {
                movement.x += blockBound.left + blockBound.width - newBounds.left;
            }
            else if (movement.x > 0)
            {
                movement.x -= newBounds.left + newBounds.width - blockBound.left;
            }
            changed = true;
            newBounds = moveRect(oldBounds, movement);
        }
    }
    return changed;
}

void destroyField(Field &field)
{
    delete[] field.cells;
}