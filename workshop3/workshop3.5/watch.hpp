#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned CLOCK_CIRCLE_SIZE = 250;
constexpr unsigned CLOCK_CIRCLE_THICKNESS = 2;

struct Watch
{
    sf::CircleShape dot[60];
    sf::CircleShape clockCircle;
    sf::CircleShape centerCircle;
    sf::RectangleShape hourHand;
    sf::RectangleShape minuteHand;
    sf::RectangleShape secondsHand;
    sf::Texture clockBrand;
    sf::Sprite clockBrandSprite;
    sf::Texture clockImage;
};

void initHands(Watch &clock, sf::Vector2f windowCenter);

void initDots(Watch &clock, sf::RenderWindow &window);

void initCircles(Watch &clock, sf::RenderWindow &window, sf::Vector2f windowCenter);

void initOthers(Watch &clock, sf::RenderWindow &window);

void init(Watch &clock, sf::RenderWindow &window);
