#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <cmath>

struct Cat
{
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f scale;
};

struct Laser
{
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f scale;
};

void init(Cat &cat, Laser &laser)
{
    cat.texture.loadFromFile("./cat.png");
    cat.sprite.setTexture(cat.texture);
    cat.sprite.setOrigin(cat.texture.getSize().x / 2, cat.texture.getSize().y / 2);
    cat.position = {400, 300};

    laser.texture.loadFromFile("./laser.png");
    laser.sprite.setTexture(laser.texture);
    laser.sprite.setOrigin(laser.texture.getSize().x / 2, laser.texture.getSize().y / 2);
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void update(sf::Vector2f &mousePosition, Cat &cat, Laser &laser, float deltaTime)
{
    const float maxMoveSpeed = 100.f;

    const sf::Vector2f delta = mousePosition - cat.position;
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle += float(2 * M_PI);
    }
    angle = toDegrees(angle);

    if (((angle >= 0) && (angle < 90))||((angle <=360)&&(angle>270)))
    {
        cat.sprite.setScale(1, 1);
    }
    else
    {
        cat.sprite.setScale(-1, 1);
    }

    sf::Vector2f direction = {0, 0};

    const float deltaPos = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));
    if (deltaPos != 0)
    {
        direction = {delta.x / deltaPos, delta.y / deltaPos};
    }

    float speed = std::min(deltaPos, maxMoveSpeed * deltaTime);

    cat.position += direction * speed;
    cat.sprite.setPosition(cat.position);
    cat.sprite.setScale(cat.sprite.getScale());

    laser.position = mousePosition;
    laser.sprite.setPosition(laser.position);
    laser.sprite.setScale(laser.sprite.getScale());
}

void onMouseClick(sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition, Laser &laser)
{
    laser.scale = {1, 1};
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, Laser &laser)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition, laser);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Laser &laser, Cat &cat)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(cat.sprite);
    if (cat.position != laser.position)
    {
        window.draw(laser.sprite);
    }
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cat follows laser");
    sf::Clock clock;

    Cat cat;
    Laser laser;

    sf::Vector2f mousePosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    init(cat, laser);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, laser);
        float deltaTime = clock.restart().asSeconds();
        update(mousePosition, cat, laser, deltaTime);
        redrawFrame(window, laser, cat);
    }
}
