#include "Game.h"

Game::Game():
	m_window("Snake", sf::Vector2u(800, 600)),
	m_world(sf::Vector2u(800, 600)),
	m_snake(m_world.GetBlockSize())
{}

Game::~Game() {}

bool Game::IsOver() {
	return m_window.IsDone();
}

void Game::Update() {
	m_window.Update();

	if (IsTimeToUpdate()) {
		m_snake.SetDirection(CurrentDirection());
		m_snake.Tick();
		m_world.Update(m_snake);

		if (m_snake.HasLost()) {
			m_snake.Reset();
		}
	}
}

Direction Game::CurrentDirection() const {
	Direction dir = m_snake.GetDirection();
	if (dir != Direction::None) {
		dir = m_snake.GetPhysicalDirection();	
	}	
	auto key = sf::Keyboard::isKeyPressed;

	if (key(sf::Keyboard::Up) && dir != Direction::Down) {
		dir = Direction::Up;
	} else if (key(sf::Keyboard::Down) && dir != Direction::Up) {
		dir = Direction::Down;
	} else if (key(sf::Keyboard::Left) && dir != Direction::Right) {
		dir = Direction::Left;
	} else if (key(sf::Keyboard::Right) && dir != Direction::Left) {
		dir = Direction::Right;
	}
	return dir;
}

bool Game::IsTimeToUpdate() {
	float timestep = 1.0f / m_snake.GetSpeed();
	m_iterationDuration += m_clock.restart();
	
	if (m_iterationDuration.asSeconds() >= timestep) {
		m_iterationDuration -= sf::seconds(timestep);
		return true;
	}
	return false;
}

void Game::Render() {
	m_window.BeginDraw();
	
	m_world.Render(m_window);
	m_snake.Render(m_window);

	m_window.EndDraw();
}