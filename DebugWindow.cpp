#include "DebugWindow.h"

DebugWindow::DebugWindow(sf::Font& font)
{
	time = clock.restart();
	timer = time;

	isMore = false;
	moretext.setFont(font);
	moretext.setString(". . .");
	moretext.setFillColor(sf::Color::White);
	moretext.setCharacterSize(15);
	moretext.setStyle(sf::Text::Style::Underlined);

	fpstext.setFont(font);
	fpstext.setCharacterSize(18);
	fpstext.setFillColor(sf::Color::Green);
	fpstext.setString("FPS 0");

	fttext.setFont(font);
	fttext.setCharacterSize(14);
	fttext.setFillColor(sf::Color::Green);
	fttext.setString("Frame Time 0 ms");

	hidetext.setFont(font);
	hidetext.setCharacterSize(13);
	hidetext.setFillColor(sf::Color::White);
	hidetext.setString("the H key hides/shows\nthe overlay");

	rect.setFillColor(sf::Color(42, 42, 42, 128));

	const sf::Vector2f chartsize = { 120, 30 };
	chartrect.setSize(chartsize);
	chartrect.setOutlineThickness(2);
	chartrect.setFillColor(sf::Color::Transparent);

	chartlist.assign(chartsize.x, 0);
	chartlist.reserve(chartsize.x + 1);
}

void DebugWindow::draw(sf::RenderWindow& win)
{
	time = clock.getElapsedTime();

	if (timer.asSeconds() > samplingInterval) {
		timer = sf::Time::Zero;
		update();
	}

	if (!isMore) {
		fpstext.setPosition(0, 0);

		rect.setSize(sf::Vector2f(75, 30));

		moretext.setPosition(rect.getSize().x / 2.f - moretext.getLocalBounds().width / 2.f, rect.getSize().y - 20);

		win.draw(rect);
		win.draw(fpstext);
		win.draw(moretext);
	}
	else
	{
		rect.setSize(sf::Vector2f(160, 145));

		fpstext.setPosition(0, 0);
		fttext.setPosition(0, 20);

		chartrect.setPosition(rect.getSize().x / 2.f - chartrect.getSize().x / 2.f, 60);

		hidetext.setPosition(5, chartrect.getPosition().y + chartrect.getSize().y + 10);

		moretext.setPosition(rect.getSize().x / 2.f - moretext.getLocalBounds().width / 2.f, rect.getSize().y - 20);

		win.draw(rect);
		win.draw(fpstext);
		win.draw(fttext);
		win.draw(chartrect);
		sf::RectangleShape line;
		line.setFillColor(sf::Color::Cyan);
		for (int i{}; i < chartlist.size(); i++) {
			float h = chartlist[i] * rect.getSize().y / 100.f;
			if (h > chartrect.getSize().y) h = chartrect.getSize().y;
			line.setSize(sf::Vector2f(1, h));
			line.setOrigin(0, h);
			line.setPosition(chartrect.getPosition().x + i, chartrect.getPosition().y + chartrect.getSize().y);
			win.draw(line);
		}
		win.draw(hidetext);
		win.draw(moretext);
	}

	timer += time;
	clock.restart();
}

void DebugWindow::moreButton(sf::Vector2i& pos)
{
	if (pos.x >= rect.getPosition().x &&
		pos.x <= rect.getPosition().x + rect.getSize().x &&
		pos.y >= rect.getPosition().y &&
		pos.y <= rect.getPosition().y + rect.getSize().y) {

		isMore = !isMore;
	}
}

void DebugWindow::update()
{
	fpstext.setString(std::string("FPS ") + std::to_string(0xf4240 / time.asMicroseconds()));
	if (!isMore) return;
	std::string ftstr = std::to_string(time.asMicroseconds() / 1000.f);
	ftstr.erase(ftstr.begin() + ftstr.find('.') + 3, ftstr.end());
	fttext.setString(std::string("Frame Time ") + ftstr + std::string(" ms"));
	chartlist.push_back(time.asMilliseconds());
	chartlist.erase(chartlist.begin());
}
