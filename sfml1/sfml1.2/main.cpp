#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Initials");

    window.clear();

    sf::RectangleShape shape1;
    shape1.setSize({20, 350});
    shape1.setRotation(15);
    shape1.setPosition({100, 120});
    shape1.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({20, 350});
    shape2.setRotation(-15);
    shape2.setPosition({100, 120});
    shape2.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({20, 100});
    shape3.setRotation(90);
    shape3.setPosition({160, 300});
    shape3.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({20, 350});
    shape4.setRotation(0);
    shape4.setPosition({230, 120});
    shape4.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({20, 350});
    shape5.setRotation(-15);
    shape5.setPosition({230, 120});
    shape5.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({20, 350});
    shape6.setRotation(15);
    shape6.setPosition({410, 120});
    shape6.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({20, 350});
    shape7.setRotation(0);
    shape7.setPosition({420, 120});
    shape7.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({20, 350});
    shape8.setRotation(-15);
    shape8.setPosition({500, 120});
    shape8.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({20, 350});
    shape9.setRotation(15);
    shape9.setPosition({680, 120});
    shape9.setFillColor(sf::Color(0x0, 0x0, 0xFF));
    window.draw(shape9);

    window.display();

    sf::sleep(sf::seconds(5));
}