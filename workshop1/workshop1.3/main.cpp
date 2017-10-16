#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cat");

    sf::Texture texture;
    texture.loadFromFile("./workshop1.3/cat.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

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

        window.clear(sf::Color(255, 255, 255));
        window.draw(sprite);
        window.display();
    }
}