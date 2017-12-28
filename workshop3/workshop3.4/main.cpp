#include "main.hpp"
#include "ship.hpp"

void redrawFrame(sf::RenderWindow &window, Ship &ship)
{
    window.clear();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        window.draw(ship.flame);
    }
    window.draw(ship.body);
    window.display();
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spaceship");
    Ship ship;
    sf::Clock clock;

    init(ship);

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window);
        update(ship, deltaTime);
        redrawFrame(window, ship);
    }
}