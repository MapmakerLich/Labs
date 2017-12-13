#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <cmath>
#include <cassert>

class Initials : public sf::Drawable
{
public:
  Initials(const sf::Vector2f position);

  void updatePos(float deltaTime);

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void initBall(const sf::Vector2f position);

  void initText(const sf::Vector2f position);

  void elements(const sf::Vector2f nextPosition);

  void edgeStrike();

  sf::CircleShape ball;
  sf::Text text;
  sf::Font font;

  float time = 0;
  float startY = 0;
};