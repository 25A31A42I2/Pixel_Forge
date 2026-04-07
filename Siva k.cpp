#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

// Window size
const int WIDTH = 800;
const int HEIGHT = 600;

// Player settings
float playerSpeed = 5.0f;

// Enemy settings
float enemySpeedX = 3.0f;
float enemySpeedY = 3.0f;

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PixelForge");
    window.setFramerateLimit(60);

    // Player (square)
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Green);
    player.setPosition(100, 100);

    // Enemy (circle)
    sf::CircleShape enemy(25);
    enemy.setFillColor(sf::Color::Red);
    enemy.setPosition(400, 300);

    // Font (optional - comment if not available)
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        cout << "Font not found!\n";
    }

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over!");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(300, 250);

    bool gameOver = false;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;

        // Event handling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player movement (only if game not over)
        if (!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                player.move(0, -playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                player.move(0, playerSpeed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                player.move(-playerSpeed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                player.move(playerSpeed, 0);
        }

        // Keep player inside window
        sf::Vector2f pos = player.getPosition();
        if (pos.x < 0) player.setPosition(0, pos.y);
        if (pos.y < 0) player.setPosition(pos.x, 0);
        if (pos.x + 50 > WIDTH) player.setPosition(WIDTH - 50, pos.y);
        if (pos.y + 50 > HEIGHT) player.setPosition(pos.x, HEIGHT - 50);

        // Enemy movement (bounce)
        if (!gameOver) {
            enemy.move(enemySpeedX, enemySpeedY);

            if (enemy.getPosition().x <= 0 || enemy.getPosition().x + 50 >= WIDTH)
                enemySpeedX = -enemySpeedX;

            if (enemy.getPosition().y <= 0 || enemy.getPosition().y + 50 >= HEIGHT)
                enemySpeedY = -enemySpeedY;
        }

        // Collision detection
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            gameOver = true;
        }

        // Rendering
        window.clear();

        window.draw(player);
        window.draw(enemy);

        if (gameOver) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
