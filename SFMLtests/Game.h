#include "Window.h"

class Game {

public:
	Game();

	~Game();

	void Update();

	void Render();

	bool IsOver();

	void Synchronize();

private:
	void MoveMushroom();

private:
	Window m_window;
	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	sf::Vector2i m_increment;
	sf::Clock m_clock;
	sf::Time m_iterationDuration;
};