//
// Created by Michael Rosado on 8/6/26.
//

#ifndef ASTEROID_H
#define ASTEROID_H
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Asteroid : public sf::Transformable{
private:
    sf::CircleShape shape;
    float asteroidSpeed;
    sf::Vector2f direction;
    sf::RectangleShape debugBox;

public:
    Asteroid();
    ~Asteroid();

    void move(float deltaTime);

    sf::CircleShape& getShape();
    void draw(sf::RenderWindow& window);
};
#endif //ASTEROID_H
