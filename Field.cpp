#include "Field.h"

sf::Field::Field(sf::Font& _font) {
	if (!fldtx.create(500, 500, sf::ContextSettings(0, 0, 4))) exit(1);
	font = _font;
	text.setFont(font);
	text.setCharacterSize(50);

	flagAnimMove = false;
	flagAnimWt = false;
	flagAnimRand = false;

	fieldRect.setSize(sf::Vector2f(500, 500));
	fieldRect.setPosition(sf::Vector2f(0, 0));
	fieldRect.setFillColor(sf::Color::White);

	rect.setCornerPointCount(10);
	rect.setSize(sf::Vector2f(498, 498));
	rect.move(1, 1);
	rect.setCornersRadius(10);
	rect.setFillColor(sf::Color(187, 173, 160));

	fldtx.clear(sf::Color(237, 236, 231));
	fldtx.draw(rect);

	rect.setSize(sf::Vector2f(108, 108));
	rect.setCornersRadius(5);
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			rect.setFillColor(colorTable[0]);
			rect.setPosition(j * (108 + 13.6f) + 13.6f, i * (108 + 13.6f) + 13.6f);
			fldtx.draw(rect);
		}
	}

	fldtx.display();
	sf::Texture* tx = new sf::Texture{ fldtx.getTexture() };
	background.setTexture(*tx);
}

void sf::Field::loadFromFile(string path)
{
	ifstream fin(path, ios_base::binary);
	if (!fin.is_open()) {
		bestscore = 0;
		return;
	}

	fin.read((char*)&bestscore, sizeof bestscore);

	char flag{};
	fin.read((char*)&flag, sizeof flag);
	if (flag == 0) {
		fin.close();
		return;
	}

	FieldFile ff{};
	fin.read((char*)&ff, sizeof ff);
	gf.setScore(ff.score);
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			gf.at(i, j) = ff.arr[i][j];
		}
	}
	fin.close();
}

void sf::Field::saveFromFile(string path)
{
	ofstream fout(path, ios_base::binary);
	if (!fout.is_open()) return;

	fout.write((char*)&bestscore, sizeof bestscore);
	char flag = static_cast<char> (!gf.isGameOver());
	fout.write((char*)&flag, sizeof flag);
	if (flag == 0) {
		fout.close();
		return;
	}

	FieldFile ff{};
	ff.score = gf.getScore();
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			ff.arr[i][j] = gf.at(i, j);
		}
	}
	fout.write((char*)&ff, sizeof ff);
	fout.close();
}

int sf::Field::getScore() const {
	return gf.getScore();
}

int sf::Field::getBestScore() const
{
	return bestscore;
}

void sf::Field::setBestScore(int scr)
{
	bestscore = scr;
}

bool sf::Field::isAnimation() const
{
	return flagAnimMove || flagAnimWt || flagAnimRand;
}

bool sf::Field::isGameOver() const
{
	return flagGameOver;
}

bool sf::Field::isWin() const
{
	return flagWin;
}

void sf::Field::restart()
{
	flagGameOver = false;
	flagWin = false;
	valueGO = 0;
	valueW = 0;
	gf.restart();
}

void sf::Field::keepGoing()
{
	gf.keepGoing();
	flagWin = false;
	valueW = 0;
}

void sf::Field::move(char dir) {
	if (flagGameOver || flagWin) return;
	direction = dir;
	bool isMove = gf.move(dir);
	flagGameOver = gf.isGameOver();
	flagWin = gf.isWin();

	if (isMove) {
		flagAnimMove = true;
		flagAnimWt = true;
		flagAnimRand = true;
		randtlsize = 0;
		for (int i{}; i < 4; i++) {
			for (int j{}; j < 4; j++) {
				tlsize[i][j] = -1;
				if (gf.atd(i, j)) {
					tlcoord[i][j] = { j * (108 + 13.6f) + 13.6f, i * (108 + 13.6f) + 13.6f };
				}
			}
		}
	}
}

