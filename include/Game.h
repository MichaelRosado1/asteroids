#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"

class Game {
private:
    double ASTEROID_MULTIPLIER = .75;
    sf::RenderWindow window;
    const sf::Vector2u windowSize;
    const sf::Vector2f screenCenter;
    sf::Clock clock;
    Player player;
    std::vector<Asteroid> asteroids;
    float deltaTime;
    std::string scoreText;
    int score = 0;
    int current_level = 0;
    [[maybe_unused]] int num_asteroids = 5;
    bool levelComplete = true;
    bool playerLost = false;


    void processEvents();
    void update();
    void handleCollisions();
    void render();
    int getScore();
    void updateLevel();
    void startLevel();
    void checkGameState();
    void playerLostScreen();
    void resetGame();
public:
    Game();
    ~Game();
    void run();

};