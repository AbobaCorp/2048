#pragma once
#include <SFML/Graphics.hpp>
#include "RoundedRectangleShape.h"
#include <string>

class ScoreRect {
public:
	ScoreRect(sf::String Label, sf::Font& font);

	void setPosition(float x, float y);

	sf::Vector2f getPosition() const;

	sf::Vector2f getSize() const;

	void setLabelString(std::string str);

	void setScore(int scr);

	int getScore() const;

	void draw(sf::RenderWindow& win);

private:
	sf::Text label{};
	sf::Text score{};
	int scoreInt{};
	sf::RoundedRectangleShape rect;
};