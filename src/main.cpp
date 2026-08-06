#include <iostream>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Asteroid.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2f screenCenter {static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f};
	Player player = Player(screenCenter);		

	player.setPosition(screenCenter);
	std::vector<Asteroid> asteroids;

	sf::Clock clock;
	while (window.isOpen()) {
		const float deltaTime = clock.restart().asSeconds();
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

		player.updateState(deltaTime);
		window.clear();
		window.draw(player.getPlayerShape());
		std::list<Bullet>& bullets = player.getBullets();


		for (auto& bullet : bullets) {
			window.draw(bullet.getShape());
		}

		for (auto& asteroid : asteroids) {
			asteroid.move(deltaTime);
			asteroid.draw(window);
		}


		window.display();
	}
	return 1;
}