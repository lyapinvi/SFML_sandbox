#include <vector>

#include "SFML/system.h"

struct SnakeSegment {
	SnakeSegment(int x, int y): position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {None, Up, Down, Left, Right};

class Snake {
public:
	Snake(int blocksize);
	~Snake();

	// Helper methods
	void SetDirection(Direction dir);
	Direction GetDirection() const;
	int GetSpeed();
	sf::Vector2i GetPosition();
	int GetLives();
	int GetScore();
	void IncreaseScore();
	bool HasLost();

	// Losing
	void Lose();
	void ToggleLost();

	// Growth
	void Extend();

	//Reset
	void Reset();

	void Move();
	void Tick();
	void Cut(int segments);
	void Render(sf::RenderWindow& window);

private:
	void CheckCollision();

private:
	SnakeContainer m_snakeBody;
	int m_size;
	Direction m_dir;
	int m_speed;
	int m_lives;
	int m_score;
	bool m_lost;
	sf::RectangleShape m_bodyRect;
};