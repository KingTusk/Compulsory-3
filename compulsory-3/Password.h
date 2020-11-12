#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>

char passwordtable[4][4]
{
	{'A','B','C','D',},
	{'E','F','G','H',},
	{'I','J','K','L',},
	{'M','N','O','P',}
};

std::string password = "ABCDHLPONM";
int asteriskposition[2]{ 0,0 };
std::string input = "A"; //this variable is used for all user related input in this header file

void print_Ptable(); //prints passwordtable
void reset_Password(); //resets the password
void updateinput(); //updates the input varable
bool input_password(); //adds to the input varable
bool read_Password(); //compares the input varable and the password varable
void user_Input(); //makes user input a password
void change_Password(); //changes the password
void update_Password(); //updates the password variable with a new password from the passworf.txt resource file
void reset(); //resets the input and the asteriskposition variable
void resetPassword(); //resets the password to it's default value

void resetPassword() {
	password = "ABCDHLPONM";
}

void update_Password() {
	std::fstream passwordFile("password.txt", std::ios::in);
	passwordFile >> password;
	passwordFile.close();
}

void reset() {
	input = "A";
	asteriskposition[0] = 0;
	asteriskposition[0] = 0;
}

void change_Password() {
	reset();
	user_Input();
	std::fstream passwordFile("password.txt", std::ios::out);
	passwordFile << input;
	passwordFile.close();
	update_Password();
	std::cout << "Password has been changed, relaunch application to continue" << std::endl;
}

void user_Input() {
	for (int i = 1; i < password.length(); i++) { //i starts at 1 here because input already has 1 letter: "A"
		system("cls");
		print_Ptable();
		if (input_password()) {
			updateinput();
		}
		else i--;
	}
	system("cls");
	print_Ptable();
}

void print_Ptable() {
	for (int i = 0; i < sizeof(passwordtable) / sizeof(passwordtable[0]); i++) {
		for (int j = 0; j < sizeof(passwordtable[0]) / sizeof(passwordtable[0][0]); j++) {
			if (i == asteriskposition[0] && j == asteriskposition[1]) {
				std::cout << "|*|";
			}
			else {
				std::cout << "|" <<passwordtable[i][j]<< "|";
			}
			if (j % 3 == 0 && j != 0) {
				std::cout << std::endl;
			}
		}
	}
}

void reset_Password() {
	asteriskposition[0] = 0;
	asteriskposition[1] = 0;
	input = "A";
}

bool read_Password() {
	update_Password(); // runs this function to ensure we compare the correct password
	if (input == password) {
		return true;
	}
	else return false;
}

void updateinput() {
	input += passwordtable[asteriskposition[0]][asteriskposition[1]];
}

bool input_password() {
	char keypressed = 'n';
	keypressed = _getch();
	if (keypressed == -32 || keypressed == 224) {
		keypressed = _getch();
	}
	switch (keypressed) {
	case 'w':
	case'W':
	case 72:
		if (asteriskposition[0] != 0) {
			asteriskposition[0]--;
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case's':
	case'S':
	case 80:
		if (asteriskposition[0] != 3) {
			asteriskposition[0]++;
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 'a':
	case 'A':
	case 75:
		if (asteriskposition[1] != 0) {
			asteriskposition[1]--;
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case'd':
	case'D':
	case 77:
		if (asteriskposition[1] != 3) {
			asteriskposition[1]++;
			return true;
			break;
		}
		else{ 
		return false;
		break; }
	default:
		return false;
		break;
	}
}

