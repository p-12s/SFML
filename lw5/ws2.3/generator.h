#pragma once

#include <vector>
#include <iostream>
#include <cassert>
#include <string>
#include <set>
#include <random>
#include <ctime>
#include <random>

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator);

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue);

// Генерирует число с плавающей точкой в диапазоне [minValue, maxValue)
float randomFloat(PRNG &generator, float minValue, float maxValue);