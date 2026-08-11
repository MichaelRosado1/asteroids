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
		std::size_t lives = 3;
		sf::CircleShape shape;	
		float speed;	
		std::list<Bullet> bullets;
		std::unordered_map<int, std::list<Bullet>::iterator> bullet_map;
		int updateBullets(float deltaTime, std::vector<Asteroid>& asteroids);
		[[maybe_unused]] const sf::Vector2f& screenCenter;
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
		int updateState(float deltaTime, std::vector<Asteroid>& asteroids);

		void boostSpeed(float deltaTime);

		void setPlayerPosition(const sf::Vector2f& position);

		void shoot();
		void pruneBullets();
		std::list<Bullet>& getBullets();
		// return true if player loses after getting hit
		bool playerHit();
		int getPlayerLives();
		void reset();

};

#endif