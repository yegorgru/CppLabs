#include "Header.h"

std::ostream& operator<<(std::ostream& out, const point& point)
{
	out << '(' << point.x << ", " << point.y << ", " << point.z << ')';
	return out;
}

bool operator==(const point& point1, const point& point2)
{
	return (point1.x==point2.x&& point1.y == point2.y&& point1.z == point2.z);
}

void main_launch() {
	int what_mode1 = main_menu1();
	if (what_mode1 == 2) {
		system("cls");
		std::cout << "goodby!" << std::endl;
		return;
	}
	else {
		int what_mode2 = main_menu2();
		if (what_mode1 == 0 && what_mode2 == 0) {
			actions();
		}
		else if (what_mode1 == 0 && what_mode2 == 1) {
			demomode1();
			system("pause");
			system("cls");
			main_launch();
			return;
		}
		else  if (what_mode1 == 1 && what_mode2 == 0) {
			actions2();
		}
		else if (what_mode1 == 1 && what_mode2 == 1) {
			demomode2();
			system("pause");
			system("cls");
			main_launch();
			return;
		}
	}
}


int main_menu1() {
	int what_mode = 0;
	int code;
	do {
		system("cls");
		std::cout << "What mode?\n";
		what_mode = (what_mode + 3) % 3;
		if (what_mode == 0) std::cout << "-> Hashed array tree (Lab 2b 28, 1)" << std::endl;
		else  std::cout << "   Hashed array tree (Lab 2b 28, 1)" << std::endl;
		if (what_mode == 1) std::cout << "-> messages (Lab 2b 16)" << std::endl;
		else  std::cout << "   messages (Lab 2b 16)" << std::endl;
		if (what_mode == 2) std::cout << "-> finish" << std::endl;
		else  std::cout << "   finish" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) what_mode++;
			if (code == 72) what_mode--;
		}
	} while (code != 13);
	system("cls");
	return what_mode;
}


int main_menu2() {
	int what_mode = 0;
	int code;
	do {
		system("cls");
		std::cout << "What mode?\n";
		what_mode = (what_mode + 3) % 3;
		if (what_mode == 0) std::cout << "-> interactive mode" << std::endl;
		else  std::cout << "   interactive mode" << std::endl;
		if (what_mode == 1) std::cout << "-> demo mode" << std::endl;
		else  std::cout << "   demo mode" << std::endl;
		if (what_mode == 2) std::cout << "-> exit" << std::endl;
		else  std::cout << "   exit" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) what_mode++;
			if (code == 72) what_mode--;
		}
	} while (code != 13);
	system("cls");
	return what_mode;
}

int menu() {
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 11) % 11;
		if (choise == 0) std::cout << "-> push point back" << std::endl;
		else  std::cout << "   push point back" << std::endl;
		if (choise == 1) std::cout << "-> push point front" << std::endl;
		else  std::cout << "   push point front" << std::endl;
		if (choise == 2) std::cout << "-> pop point back" << std::endl;
		else  std::cout << "   pop point back" << std::endl;
		if (choise == 3) std::cout << "-> pop point front" << std::endl;
		else  std::cout << "   pop point front" << std::endl;
		if (choise == 4) std::cout << "-> insert point" << std::endl;
		else  std::cout << "   insert point" << std::endl;
		if (choise == 5) std::cout << "-> remove point" << std::endl;
		else  std::cout << "   remove point" << std::endl;
		if (choise == 6) std::cout << "-> set element" << std::endl;
		else  std::cout << "   set element" << std::endl;
		if (choise == 7) std::cout << "-> show elements" << std::endl;
		else  std::cout << "   show elements" << std::endl;
		if (choise == 8) std::cout << "-> find out size of tree" << std::endl;
		else  std::cout << "   find out size of tree" << std::endl;
		if (choise == 9) std::cout << "-> find element" << std::endl;
		else  std::cout << "   find element" << std::endl;
		if (choise == 10) std::cout << "-> finish" << std::endl;
		else  std::cout << "   finish" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}

	} while (code != 13);
	system("cls");
	return choise;
}



