#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    float time = 0;
    const float mradius = 100;
    const float period = 4.f;
    sf::Vector2f position = {400.f, 300.f};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Polar Rose",
        sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape rose;
    rose.setPosition({400, 320});
    rose.setFillColor({205, 155, 255});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        time = time + dt;

        rose.setPointCount(pointCount);
        for (int pointNo = 0; pointNo < pointCount; ++pointNo)
        {
            float angle = float(2 * M_PI * pointNo) / float(pointCount);
            float radius = 200 * sin(6 * angle);
            sf::Vector2f point = {
                radius * std::sin(angle),
                radius * std::cos(angle)};
            rose.setPoint(pointNo, point);
        }

        float phase = time * float(2 * M_PI);
        float x = mradius * std::sin(phase / period);
        float y = mradius * std::cos(phase / period);
        sf::Vector2f offset = {x, y};

        rose.setPosition(position + offset);

        window.clear();
        window.draw(rose);
        window.display();
    }
}