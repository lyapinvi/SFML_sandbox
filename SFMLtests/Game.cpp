#include "Game.h"

Game::Game():
m_window("Jumping Mushroom", sf::Vector2u(800, 600)), m_increment(100, 100) 
{
	m_mushroomTexture.loadFromFile("mushroom.jpg");
	m_mushroom.setTexture(m_mushroomTexture);
}

Game::~Game() {}

bool Game::IsOver() {
	return m_window.IsDone();
}

void Game::Update() {
	m_window.Update();
	MoveMushroom();
}

void Game::MoveMushroom() {
	sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_mushroomTexture.getSize();
	sf::Vector2f l_mushPos = m_mushroom.getPosition();

	if ((l_mushPos.x > l_windSize.x - l_textSize.x && m_increment.x > 0) ||
		(l_mushPos.x < 0 && m_increment.x < 0)) {
		m_increment.x = -m_increment.x;
	}

	if ((l_mushPos.y > l_windSize.y - l_textSize.y && m_increment.y > 0) ||
		(l_mushPos.y < 0 && m_increment.y < 0)) {
		m_increment.y = -m_increment.y;
	}

	float fElapsed = m_iterationDuration.asSeconds();
	m_mushroom.setPosition(l_mushPos.x + m_increment.x * fElapsed, 
						   l_mushPos.y + m_increment.y * fElapsed);
}

void Game::Render() {
	m_window.BeginDraw();
	m_window.Draw(m_mushroom);
	m_window.EndDraw();
}

void Game::Synchronize() {
	m_iterationDuration = m_clock.restart();
}