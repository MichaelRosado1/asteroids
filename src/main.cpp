#include <iostream>
#include <SFML/Window.hpp>
#include "Player.h"

int main() {
	sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2f screenCenter {static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f};
	Player player = Player(screenCenter);		

	player.setPosition(screenCenter);

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


		player.goForward(deltaTime);
		window.clear();
		window.draw(player.getPlayerShape());
		window.display();
	}
	return 1;
}