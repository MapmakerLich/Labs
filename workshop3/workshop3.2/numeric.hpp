#pragma once

#include "ball.hpp"

float randomFloat(PRNG &generator, float minValue, float maxValue);

int random(PRNG &generator, int minValue, int maxValue);

sf::Vector2f getImpulse(std::vector<Ball> &balls);

float getEnergy(std::vector<Ball> &balls);

sf::Color randomColor(sf::Color (&pattern)[8], PRNG &generator);

void initGenerator(PRNG &generator);

bool areCloseAbsolute(float a, float b, float tolerance);

bool areCloseRelative(float a, float b, float tolerance);

bool areFuzzyEqual(float a, float b);

bool areVectorsFuzzyEqual(sf::Vector2f a, sf::Vector2f b);

void checkEdge(Ball &ball);

void gravityPower(std::vector<Ball> &balls);

void coulombPower(std::vector<Ball> &balls);