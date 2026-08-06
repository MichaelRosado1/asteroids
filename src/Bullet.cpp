#include "Bullet.h"
#include <iostream>


Bullet::Bullet(const int id, sf::Vector2f position, sf::Vector2f direction) : bullet_id(id), shape(2.f) {
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(position);
	this->direction = direction;
}

Bullet::~Bullet() {
	std::cout << "Bullet destruction\n";
}

int Bullet::getId() {
	return bullet_id;
}

sf::CircleShape& Bullet::getShape() {
	return shape;
}

bool Bullet::goForward(float deltaTime) {
	sf::Vector2f bulletPosition = shape.getPosition();
	if (bulletPosition.x > 800 || bulletPosition.x < 0 || bulletPosition.y > 800 || bulletPosition.y < 0) {
		return false;
	}
	shape.move(direction * deltaTime * bulletSpeed);
	return true;
}