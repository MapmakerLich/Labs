#pragma once

#include "ball.hpp"

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>
#include <random>
#include <cassert>

constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned BALL_SIZE = 40;
constexpr float MAX_LIFETIME = 10.0;
constexpr float MAX_INTERVAL_NUMBER = 10.0;

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f position;
    sf::Vector2f speed;
    float lifetime;
};

struct PRNG
{
    std::mt19937 engine;
};