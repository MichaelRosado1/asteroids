#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"

class Game {
private:
    sf::RenderWindow window;
    const sf::Vector2u windowSize;
    const sf::Vector2f screenCenter;
    sf::Clock clock;
    Player player;
    std::vector<Asteroid> asteroids;
    float deltaTime;


    void processEvents();
    void update();
    void handleCollisions();
    void render();


public:
    Game();
    ~Game();
    void run();

};