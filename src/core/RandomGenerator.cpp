#include "RandomGenerator.h"

namespace core
{
    RandomGenerator::RandomGenerator() : _engine(_rd()) {}

    int RandomGenerator::generateUniformInt(int min, int max)
    {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(_engine);
    }

    float RandomGenerator::generateUniformFloat(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(_engine);
    }

    double RandomGenerator::generateUniformDouble(double min, double max)
    {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(_engine);
    }

    void RandomGenerator::reseed(unsigned int seed)
    {
        _engine.seed(seed);
    }
}
