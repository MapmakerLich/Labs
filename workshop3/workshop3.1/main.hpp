#pragma once

#include "ball.hpp"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_SIZE = 100;
constexpr unsigned BALL_OUTLINE = 4;
constexpr float GRAVITY = 9.8;
const unsigned SPEED = 80;

void pollEvents(sf::RenderWindow &window);

void redrawFrame(sf::RenderWindow &window, Initials &initials);

void createWindow(sf::RenderWindow &window);

void update(float deltaTime, Initials &initials);
