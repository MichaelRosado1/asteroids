#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class Bullet : public sf::Transformable{
private:
	int bullet_id;
	sf::CircleShape shape;
	sf::Vector2f direction;
	float bulletSpeed = 600;

public:
	Bullet(int id, sf::Vector2f position, sf::Vector2f direction);

	~Bullet();

	int getId();
	bool goForward(float deltaTime);
	sf::CircleShape& getShape();
};
