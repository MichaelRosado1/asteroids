#include "Player.h"

Player::Player(const sf::Vector2f& screenCenter) : shape(sf::CircleShape(10.f, 3)) {
	shape.setOrigin(shape.getGeometricCenter());
	shape.setPosition(screenCenter);
	speed = 0.0;
}

Player::~Player() {

}

sf::CircleShape Player::getPlayerShape() {
	return shape;
}

void Player::turnLeft(float deltaTime) {
	shape.rotate(sf::degrees(-TURN_SPEED * deltaTime));
}

void Player::turnRight(float deltaTime) {
	shape.rotate(sf::degrees(TURN_SPEED * deltaTime));
}

void Player::boostSpeed(float deltaTime) {
	speed = std::min((speed + SPEED_INCREASE_RATE * deltaTime), MAX_SPEED);
}

void Player::goForward(float deltaTime) {
	const float radians = shape.getRotation().asRadians();

	const sf::Vector2f direction{std::sin(radians), -std::cos(radians)};

	shape.move(direction * deltaTime * speed);

	speed *= std::pow(DAMPING_RATE, deltaTime);
}

void Player::setPlayerPosition(const sf::Vector2f& position) {
	shape.setPosition(position);
}

void Player::shoot() {

	bullet_map[new_bullet_id] = bullets.begin();
	bullets.emplace_front(new_bullet_id++);
	pruneBullets();
}

void Player::pruneBullets() {
	if (bullets.size() > MAX_ACTIVE_BULLETS) {
		int id = bullets.back().getId();
		bullets.pop_back();
		bullet_map.erase(id);
	}
}
