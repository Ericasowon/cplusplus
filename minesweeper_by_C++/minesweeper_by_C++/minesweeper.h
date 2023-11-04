#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

const int SIZE = 8;
const int MAX_TEST = 54;
const int BOMBS = 10;

void minesweeper(string commands, string output);
void TouchBoard(bool board[SIZE][SIZE], int x, int y);
void loadBoardFromFile(string file, char board[SIZE][SIZE]);
void DisplayBoard(char board[SIZE][SIZE], bool boardtouched[SIZE][SIZE], ofstream& outputFile, bool GAME_END);
int BombCounts(char board[SIZE][SIZE], int x, int y);