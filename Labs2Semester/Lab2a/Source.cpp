#include "Header.h"
#include "Header1.h"


std::ostream& operator<<(std::ostream& out, const point& point)
{
	out << '(' << point.x << ", " << point.y << ", " << point.z << ')';
	return out;
}

void main_launch() {
	int what_mode = main_menu();
	if (what_mode == 4) {
		system("cls");
		std::cout << "goodby!" << std::endl;
		return;
	}
	else if (what_mode == 2) {
		demomode();
		system("pause");
		system("cls");
		main_launch();
		return;
	}
	else if (what_mode == 3) {
		benchmark();
		system("pause");
		system("cls");
		main_launch();
		return;
	}
	else {
		int what_storage=storage();
		if (what_storage == 1) {
			int size = -1;
			bool correct = false;
			char ch;
			while (!correct || size <=0) {
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
			actions(my_list,1);
		}
		if (what_storage == 2) {
			secondList::List<point>my_list;
			actions(my_list,2);
		}
		if (what_storage == 3) {
			thirdList::List<point>my_list;
			actions(my_list, 3);
		}
		if (what_storage == 4) {
			system("cls");
			std::cout << "goodby!" << std::endl;
			return;
		}
	}
}

int main_menu() {
	int what_mode = 0;
	int code;
	do {
		system("cls");
		std::cout << "What mode?\n";
		what_mode = (what_mode + 4) % 4;
		if (what_mode == 0) std::cout << "-> interactive mode" << std::endl;
		else  std::cout << "   interactive mode" << std::endl;
		if (what_mode == 1) std::cout << "-> demo mode" << std::endl;
		else  std::cout << "   demo mode" << std::endl;
		if (what_mode == 2) std::cout << "-> benchmark" << std::endl;
		else  std::cout << "   benchmark" << std::endl;
		if (what_mode == 3) std::cout << "-> exit" << std::endl;
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
	return what_mode + 1;
}

int storage() {
	int what_storage = 0;
	int code;
	do {
		system("cls");
		std::cout << "Continue in:"<<std::endl;
		what_storage = (what_storage + 4) % 4;
		if (what_storage == 0) std::cout << "-> ordinary array" << std::endl;
		else  std::cout << "   ordinary array" << std::endl;
		if (what_storage == 1) std::cout << "-> dynamic array" << std::endl;
		else  std::cout << "   dynamic array" << std::endl;
		if (what_storage == 2) std::cout << "-> double-linked list" << std::endl;
		else  std::cout << "   double-linked list" << std::endl;
		if (what_storage == 3) std::cout << "-> exit" << std::endl;
		else  std::cout << "   exit" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) what_storage++;
			if (code == 72) what_storage--;
		}
	} while (code != 13);
	system("cls");
	return what_storage + 1;
}

