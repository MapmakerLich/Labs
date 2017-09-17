#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "House");

    window.clear();

    sf::RectangleShape wall;
    wall.setSize({400, 600});
    wall.setRotation(90);
    wall.setPosition(700, 480);
    wall.setFillColor(sf::Color({0x8B, 0x45, 0x13}));
    window.draw(wall);

    sf::RectangleShape door;
    door.setSize({100, 320});
    door.setRotation(0);
    door.setPosition(180, 560);
    door.setFillColor(sf::Color({0x2F, 0x4F, 0x4F}));
    window.draw(door);

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color({0x80, 0x00, 0x00}));
    roof.setPosition({90, 360});
    roof.setPointCount(4);
    roof.setPoint(0, {+100, 0});
    roof.setPoint(1, {+520, 0});
    roof.setPoint(2, {+680, 120});
    roof.setPoint(3, {-60, 120});
    window.draw(roof);

    sf::RectangleShape tube1;
    tube1.setSize({50, 100});
    tube1.setRotation(0);
    tube1.setPosition({500, 330});
    tube1.setFillColor(sf::Color({128, 128, 128}));
    window.draw(tube1);

    sf::CircleShape smoke1(15);
    smoke1.setPosition(525, 285);
    smoke1.setFillColor(sf::Color({169, 169, 169}));
    window.draw(smoke1);

    sf::RectangleShape tube2;
    tube2.setSize({80, 40});
    tube2.setRotation(0);
    tube2.setPosition({484, 310});
    tube2.setFillColor(sf::Color({128, 128, 128}));
    window.draw(tube2);

    sf::CircleShape smoke2(20);
    smoke2.setPosition(535, 255);
    smoke2.setFillColor(sf::Color({169, 169, 169}));
    window.draw(smoke2);

    sf::CircleShape smoke3(25);
    smoke3.setPosition(545, 220);
    smoke3.setFillColor(sf::Color({169, 169, 169}));
    window.draw(smoke3);

    sf::CircleShape smoke4(30);
    smoke4.setPosition(565, 185);
    smoke4.setFillColor(sf::Color({169, 169, 169}));
    window.draw(smoke4);

    window.display();

    sf::sleep(sf::seconds(5));
}