#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <random>
#include <ctime>
#include <random>
#include <cassert>

struct PRNG;

PRNG *newGenerator();

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue);

// Генерирует число с плавающей точкой в диапазоне [minValue, maxValue)
float randomFloat(PRNG generator, float minValue, float maxValue);