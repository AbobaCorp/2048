#pragma once
#include <cmath>

namespace game {
	struct point {
		int i;
		int j;
		int data;
	};

	class field {
		//плитки
		int tiles[4][4]{};
		//предыдущее положение плиток
		int prevt[4][4]{};
		//матрица движения плиток
		int dist[4][4]{};
		//положение рандомной плитки
		point randTile{};
		//счет игры
		int score{};
		bool flagKeepGoing{};
		//поворот матрицы tiles
		void rotate(int deg);
		//добавление случайной плитки
		void addRandTiles();
	public:
		field();

		int& at(int i, int j) { return tiles[i][j]; }
		int atd(int i, int j) const { return dist[i][j]; }
		int atp(int i, int j) const { return prevt[i][j]; }
		//\return True если было движение плиток, иначе - False
		bool move(char dir);
		void restart();
		void keepGoing();
		point getRandTile() const { return randTile; }
		bool isGameOver() const;
		bool isWin() const;
		int getScore() const { return score; }
		void setScore(int scr) { score = scr; }
	};
}