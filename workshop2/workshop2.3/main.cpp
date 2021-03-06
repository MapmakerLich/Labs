#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <random>
#include <cassert>

constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned BALL_SIZE = 40;

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f position;
    sf::Vector2f speed;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

float getRandomFloat(PRNG &generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);

    std::uniform_real_distribution<float> distribution(minValue, maxValue);

    return distribution(generator.engine);
}

void redrawFrame(sf::RenderWindow &window, Ball (&balls)[5])
{
    window.clear();
    for (int i = 0; i < std::size(balls); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

void update(Ball (&balls)[5], const float deltaTime)
{
    for (int i = 0; i < std::size(balls); ++i)
    {
        balls[i].position = balls[i].ball.getPosition();
        balls[i].position += balls[i].speed * deltaTime;

        if ((balls[i].position.x + BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((balls[i].position.x - BALL_SIZE < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((balls[i].position.y + BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((balls[i].position.y - BALL_SIZE < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        balls[i].ball.setPosition(balls[i].position);
    }

    for (int fi = 0; fi < std::size(balls); ++fi)
    {
        for (int si = fi + 1; si < std::size(balls); ++si)
        {
            sf::Vector2f deltaPos = balls[si].position - balls[fi].position;
            sf::Vector2f deltaSpeed = balls[si].speed - balls[fi].speed;
            float distance = std::sqrt(std::pow(deltaPos.x, 2) + std::pow(deltaPos.y, 2));
            float change = (((deltaPos.x * deltaSpeed.x) + (deltaPos.y * deltaSpeed.y)) / std::pow(distance, 2));
            if (distance <= (2 * BALL_SIZE))
            {
                balls[fi].speed = balls[fi].speed + change * deltaPos;
                balls[si].speed = balls[si].speed - change * deltaPos;
            }
        }
    }
}

int main()
{
    PRNG generator;
    sf::Clock clock;

    initGenerator(generator);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing balls");

    Ball balls[5];
    for (int i = 0; i < std::size(balls); ++i)
    {
        balls[i].position = {100.f * i + 100.f, 100.f * i};
        balls[i].ball.setPosition(balls[i].position);
        balls[i].ball.setFillColor(sf::Color(24 * i, 50, 150));
        balls[i].speed = {getRandomFloat(generator, -200.f, 200.f), getRandomFloat(generator, -200.f, 200.f)};
        balls[i].ball.setOrigin(BALL_SIZE, BALL_SIZE);
        balls[i].ball.setRadius(BALL_SIZE);
    }

    while (window.isOpen())
    {
        sf::Event event;
        const float deltaTime = clock.restart().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        update(balls, deltaTime);
        redrawFrame(window, balls);
    }
}