sf::RectangleShape sf::Field::update() {
	if (!isAnimation()) {
		if (flagGameOver) {
			AnimGameOver();
		}
		else if (flagWin) {
			AnimWin();
		}
		else {
			withoutAnim();
		}
	}
	else if (flagAnimMove) {
		AnimMove();
	}
	else if (flagAnimWt) {
		AnimWt();
	}
	else if (flagAnimRand) {
		AnimRand();
	}

	fieldRect.setTexture(&fldtx.getTexture());
	clock.restart();
	return fieldRect;
}

void sf::Field::AnimMove() {
	flagAnimMove = false;
	fldtx.clear();
	fldtx.draw(background);

	rect.setSize(sf::Vector2f(108, 108));

	time = clock.getElapsedTime().asMilliseconds();
	const float speed = 2.4;
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {

			if (gf.atd(i, j)) {
				switch (direction) {
				case 'w':
					if (tlcoord[i][j].y - 1.f * time * speed <= (i - gf.atd(i, j)) * (108 + 13.6f) + 13.6f) {
						tlcoord[i][j].y = (i - gf.atd(i, j)) * (108 + 13.6f) + 13.6f;
						break;
					}
					flagAnimMove = true;
					tlcoord[i][j].y -= 1.f * time * speed;
					break;
				case 's':
					if (tlcoord[i][j].y + 1.f * time * speed >= (i + gf.atd(i, j)) * (108 + 13.6f) + 13.6f) {
						tlcoord[i][j].y = (i + gf.atd(i, j)) * (108 + 13.6f) + 13.6f;
						break;
					}
					flagAnimMove = true;
					tlcoord[i][j].y += 1.f * time * speed;
					break;
				case 'a':
					if (tlcoord[i][j].x - 1.f * time * speed <= (j - gf.atd(i, j)) * (108 + 13.6f) + 13.6f) {
						tlcoord[i][j].x = (j - gf.atd(i, j)) * (108 + 13.6f) + 13.6f;
						break;
					}
					flagAnimMove = true;
					tlcoord[i][j].x -= 1.f * time * speed;
					break;
				case 'd':
					if (tlcoord[i][j].x + 1.f * time * speed >= (j + gf.atd(i, j)) * (108 + 13.6f) + 13.6f) {
						tlcoord[i][j].x = (j + gf.atd(i, j)) * (108 + 13.6f) + 13.6f;
						break;
					}
					flagAnimMove = true;
					tlcoord[i][j].x += 1.f * time * speed;
					break;
				}
				rect.setFillColor(colorTable[gf.atp(i, j) < 14 ? gf.atp(i, j) : 13]);
				rect.setPosition(tlcoord[i][j]);
				fldtx.draw(rect);

				text.setString(sf::String(to_string(0x1 << gf.atp(i, j))));
				text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
				text.setPosition(tlcoord[i][j].x + 52, tlcoord[i][j].y + 40);
				if (gf.atp(i, j) < 3) text.setFillColor(sf::Color(119, 110, 101));
				else text.setFillColor(sf::Color(249, 246, 242));
				fldtx.draw(text);
			}

			else if (gf.atp(i, j)) {
				if (gf.getRandTile().i == i && gf.getRandTile().j == j) continue;

				rect.setFillColor(colorTable[gf.atp(i, j) < 14 ? gf.atp(i, j) : 13]);
				rect.setPosition(j * (108 + 13.6f) + 13.6f, i * (108 + 13.6f) + 13.6f);
				fldtx.draw(rect);

				text.setString(sf::String(to_string(0x1 << gf.atp(i, j))));
				text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
				text.setPosition(j * (108 + 13.6f) + 13.6f + 52, i * (108 + 13.6f) + 13.6f + 40);
				if (gf.atp(i, j) < 3) text.setFillColor(sf::Color(119, 110, 101));
				else text.setFillColor(sf::Color(249, 246, 242));
				fldtx.draw(text);
			}

		}
	}

	fldtx.display();
}

