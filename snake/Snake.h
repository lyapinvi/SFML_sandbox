#include "SFML/system.h"

struct SnakeSegment {
	SnakeSegment(int x, int y): position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction {None, Up, Down, Left, Right};

