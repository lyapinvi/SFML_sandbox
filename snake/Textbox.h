#include <vector>
#include <string>

#include "SFML/System.hpp"

#include "Window.h"

using MessageContainer = std::vector<std::string>;

class Textbox {
public:
	Textbox();
	Textbox(int visible, int charSize, int width,
		const sf::Vector2f& screenPos);
	~Textbox();

	void Setup(int visible, int charSize, int width, 
		const sf::Vector2f& screenPos);
	void Add(const std::string& message);
	void Clear();
	void Render(Window& Window);

private:
	MessageContainer m_messages;
	int m_numVisible;
	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};