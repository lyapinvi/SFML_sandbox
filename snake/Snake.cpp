#include <stdexcept>

#include "Snake.h"

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
	//TODO: this looks horriblle (empty snake body == (1, 1))
	return (m_snakeBody.empty() ? sf::Vector2i(1, 1) : m_snakeBody.front());
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
