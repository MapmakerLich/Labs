#include "numeric.hpp"

float randomFloat(PRNG &generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);

    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    return distribution(generator.engine);
}

unsigned random(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);

    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    return distribution(generator.engine);
}

sf::Vector2f getImpulse(std::vector<Ball> &balls)
{
    sf::Vector2f sum = {0, 0};
    for (int i = 0; i < balls.size(); ++i)
    {
        sum += balls[i].speed;
    }
    return sum;
}

float getEnergy(std::vector<Ball> &balls)
{
    float full = 0.f;
    for (int i = 0; i < balls.size(); ++i)
    {
        full += std::pow(balls[i].speed.x, 2) + std::pow(balls[i].speed.y, 2);
    }
    return full;
}

sf::Color randomColor(sf::Color (&pattern)[8], PRNG &generator)
{
    const unsigned firstIndex = random(generator, 0, 7);
    const unsigned secondIndex = random(generator, 0, 7);

    sf::Color firstColor = pattern[firstIndex];
    sf::Color secondColor = pattern[secondIndex];

    sf::Color finalColor;
    finalColor.r = sf::Uint8((firstColor.r + secondColor.r) / 2);
    finalColor.g = sf::Uint8((firstColor.g + secondColor.g) / 2);
    finalColor.b = sf::Uint8((firstColor.b + secondColor.b) / 2);

    return finalColor;
}

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

bool areCloseAbsolute(float a, float b, float tolerance)
{
    return std::abs(a - b) < tolerance;
}

bool areCloseRelative(float a, float b, float tolerance)
{
    return std::abs((a - b) / b) < tolerance;
}

bool areFuzzyEqual(float a, float b)
{
    constexpr float tolerance = 0.001f;
    if (std::abs(b) > 1.f)
    {
        return areCloseRelative(a, b, tolerance);
    }
    return areCloseAbsolute(a, b, tolerance);
}

bool areVectorsFuzzyEqual(sf::Vector2f a, sf::Vector2f b)
{
    bool areXEqual = areFuzzyEqual(a.x, b.x);
    bool areYEqual = areFuzzyEqual(a.y, b.y);
    return (areXEqual && areYEqual);
}

void gravityPower(std::vector<Ball> &balls)
{
    for (int fi = 0; fi < balls.size(); ++fi)
    {
        balls[fi].power = {0, 0};
        for (int si = 0; si < balls.size(); ++si)
        {
            if (si != fi)
            {
                sf::Vector2f delta = balls[fi].position - balls[si].position;
                float deltaLength = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));
                balls[fi].power += delta * G * float(std::pow(10, -11)) / float(std::pow(deltaLength, 3));
            }
        }
    }
}