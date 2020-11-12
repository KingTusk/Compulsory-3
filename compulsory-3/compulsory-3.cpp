#include <iostream>
#include <Windows.h>
#include "Password.h"
#include "Battleship.h"

int main()
{
	user_Input();
	if (read_Password()) {
		bool acceptableInput = false;
		char choice = 'n';
		do {
			std::cout << "Choose what to do:" << std::endl << "1: Change the password" << std::endl << "2: play battleship" << std::endl << "3: Quit" << std::endl;
			choice = _getch();
			system("cls");
			if (choice == '1' || choice == '2' || choice == '3') {
				acceptableInput = true;
			}
			else {
				std::cout << "You can only type 1, 2 or 3!" << std::endl;
			}
		} while (!acceptableInput);
		switch (choice) {
		case '1':
			change_Password();
			break;
		case '2':
			play();
			break;
		case '3':
			std::cout << "Ending applicaiton...";
			Sleep(3000);
			return 0;
		}
	}
	else
	{
		std::cout << "fail, input was " << input << " password was " << password;
	}
}