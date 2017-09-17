#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({100, 400}), "Traffic light");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({380, 120});
    shape1.setRotation(90);
    shape1.setPosition({130, 10});
    shape1.setFillColor(sf::Color(0xF0, 0xF0, 0xF0));
    window.draw(shape1);

    sf::CircleShape shape2(50);
    shape2.setPosition({20, 20});
    shape2.setFillColor(sf::Color(0x00, 0xFF, 0x00));
    window.draw(shape2);

    sf::CircleShape shape3(50);
    shape3.setPosition({20, 140});
    shape3.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    window.draw(shape3);

    sf::CircleShape shape4(50);
    shape4.setPosition({20, 260});
    shape4.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    window.draw(shape4);

    window.display();

    sf::sleep(sf::seconds(5));
}