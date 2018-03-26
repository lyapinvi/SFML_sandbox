#include "Window.h"
#include "World.h"
#include "Snake.h"

class Game {

public:
	Game();
	~Game();

	void Update();
	void Render();
	bool IsOver();
	bool Game::IsTimeToUpdate();

private:
	Direction CurrentDirection() const;

private:
	Window m_window;
	World m_world;
	Snake m_snake;
	sf::Clock m_clock;
	sf::Time m_iterationDuration;
};