point get_point() {
	system("cls");
	point to_return;
	bool correct = false;
	char ch;
	while (!correct) {
		std::cout << "Enter x-coordinate" << std::endl;
		std::cin >> to_return.x;
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
		if (correct) {
			std::cout << "Enter y-coordinate" << std::endl;
			std::cin >> to_return.y;
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
			if (correct) {
				std::cout << "Enter z-coordinate" << std::endl;
				std::cin >> to_return.z;
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
		}
	}
	return to_return;
}

void actions() {
	HAT<point>tree;
	int control = menu();
	while (control != 10) {
		if (control == 0) {
			point to_push = get_point();
			tree.push_back(to_push);
			std::cout << "Successfully" << std::endl;
			system("pause");
			control = menu();
		}
		else if (control == 1) {
			point to_push = get_point();
			tree.push_front(to_push);
			std::cout << "Successfully" << std::endl;
			system("pause");
			control = menu();
		}
		else if (control == 2) {
			if (tree.pop_back()) {
				std::cout << "Successfully" << std::endl;
			}
			system("pause");
			control = menu();
		}
		else if (control == 3) {
			if (tree.pop_front()) {
				std::cout << "Successfully" << std::endl;
			}
			system("pause");
			control = menu();
		}
		else if (control == 4) {
			if (tree.length() == 0) {
				std::cout << "You can't insert in empty tree" << std::endl;
				system("pause");
			}
			else {
				point to_insert = get_point();
				int number = 0;
				bool correct = false;
				char ch;
				int position;
				system("cls");
				while (!correct) {
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
				if (tree.insert(position, to_insert)) {
					std::cout << "Successfully" << std::endl;
				}
				system("pause");
			}
			control = menu();
		}
		else if (control == 5) {
			if (tree.length() == 0) {
				std::cout << "You can't remove from empty list" << std::endl;
				system("pause");
			}
			else {
				int position;
				bool correct = false;
				char ch;
				while (!correct) {
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
				if (tree.erase(position)) {
					std::cout << "Successfully" << std::endl;
				}
				system("pause");
			}
			control = menu();
		}
		else if (control == 6) {
			if (tree.length() == 0) {
				std::cout << "This list is empty" << std::endl;
				system("pause");
			}
			else {
				int position;
				bool correct = false;
				char ch;
				while (!correct) {
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
				if (tree.set(position, value)) {
					std::cout << "Successfully" << std::endl;
				}
				system("pause");
			}
			control = menu();
		}
		else if (control == 8) {
			std::cout << tree.length();
			std::cout << std::endl;
			system("pause");
			control = menu();
		}
		else if (control == 7) {
			if (tree.length() == 0) {
				std::cout << "This list is empty" << std::endl;
				system("pause");
			}
			else {
				tree.show();
				system("pause");
			}
			control = menu();
		}
		else if (control == 9) {
			point to_search = get_point();
			std::cout << tree.search(to_search)<<std::endl;
			system("pause");
			control = menu();
		}
	}
	if (control == 10) {
		std::cout << "goodby!" << std::endl;
		return;
	}
}

int menu2() {
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 3) % 3;
		if (choise == 0) std::cout << "-> to add message" << std::endl;
		else  std::cout << "   to add message" << std::endl;
		if (choise == 1) std::cout << "-> show last K messages" << std::endl;
		else  std::cout << "   show last K messages" << std::endl;
		if (choise == 2) std::cout << "-> finish" << std::endl;
		else  std::cout << "   finish" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}

	} while (code != 13);
	system("cls");
	return choise;
}

void actions2()
{
	int size=-1;
	int number = 0;
	bool correct = false;
	char ch;
	system("cls");
	while (!correct || size == -1) {
		std::cout << "Enter max size"<<std::endl;
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
	messageList messages(size);
	int control = menu2();
	while (control != 2) {
		if (control == 0) {
			std::cout << "Enter your message" << std::endl;
			std::string str;
			std::getline(std::cin,str);
			tm* current;
			const time_t timer = time(NULL);
			current = localtime(&timer);
			messages.push_back(str, *current);
			control = menu2();
		}
		else if (control == 1) {
			int K = -1;
			int number = 0;
			bool correct = false;
			char ch;
			system("cls");
			while (!correct || K == -1) {
				std::cout << "Enter K" << std::endl;
				std::cin >> K;
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
			messages.show_K(K);
			system("pause");
			control = menu2();
		}
	}
	if (control == 2) {
		std::cout << "goodby!" << std::endl;
		return;
	}
}

void show_menu(int choise) {
	std::string menu[] = { "push point back","push point front","pop point back","pop point front","insert point","remove point",
	"set element","show elements",
	"find out size of tree", "find element","finish" };
	for (int i = 0; i <= choise; i++) {
		for (int j = 0; j < 11; j++) {
			if (j == i) {
				std::cout << "-> " << menu[j] << std::endl;
			}
			else {
				std::cout << "   " << menu[j] << std::endl;
			}
		}
		Sleep(250);
		system("cls");
	}
}

void demomode1() {
	HAT<point>list;
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(0);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 0 << std::endl;
	std::cout << "Enter y-coordinate" << std::endl;
	Sleep(1000);
	std::cout << '-';
	Sleep(1000);
	std::cout << 2 << std::endl;
	std::cout << "Enter z-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 2;
	Sleep(500);
	std::cout << 7;
	Sleep(1000);
	system("cls");
	list.push_front({ 10,-2,27 });
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");


	show_menu(1);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << '-';
	Sleep(1000);
	std::cout << 5 << std::endl;
	std::cout << "Enter y-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 5;
	Sleep(1000);
	std::cout << 6 << std::endl;
	std::cout << "Enter z-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 7 << std::endl;
	Sleep(1000);
	system("cls");
	list.push_front({ -5,56,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");


	show_menu(2);
	list.pop_back();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(4);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 2 << std::endl;
	std::cout << "Enter y-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 6 << std::endl;
	std::cout << "Enter z-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 3 << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Insert before... ";
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	list.insert(0, { 12,6,3 });
	std::cout << "Successfully" << std::endl;
	Sleep(2000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(2);
	list.pop_front();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(0);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 0 << std::endl;
	std::cout << "Enter y-coordinate" << std::endl;
	Sleep(1000);
	std::cout << '-';
	Sleep(1000);
	std::cout << 2 << std::endl;
	std::cout << "Enter z-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 2;
	Sleep(500);
	std::cout << 7;
	Sleep(1000);
	system("cls");
	list.push_front({ 10,-2,27 });
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");


	show_menu(5);
	Sleep(1000);
	system("cls");
	std::cout << "Remove position... ";
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	list.erase(1);
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(8);
	std::cout << list.length() << std::endl;
	Sleep(1000);
	system("cls");


	show_menu(6);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 3;
	Sleep(1000);
	std::cout << 2 << std::endl;
	std::cout << "Enter y-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 4 << std::endl;
	std::cout << "Enter z-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 7 << std::endl;
	Sleep(1000);
	system("cls");
	list.set(0, { 32,4,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(7);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(6);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 3;
	Sleep(1000);
	std::cout << 2 << std::endl;
	std::cout << "Enter y-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 4 << std::endl;
	std::cout << "Enter z-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 7 << std::endl;
	Sleep(1000);
	system("cls");
	std::cout<<list.search({ 32,4,7 });
	Sleep(2000);
	system("cls");
	show_menu(10);
	std::cout << "goodby" << std::endl;
	system("cls");
}

void demomode2()
{
	std::cout << "Enter max size" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(500);
	system("cls");
	messageList list(5);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'A';
	Sleep(500);
	std::cout << 'A';
	Sleep(500);
	std::cout << 'A';
	Sleep(500);
	system("cls");
	tm* current;
	time_t timer = time(NULL);
	current = localtime(&timer);
	list.push_back("AAA", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(500);
	system("cls");
	list.show_K(1);
	Sleep(3000);
	system("cls");

	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'B';
	Sleep(500);
	std::cout << 'B';
	Sleep(500);
	std::cout << 'B';
	Sleep(500);
	system("cls");
	timer = time(NULL);
	current = localtime(&timer);
	list.push_back("BBB", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(500);
	system("cls");
	list.show_K(2);
	Sleep(3000);
	system("cls");

	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'C';
	Sleep(500);
	std::cout << 'C';
	Sleep(500);
	std::cout << 'C';
	Sleep(500);
	system("cls");
	timer = time(NULL);
	current = localtime(&timer);
	list.push_back("CCC", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(500);
	system("cls");
	list.show_K(3);
	Sleep(3000);
	system("cls");



	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'D';
	Sleep(500);
	std::cout << 'D';
	Sleep(500);
	std::cout << 'D';
	Sleep(500);
	system("cls");
	timer = time(NULL);
	current = localtime(&timer);
	list.push_back("DDD", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(500);
	system("cls");
	list.show_K(4);
	Sleep(3000);
	system("cls");

	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'E';
	Sleep(500);
	std::cout << 'E';
	Sleep(500);
	std::cout << 'E';
	Sleep(500);
	system("cls");
	timer = time(NULL);
	current = localtime(&timer);
	list.push_back("EEE", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(500);
	system("cls");
	list.show_K(5);
	Sleep(3000);
	system("cls");



	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'F';
	Sleep(500);
	std::cout << 'F';
	Sleep(500);
	std::cout << 'F';
	Sleep(500);
	system("cls");
	timer = time(NULL);
	current = localtime(&timer);
	list.push_back("FFF", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(500);
	system("cls");
	list.show_K(5);
	Sleep(3000);
	system("cls");


	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter your message" << std::endl;
	std::cout << 'G';
	Sleep(500);
	std::cout << 'G';
	Sleep(500);
	std::cout << 'G';
	Sleep(500);
	system("cls");
	timer = time(NULL);
	current = localtime(&timer);
	list.push_back("GGG", *current);
	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter K" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(500);
	system("cls");
	list.show_K(5);
	Sleep(3000);
	system("cls");

	std::cout << "-> to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "-> show last K messages" << std::endl;
	std::cout << "   finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   to add message" << std::endl;
	std::cout << "   show last K messages" << std::endl;
	std::cout << "-> finish" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "goodby" << std::endl;
}
