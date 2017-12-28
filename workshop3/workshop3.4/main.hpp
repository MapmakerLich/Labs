#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <conio.h>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr float MAX_ROTATION_SPEED = 0.02;
constexpr float ENGINE_POWER = 1000.f;
constexpr float AIR_STOPPER_MULTIPILER = 0.001;

struct Ship
{
    sf::ConvexShape body;
    sf::ConvexShape flame;
    sf::Vector2f position;
    sf::Vector2f speed;
    float speedAbsolute;
};