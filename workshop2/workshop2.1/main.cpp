#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>

struct Ball
{
    sf::CircleShape ball{40};
    sf::Vector2f position;
    sf::Vector2f speed;
};

void redrawFrame(sf::RenderWindow& window, Ball (&balls)[5])
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

        if ((balls[i].position.x + 80 >= 800)&&(balls[i].speed.x>0))
        {
            balls[i].speed.x = - balls[i].speed.x;
        }
        if ((balls[i].position.x < 0)&&(balls[i].speed.x<0))
        {
            balls[i].speed.x = - balls[i].speed.x;
        }
        if ((balls[i].position.y + 80 >= 600)&&(balls[i].speed.y>0))
        {
            balls[i].speed.y = - balls[i].speed.y;
        }
        if ((balls[i].position.y < 0)&&(balls[i].speed.y<0))
        {
            balls[i].speed.y = - balls[i].speed.y;
        }

        balls[i].ball.setPosition(balls[i].position);
    }
}

int main()
{

    sf::Clock clock;
    
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned WINDOW_WIDTH = 800;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Balls striking edge");
    
    Ball balls[5];
    for (int i = 0; i<std::size(balls); ++i)
    {
        balls[i].position = {100.f * i+40.f, 100.f};
        balls[i].ball.setPosition(balls[i].position);
        balls[i].ball.setFillColor(sf::Color(24*i, 50, 150));
        balls[i].speed = {24.f*i, 120.f};
    }

    while (window.isOpen())
    {
        sf::Event event;
        const float deltaTime = clock.restart().asSeconds();
        while(window.pollEvent(event))
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