void sf::Field::AnimWt()
{
	flagAnimWt = false;
	withoutAnim(false);

	time = clock.getElapsedTime().asMilliseconds();
	const float speed = .06;
	float size{};
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			bool flag = false;
			int x{}, y{};
			if (gf.atd(i, j)) {

				switch (direction)
				{
				case 'w':
					if (gf.atp(i, j) != gf.at(i - gf.atd(i, j), j)) {
						flag = true;
						x = j;
						y = i - gf.atd(i, j);
					}
					break;

				case 's':
					if (gf.atp(i, j) != gf.at(i + gf.atd(i, j), j)) {
						flag = true;
						x = j;
						y = i + gf.atd(i, j);
					}
					break;

				case 'a':
					if (gf.atp(i, j) != gf.at(i, j - gf.atd(i, j))) {
						flag = true;
						x = j - gf.atd(i, j);
						y = i;
					}
					break;

				case 'd':
					if (gf.atp(i, j) != gf.at(i, j + gf.atd(i, j))) {
						flag = true;
						x = j + gf.atd(i, j);
						y = i;
					}
					break;
				}

				if (flag) {
					if (tlsize[i][j] == -1) tlsize[i][j] = 0;
					size = (-cosf(tlsize[i][j] * 0.95727f) * 15) + 108 - 3;
					//size = -cosf(tlsize[i][j] * 0.7909523f) * 30 + 108 - 25;
					//size = -cosf(tlsize[i][j] * 0.8721543f) * 30 + 108 - 17;

					rect.setFillColor(colorTable[0]);
					rect.setOrigin(0, 0);
					rect.setPosition(x * (108 + 13.6f) + 13.6f, y * (108 + 13.6f) + 13.6f);
					rect.setSize(sf::Vector2f(108, 108));
					fldtx.draw(rect);

					rect.setFillColor(colorTable[gf.at(y, x) < 14 ? gf.at(y, x) : 13]);
					rect.setOrigin(size / 2.f, size / 2.f);
					rect.setPosition(x * (108 + 13.6f) + 13.6f + 54, y * (108 + 13.6f) + 13.6f + 54);
					rect.setSize(sf::Vector2f(size, size));
					fldtx.draw(rect);

					text.setString(sf::String(to_string(0x1 << gf.at(y, x))));
					text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
					text.setPosition(x * (108 + 13.6f) + 13.6f + 52, y * (108 + 13.6f) + 13.6f + 40);
					if (gf.at(y, x) < 3) text.setFillColor(sf::Color(119, 110, 101));
					else text.setFillColor(sf::Color(249, 246, 242));
					fldtx.draw(text);

					if (tlsize[i][j] + .5f * time * speed >= 3 * M_PI / 2) {
						tlsize[i][j] = 3 * M_PI / 2;
					}
					else {
						flagAnimWt = true;
						tlsize[i][j] += .5f * time * speed;
					}
				}
				
			}

			if (gf.getRandTile().i == i && gf.getRandTile().j == j) {
				rect.setFillColor(colorTable[0]);
				rect.setOrigin(0, 0);
				rect.setPosition(j * (108 + 13.6f) + 13.6f, i * (108 + 13.6f) + 13.6f);
				rect.setSize(sf::Vector2f(108, 108));
				fldtx.draw(rect);
			}
		}
	}
	fldtx.display();
	rect.setOrigin(0, 0);
}

