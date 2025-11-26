// g++ sfml-animation.cpp -o shapes -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Animated Square and Disc");

    // Square
    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    square.setFillColor(sf::Color::Blue);
    square.setPosition(100.f, 150.f);

    // Disc
    sf::CircleShape disc(50.f); // radius
    disc.setFillColor(sf::Color::Red);
    disc.setOrigin(50.f, 50.f); // center for rotation
    disc.setPosition(400.f, 200.f);

    float t = 0.f;   // time variable for animation
    sf::Clock clock; // measures frame time

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Time step ---
        float dt = clock.restart().asSeconds();
        t += dt;

        // --- Animation ---
        // Square oscillates horizontally using a sine wave
        float x = 100.f + 100.f * std::sin(t * 2.f);  // amplitude 100, speed factor 2
        square.setPosition(x, 150.f);

        // Disc rotates around its center
        disc.rotate(90.f * dt);  // 90 degrees per second

        // --- Drawing ---
        window.clear(sf::Color::Black);
        window.draw(square);
        window.draw(disc);
        window.display();
    }

    return 0;
}
