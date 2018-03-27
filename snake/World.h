#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Snake.h"
#include "World.h"

class World {
public:
	World(const sf::Vector2u& windowSize);
	~World();

	int GetBlockSize() const;
	void RespawnApple();
	void Update(Snake& player);
	void Render(Window& window) const;

private:
	void RenderBorders(Window& window) const;
	void RenderApple(Window& window) const;

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_apple;
	int m_blockSize;
	std::vector<sf::RectangleShape> m_bounds;
};

#endif // WORLD_H