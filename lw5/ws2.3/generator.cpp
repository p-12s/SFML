#include "generator.h"

struct PRNG
{
    std::mt19937 engine;
};

PRNG *newGenerator()
{
    PRNG *generator = new PRNG;
    // Используем время с 1 января 1970 года в секундах как случайное зерно
    unsigned seed = unsigned(std::time(nullptr));
    // Делим по модулю на псевдо-случайное число
    seed = seed % (std::rand() + 1);
    generator->engine.seed(seed);

    return generator;
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
