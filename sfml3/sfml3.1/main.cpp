#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    const float maxAngleInSecond = 15;
    float angle = atan2(delta.y, delta.x);
    const float maxRotationSpeed = maxAngleInSecond * deltaTime;
    if (angle < 0)
    {
        angle += 2 * M_PI;
    }
    float rotationAngle = toDegrees(angle) - pointer.getRotation();
    float rotationSpeed = std::abs(rotationAngle) * deltaTime;
    if (rotationAngle != 0)
    {
        if (rotationAngle > 0)
        {
            if ((rotationAngle - 180) > 0)
            {
                pointer.setRotation(pointer.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
            }
        }
        else
        {
            if ((rotationAngle + 180) < 0)
            {
                pointer.setRotation(pointer.getRotation() + std::min(rotationSpeed, maxRotationSpeed));
            }
            else
            {
                pointer.setRotation(pointer.getRotation() - std::min(rotationSpeed, maxRotationSpeed));
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    constexpr unsigned ANTIALIASING_LEVEL = 8;
    constexpr unsigned FPS = 60;

    sf::Clock clock;
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTIALIASING_LEVEL;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pointer follows mouse", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);
    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, deltaTime);
        redrawFrame(window, pointer);
    }
}