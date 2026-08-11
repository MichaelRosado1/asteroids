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
	while (playerLost) {
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			// reset game
			resetGame();
			playerLost = false;
		}
	}
}

void Game::resetGame() {
	// reset player
	player.reset();
	asteroids.clear();
	score = 0;
	current_level = 0;
}

void Game::update() {
	int point_increase = player.updateState(deltaTime, asteroids);
	score += point_increase;

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
	sf::Font font;
	if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
		std::cout << "Error\n";
		return;
	}
	sf::Text scoreText(font);
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(getScore()));
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition({20.f, 20.f});

	sf::Text levelText(font);
	levelText.setFont(font);
	levelText.setCharacterSize(20);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition({20.f, 50.f});
	levelText.setString("Level: " + std::to_string(current_level));
	window.draw(scoreText);
	window.draw(levelText);
	std::list<Bullet>& bullets = player.getBullets();


	for (auto& bullet : bullets) {
		window.draw(bullet.getShape());
	}

	for (auto& asteroid : asteroids) {
		asteroid.draw(window);
	}
}

void Game::updateLevel() {
	levelComplete = false;
	current_level++;
	num_asteroids = num_asteroids + (ASTEROID_MULTIPLIER * num_asteroids * current_level);
}

void Game::startLevel() {
	for (int i = 0; i < num_asteroids; ++i) {
		asteroids.emplace_back();
	}
}

void Game::checkGameState() {
	if (asteroids.empty()) {
		// new level needed
		levelComplete = true;
	}

	if (player.getPlayerLives() == 0) {
		playerLost = true;
	}
}

void Game::playerLostScreen() {
	window.clear();
	sf::Font font;
	if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
		std::cout << "Error\n";
		return;
	}
	sf::Text lostText(font);
	lostText.setFont(font);
	lostText.setCharacterSize(20);
	lostText.setFillColor(sf::Color::White);
	lostText.setPosition(screenCenter);
	lostText.setString("Final Score: " + std::to_string(getScore()) + " Press space to restart");
	window.draw(lostText);
	window.display();
}
void Game::run() {
	player.setPosition(screenCenter);

	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		if (playerLost) {
			playerLostScreen();
		}

		if (levelComplete) {
			updateLevel();
			startLevel();
		}
		processEvents();
		update();
		handleCollisions();
		checkGameState();
		window.clear();
		render();
		window.display();
	}
}

int Game::getScore() {
	return score;
}