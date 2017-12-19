#pragma once

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
constexpr float VIEW_MOVE_SPEED = 0.1;
constexpr float G = 6.67;
constexpr float K = 9.0;

struct PRNG
{
    std::mt19937 engine;
};

struct Ball
{
    sf::CircleShape ball;
    sf::Vector2f position;
    sf::Vector2f speed;
    float lifetime;
    sf::Vector2f gravityPower;
    sf::Vector2f coulombPower;
    int charge;
};

void createBall(sf::CircleShape &shape, sf::Color (&pattern)[8], PRNG &generator);

void init(std::vector<Ball> &balls, PRNG &generator, sf::Color (&pattern)[8]);

void removeDeathBalls(std::vector<Ball> &balls);

void checkEdge(Ball &ball);

void edgeStrike(std::vector<Ball> &balls, const float deltaTime);

void ballStrike(std::vector<Ball> &balls);

void update(std::vector<Ball> &balls, const float deltaTime);

void checkCreation(std::vector<Ball> &balls, sf::Vector2f &mousePosition, bool &correctCreation);

void onMouseClick(const sf::Event::MouseButtonEvent &event, std::vector<Ball> &balls, sf::Color (&pattern)[8], PRNG &generator, sf::RenderWindow &window);

void initPattern(sf::Color (&pattern)[8]);

void initView(sf::View &view);

void unitedInit(sf::Color (&pattern)[8], PRNG &generator, std::vector<Ball> &balls, sf::View &view);