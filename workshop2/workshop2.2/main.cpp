#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <cassert>

struct Ball
{
    sf::CircleShape ball{40};
    sf::Vector2f position;
    sf::Vector2f speed;
};

void redrawFrame(sf::RenderWindow &window, Ball (&balls)[5])
{
    window.clear();
    for (int i = 0; i < std::size(balls); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

sf::Vector2f getImpulse(Ball (&balls)[5])
{
    sf::Vector2f sum = {0, 0};
    for (int i = 0; i < std::size(balls); ++i)
    {
        sum += balls[i].speed;
    }
    return sum;
}

bool areFuzzyEqual(float a, float b)
{
    constexpr float tolerance = 0.01f;
    const bool areEqual = (std::abs(a - b) < tolerance);

    return areEqual;
}

bool areVectorsFuzzyEqual(sf::Vector2f a, sf::Vector2f b)
{
    const bool areXEqual = areFuzzyEqual(a.x, b.x);
    const bool areYEqual = areFuzzyEqual(a.y, b.y);
    const bool areEqual = ((areXEqual) && (areYEqual));

    return areEqual;
}

void update(Ball (&balls)[5], const float deltaTime)
{
    for (int i = 0; i < std::size(balls); ++i)
    {
        balls[i].position = balls[i].ball.getPosition();
        balls[i].position += balls[i].speed * deltaTime;

        if ((balls[i].position.x + 40 >= 800) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((balls[i].position.x - 40 < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((balls[i].position.y + 40 >= 600) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((balls[i].position.y - 40 < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }

        balls[i].ball.setPosition(balls[i].position);
    }
    
    sf::Vector2f oldImpulse = getImpulse(balls);

    for (int fi = 0; fi < std::size(balls); ++fi)
    {
        for (int si = fi + 1; si < std::size(balls); ++si)
        {
            sf::Vector2f deltaPos = balls[si].position - balls[fi].position;
            sf::Vector2f deltaSpeed = balls[si].speed - balls[fi].speed;
            float distance = std::sqrt(std::pow(deltaPos.x, 2) + std::pow(deltaPos.y, 2));
            float change = (((deltaPos.x * deltaSpeed.x) + (deltaPos.y * deltaSpeed.y)) / std::pow(distance, 2));
            if (distance <= (2 * 40))
            {
                balls[fi].speed = balls[fi].speed + change * deltaPos;
                balls[si].speed = balls[si].speed - change * deltaPos;
            }
        }
    }

    sf::Vector2f newImpulse = getImpulse(balls);
    assert(areVectorsFuzzyEqual(oldImpulse, newImpulse));
}


int main()
{

    sf::Clock clock;

    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned WINDOW_WIDTH = 800;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing balls");

    Ball balls[5];
    for (int i = 0; i < std::size(balls); ++i)
    {
        balls[i].position = {100.f * i + 100.f, 100.f * i};
        balls[i].ball.setPosition(balls[i].position);
        balls[i].ball.setFillColor(sf::Color(24 * i, 50, 150));
        balls[i].speed = {50.f * i, 120.f};
        balls[i].ball.setOrigin(40, 40);
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