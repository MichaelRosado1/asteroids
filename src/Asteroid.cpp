//
// Created by Michael Rosado on 8/6/26.
//
#include "Asteroid.h"
Asteroid::Asteroid() {
    float asteroidSize = static_cast<float>(std::rand() % (50 - 30 + 1));
    shape.setRadius(asteroidSize);
    shape.setPointCount(4);
    shape.setFillColor(sf::Color::Green);
    asteroidSpeed = static_cast<float>(std::rand() % (100 - 50 + 1));
    angle = static_cast<float>(std::rand() % (360 - 45 + 1));
    direction  = sf::Vector2f(std::cos(angle), std::sin(angle));

    shape.setPosition(sf::Vector2f((std::rand() % (800 - 0 + 1)), (std::rand() % (600 - 0 + 1))));

    sf::FloatRect bounds = shape.getGlobalBounds();
    debugBox.setPosition(bounds.position);
    debugBox.setSize(bounds.size);
    debugBox.setOutlineColor(sf::Color::Red);
    debugBox.setOutlineThickness(1);
}

Asteroid::~Asteroid() {

}

void Asteroid::move(float deltaTime) {
    // check if out of bounds
    sf::Vector2f asteroidPosition = shape.getPosition();
    if (asteroidPosition.x > 800 || asteroidPosition.x < 0 || asteroidPosition.y > 600 || asteroidPosition.y < 0) {
       direction = -direction;
    }
    shape.move(direction * asteroidSpeed * deltaTime);
    debugBox.move(direction * asteroidSpeed * deltaTime);
}

sf::CircleShape& Asteroid::getShape() {
    return shape;
}

void Asteroid::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(debugBox);
}
