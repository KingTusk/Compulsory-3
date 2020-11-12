#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>


const int M = 6, N = 6;
const char BLANK = ' ';
const char SHIP = 'S';
const char MISS = 'M';
const char HIT = 'H';
char board[M][N]; // 2d array with M rows and N columns
int numberOfHits = 0;
int numberOfShots = 15;
int numberOfShipsToShoot = 11;
int numberOfThreeShipsToShoot = 4;
int letterToNumber(char letter);
void makeEmptyBoard();
int randomRow();
int randomColumn();
void writeLetters();
void makeBoard(int numberOfShips);
void printBoard();
void printPlayerBoard();
void shoot();
int getRandomNumber(int min, int max);
void play();
void makeBoard3(int numberOfShips);

void makeBoard3(int numberOfShips) {
    int row = -1;
    int column = -1;
    bool right = false; //this bool is used to determine the rotation of the ship, if true: left to right; else : up to down
    bool okayPos = false;
    for (int i = 0; i < numberOfShips; i++) {//runs until we place the required number of ships
        right = getRandomNumber(0, 1);
        okayPos = false;
        do{ //repeats until we determine a safe starting position for the ship
            row = randomRow();
            column = randomColumn();
            //check for obstructions, other ships or out of bounds
            if (right) {
                if ((row + 3) < M) {
                    okayPos = true;
                }
            }
            else {
                if ((column + 3) < N) {
                    okayPos = true;
                }
            }
        }while (!okayPos);

        if (right) {
            for (int j = 0; j < 3; j++) {
                board[row + j][column] = SHIP;
            }
        }
        else {
            for (int j = 0; j < 3; j++) {
                board[row][column + j] = SHIP;
            }
        }
    }
}

void play() {
    std::cout << "Do you want to pay with big or small ships? 1 for big, 2 for small";
    bool acceptableinput = false;
    char choice = _getch();
    do {
        if (choice == '1' || choice == '2') {
            acceptableinput = true;
            std::cout << "You can only type 1 or 2!";
        }
    } while (!acceptableinput);
    makeEmptyBoard();
    makeBoard(numberOfShipsToShoot);
    do {
        printPlayerBoard();
        std::cout << "There are " << numberOfShipsToShoot << " ships to shoot, you have hit " << numberOfHits << "ships, and you have " << numberOfShots << " shot to get all of them" << std::endl;
        shoot();
        system("cls");
    } while (numberOfShots > 0 && numberOfShipsToShoot > 0);
    if (numberOfShipsToShoot == 0) {
        std::cout << "Congratulations! you got all the ships, and you had " << numberOfShots << " shots left." << std::endl;
    }
    else {
        std::cout << "Too bad! look like you lost, and you only had " << numberOfShipsToShoot << " ships left to shoot as well!" << std::endl;
    }
    std::cout << "You can compare your shots and the ship positions below" << std::endl;
    printBoard();
    printPlayerBoard();
}

void shoot() {
    int row = -1;
    int column = -1;
    char choice = ' ';
    std::cout << "Choose where to shoot by typing Letter and then Number(Example: A3, B4, C2)";
    bool acceptable = false;
    do { //runs until we get a valid input for column
        acceptable = false;
        choice = _getch();
        choice = toupper(choice);
        column = letterToNumber(choice);
        if (column >= 0 && column < N) {
            acceptable = true;
        }
    } while (!acceptable);
    std::cout << choice;
    do { //runs until we get a valid input for row
        acceptable = false;
        row = _getch() - 49;
        if (row >= 0 && row < M) {
            acceptable = true;
        }
    } while (!acceptable);
    if (board[row][column] == SHIP) {
        board[row][column] = HIT;
        numberOfHits++;
    }
    else if (board[row][column] == BLANK) {
        board[row][column] = MISS;
    }
    else if (board[row][column] == MISS || board[row][column] == HIT) {
    }
    numberOfShots--;
}

void printPlayerBoard() {
    for (int i = 0; i < M; i++) {
        std::cout << i + 1 << " |";
        for (int j = 0; j < N; j++) {
            if (board[i][j] == SHIP) {
                std::cout << BLANK << "|";
            }
            else {
                std::cout << board[i][j] << "|";
            }
            if ((j + 1) == N) {
                std::cout << std::endl;
            }
        }
    }
    writeLetters();
    std::cout << std::endl;
}

void printBoard() {
    for (int i = 0; i < M; i++) {
        std::cout << i+1 << " |";
        for (int j = 0; j < N; j++) {
            if (board[i][j] == HIT) {
                std::cout << SHIP << "|";
            }
            else if (board[i][j] == MISS) {
                std::cout << BLANK << "|";
            }
            else {
                std::cout << board[i][j] << "|";
            }
            if ((j + 1) == N) {
                std::cout << std::endl;
            }
        }
    }
    writeLetters();
    std::cout << std::endl;
}

void makeBoard(int numberOfShips) {
    for (int i = 0; i < numberOfShips; i++) {
        //ensures we will always place the required number of ships
        if (board[randomRow()][randomColumn()] != SHIP) {
            board[randomRow()][randomColumn()] = SHIP;
        }
        else {
            i--;
        }
    }
}

void writeLetters() {
    int character = 65;
    std::cout << "   ";
    for (int i = 0; i < N; i++) {
        std::cout << char(character) << " ";
        character++;
    }
}

int randomRow() {
    return getRandomNumber(0, M-1);
}

int randomColumn() {
    return getRandomNumber(0, N-1);
}

void makeEmptyBoard() {
    for (int i = 0; i < M;i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = BLANK;
        }
    }
}

int letterToNumber(char letter) // only big letters
{
    return static_cast<int>(letter) - 65;
}

int getRandomNumber(int min, int max) //code is from learncpp.com, it produces a random number between min and max
{
    static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}