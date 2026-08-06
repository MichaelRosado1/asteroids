#pragma once
#ifndef Player_H
#define Player_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <unordered_map>

#include "Bullet.h"
#

class Player : public sf::Transformable {
	private:
		int new_bullet_id = 0;
		float MAX_SPEED = 500;
		float SPEED_INCREASE_RATE = 100.0;
		float TURN_SPEED = 250.0;
		float DAMPING_RATE = 0.8f;
		std::size_t MAX_ACTIVE_BULLETS = 10;

		sf::CircleShape shape;	
		float speed;	
		long long iteration_count = 0;
		std::list<Bullet> bullets;
		std::unordered_map<int, std::list<Bullet>::iterator> bullet_map;
		void updateBullets(float deltaTime);
	public:
		Player(const sf::Vector2f& screenCenter);

		Player(const Player&) = delete;
		Player(const Player&&) = delete;
		const Player operator=(const Player&) = delete;
		const Player operator=(const Player&&) = delete;

		~Player();

		sf::CircleShape getPlayerShape();

		void turnLeft(float deltaTime);
		void turnRight(float deltaTime);
		void goForward(float deltaTime);
		void decelerate(float deltaTime);
		void updateState(float deltaTime);

		void boostSpeed(float deltaTime);

		void setPlayerPosition(const sf::Vector2f& position);

		void shoot();
		void pruneBullets();
		std::list<Bullet>& getBullets();
};

#endif