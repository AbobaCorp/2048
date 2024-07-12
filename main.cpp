#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Field.h"
#include "ScoreRect.h"
#include "DebugWindow.h"
using namespace std;

void welcome_draw(sf::RenderWindow& win, sf::Font& font);

int main()
{
	sf::Font arialfont;
	if (!arialfont.loadFromFile("fonts/arialbd.ttf")) return 1;
	sf::Font kryptonfont;
	if (!kryptonfont.loadFromFile("fonts/krypton.otf")) return 1;
	sf::Font consolfont;
	if (!consolfont.loadFromFile("fonts/consola.ttf")) return 1;
	sf::Image icon;
	if (!icon.loadFromFile("texture/iconwin.png")) return 1;

	srand(time(0));

	int width = 520;
	int height = 650;
	sf::ContextSettings windowSettings(0, 0, 4);
	sf::RenderWindow window(sf::VideoMode(width, height), "2048 (Debug Edition)", sf::Style::Titlebar | sf::Style::Close, windowSettings);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(100);

	sf::Field field(arialfont);
	field.loadFromFile("player.data");
	field.setPosition(10, 10);

	DebugWindow debug(consolfont);
	bool isShowDebug = true;

	ScoreRect score("SCORE", arialfont);
	score.setPosition(20, 540);
	ScoreRect scoreBest("BEST", arialfont);
	scoreBest.setPosition(400, 540);
	scoreBest.setScore(field.getBestScore());

	sf::RoundedRectangleShape restartBtn(sf::Vector2f({}), 3.f, 5);
	sf::Text restartText("New Game", arialfont, 20);
	restartText.setFillColor(sf::Color::White);
	restartBtn.setSize(sf::Vector2f(restartText.getLocalBounds().width + 20, restartText.getLocalBounds().height + 20));
	restartBtn.setFillColor(sf::Color(166, 141, 118));

	sf::RoundedRectangleShape continueBtn(sf::Vector2f({}), 3.f, 5);
	sf::Text continueText("Continue", arialfont, 20);
	continueText.setFillColor(sf::Color::White);
	continueBtn.setSize(sf::Vector2f(continueText.getLocalBounds().width + 20, continueText.getLocalBounds().height + 20));
	continueBtn.setFillColor(sf::Color(166, 141, 118));

	sf::Text authorText("by AbobaCorp", kryptonfont, 14);
	authorText.setFillColor(sf::Color(119, 110, 101));
	authorText.setPosition(5, height - authorText.getGlobalBounds().height - 10);

	while (window.isOpen())
	{
		sf::Event winevent;
		while (window.pollEvent(winevent))
		{
			if (winevent.type == sf::Event::Closed) {
				field.saveFromFile("player.data");
				window.close();
			}

			if (winevent.type == sf::Event::MouseButtonPressed) {

				if (winevent.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i pos = sf::Mouse::getPosition(window);
					if (pos.x >= restartBtn.getPosition().x &&
						pos.x <= restartBtn.getPosition().x + restartBtn.getSize().x &&
						pos.y >= restartBtn.getPosition().y &&
						pos.y <= restartBtn.getPosition().y + restartBtn.getSize().y) {

						restartBtn.setFillColor(sf::Color(101, 86, 72));
					}

					if (pos.x >= continueBtn.getPosition().x &&
						pos.x <= continueBtn.getPosition().x + continueBtn.getSize().x &&
						pos.y >= continueBtn.getPosition().y &&
						pos.y <= continueBtn.getPosition().y + continueBtn.getSize().y) {

						continueBtn.setFillColor(sf::Color(101, 86, 72));
					}
				}
			}

			if (winevent.type == sf::Event::MouseButtonReleased) {

				if (winevent.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i pos = sf::Mouse::getPosition(window);

					if (pos.x >= restartBtn.getPosition().x &&
						pos.x <= restartBtn.getPosition().x + restartBtn.getSize().x &&
						pos.y >= restartBtn.getPosition().y &&
						pos.y <= restartBtn.getPosition().y + restartBtn.getSize().y) {

						field.restart();
						restartBtn.setFillColor(sf::Color(166, 141, 118));
					}

					if (pos.x >= continueBtn.getPosition().x &&
						pos.x <= continueBtn.getPosition().x + continueBtn.getSize().x &&
						pos.y >= continueBtn.getPosition().y &&
						pos.y <= continueBtn.getPosition().y + continueBtn.getSize().y) {

						field.keepGoing();
						continueBtn.setFillColor(sf::Color(166, 141, 118));
					}

					if (isShowDebug) debug.moreButton(pos);
				}
			}

			if (winevent.type == sf::Event::KeyReleased) {

				if (winevent.key.code == sf::Keyboard::W ||
					winevent.key.code == sf::Keyboard::Up) {
					field.move('w');
				}
				else if (winevent.key.code == sf::Keyboard::S ||
					winevent.key.code == sf::Keyboard::Down) {
					field.move('s');
				}
				else if (winevent.key.code == sf::Keyboard::A ||
					winevent.key.code == sf::Keyboard::Left) {
					field.move('a');
				}
				else if (winevent.key.code == sf::Keyboard::D ||
					winevent.key.code == sf::Keyboard::Right) {
					field.move('d');
				}

				else if (winevent.key.code == sf::Keyboard::H) {
					isShowDebug = !isShowDebug;
				}
			}
		}

		score.setScore(field.getScore());
		if (score.getScore() > scoreBest.getScore()) {
			field.setBestScore(field.getScore());
			scoreBest.setScore(field.getScore());
		}
		score.setPosition(width / 2.f - score.getSize().x - 10, 540);
		scoreBest.setPosition(width / 2.f + 10, 540);

		restartBtn.setPosition(scoreBest.getPosition().x + scoreBest.getSize().x + 10, 540);
		restartText.setPosition(restartBtn.getPosition().x + 10, restartBtn.getPosition().y + 5);

		continueBtn.setPosition(score.getPosition().x - continueBtn.getSize().x - 10, 540);
		continueText.setPosition(continueBtn.getPosition().x + 10, continueBtn.getPosition().y + 5);

		window.clear(sf::Color(237, 236, 231));
		window.draw(field.update());
		score.draw(window);
		scoreBest.draw(window);
		window.draw(restartBtn);
		window.draw(restartText);
		if (field.isWin() && !field.isGameOver()) {
			window.draw(continueBtn);
			window.draw(continueText);
		}
		window.draw(authorText);
		welcome_draw(window, arialfont);
		if(isShowDebug) debug.draw(window);
		window.display();
	}

	return 0;
}

void welcome_draw(sf::RenderWindow& win, sf::Font& font)
{
	static float value = -1;
	static sf::Clock fps;
	const float speed = 0.01;

	if (value >= M_PI) return;

	int width = win.getSize().x;
	int height = win.getSize().y;

	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color(250, 248, 239));
	if (value < 0) rect.setPosition(0, 0);
	else rect.setPosition(0, (cosf(value) - 1) * height / 2.f);

	sf::Text text("2048", font, 120);
	text.setFillColor(sf::Color(119, 110, 101));
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f + 30);
	text.setPosition(width / 2.f, height / 2.f);

	if (rect.getPosition().y + height - 100 <= text.getPosition().y + text.getLocalBounds().height / 2.f) {
		text.setPosition(width / 2.f, rect.getPosition().y + height - 100 - text.getLocalBounds().height / 2.f);
	}

	value += 0.5f * fps.getElapsedTime().asMilliseconds() * speed;

	win.draw(rect);
	win.draw(text);
	fps.restart();
}