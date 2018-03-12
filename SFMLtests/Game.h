class Game {

public:
	Game();

	~Game();

	void HandleInput();

	void Update();

	void Render();

	bool IsOver();

private:
	void MoveMushroom();

private:
	Window m_window;
	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	sf::Vector2i m_increment;
}