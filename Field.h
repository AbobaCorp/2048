#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "game.h"
#include "RoundedRectangleShape.h"
#include <fstream>
using namespace std;

namespace sf {
	struct FieldFile {
		int score;
		int arr[4][4];
	};

	class Field {
	public:
		Field(sf::Font& font);

		void loadFromFile(string path);
		void saveFromFile(string path);

		int getScore() const;
		int getBestScore() const;
		void setBestScore(int scr);
		bool isAnimation() const;
		bool isGameOver() const;
		bool isWin() const;

		void restart();
		void keepGoing();

		void move(char dir);

		void setPosition(float x, float y) { fieldRect.setPosition(x, y); }

		sf::RectangleShape update();

	private:
		void AnimMove();
		void AnimWt();
		void AnimRand();
		void AnimGameOver();
		void AnimWin();
		void withoutAnim(bool isDisplay = true);

		sf::Color colorTable[14] = {
			{205,193,180},
			{238,228,218},
			{238,225,201},
			{243,178,122},
			{246,150,100},
			{247,124,95},
			{247,95,59},
			{237,208,115},
			{237,204,98},
			{237,201,80},
			{237,197,63},
			{237,194,46},
			{255,57,58},
			{255,24,24 }
		};

		sf::RenderTexture fldtx;
		sf::Sprite background;
		sf::Font font;
		sf::Text text;
		game::field gf;
		sf::RoundedRectangleShape rect;
		sf::RectangleShape fieldRect;

		int bestscore{};
		char direction{};
		bool flagAnimMove{};
		sf::Vector2f tlcoord[4][4]{};
		bool flagAnimWt{};
		float tlsize[4][4]{};
		bool flagAnimRand{};
		float randtlsize{};

		bool flagGameOver{};
		float valueGO{};
		bool flagWin{};
		float valueW{};

		sf::Clock clock;
		sf::Int64 time{};
	};
}