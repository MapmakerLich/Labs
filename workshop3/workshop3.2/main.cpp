#include "ball.hpp"
#include "numeric.hpp"

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls, sf::View &view)
{
    window.clear();
    window.setView(view);
    for (int i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].ball);
    }
    window.display();
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &balls, sf::Color (&pattern)[8], PRNG &generator)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, balls, pattern, generator, window);
            break;
        default:
            break;
        }
    }
}

void updateView(sf::View &view)
{
    sf::Vector2f center = view.getCenter();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (center.x >= (WINDOW_WIDTH / 2))
        {
            center.x = center.x - VIEW_MOVE_SPEED;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (center.x <= (2.5 * WINDOW_WIDTH))
        {
            center.x = center.x + VIEW_MOVE_SPEED;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (center.y >= (WINDOW_HEIGHT / 2))
        {
            center.y = center.y - VIEW_MOVE_SPEED;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (center.y <= (2.5 * WINDOW_HEIGHT))
        {
            center.y = center.y + VIEW_MOVE_SPEED;
        }
    }
    view.setCenter(center);
}

int main()
{
    PRNG generator;
    sf::Clock clock;
    std::vector<Ball> balls(5, Ball());
    sf::Color pattern[8];
    unitedInit(pattern, generator, balls, view);
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bouncing balls");
    sf::View view;

    while (window.isOpen())
    {
        const float dtPhysics = clock.restart().asSeconds() / MAX_INTERVAL_NUMBER;
        pollEvents(window, balls, pattern, generator);
        for (int i = 0; i < MAX_INTERVAL_NUMBER; ++i)
        {
            update(balls, dtPhysics);
        }
        updateView(view);
        redrawFrame(window, balls, view);
    }
}