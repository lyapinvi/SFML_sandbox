#include "Game.h"

Game::Game():
	m_window("Snake", sf::Vector2u(800, 600)),
	m_world(sf::Vector2u(800, 600)),
	m_snake(m_world.GetBlockSize())
{
	m_textbox.Setup(5, 14, 350, sf::Vector2f(225, m_world.GetBlockSize()));
	m_textbox.Add("Seeded random number generator with: "
		+ std::to_string(time(NULL)));
}

Game::~Game() {}

bool Game::IsOver() {
	return m_window.IsDone();
}

void Game::Update() {
	m_window.Update();

	if (IsTimeToUpdate()) {
		int prevScore = m_snake.GetScore();

		m_snake.SetDirection(CurrentDirection());
		m_snake.Tick();
		m_world.Update(m_snake);

		if (m_snake.HasLost()) {
			m_snake.Reset();
			m_textbox.Add("GAME OVER! Score: "
				+ std::to_string(m_snake.GetScore()));

		} else if (prevScore != m_snake.GetScore()) {
			m_textbox.Add("New score: " + std::to_string(m_snake.GetScore()));
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
	
	m_textbox.Render(m_window);
	m_world.Render(m_window);
	m_snake.Render(m_window);

	m_window.EndDraw();
}