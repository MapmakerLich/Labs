#include "ball.hpp"
#include "numeric.hpp"

void createBall(sf::CircleShape &shape, sf::Color (&pattern)[8], PRNG &generator)
{
    shape.setFillColor(randomColor(pattern, generator));
    shape.setOrigin(BALL_SIZE, BALL_SIZE);
    shape.setRadius(BALL_SIZE);
}

void init(std::vector<Ball> &balls, PRNG &generator, sf::Color (&pattern)[8])
{
    for (int i = 0; i < balls.size(); ++i)
    {
        balls[i].position = {100.f + 100.f * i, 100.f + 100.f * i};
        balls[i].speed = {randomFloat(generator, -200.f, 200.f), randomFloat(generator, -200.f, 200.f)};
        balls[i].ball.setPosition(balls[i].position);
        createBall(balls[i].ball, pattern, generator);
        balls[i].lifetime = 0;
        balls[i].charge = random(generator, -1, 1);
        if (balls[i].charge = 0)
        {
            balls[i].charge = -1;
        }
    }
}

void removeDeathBalls(std::vector<Ball> &balls)
{
    auto removeBalls = [&](Ball ball) -> bool {
        return ball.lifetime > MAX_LIFETIME;
    };
    balls.erase(std::remove_if(balls.begin(), balls.end(), removeBalls), balls.end());
}

void checkEdge(Ball &ball)
{
    if ((ball.position.x + BALL_SIZE >= 3 * WINDOW_WIDTH) && (ball.speed.x > 0))
    {
        ball.speed.x = -ball.speed.x;
    }
    if ((ball.position.x - BALL_SIZE < 0) && (ball.speed.x < 0))
    {
        ball.speed.x = -ball.speed.x;
    }
    if ((ball.position.y + BALL_SIZE >= 3 * WINDOW_HEIGHT) && (ball.speed.y > 0))
    {
        ball.speed.y = -ball.speed.y;
    }
    if ((ball.position.y - BALL_SIZE < 0) && (ball.speed.y < 0))
    {
        ball.speed.y = -ball.speed.y;
    }
}

void edgeStrike(std::vector<Ball> &balls, const float deltaTime)
{
    for (int i = 0; i < balls.size(); ++i)
    {
        balls[i].position = balls[i].ball.getPosition();
        balls[i].position += balls[i].speed * deltaTime;
        balls[i].lifetime += deltaTime;
        balls[i].speed += (balls[i].gravityPower + balls[i].coulombPower) * deltaTime;

        checkEdge(balls[i]);

        balls[i].ball.setPosition(balls[i].position);
    }
}

void ballStrike(std::vector<Ball> &balls)
{
    for (int fi = 0; fi < balls.size(); ++fi)
    {
        for (int si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f deltaPos = balls[si].position - balls[fi].position;
            sf::Vector2f deltaSpeed = balls[si].speed - balls[fi].speed;
            float distance = std::sqrt(std::pow(deltaPos.x, 2) + std::pow(deltaPos.y, 2));
            float change = (((deltaPos.x * deltaSpeed.x) + (deltaPos.y * deltaSpeed.y)) / std::pow(distance, 2));
            if (distance <= (2 * BALL_SIZE))
            {
                balls[fi].speed = balls[fi].speed + change * deltaPos;
                balls[si].speed = balls[si].speed - change * deltaPos;
            }
        }
    }
}

void update(std::vector<Ball> &balls, const float deltaTime)
{
    gravityPower(balls);
    edgeStrike(balls, deltaTime);

    float oldEnergy = getEnergy(balls);
    sf::Vector2f oldImpulse = getImpulse(balls);

    ballStrike(balls);

    float newEnergy = getEnergy(balls);
    sf::Vector2f newImpulse = getImpulse(balls);

    assert(areFuzzyEqual(newEnergy, oldEnergy));
    assert(areVectorsFuzzyEqual(newImpulse, oldImpulse));

    removeDeathBalls(balls);
}

void checkCreation(std::vector<Ball> &balls, sf::Vector2f &mousePosition, bool &correctCreation)
{
    for (int i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f ballPosition = balls[i].ball.getPosition();
        sf::Vector2f delta = mousePosition - ballPosition;
        float length = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));
        if ((length <= 2 * BALL_SIZE) || (mousePosition.x <= BALL_SIZE) || (mousePosition.y <= BALL_SIZE) || (mousePosition.x >= 3 * WINDOW_WIDTH - BALL_SIZE) || (mousePosition.y >= 3 * WINDOW_HEIGHT - BALL_SIZE))
        {
            correctCreation = false;
        }
    }
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, std::vector<Ball> &balls, sf::Color (&pattern)[8], PRNG &generator, sf::RenderWindow &window)
{
    bool correctCreation = true;
    sf::Vector2f mousePosition = window.mapPixelToCoords({int(event.x), int(event.y)});
    checkCreation(balls, mousePosition, correctCreation);
    if (correctCreation)
    {
        Ball newBall;
        newBall.speed = {randomFloat(generator, -200.f, 200.f), randomFloat(generator, -200.f, 200.f)};
        createBall(newBall.ball, pattern, generator);
        newBall.ball.setPosition(mousePosition);
        newBall.lifetime = 0;
        newBall.charge = random(generator, -1, 1);
        if (newBall.charge = 0)
        {
            newBall.charge = 1;
        }
        balls.push_back(newBall);
    }
}

void initPattern(sf::Color (&pattern)[8])
{
    pattern[0] = {0, 102, 51};
    pattern[1] = {102, 0, 51};
    pattern[2] = {0, 51, 102};
    pattern[3] = {102, 51, 0};
    pattern[4] = {51, 102, 0};
    pattern[5] = {51, 0, 102};
    pattern[6] = {102, 0, 0};
    pattern[7] = {0, 51, 0};
}

void initView(sf::View &view)
{
    view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
}

void unitedInit(sf::Color (&pattern)[8], PRNG &generator, std::vector<Ball> &balls, sf::View &view)
{
    initGenerator(generator);
    initPattern(pattern);
    init(balls, generator, pattern);
    initView(view);
}