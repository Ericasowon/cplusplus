#include "minesweeper.h"

/*
* I'm gonna make some sample testing program of game, minesweeper.
* In this game, there are a series of commands that will play the game.
*
* This project is focusing on the use of an array to store our information
*  about the bombs and where they are on the board.
* I would read a series of commands from a command file and
*  proceed to play the game until either there are no more commands
*   or the game is over.
* The game is over when 1 of two things happen, the player has touched
*  all the spaces in the grid without any bombs, thus safely clearing
*   the board, or they touch a bomb.
*/

void minesweeper(string commands, string output) {

    ifstream inputFile(commands);
    ofstream outputFile(output);

    char board[SIZE][SIZE];
    bool boardtouched[SIZE][SIZE] = { false };

    string command, testboard;
    getline(inputFile, command);
    istringstream iss(command);
    iss >> command >> testboard;

    if (command == "load")
        loadBoardFromFile(testboard, board);
    outputFile << "Command: " << command << " " << testboard << endl;

    int x = 0, y = 0;
    bool GAME_END = { false };
    /* The Game is over when 1 of 3 things has occured:
    *
    *  1: When there are no more commands in the input command file.
    *  2: When the user has touched all 54 spaces that do not contain a bomb.
    *     (Winning Condition)
    *  3: When the user touches a bomb.
    *     (Losing Condigion)
    */

    while (inputFile >> command) {
        if (command == "touch") {
            inputFile >> x >> y;
            TouchBoard(boardtouched, x, y);
            outputFile << "Command: " << command << " " << x << " " << y << endl;
            if (board[x - 1][y - 1] == '*') {
                GAME_END = true;
                break;
            }
        }
        else if (command == "display") {
            outputFile << "Command: " << command << endl;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++)
                    outputFile << '.';
                outputFile << endl;
            }
            outputFile << endl;
            break;
        }
    }
    DisplayBoard(board, boardtouched, outputFile, GAME_END);

    outputFile.close();
    inputFile.close();
}

void TouchBoard(bool board[SIZE][SIZE], int x, int y) {
    board[x - 1][y - 1] = true;
}

void loadBoardFromFile(string file, char board[SIZE][SIZE]) {
    ifstream testingboard(file);
    char element;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            testingboard >> element;
            board[i][j] = element;
        }
    }
}

void DisplayBoard(char board[SIZE][SIZE], bool boardtouched[SIZE][SIZE], ofstream& outputFile, bool GAME_END) {

    int NumberOfTouch = 0;
    int RealBoard[SIZE][SIZE];
    for (int m = 0; m < SIZE; m++) {
        for (int n = 0; n < SIZE; n++) {
            RealBoard[m][n] = 0;
            if (boardtouched[m][n])
                NumberOfTouch++;
        }
    }

    if (GAME_END) {
        if (NumberOfTouch != 0) {
            outputFile << "Game Over" << endl;
            outputFile << "~~~~~~~~~" << endl;
            outputFile << "Final Board" << endl;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (boardtouched[i][j]) {
                        if (board[i][j] == '*')
                            outputFile << '*';
                        else {
                            int bombcount = BombCounts(board, i, j);
                            if (bombcount == 0) {
                                outputFile << '0';
                            }
                            else {
                                outputFile << bombcount;
                                bombcount = 0;
                            }
                        }
                    }
                    else {
                        if (board[i][j] == '*')
                            outputFile << '@';
                        else if (board[i][j] == '.')
                            outputFile << '.';
                    }
                }
                outputFile << endl;
            }
        }
    }
    else {
        outputFile << "Game Over" << endl;
        outputFile << "~~~~~~~~~" << endl;
        outputFile << "Final Board" << endl;

        if (NumberOfTouch == 0) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == '*') {
                        outputFile << '@';
                    }
                    else
                        outputFile << '.';
                }
                outputFile << endl;
            }
        }
        else {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (boardtouched[i][j]) {
                        if (board[i][j] == '*')
                            outputFile << '*';
                        else {
                            int bombcount = BombCounts(board, i, j);
                            if (bombcount == 0) {
                                outputFile << '0';
                            }
                            else {
                                outputFile << bombcount;
                            }
                        }
                    }
                    else {
                        if (board[i][j] == '*')
                            outputFile << '@';
                        else if (board[i][j] == '.')
                            outputFile << '.';
                    }
                }
                outputFile << endl;
            }
        }
    }
    outputFile << endl;
    outputFile << "Spaces touched: " << NumberOfTouch << endl;
}

int BombCounts(char board[SIZE][SIZE], int x, int y) {
    int bombcount = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int _x = x + i;
            int _y = y + j;
            if (_x >= 0 && _x < SIZE && _y >= 0 && _y < SIZE) {
                if (board[_x][_y] == '*')
                    bombcount++;
            }

        }
    }
    return bombcount;
}


int main() {
    cout << "Testing minesweeper" << endl;
    minesweeper("test1commands.txt", "test1_output_mine.txt");
    minesweeper("test2commands.txt", "test2_output_mine.txt");
    minesweeper("test3commands.txt", "test3_output_mine.txt");
    minesweeper("test4commands.txt", "test4_output_mine.txt");
    minesweeper("test5commands.txt", "test5_output_mine.txt");
    minesweeper("test6commands.txt", "test6_output_mine.txt");
    minesweeper("test7commands.txt", "test7_output_mine.txt");
    minesweeper("test8commands.txt", "test8_output_mine.txt");
    minesweeper("test9commands.txt", "test9_output_mine.txt");
    minesweeper("test10commands.txt", "test10_output_mine.txt");
    return 0;
}