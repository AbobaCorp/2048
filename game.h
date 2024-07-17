#pragma once
#include <cmath>

namespace game {
	struct point {
		int i;
		int j;
		int data;
	};

	class field {
		int tiles[4][4]{};
		int prevt[4][4]{};
		int dist[4][4]{};
		point randTile{};
		int score{};
		bool flagKeepGoing{};
		void rotate(int deg);
		void addRandTiles();
	public:
		field();

		int& at(int i, int j) { return tiles[i][j]; }
		int atd(int i, int j) const { return dist[i][j]; }
		int atp(int i, int j) const { return prevt[i][j]; }
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