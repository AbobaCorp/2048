#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DebugWindow {
public:
	DebugWindow(sf::Font& font);

	void draw(sf::RenderWindow& win);

	void moreButton(sf::Vector2i& pos);

private:
	void update();

	sf::Clock clock;
	sf::Time time;
	const float samplingInterval = 0.25;
	sf::Time timer;
	bool isMore;
	sf::Text moretext;
	sf::Text fpstext;
	sf::Text fttext;
	sf::Text hidetext;
	sf::RectangleShape rect;
	sf::RectangleShape chartrect;
	std::vector<sf::Uint32> chartlist;
};