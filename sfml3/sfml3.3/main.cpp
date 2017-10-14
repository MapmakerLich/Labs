#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <iostream>
struct Eye
{
    sf::ConvexShape white;
    sf::ConvexShape black;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEucledian(float x, float y, float angle)
{
    return {x * std::cos(angle), y * std::sin(angle)};
}

float checkCursorInEye(const sf::Vector2f &mousePosition, const sf::Vector2f &position, float x, float y)
{
    return ((std::pow((mousePosition.x - position.x) / x, 2)) + std::pow((mousePosition.y - position.y) / y, 2));
}

void updateLeftEye(Eye &leftEye)
{
    const sf::Vector2f rotationRadius = {30.f, 50.f};

    const sf::Vector2f whiteLeftEyeOffset = toEucledian(rotationRadius.x, rotationRadius.y, leftEye.rotation);
    leftEye.black.setPosition(leftEye.position + whiteLeftEyeOffset);
}
void updateRightEye(Eye &rightEye)
{
    const sf::Vector2f rotationRadius = {30.f, 50.f};

    const sf::Vector2f whiteRightEyeOffset = toEucledian(rotationRadius.x, rotationRadius.y, rightEye.rotation);
    rightEye.black.setPosition(rightEye.position + whiteRightEyeOffset);
}

void initEye(Eye &leftEye, Eye &rightEye)
{
    sf::Vector2f whiteRadius = {50.f, 100.f};
    sf::Vector2f blackRadius = {10.f, 20.f};
    constexpr int pointCount = 200;

    leftEye.position = {300, 300};
    rightEye.position = {500, 300};

    leftEye.white.setFillColor(sf::Color(255, 255, 255));
    leftEye.white.setPointCount(pointCount);
    leftEye.white.setPosition(leftEye.position);
    rightEye.white.setFillColor(sf::Color(255, 255, 255));
    rightEye.white.setPointCount(pointCount);
    rightEye.white.setPosition(rightEye.position);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            whiteRadius.x * std::sin(angle),
            whiteRadius.y * std::cos(angle)};
        leftEye.white.setPoint(pointNo, point);
        rightEye.white.setPoint(pointNo, point);
    }

    leftEye.black.setPointCount(pointCount);
    leftEye.black.setFillColor(sf::Color(0, 0, 0));
    rightEye.black.setPointCount(pointCount);
    rightEye.black.setFillColor(sf::Color(0, 0, 0));
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            blackRadius.x * std::sin(angle),
            blackRadius.y * std::cos(angle)};
        leftEye.black.setPoint(pointNo, point);
        rightEye.black.setPoint(pointNo, point);
    }
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

void update(const sf::Vector2f &mousePosition, Eye &leftEye, Eye &rightEye)
{
    const sf::Vector2f whiteRadius = {10.f, 30.f};
    const sf::Vector2f blackRadius = {4.f, 10.f};
    const float isInLeftEye = checkCursorInEye(mousePosition, leftEye.white.getPosition(), whiteRadius.x, whiteRadius.y);
    const float isInRightEye = checkCursorInEye(mousePosition, rightEye.white.getPosition(), whiteRadius.x, whiteRadius.y);

    if (isInLeftEye > 1.f)
    {
        const sf::Vector2f leftEyeDelta = mousePosition - leftEye.position;
        leftEye.rotation = atan2(leftEyeDelta.y, leftEyeDelta.x);
        updateLeftEye(leftEye);
    }
    else
    {
        leftEye.black.setPosition(mousePosition);
    }
    if (isInRightEye > 1.f)
    {
        const sf::Vector2f rightEyeDelta = mousePosition - rightEye.position;
        rightEye.rotation = atan2(rightEyeDelta.y, rightEyeDelta.x);
        updateRightEye(rightEye);
    }
    else
    {
        rightEye.black.setPosition(mousePosition);
    }
}

void redrawFrame(sf::RenderWindow &window, Eye &leftEye, Eye &rightEye)
{
    window.clear();
    window.draw(leftEye.white);
    window.draw(leftEye.black);
    window.draw(rightEye.white);
    window.draw(rightEye.black);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye leftEye;
    Eye rightEye;
    sf::Vector2f mousePosition;

    initEye(leftEye, rightEye);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}