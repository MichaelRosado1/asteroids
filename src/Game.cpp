//
// Created by Michael Rosado on 8/7/26.
//
#include "Game.h"

Game::Game() : window(sf::VideoMode({800, 600}), "Asteroids"), windowSize(window.getSize()),
                screenCenter({static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f}), player(Player(screenCenter)) {
}

Game::~Game() {}

void Game::processEvents() {
	while (auto event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window.close();
		}
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->code == sf::Keyboard::Key::Space) {
				player.shoot();
			} else if (keyPressed->code == sf::Keyboard::Key::R) {
				asteroids.emplace_back();
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		player.boostSpeed(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		player.turnLeft(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		player.turnRight(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		player.decelerate(deltaTime);
	}
}


void Game::update() {
	player.updateState(deltaTime, asteroids);

	for (auto& asteroid : asteroids) {
		asteroid.move(deltaTime);
	}
}

void Game::handleCollisions() {
	// check player asteroid collision
	std::vector<std::size_t> asteroids_hit;
	for (std::size_t i = 0; i < asteroids.size(); ++i) {
		if (player.getPlayerShape().getGlobalBounds().findIntersection(asteroids[i].getShape().getGlobalBounds())) {
			// player hit asteroid
			asteroids_hit.emplace_back(i);
			if (player.playerHit()) {
				std::cout << "player loses\n";
			}
		}
	}

	for (std::size_t i = 0; i < asteroids_hit.size(); ++i) {
		asteroids.erase(asteroids.begin() + asteroids_hit[i]);
	}


}

void Game::render() {
	window.draw(player.getPlayerShape());
	std::list<Bullet>& bullets = player.getBullets();


	for (auto& bullet : bullets) {
		window.draw(bullet.getShape());
	}

	for (auto& asteroid : asteroids) {
		asteroid.draw(window);
	}
}

void Game::run() {
	player.setPosition(screenCenter);

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		processEvents();
		update();
		handleCollisions();
		window.clear();
		render();
		window.display();
	}
}