#include "game.h"

game::field::field() {
	addRandTiles();
	addRandTiles();
	//int count{};
	//for (int i{}; i < 4; i++) {
	//	for (int j{}; j < 4; j++) {
	//		tiles[j][i] = count;
	//		count++;
	//	}
	//}

	//tiles[0][0] = 10;
	//tiles[0][1] = 10;
}

bool game::field::move(char dir)
{
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			prevt[i][j] = tiles[i][j];
		}
	}

	int deg{};
	switch (dir)
	{
	case 'w':
		deg = 1;
		break;
	case 's':
		deg = 3;
		break;
	case 'a':
		deg = 2;
		break;
	case 'd':
		deg = 0;
		break;
	default:
		return false;
	}

	rotate(deg);
	bool flag = false;
	for (int i{}; i < 4; i++) {
		for (int j = 4 - 1; j >= 0; j--) {
			dist[i][j] = 0;
			if (!tiles[i][j]) continue;

			int k = j;
			for (k; k < 4 - 1; k++) {
				if (tiles[i][k + 1] == 0) {
					tiles[i][k + 1] = tiles[i][k];
					tiles[i][k] = 0;
				}
				else if (tiles[i][k + 1] == tiles[i][k]) {
					tiles[i][k + 1] += 1;
					tiles[i][k] = 0;

					score += (0x1 << tiles[i][k + 1]);
					k++;
					break;
				}
				else if (tiles[i][k + 1] != tiles[i][k]) {
					break;
				}
			}
			if (k - j != 0) { flag = true; }
			dist[i][j] = k - j;
		}
	}
	rotate(4 - deg);

	if (flag) addRandTiles();
	return flag;
}

void game::field::restart()
{
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			tiles[i][j] = 0;
		}
	}

	addRandTiles();
	addRandTiles();
	score = 0;
	flagKeepGoing = false;
}

void game::field::keepGoing()
{
	flagKeepGoing = true;
}

void game::field::addRandTiles() {
	while (true) {
		int i, j;
		i = rand() % 4;
		j = rand() % 4;
		if (tiles[i][j] == 0) {
			tiles[i][j] = (rand() % 10 > 0 ? 1 : 2);
			randTile = { i, j, tiles[i][j] };
			break;
		}
	}
}

void game::field::rotate(int deg)
{
	if (deg == 4) return;
	int tmpt[4][4]{};
	int tmpd[4][4]{};
	for (int d{}; d < deg; d++)
	{
		for (int i{}; i < 4; i++) {
			for (int j{}; j < 4; j++) {
				tmpt[j][4 - 1 - i] = tiles[i][j];
				tmpd[j][4 - 1 - i] = dist[i][j];
			}
		}
		for (int i{}; i < 4; i++) {
			for (int j{}; j < 4; j++) {
				tiles[i][j] = tmpt[i][j];
				dist[i][j] = tmpd[i][j];
			}
		}
	}
}

bool game::field::isGameOver() const
{
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			if (tiles[i][j] == 0) return false;

			if (i - 1 >= 0) {
				if (tiles[i - 1][j] == tiles[i][j]) return false;
			}
			if (i + 1 < 4) {
				if (tiles[i + 1][j] == tiles[i][j]) return false;
			}
			if (j - 1 >= 0) {
				if (tiles[i][j - 1] == tiles[i][j]) return false;
			}
			if (j + 1 < 4) {
				if (tiles[i][j + 1] == tiles[i][j]) return false;
			}

		}
	}
	return true;
}

bool game::field::isWin() const
{
	if (flagKeepGoing) return false;
	for (int i{}; i < 4; i++) {
		for (int j{}; j < 4; j++) {
			if (tiles[i][j] == 11) return true;
		}
	}
	return false;
}
