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


sf::Vector2f calcNewPosition(const sf::Vector2u& windowSize,
                             const sf::Sprite& sprite,
                             sf::Vector2f& vect) {

    sf::Vector2u size = sprite.getTexture()->getSize();

    if ((sprite.getPosition().x + (size.x / 2) > windowSize.x && vect.x > 0) ||
        (sprite.getPosition().x - (size.x / 2) < 0 && vect.x < 0)) {

        vect.x = -vect.x;
    }

    if ((sprite.getPosition().y + (size.y / 2) > windowSize.y && vect.y > 0) ||
        (sprite.getPosition().y - (size.y / 2) < 0 && vect.y < 0)) {

        vect.y = -vect.y;
    }

    return sprite.getPosition() + vect;
}


int main(int, char**) {

    sf::RenderWindow window(sf::VideoMode(640, 480), "First window!");

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 120.f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(320, 240);
    rectangle.setOrigin(rectangle.getSize().x / 2, rectangle.getSize().y / 2);

    sf::Texture texture;
    texture.loadFromFile("mushroom.jpg");

    sf::Sprite mushroom(texture);
    mushroom.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    sf::Vector2f inc(0.1, 0.1);

    while (shouldContinue(window)) {
        window.clear(sf::Color::Green);

        mushroom.setPosition(
                    calcNewPosition(window.getSize(), mushroom, inc));

        window.draw(rectangle);
        window.draw(mushroom);
        window.display();
    }

    std::cout << "Finishing..." << std::endl;
    window.close();

    return 0;
}
