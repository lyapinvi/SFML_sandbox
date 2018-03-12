#include <string>
#include "SFML/Graphics.hpp"

class Window {
public:
	
	Window();

	Window(const std::string& l_title, const sf::Vector2u& l_size);

	~Window();

	void BeginDraw();

	void EndDraw();

	void Update();

	bool IsDone() const;

	bool IsFullscreen() const;

	sf::Vector2u GetWindowSize() const;

	void ToggleFullScreen();

	void Draw(const sf::Drawable& l_drawable);

private:

	void Setup(const std::string& l_title, const sf::Vector2u& l_size);

	void Destroy();

	void Create();

private:

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};