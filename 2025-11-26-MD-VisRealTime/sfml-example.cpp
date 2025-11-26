// g++ sfml-example.cpp -o shapes -lsfml-graphics -lsfml-window -lsfml-system 

#include <SFML/Graphics.hpp>

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(600, 400), "Square and Disc - Minimal Example");

    // ---- Create a square (use RectangleShape) ----
    sf::RectangleShape square(sf::Vector2f(100.f, 100.f)); // width, height
    square.setFillColor(sf::Color::Blue);
    square.setPosition(100.f, 150.f); // x, y

    // ---- Create a disc (use CircleShape) ----
    sf::CircleShape disc(50.f); // radius = 50
    disc.setFillColor(sf::Color::Red);
    disc.setPosition(300.f, 150.f); // top-left corner of bounding box

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(square);
        window.draw(disc);
        window.display();
    }

    return 0;
}
