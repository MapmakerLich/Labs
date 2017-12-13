#include "main.hpp"

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

void update(float deltaTime, Initials &initials)
{
    initials.updatePos(deltaTime);
}

void redrawFrame(Initials &initials, sf::RenderWindow &window)
{
    window.clear();
    window.draw(initials);
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "Initals in ball", sf::Style::Default, settings);

    sf::Clock clock;

    const sf::Vector2f position = {WINDOW_WIDTH / 2, WINDOW_HEIGHT - (BALL_SIZE + BALL_OUTLINE)};
    Initials initials(position);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        pollEvents(window);
        update(deltaTime, initials);
        redrawFrame(initials, window);
    }
}