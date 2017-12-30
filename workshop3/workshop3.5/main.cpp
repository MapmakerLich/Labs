#include "watch.hpp"

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

void redrawFrame(sf::RenderWindow &window, Watch &clock)
{
    window.clear(sf::Color::White);
    window.draw(clock.clockCircle);
    window.draw(clock.clockBrandSprite);
    for (int i = 0; i < 60; i++)
    {
        window.draw(clock.dot[i]);
    }
    window.draw(clock.hourHand);
    window.draw(clock.minuteHand);
    window.draw(clock.secondsHand);
    window.draw(clock.centerCircle);
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Analog watch", sf::Style::Close, settings);
    Watch clock;
    init(clock, window);
    while (window.isOpen())
    {
        pollEvents(window);
        std::time_t currentTime = std::time(NULL);
        struct tm *ptm = localtime(&currentTime);
        clock.hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
        clock.minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
        clock.secondsHand.setRotation(ptm->tm_sec * 6);
        redrawFrame(window, clock);
    }
}