#include "watch.hpp"

void initHands(Watch &clock, sf::Vector2f windowCenter)
{
    clock.hourHand.setSize({5, 180});
    clock.minuteHand.setSize({3, 240});
    clock.secondsHand.setSize({2, 250});
    clock.hourHand.setFillColor(sf::Color::Black);
    clock.minuteHand.setFillColor(sf::Color::Black);
    clock.secondsHand.setFillColor(sf::Color::Red);
    clock.hourHand.setOrigin(clock.hourHand.getGlobalBounds().width / 2, clock.hourHand.getGlobalBounds().height - 25);
    clock.minuteHand.setOrigin(clock.minuteHand.getGlobalBounds().width / 2, clock.minuteHand.getGlobalBounds().height - 25);
    clock.secondsHand.setOrigin(clock.secondsHand.getGlobalBounds().width / 2, clock.secondsHand.getGlobalBounds().height - 25);
    clock.hourHand.setPosition(windowCenter);
    clock.minuteHand.setPosition(windowCenter);
    clock.secondsHand.setPosition(windowCenter);
}

void initDots(Watch &clock, sf::RenderWindow &window)
{
    int y;
    int x;
    float angle = 0.0;
    for (int i = 0; i < 60; i++)
    {
        x = (CLOCK_CIRCLE_SIZE - 10) * cos(angle);
        y = (CLOCK_CIRCLE_SIZE - 10) * sin(angle);
        if (i % 5 == 0)
        {
            clock.dot[i] = sf::CircleShape(5);
        }
        else
        {
            clock.dot[i] = sf::CircleShape(2);
        }
        clock.dot[i].setFillColor(sf::Color::Black);
        clock.dot[i].setOrigin(clock.dot[i].getGlobalBounds().width / 2, clock.dot[i].getGlobalBounds().height / 2);
        clock.dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);
        angle = angle + ((2 * float(M_PI)) / 60);
    }
}

void initCircles(Watch &clock, sf::RenderWindow &window, sf::Vector2f windowCenter)
{
    clock.clockCircle.setRadius(CLOCK_CIRCLE_SIZE);
    clock.clockCircle.setPointCount(100);
    clock.clockCircle.setOutlineThickness(CLOCK_CIRCLE_THICKNESS);
    clock.clockCircle.setOutlineColor(sf::Color::Black);
    clock.clockCircle.setOrigin(clock.clockCircle.getGlobalBounds().width / 2, clock.clockCircle.getGlobalBounds().height / 2);
    clock.clockCircle.setPosition(window.getSize().x / 2 + CLOCK_CIRCLE_THICKNESS, window.getSize().y / 2 + CLOCK_CIRCLE_THICKNESS);
    clock.centerCircle.setRadius(10);
    clock.centerCircle.setPointCount(100);
    clock.centerCircle.setFillColor(sf::Color::Red);
    clock.centerCircle.setOrigin(clock.centerCircle.getGlobalBounds().width / 2, clock.centerCircle.getGlobalBounds().height / 2);
    clock.centerCircle.setPosition(windowCenter);
}

void initOthers(Watch &clock, sf::RenderWindow &window)
{
    clock.clockBrand;
    clock.clockBrand.loadFromFile("resources/clock-brand.png");
    clock.clockBrandSprite;
    clock.clockBrandSprite.setTexture(clock.clockBrand);
    clock.clockBrandSprite.setOrigin(clock.clockBrandSprite.getTextureRect().left + clock.clockBrandSprite.getTextureRect().width / 2.0f, clock.clockBrandSprite.getTextureRect().top + clock.clockBrandSprite.getTextureRect().height / 2.0f);
    clock.clockBrandSprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    clock.clockImage;
    clock.clockImage.loadFromFile("resources/clock-image.png");
    clock.clockCircle.setTexture(&clock.clockImage);
    clock.clockCircle.setTextureRect(sf::IntRect(40, 0, 500, 500));
}

void init(Watch &clock, sf::RenderWindow &window)
{
    sf::Vector2f windowCenter = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    initHands(clock, windowCenter);
    initDots(clock, window);
    initCircles(clock, window, windowCenter);
    initOthers(clock, window);
}