void demomode() {
	std::cout << "-> ordinary array" << std::endl
		<< "   dynamic array" << std::endl
		<< "   double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(2000);
	system("cls");
	std::cout << "Enter size... ";
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	firstList::List<point>list(1000);
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(0);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout 	<< 0 << std::endl;
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
	list.append({ 10,-2,27 });
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");


	show_menu(1);
	std::cout << "Enter x-coordinate" << std::endl;
	Sleep(1000);
	std::cout << '-';
	Sleep(1000);
	std::cout << 5<<std::endl;
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
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");

	
	show_menu(2);
	list.pop_back();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
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
	std::cout << "How many points do you want to insert?" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	std::cout << "Insert before... ";
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	list.insert(0, 10, {12,6,3});
	std::cout << "Successfully" << std::endl;
	Sleep(2000);
	system("cls");
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(2);
	list.pop_front();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(5);
	std::cout << "-> remove 1 point" << std::endl
		<< "   remove range of points" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Remove position... ";
	Sleep(1000);
	std::cout << 5;
	Sleep(1000);
	list.remove(5);
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(5);
	std::cout << "   remove 1 point" << std::endl
		<< "-> remove range of points" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   remove 1 point" << std::endl
		<< "-> remove range of points" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Remove from... ";
	Sleep(1000);
	std::cout << 3;
	Sleep(1000);
	system("cls");
	std::cout << "Remove to... ";
	Sleep(1000);
	std::cout << 6;
	Sleep(1000);
	system("cls");
	list.remove(3,6);
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");

	show_menu(6);
	std::cout << list.length()<<std::endl;
	Sleep(1000);
	system("cls");

	show_menu(7);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 2;
	Sleep(1000);
	system("cls");
	point* found = list.get(2);
	std::cout << "Address is: " << found << std::endl;
	Sleep(1000);
	system("cls");

	show_menu(8);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 3;
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
	list.set(3, { 32,4,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list.show();
	Sleep(3000);
	system("cls");
	show_menu(10);
	system("cls");
	std::cout << "-> continue in ordinary list" << std::endl
		<< "   continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "   continue in ordinary list" << std::endl
		<< "-> continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	secondList::List<point>list1;
	for (size_t i = 0; i < list.length(); i++) {
		list1.append(*list.get(i));
	}










	system("cls");
	show_menu(9);
	list1.show();
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
	list1.append({ 10,-2,27 });
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
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
	list1.push_front({ -5,56,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
	Sleep(3000);
	system("cls");


	show_menu(2);
	list1.pop_back();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
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
	std::cout << "How many points do you want to insert?" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	std::cout << "Insert before... ";
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	list1.insert(0, 10, { 12,6,3 });
	std::cout << "Successfully" << std::endl;
	Sleep(2000);
	system("cls");
	show_menu(9);
	list1.show();
	Sleep(3000);
	system("cls");

	show_menu(2);
	list1.pop_front();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
	Sleep(3000);
	system("cls");

	show_menu(5);
	std::cout << "-> remove 1 point" << std::endl
		<< "   remove range of points" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Remove position... ";
	Sleep(1000);
	std::cout << 5;
	Sleep(1000);
	list1.remove(5);
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
	Sleep(3000);
	system("cls");

	show_menu(5);
	system("cls");
	std::cout << "   remove 1 point" << std::endl
		<< "-> remove range of points" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   remove 1 point" << std::endl
		<< "-> remove range of points" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Remove from... ";
	Sleep(1000);
	std::cout << 3;
	Sleep(1000);
	system("cls");
	std::cout << "Remove to... ";
	Sleep(1000);
	std::cout << 6;
	Sleep(1000);
	system("cls");
	list1.remove(3, 6);
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
	Sleep(3000);
	system("cls");

	show_menu(6);
	std::cout << list1.length() << std::endl;
	Sleep(1000);
	system("cls");

	show_menu(7);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 2;
	Sleep(1000);
	system("cls");
	found = list1.get(2);
	std::cout << "Address is: " << found << std::endl;
	Sleep(1000);
	system("cls");

	show_menu(8);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 3;
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
	list1.set(3, { 32,4,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list1.show();
	Sleep(3000);
	system("cls");
	show_menu(10);
	system("cls");
	std::cout << "-> continue in ordinary list" << std::endl
		<< "   continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "   continue in ordinary list" << std::endl
		<< "-> continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "   continue in ordinary list" << std::endl
		<< "   continue in dynamic list" << std::endl
		<< "-> continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);



	thirdList::List<point>list2;
	for (size_t i = 0; i < list1.length(); i++) {
		list2.append(*list1.get(i));
	}








	system("cls");
	show_menu(9);
	list2.show();
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
	list2.append({ 10,-2,27 });
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
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
	list2.push_front({ -5,56,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
	Sleep(3000);
	system("cls");


	show_menu(2);
	list2.pop_back();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
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
	std::cout << "How many points do you want to insert?" << std::endl;
	Sleep(1000);
	std::cout << 1;
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	std::cout << "Insert before... ";
	Sleep(1000);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	list2.insert(0, 10, { 12,6,3 });
	std::cout << "Successfully" << std::endl;
	Sleep(2000);
	system("cls");
	show_menu(9);
	list2.show();
	Sleep(3000);
	system("cls");

	show_menu(2);
	list2.pop_front();
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
	Sleep(3000);
	system("cls");

	show_menu(5);
	std::cout << "-> remove 1 point" << std::endl
		<< "   remove range of points" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Remove position... ";
	Sleep(1000);
	std::cout << 5;
	Sleep(1000);
	list2.remove(5);
	system("cls");
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
	Sleep(3000);
	system("cls");

	show_menu(5);
	std::cout << "   remove 1 point" << std::endl
		<< "-> remove range of points" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   remove 1 point" << std::endl
		<< "-> remove range of points" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "Remove from... ";
	Sleep(1000);
	std::cout << 3;
	Sleep(1000);
	system("cls");
	std::cout << "Remove to... ";
	Sleep(1000);
	std::cout << 6;
	Sleep(1000);
	system("cls");
	list2.remove(3, 6);
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
	Sleep(3000);
	system("cls");

	show_menu(6);
	std::cout << list2.length() << std::endl;
	Sleep(1000);
	system("cls");

	show_menu(7);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 2;
	Sleep(1000);
	system("cls");
	found = list2.get(2);
	std::cout << "Address is: " << found << std::endl;
	Sleep(1000);
	system("cls");

	show_menu(8);
	std::cout << "Point's position... ";
	Sleep(1000);
	std::cout << 3;
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
	list2.set(3, { 32,4,7 });
	std::cout << "Successfully" << std::endl;
	Sleep(1000);
	system("cls");
	show_menu(9);
	list2.show();
	Sleep(3000);
	system("cls");
	show_menu(10);
	system("cls");
	std::cout << "-> continue in ordinary list" << std::endl
		<< "   continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "   continue in ordinary list" << std::endl
		<< "-> continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "   continue in ordinary list" << std::endl
		<< "   continue in dynamic list" << std::endl
		<< "-> continue in double-linked list" << std::endl
		<< "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout << "   continue in ordinary list" << std::endl
		<< "   continue in dynamic list" << std::endl
		<< "   continue in double-linked list" << std::endl
		<< "-> exit" << std::endl;
	Sleep(1000);
	system("cls");
	std::cout<<"goodby!"<<std::endl;
}

void show_menu(int choise) {
	std::string menu[] = { "push point back","push point front","pop point back","pop point front","insert point (points)","remove point (points)",
	"find out length of list", "get address of element","set element","show element (elements)","finish" };
	for (int i = 0; i <= choise; i++) {
		for (int j = 0; j<11; j++) {
			if (j==i) {
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

point random_point() {
	srand(time(nullptr));
	point to_return;
	to_return.x = rand() % 1000;
	to_return.y = rand() % 1000;
	to_return.z = rand() % 1000;
	return to_return;
}


void benchmark() {
	std::cout << "In process...\n";
	std::ofstream benchm;
	benchm.open("benchmark.txt");
	benchm << "fixed size array:\n";
	benchm << "Count:\tCreating\tRemove(Count/10, from the beginning)\tRemove(Count/10, from the end)\tRemove(Count/10, from the middle)\tInsert(Count/10, in the beginning)\tInsert(Count/10, in the end)\tInsert(Count/10, in the middle)\t\tGet(Count/100, randomly)\tSet(Count/100, randomly)\tPop back(Count/100)\tPop front(Count/1000)\tAppend(Count/100)\tPush front(Count/1000)\n";
	double Time = 0;
	int count = 100;
	/*for (int j = 0; j < 4;j++) {*/
	while(Time<1&&count<100001){
		count *= 10;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		firstList::List<point>list(count,random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0,count/10);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length()-count/10, list.length()-1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length()/2-count/20,list.length()/2+count/20-1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.set(rand() % list.length(),random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 1000; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 1000; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << '\n';
	}
	while (Time < 10 && count < 500001) {
		count *= 2;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		firstList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 10);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 10, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 20, list.length() / 2 + count / 20 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 1000; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 100; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 1000; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << '\n';
	}
	benchm << "changed size array:\n";
	benchm << "Count:\t\tCreating\tRemove(Count/10, from the beginning)\tRemove(Count/10, from the end)\tRemove(Count/10, from the middle)\tInsert(Count/10, in the beginning)\tInsert(Count/10, in the end)\tInsert(Count/10, in the middle)\t\tGet(Count/10, randomly)\tSet(Count/10, randomly)\tPop back(Count/10)\tPop front(Count/10)\tAppend(Count/10)\tPush front(Count/10)\n";
	Time = 0;
	count = 100;
	/*for (int j = 0; j < 4;j++) {*/
	while (Time < 1 && count < 100001) {
		count *= 10;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		secondList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 10);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 10, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 20, list.length() / 2 + count / 20 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << '\n';
	}
	while (Time < 10 && count < 500001) {
		count *= 2;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		secondList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 10);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 10, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 20, list.length() / 2 + count / 20 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 10, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << '\n';
	}
	benchm << "Double-linked list:\n";
	benchm << "Count:\tCreating\t\tGet(Count/10, randomly)\tSet(Count/10, randomly)\tPop back(Count/10)\tPop front(Count/10)\tAppend(Count/10)\tPush front(Count/10)\tRemove(Count/100, from the beginning)\tRemove(Count/100, from the end)\tRemove(Count/100, from the middle)\tInsert(Count/100, in the beginning)\tInsert(Count/100, in the end)\tInsert(Count/100, in the middle)\n";
	Time = 0;
	count = 100;
	/*for (int j = 0; j < 4;j++) {*/
	while (Time < 1 && count < 100001) {
		count *= 10;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		thirdList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 100);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 100, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 200, list.length() / 2 + count / 200 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\n";
	}
	while (Time < 10 && count < 500001) {
		count *= 2;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		thirdList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 100);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 100, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 200, list.length() / 2 + count / 200 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\n";
	}
	benchm << "Another dynamic list:\n";
	benchm << "Count:\tCreating\t\tGet(Count/10, randomly)\t\tSet(Count/10, randomly)\tPop back(Count/10)\tPop front(Count/10)\tAppend(Count/10)\tPush front(Count/10)\tRemove(Count/100, from the beginning)\tRemove(Count/100, from the end)\tRemove(Count/100, from the middle)\tInsert(Count/100, in the beginning)\tInsert(Count/100, in the end)\tInsert(Count/100, in the middle)\n";
	Time = 0;
	count = 100;
	while (Time < 1 && count < 100001) {
		count *= 10;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		fourthList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 100);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 100, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 200, list.length() / 2 + count / 200 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\n";
	}
	while (Time < 10 && count < 500001) {
		count *= 2;
		benchm << count << "\t";
		point random = random_point();
		clock_t start = clock();
		fourthList::List<point>list(count, random);
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.get(rand() % list.length());
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.set(rand() % list.length(), random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_back();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.pop_front();
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.append(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		for (int i = 0; i < count / 10; i++) {
			list.push_front(random);
		}
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.remove(0, count / 100);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() - count / 100, list.length() - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.remove(list.length() / 2 - count / 200, list.length() / 2 + count / 200 - 1);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		start = clock();
		list.insert(0, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.insert(list.length() - 1, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		list.insert(list.length() / 2, count / 100, random);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\n";
	}
	system("cls");
	std::cout << "Done! Check \"benchmark.txt\"\n";
	benchm.close();
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
		if (choise == 4) std::cout << "-> insert point (points)" << std::endl;
		else  std::cout << "   insert point (points)" << std::endl;
		if (choise == 5) std::cout << "-> remove point (points)" << std::endl;
		else  std::cout << "   remove point (points)" << std::endl;
		if (choise == 6) std::cout << "-> find out length of list" << std::endl;
		else  std::cout << "   find out length of list" << std::endl;
		if (choise == 7) std::cout << "-> get address of element" << std::endl;
		else  std::cout << "   get address of element" << std::endl;
		if (choise == 8) std::cout << "-> set element" << std::endl;
		else  std::cout << "   set element" << std::endl;
		if (choise == 9) std::cout << "-> show element (elements)" << std::endl;
		else  std::cout << "   show element (elements)" << std::endl;
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
		while (correct&&std::cin.get(ch)) {
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

/*void copy(int*& first, int* second,const int size) {
	delete[]first;
	first = new int[size];
	for (int i = 0; i < size; i++) {
		first[i] = second[i];
	}
}

void push_back(int*& arr, int& size, const int value) {
	size++;
	int* newArr = new int[size];
	for (int i = 0; i < size; i++) {
		newArr[i] = arr[i];
	}
	newArr[size-1] = value;
	delete[] arr;
	arr = newArr;
	newArr = nullptr;
}

void push_front(int*& arr, int& size, const int value) {
	size++;
	int* newArr = new int[size];
	for (int i = 1; i < size; i++) {
		newArr[i] = arr[i-1];
	}
	newArr[0] = value;
	delete[] arr;
	arr = newArr;
	newArr = nullptr;
}

void pop_back(int*& arr, int& size) {
	size--;
	int* newArr = new int[size];
	for (int i = 0; i < size; i++) {
		newArr[i] = arr[i];
	}
	delete[] arr;
	arr = newArr;
	newArr = nullptr;
}

void pop_front(int*& arr, int& size) {
	size--;
	int* newArr = new int[size];
	for (int i = 0; i < size; i++) {
		newArr[i] = arr[i+1];
	}
	delete[] arr;
	arr = newArr;
	newArr = nullptr;
}


void insert(int*& arr, int& size, size_t pos, size_t value) {
	insert(arr, size, pos, 1, value);
}


void insert(int*& arr, int& size, size_t pos, int number, int value) {
	if (number < 0||pos>size) {
		cout << "ERROR\t";
		return;
	}
	size+=number;
	int* newArr = new int[size];
	for (int i = 0; i < pos; i++) {
		newArr[i] = arr[i];
	}
	for (int i = pos; i < pos + number; i++) {
		newArr[i] = value;
	}
	for (int i = pos+number; i < size; i++) {
		newArr[i] = arr[i - number];
	}
	delete[] arr;
	arr = newArr;
	newArr = nullptr;
}

void erase(int*& arr, int& size, size_t pos1, size_t pos2) {
	if (pos2 < pos1||pos1<0||pos2>size) {
		cout << "ERROR\t";
		return;
	}
	int copy_size = size;
	size -= pos2-pos1;
	int* newArr = new int[size];
	for (int i = 0; i < pos1; i++) {
		newArr[i] = arr[i];
	}
	for (int i = 0; i < copy_size-pos2; i++) {
		newArr[pos1+i] = arr[pos2+i];
	}
	delete[] arr;
	arr = newArr;
	newArr = nullptr;
}*/

