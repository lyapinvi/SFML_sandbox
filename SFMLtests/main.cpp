#include <iostream>
#include "SFML/Graphics.hpp"

bool shouldContinue(sf::RenderWindow& window) {
    bool should_continue = false;

    if (window.isOpen()) {
        should_continue = true;

        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (sf::Event::Closed == ev.type) {
                should_continue = false;
            }
        }
    }
    return should_continue;
}

int main(int argc, char* argv[]) {

    sf::RenderWindow window(sf::VideoMode(640, 480), "First window!");

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 120.f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(320, 240);
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

    sf::Texture texture;
    texture.loadFromFile("mushroom.jpg");

    sf::Sprite mushroom(texture);
    mushroom.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    sf::Vector2f inc(0.4, 0.4);

    while (shouldContinue(window)) {
        window.clear(sf::Color::Black);

        updateScene(mushroom, increment);

        window.draw(rectangle);
        window.draw(sprite);
        window.display();
    }

    std::cout << "Finishing..." << std::endl;
    window.close();

    return 0;
}
