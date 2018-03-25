#include <vector>

class World {
public:
	World(const sf::Vector2u& windowSize);
	~World();

	int GetBlockSize() const;
	void RespawnApple();
	void Update(Snake& player);
	void Render(sf::RenderWindow& window);

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_apple;
	int m_blockSize;
	std::vector<sf::RectangleShape> m_bounds;
};