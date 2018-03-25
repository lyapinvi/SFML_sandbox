#include <World.h>

static std::vector<sf::RectangleShape> CreateBorderWalls(
	const sf::Vector2u& worldSize,
	int width, 
	const sf::Color& color) {

	std::vector<sf::RectangleShape> walls;
	sf::RectangleShape wall;
	wall.setFillColor(color);

	for (size_t wallInd = 0; wallInd < 4; ++wallInd) {
		sf::Vector2f wallSize = (wallInd % 2) 
			? sf::Vector2f(worldSize.x, width)
			: sf::Vector2f(width, worldSize.y);	
		wall.setSize(wallSize);

		if (wallInd <= 1) {
			// for top-left walls
			wall.setPosition(0, 0);
		} else {
			//for bottom-right walls set origin to wall's bottom right corner
			wall.setOrigin(wall.getSize());
			wall.setPosition(sf::Vector2f(worldSize));
		}
		walls.push_back(wall);
	}
	return walls;
}

World::World(sf::Vector2u windowSize):
	m_blockSize(16),
	m_windowSize(windowSize),
{
	RespawnApple();
	m_bounds = CreateBorderWalls(
		m_windowSize, m_blockSize, sf::Color(150, 0, 0));
}

World::~World() {}

void World::RespawnApple() {
	int maxX = m_windowSize.x / GetBlockSize() - 2;
	int maxY = m_windowSize.y / GetBlockSize() - 2;

	m_apple = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
}

void World::Update(Snake& player) {
	// Check if apple is eaten
	if (player.GetPosition() == m_apple) {
		player.Extend();
		player.IncreaseScore();
		RespawnApple();
	}

	sf::Vector2i border(m_windowSize.x / GetBlockSize(),
		m_windowSize.y / GetBlockSize());
	sf::Vector2i snake = player.GetPosition();

	// Check collision with a wall
	if (snake.x <= 0 || snake.y <= 0 || 
		snake.x >= border.x - 1 || snake.y >= border.y - 1)
	{
		player.Lose();
	}
}

void World::Render(sf::RenderWindow& window) {
	for (const auto& wall: m_bounds) {
		window.draw(wall)
	}

	sf::CircleShape appleShape;
	appleShape.setFillColor(sf::Color::Red);
	appleShape.setRadius(GetBlockSize() / 2);
	//TODO: add function to convert from blocks to pixels
	appleShape.setPosition(m_apple.x * GetBlockSize(), 
		m_apple.y * GetBlockSize());
	window.draw(appleShape);
}

int World::GetBlockSize() {
	return m_blockSize;
}




