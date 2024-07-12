#include "ScoreRect.h"

ScoreRect::ScoreRect(sf::String Label, sf::Font& font) {
	label.setFont(font);
	label.setCharacterSize(20);
	label.setString(Label);
	label.setFillColor(sf::Color(238, 228, 218));
	label.setOrigin(label.getLocalBounds().width / 2.f, label.getLocalBounds().height / 2.f);

	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(sf::Color::White);
	score.setString("0");
	score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);

	rect.setPosition(0, 0);
	rect.setCornerPointCount(15);
	rect.setCornersRadius(5);
	rect.setFillColor(sf::Color(187, 173, 160));
}

void ScoreRect::setPosition(float x, float y) {
	rect.setPosition(x, y);
}

sf::Vector2f ScoreRect::getPosition() const
{
	return rect.getPosition();
}

sf::Vector2f ScoreRect::getSize() const
{
	return rect.getSize();
}

void ScoreRect::setLabelString(std::string str) {
	label.setString(str);
	label.setOrigin(label.getLocalBounds().width / 2.f, label.getLocalBounds().height / 2.f);
}

void ScoreRect::setScore(int scr) {
	scoreInt = scr;
	score.setString(std::to_string(scr));
	score.setOrigin(score.getLocalBounds().width / 2.f, score.getLocalBounds().height / 2.f);
}

int ScoreRect::getScore() const {
	return scoreInt;
}

void ScoreRect::draw(sf::RenderWindow& win) {
	sf::Vector2f size;
	size.x = std::max(label.getLocalBounds().width, score.getLocalBounds().width) + 20;
	size.y = score.getLocalBounds().height * 2.f + 20;
	rect.setSize(size);

	label.setPosition(rect.getPosition().x + size.x / 2.f, rect.getPosition().y + 10);

	score.setPosition(rect.getPosition().x + size.x / 2.f, rect.getPosition().y + size.y / 2.f + 5);

	win.draw(rect);
	win.draw(label);
	win.draw(score);
}