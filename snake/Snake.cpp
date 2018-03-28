#include <stdexcept>

#include "Snake.h"

const int MIN_COLLISION_LEN = 4;

Snake::Snake(int blockSize) {
	m_size = blockSize;

	// TODO: doesn't look to be a responsibility of this class
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	Reset();
}

Snake::~Snake() {}

void Snake::Reset() {
	m_snakeBody.clear();

	// TODO: This should be refactored for sure
	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None);

	// TODO: magic numbers
	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::SetDirection(Direction dir) {
	m_dir = dir;
}

Direction Snake::GetDirection() const {
	return m_dir;
}

int Snake::GetSpeed() const {
	return m_speed;
}

sf::Vector2i Snake::GetPosition() const {
	//TODO: this looks horrible (empty snake body == (1, 1))
	return (m_snakeBody.empty() ? sf::Vector2i(1, 1) : m_snakeBody.front().position);
}

int Snake::GetLives() const {
	return m_lives;
}

int Snake::GetScore() const {
	return m_score;
}

void Snake::IncreaseScore() {
	//  TODO: magic numbers
	m_score += 10;
}

bool Snake::HasLost() {
	return m_lost;
}

void Snake::Lose() {
	m_lost = true;
}

void Snake::ToggleLost() {
	m_lost = !m_lost;
}

void Snake::Extend() {
	if (m_snakeBody.empty()) {
		return;
	}

	const sf::Vector2i& tail = m_snakeBody.back().position;
	sf::Vector2i ext = tail;

	if (m_snakeBody.size() > 1) {
		const sf::Vector2i& bone = (m_snakeBody.end() - 2)->position;

		// if tail is along the x
		if (tail.x == bone.x) {
			if (tail.y > bone.y) {
				++ext.y;
			} else {
				--ext.y;
			}

		// if tail is along the y
		} else if (tail.y == bone.y) {
			if (tail.x > bone.x) {
				++ext.x;
			} else {
				--ext.x;
			}
		} else {
			throw std::runtime_error("both x and y mismatched");
		}
	
	// x and y are the same - snake is one segment
	} else {
		switch (m_dir) {
			case Direction::Up:
				++ext.y;
				break;
			case Direction::Down:
				--ext.y;
				break;
			case Direction::Left:
				++ext.x;
				break;
			case Direction::Right:
				--ext.x;
				break;
			default:
				throw std::runtime_error("unable to extend");
		}
	}

	m_snakeBody.push_back(SnakeSegment(ext.x, ext.y));
}

void Snake::Tick() {
	Move();
	CheckCollision();
}

void Snake::Move() {
	if (m_snakeBody.empty() || m_dir == Direction::None) {
		return;
	}

	// Move all elements forward
	for (int i = m_snakeBody.size() - 1; i > 0; --i) {
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}

	// Decide where the head moves
	sf::Vector2i& head = m_snakeBody.front().position;

	if (Direction::Left == m_dir) {
		--head.x;
	} else if (Direction::Right == m_dir) {
		++head.x;
	} else if (Direction::Up == m_dir) {
		--head.y;
	} else if (Direction::Down == m_dir) {
		++head.y;
	}
}

void Snake::CheckCollision() {
	// No need to check collsion if snake is 4 segments or less
	if (m_snakeBody.size() <= MIN_COLLISION_LEN) {
		return;
	}

	const SnakeSegment& head = m_snakeBody.front();

	for (auto seg = m_snakeBody.begin() + 1; seg != m_snakeBody.end(); ++seg) {
		if (seg->position == head.position) {
			int lengthToCut = m_snakeBody.end() - seg;
			Cut(lengthToCut);
			break;
		}
	}
}

// Bad name: this funtion doesn't cut, it handles a collision,
// by cutting and checking the losing criteria
void Snake::Cut(int segCount) {
	m_snakeBody.erase(m_snakeBody.end() - segCount, m_snakeBody.end());
	if (0 == --m_lives) {
		Lose();
	}
}

void Snake::Render(Window& window) {
	if (m_snakeBody.empty()) {
		return;
	}

	for (auto seg = m_snakeBody.begin(); seg != m_snakeBody.end(); ++seg) {
		m_bodyRect.setFillColor(seg == m_snakeBody.begin()
			? sf::Color::Yellow : sf::Color::Green);

		m_bodyRect.setPosition(seg->position.x * m_size, 
			seg->position.y * m_size);
		window.Draw(m_bodyRect);
	}
}

Direction Snake::GetPhysicalDirection() const {
	if (m_snakeBody.size() <= 1) {
		return Direction::None;
	}

	const auto& head = m_snakeBody[0].position;
	const auto& neck = m_snakeBody[1].position;

	if (head.x == neck.x) {
		return head.y > neck.y ? Direction::Down : Direction::Up;
	} else if (head.y == neck.y) {
		return head.x > neck.x ? Direction::Right : Direction::Left;
	}
	return Direction::None;
}