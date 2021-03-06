#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "Textbox.h"

class Game {

public:
	Game();
	~Game();

	void Update();
	void Render();
	bool IsOver();
	bool IsTimeToUpdate();

private:
	Direction CurrentDirection() const;

private:
	Window m_window;
	World m_world;
	Snake m_snake;
	sf::Clock m_clock;
	sf::Time m_iterationDuration;
	Textbox m_textbox;
};

#endif // GAME_H