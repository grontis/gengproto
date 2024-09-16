#pragma once

#include <random>

class RandomGenerator
{
public:
    RandomGenerator();

    int generateUniformInt(int min, int max);
    float generateUniformFloat(float min, float max);
    double generateUniformDouble(double min, double max);
    void reseed(unsigned int seed);

private:
    std::random_device rd;
    std::default_random_engine engine;
};