#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;
    float speedX = 100.f;
    float amplitudeY = 80.f;
    float time = 0;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave striking ball");
    sf::Clock clock;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(255, 255, 255));

    sf::Vector2f position = {10, 350};
    float x = 10;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        constexpr float periodY = 2;

        const float dt = clock.restart().asSeconds();
        time += dt;
        const float wavePhase = time * float(2 * M_PI);
        x += speedX * dt;
        float y = amplitudeY * std::sin(wavePhase / periodY);
        sf::Vector2f offset = {x, y};

        if ((position.x + x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((position.x + x <= 0) && (speedX < 0))
        {
            speedX = -speedX;
            position.x = (position.x + x) * 2.f;
        }

        ball.setPosition(position + offset);
        sf::Vector2f position = ball.getPosition();

        window.clear();
        window.draw(ball);
        window.display();
    }
}