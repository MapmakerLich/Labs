#include "main.hpp"
#include "ship.hpp"

void initConvex(sf::ConvexShape &shape)
{
    shape.setFillColor(sf::Color::Black);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    shape.setPointCount(4);
}

void init(Ship &ship)
{
    initConvex(ship.body);
    ship.body.setPoint(0, {30, 0});
    ship.body.setPoint(1, {-30, -10});
    ship.body.setPoint(2, {-20, 0});
    ship.body.setPoint(3, {-30, 10});

    initConvex(ship.flame);
    ship.flame.setPoint(0, {10, 0});
    ship.flame.setPoint(1, {-10, 5});
    ship.flame.setPoint(2, {-30, 0});
    ship.flame.setPoint(3, {-10, -5});

    ship.speed = {0, 0};
}
void rotate(Ship &ship)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        ship.body.setRotation(ship.body.getRotation() + MAX_ROTATION_SPEED);
        ship.flame.setRotation(ship.flame.getRotation() + MAX_ROTATION_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        ship.body.setRotation(ship.body.getRotation() - MAX_ROTATION_SPEED);
        ship.flame.setRotation(ship.flame.getRotation() - MAX_ROTATION_SPEED);
    }
}

void update(Ship &ship, float deltaTime)
{
    ship.position = ship.body.getPosition();
    rotate(ship);
    float angle = ship.body.getRotation() * float(M_PI) / 180;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        ship.speedAbsolute = std::pow(ship.speed.x, 2) + std::pow(ship.speed.y, 2);
        sf::Vector2f airResistance = -ship.speedAbsolute * ship.speed * AIR_STOPPER_MULTIPILER;
        sf::Vector2f engineAcceleration = {ENGINE_POWER * std::cos(angle), ENGINE_POWER * std::sin(angle)};
        ship.speed += (airResistance + engineAcceleration) * deltaTime;
    }
    ship.position += ship.speed * deltaTime;
    ship.body.setPosition(ship.position);
    ship.flame.setPosition(ship.position);
}