void sf::Field::AnimRand()
{
	flagAnimRand = false;
	withoutAnim(false);

	int x = gf.getRandTile().j;
	int y = gf.getRandTile().i;
	float size;

	time = clock.getElapsedTime().asMilliseconds();
	const float speed = .85;

	rect.setFillColor(colorTable[0]);
	rect.setPosition(x * (108 + 13.6f) + 13.6f, y * (108 + 13.6f) + 13.6f);
	rect.setSize(sf::Vector2f(108, 108));
	fldtx.draw(rect);

	size = -powf((randtlsize - 100) * 0.0824621f, 2.f) + 108;
	//size = randtlsize * 1.08f;
	sf::Color color = colorTable[gf.getRandTile().data < 14 ? gf.getRandTile().data : 13];
	color.a = 39 + static_cast<int>(size) * 2;
	rect.setFillColor(color);

	rect.setOrigin(size / 2.f, size / 2.f);
	rect.setPosition(x * (108 + 13.6f) + 13.6f + 54, y * (108 + 13.6f) + 13.6f + 54);
	rect.setSize(sf::Vector2f(108, 108));
	fldtx.draw(rect);

	text.setString(sf::String(to_string(0x1 << gf.getRandTile().data)));
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(x * (108 + 13.6f) + 13.6f + 52, y * (108 + 13.6f) + 13.6f + 40);
	text.setFillColor(sf::Color(119, 110, 101));
	fldtx.draw(text);

	if (randtlsize + .5f * time * speed >= 100) {
		randtlsize = 100;
	}
	else {
		flagAnimRand = true;
		randtlsize += .5f * time * speed;
	}

	fldtx.display();
	rect.setOrigin(0, 0);
}

void sf::Field::AnimGameOver()
{
	withoutAnim(false);

	time = clock.getElapsedTime().asMilliseconds();
	const float speed = .5;

	rect.setSize(sf::Vector2f(500, 500));
	rect.setPosition(0, 0);
	rect.setOrigin(0, 0);
	rect.setFillColor(sf::Color(238, 228, 218, static_cast<int>(valueGO)));
	fldtx.draw(rect);

	text.setFillColor(sf::Color(119, 110, 101, static_cast<int>(valueGO + 69.f)));
	text.setCharacterSize(60);
	text.setString("Game Over!");
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(rect.getSize().x / 2.f, rect.getSize().y / 2.f - 50);
	fldtx.draw(text);

	if (valueGO + 0.5f * speed * time >= 186) {
		valueGO = 186;
	}
	else {
		valueGO += 0.5f * speed * time;
	}

	fldtx.display();
	text.setCharacterSize(50);
}

void sf::Field::AnimWin()
{
	withoutAnim(false);

	time = clock.getElapsedTime().asMilliseconds();
	const float speed = .34;

	rect.setSize(sf::Vector2f(500, 500));
	rect.setPosition(0, 0);
	rect.setOrigin(0, 0);
	rect.setFillColor(sf::Color(237, 194, 46, static_cast<int>(valueW)));
	fldtx.draw(rect);

	text.setFillColor(sf::Color(249, 246, 242, static_cast<int>(valueW + 127.f)));
	text.setCharacterSize(60);
	text.setString("You Win!");
	text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
	text.setPosition(rect.getSize().x / 2.f, rect.getSize().y / 2.f - 50);
	fldtx.draw(text);

	if (valueW + 0.5f * speed * time >= 128) {
		valueW = 128;
	}
	else {
		valueW += 0.5f * speed * time;
	}

	fldtx.display();
	text.setCharacterSize(50);
}

void sf::Field::withoutAnim(bool isDisplay)
{
	fldtx.clear();
	fldtx.draw(background);

	rect.setSize(sf::Vector2f(108, 108));
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			if (!gf.at(i, j)) continue;
			rect.setFillColor(colorTable[gf.at(i, j) < 14 ? gf.at(i, j) : 13]);
			rect.setPosition(j * (108 + 13.6f) + 13.6f, i * (108 + 13.6f) + 13.6f);
			fldtx.draw(rect);

			text.setString(sf::String(to_string(0x1 << gf.at(i, j))));
			text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
			text.setPosition(j * (108 + 13.6f) + 13.6f + 52, i * (108 + 13.6f) + 13.6f + 40);
			text.setFillColor((gf.at(i, j) < 3 ? sf::Color(119, 110, 101) : sf::Color(249, 246, 242)));
			fldtx.draw(text);
		}
	}

	if (isDisplay) fldtx.display();
}
