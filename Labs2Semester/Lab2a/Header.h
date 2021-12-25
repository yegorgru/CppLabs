#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <deque>
#include <ctime>
#include <fstream>
#include "Header1.h"


struct point {
	double x;
	double y;
	double z;

	friend std::ostream& operator<< (std::ostream& out, const point& point);
};

void main_launch();
int main_menu();
int storage();

void demomode();

void benchmark();

int menu();
void show_menu(int choise);
point get_point();


template<typename list>
void actions(list& his_list, int what_list) {
	int control = menu();
	while (control != 10) {
		if (control == 0) {
			point to_push = get_point();
			if (his_list.append(to_push)) {
				std::cout << "Successfully" << std::endl;
			}
			system("pause");
			control = menu();
		}
		else if (control == 1) {
			point to_push = get_point();
			if (his_list.push_front(to_push)) {
				std::cout << "Successfully" << std::endl;
			}
			system("pause");
			control = menu();
		}
		else if (control == 2) {
			if (his_list.pop_back()) {
				std::cout << "Successfully" << std::endl;
			}
			system("pause");
			control = menu();
		}
		else if (control == 3) {
			if (his_list.pop_front()) {
				std::cout << "Successfully" << std::endl;
			}
			system("pause");
			control = menu();
		}
		else if (control == 4) {
			if (his_list.length() == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				system("pause");
			}
			else {
				point to_insert = get_point();
				int number = 0;
				bool correct = false;
				char ch;
				system("cls");
				while (!correct||number == 0) {
					std::cout << "How many points do you want to insert?" << std::endl;
					std::cin >> number;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(INT64_MAX, '\n');
						std::cout << "Incorrect input" << std::endl;
						Sleep(3000);
						system("cls");
						correct = false;
						continue;
					}
					else {
						correct = true;
					}
					while (correct && std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							break;
						}
						else if (ch == '\n') {
							correct = true;
							break;
						}
					}
				}
				correct = false;
				int position = -1;
				system("cls");
				while (!correct||position == -1) {
					std::cout << "Insert before... ";
					std::cin >> position;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(INT64_MAX, '\n');
						std::cout << "Incorrect input" << std::endl;
						Sleep(3000);
						system("cls");
						correct = false;
						continue;
					}
					else {
						correct = true;
					}
					while (correct&& std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							break;
						}
						else if (ch == '\n') {
							correct = true;
							break;
						}
					}
				}
				if (his_list.insert(position, number, to_insert)) {
					std::cout << "Successfully" << std::endl;
				}
				system("pause");
			}
			control = menu();
		}
		else if (control == 5) {
			if (his_list.length() == 0) {
				std::cout << "You can't remove from empty list" << std::endl;
				system("pause");
			}
			else {
				int choise = 0;
				int code;
				do {
					system("cls");
					choise = (choise + 2) % 2;
					if (choise == 0) std::cout << "-> remove 1 point" << std::endl;
					else  std::cout << "   remove 1 point" << std::endl;
					if (choise == 1) std::cout << "-> remove range of points" << std::endl;
					else  std::cout << "   remove range of points" << std::endl;
					code = _getch();
					if (code == 224)
					{
						code = _getch();
						if (code == 80) choise++;
						if (code == 72) choise--;
					}
				} while (code != 13);
				system("cls");
				if (choise == 0) {
					int position = -1;
					bool correct = false;
					char ch;
					while (!correct||position == -1) {
						std::cout << "Remove position... ";
						std::cin >> position;
						if (std::cin.fail()) {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							continue;
						}
						else {
							correct = true;
						}
						while (correct&& std::cin.get(ch)) {
							if (ch != '\n' && ch != ' ') {
								std::cin.clear();
								std::cin.ignore(INT64_MAX, '\n');
								std::cout << "Incorrect input" << std::endl;
								Sleep(3000);
								system("cls");
								correct = false;
								break;
							}
							else if (ch == '\n') {
								correct = true;
								break;
							}
						}
					}
					if (his_list.remove(position)) {
						std::cout << "Successfully" << std::endl;
					}
					system("pause");
				}
				else if (choise == 1) {
					int begin = -1;
					bool correct = false;
					char ch;
					while (!correct || begin == -1) {
						std::cout << "Remove from... ";
						std::cin >> begin;
						if (std::cin.fail()) {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							continue;
						}
						else {
							correct = true;
						}
						while (correct && std::cin.get(ch)) {
							if (ch != '\n' && ch != ' ') {
								std::cin.clear();
								std::cin.ignore(INT64_MAX, '\n');
								std::cout << "Incorrect input" << std::endl;
								Sleep(3000);
								system("cls");
								correct = false;
								break;
							}
							else if (ch == '\n') {
								correct = true;
								break;
							}
						}
					}
					int end = -1;
					while (!correct || end == -1) {
						std::cout << "Remove to... ";
						std::cin >> end;
						if (std::cin.fail()) {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							continue;
						}
						else {
							correct = true;
						}
						while (correct && std::cin.get(ch)) {
							if (ch != '\n' && ch != ' ') {
								std::cin.clear();
								std::cin.ignore(INT64_MAX, '\n');
								std::cout << "Incorrect input" << std::endl;
								Sleep(3000);
								system("cls");
								correct = false;
								break;
							}
							else if (ch == '\n') {
								correct = true;
								break;
							}
						}
					}
					if (his_list.remove(begin, end)) {
						std::cout << "Successfully" << std::endl;
					}
					system("pause");
				}
			}
			control = menu();
		}
		else if (control == 6) {
			std::cout << his_list.length();
			std::cout << std::endl;
			system("pause");
			control = menu();
		}
		else if (control == 7) {
			if (his_list.length() == 0) {
				std::cout << "This list is empty" << std::endl;
				system("pause");
			}
			else {
				int position = -1;
				bool correct = false;
				char ch;
				while (!correct || position == -1) {
					std::cout << "Point's position... ";
					std::cin >> position;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(INT64_MAX, '\n');
						std::cout << "Incorrect input" << std::endl;
						Sleep(3000);
						system("cls");
						correct = false;
						continue;
					}
					else {
						correct = true;
					}
					while (correct && std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							break;
						}
						else if (ch == '\n') {
							correct = true;
							break;
						}
					}
				}
				point* found = his_list.get(position);
				if (found) {
					std::cout << "Address is: " << found << std::endl;
				}
				system("pause");
			}
			control = menu();
		}
		else if (control == 8) {
			if (his_list.length() == 0) {
				std::cout << "This list is empty" << std::endl;
				system("pause");
			}
			else {
				int position = -1;
				bool correct = false;
				char ch;
				while (!correct || position == -1) {
					std::cout << "Point's position... ";
					std::cin >> position;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(INT64_MAX, '\n');
						std::cout << "Incorrect input" << std::endl;
						Sleep(3000);
						system("cls");
						correct = false;
						continue;
					}
					else {
						correct = true;
					}
					while (correct && std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							break;
						}
						else if (ch == '\n') {
							correct = true;
							break;
						}
					}
				}
				point value = get_point();
				if (his_list.set(position, value)) {
					std::cout << "Successfully" << std::endl;
				}
				system("pause");
			}
			control = menu();
		}
		else if (control == 9) {
			if (his_list.length() == 0) {
				std::cout << "This list is empty" << std::endl;
				system("pause");
			}
			else {
				int choise = 0;
				int code;
				do {
					system("cls");
					choise = (choise + 2) % 2;
					if (choise == 0) std::cout << "-> show all points" << std::endl;
					else  std::cout << "   show all points" << std::endl;
					if (choise == 1) std::cout << "-> show certain point" << std::endl;
					else  std::cout << "   show certain point" << std::endl;
					code = _getch();
					if (code == 224)
					{
						code = _getch();
						if (code == 80) choise++;
						if (code == 72) choise--;
					}
				} while (code != 13);
				if (choise == 0) {
					his_list.show();
					system("pause");
				}
				else if (choise == 1) {
					int position = -1;
					while (position == -1) {
						std::cout << "To show position... ";
						std::cin >> position;
						if (std::cin.fail())
						{
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "You entered not a number\n";
							Sleep(3000);
							system("cls");
							position = -1;
						}
						else {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							system("cls");
						}
						his_list.show(position);
						std::cout << std::endl;
						system("pause");
					}
				}
			}
			control = menu();
		}
	}
	if (control == 10) {
		int choise = 0;
		int code;
		do {
			system("cls");
			choise = (choise + 4) % 4;
			if (choise == 0) std::cout << "-> continue in ordinary list" << std::endl;
			else  std::cout << "   continue in ordinary list" << std::endl;
			if (choise == 1) std::cout << "-> continue in dynamic list" << std::endl;
			else  std::cout << "   continue in dynamic list" << std::endl;
			if (choise == 2) std::cout << "-> continue in double-linked list" << std::endl;
			else  std::cout << "   continue in double-linked list" << std::endl;
			if (choise == 3) std::cout << "-> exit" << std::endl;
			else  std::cout << "   exit" << std::endl;
			code = _getch();
			if (code == 224)
			{
				code = _getch();
				if (code == 80) choise++;
				if (code == 72) choise--;
			}
		} while (code != 13);
		system("cls");
		if (choise == 0) {
			if (what_list == 1) {
				actions(his_list, 1);
				return;
			}
			else if (what_list == 2 || what_list == 3) {
				int size = -1;
				bool correct = false;
				char ch;
				while (!correct || size <= 0) {
					std::cout << "Enter size... ";
					std::cin >> size;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(INT64_MAX, '\n');
						std::cout << "Incorrect input" << std::endl;
						Sleep(3000);
						system("cls");
						correct = false;
						continue;
					}
					else {
						correct = true;
					}
					while (correct && std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input" << std::endl;
							Sleep(3000);
							system("cls");
							correct = false;
							break;
						}
						else if (ch == '\n') {
							correct = true;
							break;
						}
					}
				}
				firstList::List<point>my_list(size);
				for (size_t i = 0; i < his_list.length(); i++) {
					if (!my_list.append(*his_list.get(i))) {
						std::cout << "List was overflowed, some data can be losed" << std::endl;
						system("pause");
						break;
					}
				}
				actions(my_list, 1);
				return;
			}
		}
		else if (choise == 1) {
			if (what_list == 1 || what_list == 3) {
				secondList::List<point>my_list;
				for (size_t i = 0; i < his_list.length(); i++) {
					my_list.append(*his_list.get(i));
				}
				actions(my_list, 2);
				return;
			}
			else if (what_list == 2) {
				actions(his_list, 2);
				return;
			}
		}
		else if (choise == 2) {
			if (what_list == 1 || what_list == 2) {
				thirdList::List<point>my_list;
				for (size_t i = 0; i < his_list.length(); i++) {
					my_list.append(*his_list.get(i));
				}
				actions(my_list, 3);
				return;
			}
			else if (what_list == 3) {
				actions(his_list, 3);
				return;
			}
		}
		else if (choise == 3) {
			his_list.~list();
			std::cout << "goodby!" << std::endl;
			return;
		}
	}
}