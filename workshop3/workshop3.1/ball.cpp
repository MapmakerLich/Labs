#include "main.hpp"

Initials::Initials(const sf::Vector2f position)
{
    initBall(position);
    initText(position);
}

void Initials::initBall(const sf::Vector2f position)
{
    ball.setRadius(BALL_SIZE);
    ball.setPosition(position);
    ball.setOrigin(BALL_SIZE, BALL_SIZE);
    ball.setFillColor(sf::Color::Yellow);
    ball.setOutlineThickness(BALL_OUTLINE);
    ball.setOutlineColor(sf::Color::Red);
    startY = position.y;
}

void Initials::initText(const sf::Vector2f position)
{
    assert(font.loadFromFile("./resources/arial.ttf"));

    text.setFont(font);
    text.setString("AMV");
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::Black);
    const sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin({textBounds.width / 2, textBounds.height - BALL_OUTLINE});
    text.setPosition(position);
}

void Initials::updatePos(float deltaTime)
{
    time += deltaTime;
    edgeStrike();
    float nextY = startY - SPEED * time + 0.5 * GRAVITY * std::pow(time, 2);
    const sf::Vector2f nextPosition = {ball.getPosition().x, nextY};
    elements(nextPosition);
}

void Initials::elements(const sf::Vector2f nextPosition)
{
    ball.setPosition(nextPosition);
    text.setPosition(nextPosition);
}

void Initials::edgeStrike()
{
    const float currentHeight = ball.getPosition().y + BALL_SIZE + BALL_OUTLINE;
    if (currentHeight > WINDOW_HEIGHT)
    {
        time = 0;
    }
}

void Initials::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(ball, states);
    target.draw(text, states);
}