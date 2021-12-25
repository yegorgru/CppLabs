#include "Header.h"



std::ofstream& operator<<(std::ofstream& out, const date_and_time& date_and_time)
{
	out << date_and_time.day << ' ' << date_and_time.month << ' ' << date_and_time.year << ' ' << date_and_time.hours << ' ' << date_and_time.minutes;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, date_and_time& date)
{
	in >> date.day >> date.month >> date.year >> date.hours >> date.minutes;
	return in;
}

std::ostream& operator<<(std::ostream& out, const date_and_time& date_and_time)
{
	out << date_and_time.day << '.' << date_and_time.month << '.' << date_and_time.year << ' ' << date_and_time.hours << ':' << date_and_time.minutes;
	return out;
}

std::ostream& operator<<(std::ostream& out, const goods& goods)
{
	out << "Name: " << goods.name << std::endl << "Quantity: " << goods.number << " " << correct_var_units(goods.units_of_measurement, goods.number) << std::endl << goods.production_time << "\texpiration date: " << goods.expiration_date<<"\tID:"<<goods.id;
	return out;
}

std::ofstream& operator<<(std::ofstream& out, const goods& goods)
{
	out << goods.name << std::endl << goods.units_of_measurement << ' ' << goods.number << ' ';
	out << goods.production_time;
	out << ' ' << goods.expiration_date << ' ' << goods.id;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, goods& goods)
{
	getline(in, goods.name);
	in >> goods.units_of_measurement >> goods.number;
	in >> goods.production_time >> goods.expiration_date >> goods.id;
	return in;
}

bool operator>(const date_and_time &date1, const date_and_time &date2)
{
	if (date1.year > date2.year) {
		return true;
	}
	else if (date1.year == date2.year) {
		if (date1.month > date2.month) {
			return true;
		}
		else if (date1.month == date2.month) {
			if (date1.day > date2.day) {
				return true;
			}
			else if (date1.day == date2.day) {
				if (date1.hours > date2.hours) {
					return true;
				}
				else if (date1.hours == date2.hours) {
					if (date1.minutes > date2.minutes) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool operator==( const date_and_time &date1, const date_and_time &date2)
{
	if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && date1.hours == date2.hours && date1.minutes == date2.minutes) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<(const date_and_time &date1, const date_and_time &date2)
{
	return date2 > date1;
}

void main_launch() {
	int what_mode = main_menu();
	std::deque<goods> all_goods;
	std::deque<int> searched;
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
		all_goods.clear();
		system("cls");
		std::cout << "Read from: " << std::endl;
		Sleep(3000);
		int what_storage = storage();
		if (what_storage == 2) {
			get_goods_from(all_goods, "database.txt");
		}
		else if (what_storage == 3) {
			get_goods_from(all_goods, "database.bin");
		}
		actions(all_goods, searched);
	}
}


int main_menu()
{
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
		std::cout << "What storage?\n";
		what_storage = (what_storage + 3) % 3;
		if (what_storage == 0) std::cout << "-> nowhere" << std::endl;
		else  std::cout << "   nowhere" << std::endl;
		if (what_storage == 1) std::cout << "-> storage in text file" << std::endl;
		else  std::cout << "   storage in text file" << std::endl;
		if (what_storage == 2) std::cout << "-> storage in binary file" << std::endl;
		else  std::cout << "   storage in binary file" << std::endl;
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


date_and_time random_date() {
	srand(time(nullptr));
	date_and_time r_d;
	r_d.minutes = mersenne() % 60;
	r_d.hours = mersenne() % 24;
	r_d.day = mersenne() % 31 + 1;
	r_d.month = mersenne() % 12 + 1;
	r_d.year = mersenne() % 11 + 2010;
	if (correct_whole_date(r_d)) {
		return r_d;
	}
	else return random_date();
}

goods random_goods() {
	std::string names[20] = { "potato","tomato","cheese","apple","pineapple","bakery","bread","chery","sweets","milk","chocolate","porridge","rise","buckwheat","cookie","juice","tea","soup","meat","cottage cheese" };
	std::string units[4] = { "kg","piece","package","liter" };
	goods a;
	a.name = names[mersenne() % 20];
	a.units_of_measurement = units[mersenne() % 4];
	a.production_time = random_date();
	a.expiration_date = mersenne() % 3653 + 1;
	a.number = mersenne() % 1000;
	return a;
}


bool correct_date(const date_and_time& if_correct) {
	if ((if_correct.month < 1 || if_correct.month > 12) || if_correct.year < 0) {
		return false;
	}
	else if (if_correct.month == 1 || if_correct.month == 3 || if_correct.month == 5 || if_correct.month == 7 || if_correct.month == 8 || if_correct.month == 10 || if_correct.month == 12) {
		if (if_correct.day < 1 || if_correct.day > 31)
		{
			return false;
		}
	}
	else if (if_correct.month == 2)
	{
		if (if_correct.year % 4 != 0 || (if_correct.year % 400 != 0 && if_correct.year % 100 == 0)) {
			if (if_correct.day < 1 || if_correct.day > 28) {
				return false;
			}
		}
		else if (if_correct.year % 4 == 0) {
			if (if_correct.day < 1 || if_correct.day>29) {
				return false;
			}
		}
	}
	else
	{
		if (if_correct.day < 0 || if_correct.day > 30)
		{
			return false;
		}
	}
	return true;
}

bool correct_whole_date(const date_and_time& if_correct) {
	if ((if_correct.hours < 0 || if_correct.hours > 23) || (if_correct.month < 1 || if_correct.month > 12) || if_correct.year < 0) {
		return false;
	}
	else if (if_correct.month == 1 || if_correct.month == 3 || if_correct.month == 5 || if_correct.month == 7 || if_correct.month == 8 || if_correct.month == 10 || if_correct.month == 12) {
		if (if_correct.day < 1 || if_correct.day > 31)
		{
			return false;
		}
	}
	else if (if_correct.month == 2)
	{
		if (if_correct.year % 4 != 0 || (if_correct.year % 400 != 0 && if_correct.year % 100 == 0)) {
			if (if_correct.day < 1 || if_correct.day > 28) {
				return false;
			}
		}
		else if (if_correct.year % 4 == 0) {
			if (if_correct.day < 1 || if_correct.day>29) {
				return false;
			}
		}
	}
	else
	{
		if (if_correct.day < 0 || if_correct.day > 30)
		{
			return false;
		}
	}
	return true;
}

bool whether_correct_units(std::string& units) {
	while (units.size() > 1&&units[units.size() - 1] == ' ') {
		units.resize(units.size() - 1);
	}
	units[0] = tolower(units[0]);
	if (units == "kilo" || units == "kg" || units == "kilogram" || units == "kilograms" || units == "kilos" || units == "liter" || units == "liters" || units == "package" || units == "packages" || units == "piece" || units == "pieces") {
		return true;
	}
	else {
		return false;
	}
}

std::string correct_var_units(const std::string& units, double number)
{
	if (number < 0) {
		std::cout << "Error\n";
		return "";
	}
	else if (units == "kg" || units == "kilogram" || units == "kilograms" || units == "kilos") {
		if (number < 1)  return "kg";
		else if (number == 1)  return "kilogram";
		else return "kilos";
	}
	else if (units == "liter" || units == "liters") {
		if (number == 1) return "liter";
		else return "liters";
	}
	else if (units == "package" || units == "packages") {
		if (number == 1) return "package";
		else return "packages";
	}
	else if (units == "piece" || units == "pieces") {
		if (number == 1) return "piece";
		else return "pieces";
	}
	else return "";
}

bool equal_units(std::string a, std::string b) {
	if (a == "kg" || a == "kilogram" || a == "kilograms") {
		if (b == "kg" || b == "kilogram" || b == "kilograms") {
			return true;
		}
	}
	else if (a == "liter" || a == "liters") {
		if (b == "liter" || b == "liters") {
			return true;
		}
	}
	else if (a == "package" || a == "packages") {
		if (b == "package" || b == "packages") {
			return true;
		}
	}
	else if (a == "piece" || a == "pieces") {
		if (b == "piece" || b == "pieces") {
			return true;
		}
	}
	return false;
}

goods get_goods(std::string in_top)
{
	goods a;
	std::cout << in_top << "adding a goods...\n\n";
	std::cout << "Enter name of goods\n";
	a.name = "";
	while (a.name == "") {
		std::getline(std::cin, a.name);
		if (a.name == "") {
			std::cout << "Try again\n";
		}
	}
	system("cls");
	std::cout << "adding a goods...\n\n";
	bool correct = false;
	char ch;
	while (!correct) {
		std::cout << "Enter number of goods"<<std::endl;
		std::cin >> a.number;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (a.number >= 0) {
			correct = true;
		}
		else {
			std::cout << "Incorrect number";
			Sleep(2000);
			system("cls");
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
	system("cls");
	std::cout << "adding a goods...\n\n";
	std::cout << "Enter units of measurement (kilograms, liters, packages, pieces)\n";
	while (whether_correct_units(a.units_of_measurement) == false) {
		std::cin >> a.units_of_measurement;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "You entered not a string\n";
			continue;
		}
		else {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
		}
		if (whether_correct_units(a.units_of_measurement) == false) {
			std::cout << "Try again\n";
		}
	}
	if (a.units_of_measurement == "kilogram" || a.units_of_measurement == "kilograms" || a.units_of_measurement == "kilos" || a.units_of_measurement=="kilo") {
		a.units_of_measurement = "kg";
	}
	else if (a.units_of_measurement == "liters") {
		a.units_of_measurement = "liter";
	}
	else if (a.units_of_measurement == "pieces") {
		a.units_of_measurement = "piece";
	}
	else if(a.units_of_measurement == "packages") {
		a.units_of_measurement = "package";
	}
	system("cls");
	std::cout << "adding a goods...\n\n";
	std::cout << "Enter date and time\n";
	while (!correct_whole_date(a.production_time)) {
		a.production_time = get_date_and_time();
		if (!correct_whole_date(a.production_time)) {
			std::cout << "Incorrect date or time\n";
		}
	}
	system("cls");
	std::cout << "adding a goods...\n\n";
	correct = false;
	while (!correct) {
		std::cout << "Enter expiration date (1-3653)" << std::endl;
		std::cin >> a.expiration_date;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (a.expiration_date>0&&a.expiration_date<3654) {
			correct = true;
		}
		else {
			std::cout << "Incorrect exp.date";
			Sleep(2000);
			system("cls");
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
	return a;
}

void get_only_date(date_and_time& for_date) {
	bool correct = false;
	char ch;
	while (!correct) {
		std::cout << "Enter day(1-31)" << std::endl;
		std::cin >> for_date.day;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if(for_date.day>0&&for_date.day<32){
			correct = true;
		}
		else {
			std::cout << "Incorrect day";
			Sleep(2000);
			system("cls");
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
	system("cls");
	while (!correct) {
		std::cout << "Enter month(1-12)" << std::endl;
		std::cin >> for_date.month;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (for_date.month > 0 && for_date.month < 13) {
			correct = true;
		}
		else {
			std::cout << "Incorrect month";
			Sleep(2000);
			system("cls");
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
	system("cls");
	while (!correct) {
		std::cout << "Enter year(2011-2020)" << std::endl;
		std::cin >> for_date.year;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (for_date.year > 2010 && for_date.year < 2021) {
			correct = true;
		}
		else {
			std::cout << "Incorrect year";
			Sleep(2000);
			system("cls");
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

date_and_time get_date_and_time()
{
	date_and_time taken;
	bool correct = false;
	char ch;
	while (!correct) {
		std::cout << "Enter day(1-31)" << std::endl;
		std::cin >> taken.day;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (taken.day > 0 && taken.day < 32) {
			correct = true;
		}
		else {
			std::cout << "Incorrect day";
			Sleep(2000);
			system("cls");
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
	system("cls");
	while (!correct) {
		std::cout << "Enter month(1-12)" << std::endl;
		std::cin >> taken.month;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (taken.month > 0 && taken.month < 13) {
			correct = true;
		}
		else {
			std::cout << "Incorrect month";
			Sleep(2000);
			system("cls");
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
	system("cls");
	while (!correct) {
		std::cout << "Enter year(2011-2020)" << std::endl;
		std::cin >> taken.year;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (taken.year > 2010 && taken.year < 2021) {
			correct = true;
		}
		else {
			std::cout << "Incorrect year";
			Sleep(2000);
			system("cls");
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
	system("cls");
	while (!correct) {
		std::cout << "Enter hours(0-23)" << std::endl;
		std::cin >> taken.hours;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (taken.hours > -1 && taken.hours < 24) {
			correct = true;
		}
		else {
			std::cout << "Incorrect hours";
			Sleep(2000);
			system("cls");
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
	system("cls");
	while (!correct) {
		std::cout << "Enter minutes(0-59)" << std::endl;
		std::cin >> taken.minutes;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(INT64_MAX, '\n');
			std::cout << "Incorrect input" << std::endl;
			Sleep(3000);
			system("cls");
			correct = false;
			continue;
		}
		else if (taken.minutes > -1 && taken.minutes < 60) {
			correct = true;
		}
		else {
			std::cout << "Incorrect minutes";
			Sleep(2000);
			system("cls");
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
	return taken;
}

void actions(std::deque<goods>& all_goods, std::deque<int>& searched) {
	int control = menu();
	while (control != 7) {
		if (control == 1) {
			goods to_add = get_goods("");
			add(all_goods, to_add,0);
			system("pause");
			control = menu();
		}
		else if (control == 2) {
			show(all_goods);
			system("pause");
			control = menu();
		}
		else if (control == 3) {
			searched.clear();
			interactive_search(all_goods, searched);
			system("cls");
			show(all_goods, searched);
			system("pause");
			control = menu();
		}
		else if (control == 4) {
			searched.clear();
			interactive_search(all_goods, searched);
			edit_goods(all_goods, searched, 0);
			system("pause");
			control = menu();
		}
		else if (control == 5) {
			searched.clear();
			interactive_search(all_goods, searched);
			remove_goods(all_goods, searched);
			system("pause");
			control = menu();
		}
		else if (control == 6) {
			bool can = true;
			if (all_goods.size() == 0) {
				std::cout << "Ther isn't nothing to sort" << std::endl;
				can = false;
			}
			if (can) {
				std::deque<int>order;
				int help_number = -1;
				bool correct = true;
				std::cout << "Choose order of fields and ways. Enter one of numbers, then press <Enter> and repeat actions as many times as needed. In the end enter 9 instead of those numbers. You can't choose one field repeatedly. \n1 Name\n2 Units of measurement (Quicksort)\n3 Units of measurement (Counting sort)\n4 Production time\n5 expiration_date (Quicksort)\n6 expiration_date (Radix sort)\n7 number\n8 id" << std::endl;
				while (help_number != 9) {
					char ch;
					if (!correct) {
						std::cout << "Choose order of fields and ways. Enter one of numbers, then press <Enter> and repeat actions as many times as needed. In the end enter 9 instead of those numbers. You can't choose one field repeatedly. \n1 Name\n2 Units of measurement (Quicksort)\n3 Units of measurement (Counting sort)\n4 Production time\n5 expiration_date (Quicksort)\n6 expiration_date (Radix sort)\n7 number\n8 id" << std::endl;
						correct = true;
					}
					std::cin >> help_number;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(INT64_MAX, '\n');
						std::cout << "Incorrect input. Try again from the very beginning" << std::endl;
						order.clear();
						system("pause");
						system("cls");
						correct = false;
						continue;
					}
					while (correct && std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect input. Try again from the very beginning" << std::endl;
							order.clear();
							system("pause");
							system("cls");
							correct = false;
							break;
						}
						else if (ch == '\n') {
							break;
						}
					}
					if (!correct) {
						help_number = 0;
						continue;
					}
					else if (help_number == 9) {
						break;
					}
					else if (!(help_number > 0 && help_number < 9)) {
						std::cout << "Incorrect number. Try again from the very beginning" << std::endl;
						order.clear();
						system("pause");
						system("cls");
						correct = false;
						continue;
					}
					else {
						if (help_number == 2 || help_number == 3) {
							for (size_t i = 0; i < order.size(); i++) {
								if (order[i] == 2 || order[i] == 3) {
									std::cout << "This field already was in list. Try again from the very beginning\n";
									order.clear();
									system("pause");
									order.clear();
									correct = false;
									break;
								}
							}
						}
						else if (help_number == 5 || help_number == 6) {
							for (size_t i = 0; i < order.size(); i++) {
								if (order[i] == 5 || order[i] == 6) {
									std::cout << "This field already was in list. Try again from the very beginning\n";
									order.clear();
									system("pause");
									order.clear();
									correct = false;
									break;
								}
							}
						}
						else {
							for (size_t i = 0; i < order.size(); i++) {
								if (order[i] == help_number) {
									std::cout << "This field already was in list. Try again from the very beginning\n";
									order.clear();
									system("pause");
									order.clear();
									correct = false;
									break;
								}
							}
						}
						if (!correct) {
							system("cls");
							continue;
						}
						else {
							order.push_back(help_number);
						}
					}
				}
				sorting(all_goods, order, 1);
			}
			system("pause");
			control = menu();
		}
	}
	if (all_goods.size() > 0) {
		std::cout << "Save in:" << std::endl;
		Sleep(3000);
		int what_storage = storage();
		if (what_storage == 2) {
			save_goods_in(all_goods, "database.txt");
		}
		else if (what_storage == 3) {
			save_goods_in(all_goods, "database.bin");
		}
	}
	main_launch();
}

int menu() {
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 7) % 7;
		if (choise == 0) std::cout << "-> to add goods" << std::endl;
		else  std::cout << "   to add goods" << std::endl;
		if (choise == 1) std::cout << "-> to see all goods" << std::endl;
		else  std::cout << "   to see all goods" << std::endl;
		if (choise == 2) std::cout << "-> to search some goods" << std::endl;
		else  std::cout << "   to search some goods" << std::endl;
		if (choise == 3) std::cout << "-> to edit goods" << std::endl;
		else  std::cout << "   to edit goods" << std::endl;
		if (choise == 4) std::cout << "-> to remove goods" << std::endl;
		else  std::cout << "   to remove goods" << std::endl;
		if (choise == 5) std::cout << "-> to sort goods" << std::endl;
		else  std::cout << "   to sort goods" << std::endl;
		if (choise == 6) std::cout << "-> to return to main menu" << std::endl;
		else  std::cout << "   to return to main menu" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}

	} while (code != 13);
	system("cls");
	return choise + 1;
}


bool search(const std::deque<goods>& all_goods, std::deque<int>& searched, std::string what_search)
{
	bool a = false;
	for (size_t i = 0; i < all_goods.size(); i++) {
		if (string_in_end(all_goods[i].name, what_search)) {
			searched.push_back(i);
			a = true;
		}
	}
	return a;
}

bool search(const std::deque<goods>& all_goods, std::deque<int>& searched, std::string units, int exp_date) {
	bool a = false;
	for (size_t i = 0; i < all_goods.size(); i++) {
		if (equal_units(all_goods[i].units_of_measurement, units)) {
			if (all_goods[i].expiration_date >= exp_date) {
				searched.push_back(i);
				a = true;
			}
		}
	}
	return a;
}

bool search(const std::deque<goods>& all_goods, std::deque<int>& searched, date_and_time less, date_and_time bigger) {
	bool a = false;
	for (size_t i = 0; i < all_goods.size(); i++) {
		if (all_goods[i].production_time > less && bigger > all_goods[i].production_time) {
			searched.push_back(i);
			a = true;
		}
	}
	return a;
}

bool string_in_end(std::string bigger, std::string less)
{
	for (size_t i = 0; i < less.size(); i++) {
		if (less[i] > 64 && less[i] < 91) {
			less[i] += 32;
		}
	}
	if (less.size() > bigger.size() || less.size() == 0) {
		return false;
	}
	int difference = bigger.size() - less.size();
	for (size_t i = 0; i < less.size(); i++) {
		if (!(bigger[difference + i] == less[i]||(int)bigger[difference+i]==(int)less[i]-32)) {
			return false;
		}
	}
	return true;
}

void add(std::deque<goods>& all_goods, goods to_add,bool benchmark)
{
	if (all_goods.size() == 0) {
		to_add.id = 0;
	}
	else {
		std::deque<goods>for_sorting = all_goods;
		std::deque<int>order = { 8 };
		sorting(for_sorting, order,0);
		bool found = false;
		for (size_t i = 0; i < for_sorting.size(); i++) {
			if (for_sorting[i].id>i) {
				to_add.id = i;
				found = true;
				break;
			}
		}
		if (!found) {
			to_add.id = for_sorting.size();
		}
	}
	all_goods.push_back(to_add);
	if (!benchmark) {
		std::cout << "added"<<std::endl;
	}
}


void show(const std::deque<goods>& all_goods) {
	if (all_goods.empty()) {
		std::cout << "Nothing found!\n\n";
		return;
	}
	for (size_t i = 0; i < all_goods.size(); i++) {
		std::cout << all_goods[i] << std::endl << std::endl;
	}
}

void show(const std::deque<goods>& all_goods, const std::deque<int>& searched) {
	if (searched.empty()) {
		std::cout << "Nothing found!\n\n";
		return;
	}
	for (size_t i = 0; i < searched.size(); i++) {
		std::cout << all_goods[searched[i]] << std::endl << std::endl;
	}
}


void interactive_search(const std::deque<goods>& all_goods, std::deque<int>& searched)
{
	int key = search_menu();
	if (key == 1) {
		std::string end = "";
		std::cout << "Enter end of name\n";
		while (end == "") {
			std::cin >> end;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(32767, '\n');
				std::cout << "You entered not a string\n";
				end = "";
				continue;
			}
			std::cin.ignore();
			if (end == "") {
				std::cout << "Try again\n";
			}
		}
		search(all_goods, searched, end);
	}
	else if (key == 2) {
		int min_exp = 0;
		bool correct = false;
		char ch;
		while (!correct) {
			std::cout << "Enter min expiration date (1-3653)" << std::endl;
			std::cin >> min_exp;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(INT64_MAX, '\n');
				std::cout << "Incorrect input" << std::endl;
				Sleep(3000);
				system("cls");
				correct = false;
				continue;
			}
			else if (min_exp > 0 && min_exp < 3654) {
				correct = true;
			}
			else {
				std::cout << "Incorrect exp. date";
				Sleep(2000);
				system("cls");
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
		system("cls");
		std::string s_units = "";
		while (!whether_correct_units(s_units)) {
			system("cls");
			std::cout << "Enter units of measurement\n";
			std::getline(std::cin, s_units);
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cout << "You entered not a string\n";
				s_units = "";
				Sleep(2000);
				continue;
			}
			if (whether_correct_units(s_units) == false) {
				std::cout << "Incorrect units of measurement. Try again\n";
				Sleep(2000);
			}
			else {
				break;
			}
		}
		search(all_goods, searched, s_units, min_exp);
	}
	else {
		date_and_time first;
		date_and_time second;
		second.year = -2;
		while (!correct_date(first) || !correct_date(second) || first > second) {
			system("cls");
			std::cout << "Enter first date of diapason\n";
			get_only_date(first);
			system("cls");
			std::cout << "Enter second date of diapason\n";
			get_only_date(second);
			if (!correct_date(first) || !correct_date(second) || first > second) {
				std::cout << "Incorrect date or first date > second date\n";
				system("pause");
			}
		}
		search(all_goods, searched, first, second);
	}
}

int search_menu() {
	int key = 0;
	int code;
	int pos = 0;
	do {
		system("cls");
		std::cout << "Choose variant of searching\n";
		key = (key + 3) % 3;
		if (key == 0) std::cout << "-> search by end of the name" << std::endl;
		else  std::cout << "   search by end of the name" << std::endl;
		if (key == 1) std::cout << "-> search by units of measurement and expiration date" << std::endl;
		else  std::cout << "   search by units of measurement and expiration date" << std::endl;
		if (key == 2) std::cout << "-> search by date of production at the specified diapason" << std::endl;
		else  std::cout << "   search by date of production at the specified diapason" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key + 1;
}

void edit_goods(std::deque<goods>& all_goods, std::deque<int>& searched, bool demo) {
	size_t what_edit = 0;
	if (searched.empty() == true) {
		std::cout << "Nothing found\n";
		return;
	}
	else if (demo||searched.size()==1) {
		what_edit = 0;
	}
	else {
		for (size_t i = 0; i < searched.size(); i++) {
			std::cout << i + 1 << std::endl << all_goods[searched[i]] << std::endl << std::endl;
		}
		std::cout << "What goods do you want to edit?\n";
		while (!(what_edit > 0 && what_edit < searched.size() + 1)) {
			std::cin >> what_edit;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT64_MAX, '\n');
				std::cout << "You entered not a number\n";
				what_edit = -1;
				continue;
			}
			else {
				std::cin.clear();
				std::cin.ignore(INT64_MAX, '\n');
			}
			if (!(what_edit > 0 && what_edit < searched.size() + 1)) {
				std::cout << "Try again\n";
			}
		}
		what_edit--;
	}
	int choise = -1;
	if (demo) {
		choise = 1 + rand() % 5;
	}
	else {
		choise = edit_menu();
	}
	if (choise == 1) {
		if (demo) {
			std::string names[20] = { "potato","tomato","cheese","apple","pineapple","bakery","bread","chery","sweets","milk","chocolate","porridge","rise","buckwheat","cookie","juice","tea","soup","meat","cottage cheese" };
			all_goods[searched[what_edit]].name = names[rand() % 20];
		}
		else {
			std::string new_name = "";
			while (new_name == "") {
				std::cout << "Enter new name\n";
				std::getline(std::cin, new_name);
				if (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(INT64_MAX, '\n');
					std::cout << "You entered not a string\n";
					what_edit = -1;
					continue;
				}
				else {
					std::cin.clear();
				}
				if (new_name == "") {
					std::cout << "Try again\n";
				}
			}
			all_goods[searched[what_edit]].name = new_name;
		}
	}
	else if (choise == 2) {
		if (demo) {
			std::string units[4] = { "kg","piece","package","liter" };
			all_goods[searched[what_edit]].units_of_measurement = units[rand() % 4];
		}
		else {
			std::string new_units;
			bool correct = false;
			char ch;
			while (!whether_correct_units(new_units)||!correct) {
				system("cls");
				std::cout << "Enter new units of measurement" << std::endl;
				std::cin >> new_units;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(INT64_MAX, '\n');
					std::cout << "Incorrect input" << std::endl;
					Sleep(3000);
					correct = false;
					continue;
				}
				else if (!whether_correct_units(new_units)) {
					std::cout << "Incorrect units" << std::endl;
					Sleep(2000);
					new_units = "";
					continue;
				}
				else {
					while (std::cin.get(ch)) {
						if (ch != '\n' && ch != ' ') {
							std::cin.clear();
							std::cin.ignore(INT64_MAX, '\n');
							std::cout << "Incorrect units" << std::endl;
							Sleep(3000);
							new_units = "";
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
			if (new_units == "kilogram" || new_units == "kilograms" || new_units == "kilos" || new_units == "kilo") {
				new_units == "kg";
			}
			else if (new_units == "liters") {
				new_units == "liter";
			}
			else if (new_units == "pieces") {
				new_units == "piece";
			}
			else if (new_units == "packages") {
				new_units == "package";
			}
			all_goods[searched[what_edit]].units_of_measurement = new_units;
		}
	}
	else if (choise == 3) {
		if (demo) {
			date_and_time new_date = random_date();
			all_goods[searched[what_edit]].production_time = new_date;
		}
		else {
			date_and_time new_date = get_date_and_time();
			while (!correct_whole_date(new_date)) {
				new_date = get_date_and_time();
				if (!correct_whole_date(new_date)) {
					std::cout << "Incorrect date or time\n";
				}
			}
			all_goods[searched[what_edit]].production_time = new_date;
		}
	}
	else if (choise == 4) {
		if (demo) {
			all_goods[searched[what_edit]].expiration_date = rand() % 3653 + 1;;
		}
		else {
			std::cout << "Enter new expiration date (in days)\n";
			int new_exp = 0;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter expiration date (1-3653)" << std::endl;
				std::cin >> new_exp;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(INT64_MAX, '\n');
					std::cout << "Incorrect input" << std::endl;
					Sleep(3000);
					system("cls");
					correct = false;
					continue;
				}
				else if (new_exp > 0 && new_exp < 3654) {
					correct = true;
				}
				else {
					std::cout << "Incorrect exp. date";
					Sleep(2000);
					system("cls");
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
			all_goods[searched[what_edit]].expiration_date = new_exp;
		}
	}
	else if (choise == 5) {
		if (demo) {
			all_goods[searched[what_edit]].number = rand() % 1000;
		}
		else {
			std::cout << "Enter new number of goods\n";
			bool correct = false;
			char ch;
			int new_numb;
			while (!correct) {
				std::cout << "Enter new number" << std::endl;
				std::cin >> new_numb;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(INT64_MAX, '\n');
					std::cout << "Incorrect input" << std::endl;
					Sleep(3000);
					system("cls");
					correct = false;
					continue;
				}
				else if (new_numb>=0) {
					correct = true;
				}
				else {
					std::cout << "Incorrect number";
					Sleep(2000);
					system("cls");
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
			all_goods[searched[what_edit]].number = new_numb;
		}
	}
	std::cout << "Edited"<<std::endl;
}

int edit_menu() {
	int choise = 0;
	int code;
	int pos = 0;
	do {
		system("cls");
		std::cout << "What do you want to edit?\n";
		choise = (choise + 5) % 5;
		if (choise == 0) std::cout << "-> name" << std::endl;
		else  std::cout << "   name" << std::endl;
		if (choise == 1) std::cout << "-> units of measurement" << std::endl;
		else  std::cout << "   units of measurement" << std::endl;
		if (choise == 2) std::cout << "-> production time" << std::endl;
		else  std::cout << "   production time" << std::endl;
		if (choise == 3) std::cout << "-> expiration date" << std::endl;
		else  std::cout << "   expiration date" << std::endl;
		if (choise == 4) std::cout << "-> number of goods" << std::endl;
		else  std::cout << "   number of goods" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}
	} while (code != 13);
	system("cls");
	return choise + 1;
}

void remove_goods(std::deque<goods>& all_goods, std::deque<int>& searched) {
	if (searched.empty() == true) {
		std::cout << "Nothing found\n";
	}
	else if (searched.size() == 1) {
		all_goods.erase(all_goods.begin() + searched[0]);
		std::cout << "removed!\n";
	}
	else {
		for (size_t i = 0; i < searched.size(); i++) {
			std::cout << i + 1 << std::endl << all_goods[searched[i]] << std::endl << std::endl;
		}
		size_t what_remove = 0;
		std::cout << "What goods do you want to remove?\n";
		while (!(what_remove > 0 && what_remove < searched.size() + 1)) {
			std::cin >> what_remove;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(INT64_MAX, '\n');
				std::cout << "You entered not a number\n";
				what_remove = -1;
				continue;
			}
			else {
				std::cin.clear();
				std::cin.ignore(INT64_MAX, '\n');
			}
			if (!(what_remove > 0 && what_remove < searched.size() + 1)) {
				std::cout << "Try again\n";
			}
		}
		what_remove--;
		all_goods.erase(all_goods.begin() + searched[what_remove]);
		std::cout << "removed!\n";
	}
}


void save_goods_in(const std::deque<goods>& all_goods, const char* place) {
	std::ofstream fout;
	fout.open(place);
	for (size_t i = 0; i < all_goods.size() - 1; i++) {
		fout << all_goods[i] << std::endl;
	}
	fout << all_goods[all_goods.size() - 1];
	fout.close();
}

void get_goods_from(std::deque<goods>& all_goods, const char* place)
{
	std::ifstream fin;
	fin.open(place);
	while (fin) {
		goods a;
		fin >> a;
		fin.ignore();
		all_goods.push_back(a);
	}
	fin.close();
}

void demomode() {
	std::deque<goods> all_goods;
	std::deque<int>searched;
	std::cout << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << std::endl << "Adding a goods...\n";
	goods to_add = random_goods();
	add(all_goods, to_add,0);
	Sleep(3000);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "Adding a goods...\n";
	to_add = random_goods();
	add(all_goods, to_add,0);
	Sleep(3000);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "See goods with parametrs - name ends with \"abc\":\n";
	search(all_goods, searched, "abc");
	show(all_goods, searched);
	Sleep(3000);
	std::string for_search = all_goods[1].name.substr(1, all_goods[1].name.length() - 1);
	std::cout << "See goods with parametrs - name ends with \"" << for_search << "\":\n";
	searched.clear();
	search(all_goods, searched, for_search);
	show(all_goods, searched);
	Sleep(3000);
	std::cout << "See goods with parametrs - units: \"aaa\" and min expiration date: 100 :\n";
	searched.clear();
	search(all_goods, searched, "aaa", 100);
	show(all_goods, searched);
	Sleep(3000);
	std::cout << "See goods with parametrs - units: \"" << all_goods[0].units_of_measurement << "\" and min expiration date: " << all_goods[0].expiration_date - 1 << " :\n";
	searched.clear();
	search(all_goods, searched, all_goods[0].units_of_measurement, all_goods[0].expiration_date - 1);
	show(all_goods, searched);
	Sleep(3000);
	std::cout << "See goods from time of production diapason: 10.10.2010 10:10 - 10.10.2011 10:10 :\n";
	date_and_time less = { 10,10,2010,10,10 };
	date_and_time bigger = { 10,10,2011,10,10 };
	searched.clear();
	search(all_goods, searched, less, bigger);
	show(all_goods, searched);
	Sleep(3000);
	less = all_goods[1].production_time;
	--less.year;
	bigger = all_goods[1].production_time;
	++bigger.year;
	std::cout << "See goods from time of production diapason: " << less << " - " << bigger << " :\n";
	searched.clear();
	search(all_goods, searched, less, bigger);
	show(all_goods, searched);
	Sleep(3000);
	std::cout << "Editing of some goods...\n";
	searched.clear();
	searched.push_back(1);
	edit_goods(all_goods, searched, 1);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "Removing of some goods...\n";
	searched.clear();
	searched.push_back(0);
	remove_goods(all_goods, searched);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "Saving in txt...\n";
	save_goods_in(all_goods, "demodatabase.txt");
	Sleep(3000);
	std::cout << std::endl << "Reading from bin...\n";
	all_goods.clear();
	get_goods_from(all_goods, "demodatabase.bin");
	Sleep(3000);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "Reading from txt...\n";
	get_goods_from(all_goods, "demodatabase.txt");
	Sleep(3000);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "Saving in bin...\n";
	save_goods_in(all_goods, "demodatabase.bin");
	Sleep(3000);
	std::cout << "Reading from bin...\n";
	all_goods.clear();
	get_goods_from(all_goods, "demodatabase.bin");
	Sleep(3000);
	std::cout << std::endl << "See all goods:\n";
	show(all_goods);
	Sleep(3000);
	std::cout << "Adding 10 random goods:" << std::endl;
	for (int i = 0; i < 10; i++) {
		to_add = random_goods();
		add(all_goods, to_add,0);
		Sleep(100);
	}
	show(all_goods);
	std::deque<goods>copy_goods = all_goods;
	std::cout << "Sorting all goods by: units(counting)-production time-expiration date(radix)-name-number-id:" << std::endl;
	Sleep(3000);
	std::deque<int>order = { 3,4,6,1,7,8 };
	sorting(all_goods, order,0);
	show(all_goods);
	std::cout << "And checking correctness: ";
	if (sorted_correctly(all_goods, { 3,4,6,1,7,8 })) {
		std::cout << "correctly" << std::endl;
	}
	else {
		std::cout << "incorrectly" << std::endl;
	}
	Sleep(3000);
	std::cout << "Sorting all initial goods by: units(quicksort)-production time-expiration date(quicksort)-name-number-id:" << std::endl;
	Sleep(3000);
	order = { 2,4,5,1,7,8 };
	sorting(copy_goods, order,0);
	show(all_goods);
	std::cout << "And checking correctness: ";
	if (sorted_correctly(copy_goods, { 2,4,5,1,7,8 })) {
		std::cout << "correctly" << std::endl;
	}
	else {
		std::cout << "incorrectly" << std::endl;
	}
	Sleep(3000);
}



void benchmark() {
	std::cout << "In process...\n";
	std::ofstream benchm;
	benchm.open("benchmark.txt");
	benchm << "Count:\tSearch by string in end\tSearch by units and min expiration date\tSearch by dates\tSave in txt:\tSave in bin:\tRead from txt\tRead from bin\tSize of txt\tSize of bin\tSorting units with quicksort\tSorting units with counting sort\tSorting exp. date with quicksort\tSorting exp.date with radix sort\tSorting all fields with quicksort\tSorting all fields with not comparison sorts\n";
	int Time = 0;
	int count = 100;
	goods some_goods;
	std::deque<goods>all_goods;
	std::deque<goods>copy_goods;
	for (int i = 0; i < count; i++) {
		some_goods = random_goods();
		some_goods.id = all_goods.size();
		all_goods.push_back(some_goods);
	}
	bool time_to_finish = false;
	while (Time <= 1 && all_goods.size() < 100001) {
		for (int i = 0; i < 9 * count; i++) {
			some_goods = random_goods();
			some_goods.id = all_goods.size();
			all_goods.push_back(some_goods);
		}
		count *= 10;
		benchm << count << "\t\t\t";
		std::deque<int>searched;
		clock_t start = clock();
		search(all_goods, searched, "ad");
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		search(all_goods, searched, "kg", 10);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		date_and_time less = { 10,10,10,10,2014 };
		date_and_time bigger = { 10,10,10,10,2016 };
		start = clock();
		search(all_goods, searched, less, bigger);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		save_goods_in(all_goods, "benchtxt.txt");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		start = clock();
		save_goods_in(all_goods, "benchbin.bin");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		all_goods.clear();
		start = clock();
		get_goods_from(all_goods, "benchtxt.txt");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		all_goods.clear();
		start = clock();
		get_goods_from(all_goods, "benchbin.bin");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		std::fstream file("benchtxt.txt");
		file.seekg(0, std::ios::end);
		int size = file.tellg();
		benchm << size << "\t\t";
		file.close();
		file.open("benchbin.bin");
		file.seekg(0, std::ios::end);
		size = file.tellg();
		benchm << size << "\t\t\t\t";
		copy_goods = all_goods;
		std::deque<int>order = {2};
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 3 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 5 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 6 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 1,2,4,5,7,8 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		order = { 1,3,4,6,7,8 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << '\n';
	}
	while (Time <= 10&&all_goods.size()<500001) {
		for (int i = 0; i < count; i++) {
			some_goods = random_goods();
			some_goods.id = all_goods.size();
			all_goods.push_back(some_goods);
		}
		count *= 2;
		benchm << count << "\t\t\t";
		std::deque<int>searched;
		clock_t start = clock();
		search(all_goods, searched, "ad");
		clock_t finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		search(all_goods, searched, "kg", 10);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		date_and_time less = { 10,10,10,10,2014 };
		date_and_time bigger = { 10,10,10,10,2016 };
		start = clock();
		search(all_goods, searched, less, bigger);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t";
		start = clock();
		save_goods_in(all_goods, "benchtxt.txt");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		start = clock();
		save_goods_in(all_goods, "benchbin.bin");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		all_goods.clear();
		start = clock();
		get_goods_from(all_goods, "benchtxt.txt");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		all_goods.clear();
		start = clock();
		get_goods_from(all_goods, "benchbin.bin");
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t";
		std::fstream file("benchtxt.txt");
		file.seekg(0, std::ios::end);
		int size = file.tellg();
		benchm << size << "\t\t";
		file.close();
		file.open("benchbin.bin");
		file.seekg(0, std::ios::end);
		size = file.tellg();
		benchm << size << "\t\t\t\t";
		copy_goods = all_goods;
		std::deque<int>order = { 2 };
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 3 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 5 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 6 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t";
		order = { 1,2,4,5,7,8 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << "\t\t\t\t\t";
		order = { 1,3,4,6,7,8 };
		copy_goods = all_goods;
		start = clock();
		sorting(copy_goods, order, 0);
		finish = clock();
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		benchm << finish - start << '\n';
	}
	benchm.close();
	system("cls");
	std::cout << "Done! Check \"benchmark.txt\"\n";
}


void counting_sort(std::deque<goods>& all_goods,size_t begin,size_t end)
{
	if (end > begin) {
		size_t count[4] = {};
		for (size_t i = begin; i < end+1; i++) {
			if (all_goods[i].units_of_measurement == "kg" || all_goods[i].units_of_measurement == "kilogram" || all_goods[i].units_of_measurement == "kilograms" || all_goods[i].units_of_measurement == "kilos") {
				count[0]++;
			}
			else if (all_goods[i].units_of_measurement == "liter" || all_goods[i].units_of_measurement == "liters") {
				count[1]++;
			}
			else if (all_goods[i].units_of_measurement == "package" || all_goods[i].units_of_measurement == "packages") {
				count[2]++;
			}
			else {
				count[3]++;
			}
		}
		goods* in_kilos = new goods[count[0]];
		size_t count_kg=0;
		goods* in_liters = new goods[count[1]];
		size_t count_liters = 0;
		goods* in_packages = new goods[count[2]];
		size_t count_packages = 0;
		goods* in_pieces = new goods[count[3]];
		size_t count_pieces = 0;
		for (size_t i = begin; i < end+1; i++) {
			if (all_goods[i].units_of_measurement == "kg") {
				in_kilos[count_kg] = all_goods[i];
				count_kg++;
			}
			else if (all_goods[i].units_of_measurement == "liter") {
				in_liters[count_liters] = all_goods[i];
				count_liters++;
			}
			else if (all_goods[i].units_of_measurement == "package") {
				in_packages[count_packages] = all_goods[i];
				count_packages++;
			}
			else {
				in_pieces[count_pieces] = all_goods[i];
				count_pieces++;
			}
		}
		size_t i = begin;
		for (; i < begin+count_kg; i++) {
			all_goods[i] = in_kilos[i-begin];
		}
		for (; i < begin + count_kg+count_liters; i++) {
			all_goods[i] = in_liters[i - begin - count_kg];
		}
		for (; i < begin + count_kg + count_liters + count_packages; i++) {
			all_goods[i] = in_packages[i - begin- count_kg-count_liters];
		}
		for (; i < end+1; i++) {
			all_goods[i] = in_pieces[i- begin- count_kg - count_liters-count_packages];
		}

		delete[] in_kilos;
		delete[] in_liters;
		delete[] in_pieces;
		delete[] in_packages;
	}
}

void radix_sort(std::deque<goods>& all_goods, size_t begin, size_t end)
{
	int current_plus1,current,index, temp;
	std::list<goods> pocket[10];
	for (int i = 0; i < 4; i++) {
		current_plus1 = pow(10, i + 1);
		current = pow(10, i);
		for (size_t j = begin; j < end+1; j++) {
			temp = all_goods[j].expiration_date % current_plus1;
			index = temp / current;
			pocket[index].push_back(all_goods[j]);
		}
		size_t count = begin;
		for (size_t j = 0; j < 10; j++) {
			while (!pocket[j].empty()) {
				all_goods[count] = *(pocket[j].begin());
				pocket[j].pop_front();
				count++;
			}
		}
	}
}

void sorting(std::deque<goods>& all_goods,std::deque<int>& order, bool interactive) {
	if (order.size() == 0) {
		if (interactive) {
			system("cls");
			std::cout << "You don't want to sort your goods!" << std::endl;
		}
	}
	else {
		if (interactive) {
			system("cls");
			std::cout << "In process..." << std::endl;
		}
		std::deque<size_t>unclear = {0,all_goods.size()-1};
		for (size_t i = 0; i < order.size()&&unclear.size()>1; i++) {
			for (size_t j = 0; j < unclear.size(); j += 2) {
				if (order[i] == 3) {
					counting_sort(all_goods, unclear[j], unclear[j + 1]);
				}
				else if (order[i] == 6) {
					radix_sort(all_goods, unclear[j], unclear[j + 1]);
				}
				else {
					quicksort(all_goods, unclear[j], unclear[j + 1], order[i]);
				}
			}
			if (i != order.size() - 1) {
				std::deque<size_t>new_unclear;
				for (size_t j = 0; j < unclear.size(); j += 2) {
					if (order[i] == 2 || order[i] == 3) {
						for (size_t k = unclear[j] + 1; k < unclear[j + 1]+1; k++) {
							if (all_goods[k - 1].units_of_measurement == all_goods[k].units_of_measurement && k!= unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								k++;
								bool finish = false;
								while (all_goods[k].units_of_measurement == all_goods[k - 1].units_of_measurement) {
									if (k == unclear[j + 1]) {
										new_unclear.push_back(k);
										finish = true;
										break;
									}
									k++;
								}
								if (!finish) {
									new_unclear.push_back(k - 1);
								}
							}
							else if (all_goods[k - 1].units_of_measurement == all_goods[k].units_of_measurement && k == unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								new_unclear.push_back(k);
								break;
							}
						}
					}
					else if (order[i] == 5 || order[i] == 6) {
						for (size_t k = unclear[j] + 1; k < unclear[j + 1]+1; k++) {
							if (all_goods[k - 1].expiration_date == all_goods[k].expiration_date && k != unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								k++;
								bool finish = false;
								while (all_goods[k].expiration_date == all_goods[k - 1].expiration_date) {
									if (k == unclear[j + 1]) {
										new_unclear.push_back(k);
										finish = true;
										break;
									}
									k++;
								}
								if (!finish) {
									new_unclear.push_back(k - 1);
								}
							}
							else if (all_goods[k - 1].expiration_date == all_goods[k].expiration_date && k == unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								new_unclear.push_back(k);
								break;
							}
						}
					}
					else if (order[i] == 1) {
						for (size_t k = unclear[j] + 1; k < unclear[j + 1]+1; k++) {
							if (all_goods[k - 1].name == all_goods[k].name && k != unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								k++;
								bool finish = false;
								while (all_goods[k].name == all_goods[k - 1].name) {
									if (k == unclear[j + 1]) {
										new_unclear.push_back(k);
										finish = true;
										break;
									}
									k++;
								}
								if (!finish) {
									new_unclear.push_back(k - 1);
								}
							}
							else if (all_goods[k - 1].name == all_goods[k].name&& k == unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								new_unclear.push_back(k);
								break;
							}
						}
					}
					else if (order[i] == 4) {
						for (size_t k = unclear[j] + 1; k < unclear[j + 1]+1; k++) {
							if (all_goods[k - 1].production_time == all_goods[k].production_time && k != unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								k++;
								bool finish = false;
								while (all_goods[k].production_time == all_goods[k - 1].production_time) {
									if (k == unclear[j + 1]) {
										new_unclear.push_back(k);
										finish = true;
										break;
									}
									k++;
								}
								if (!finish) {
									new_unclear.push_back(k - 1);
								}
							}
							else if (all_goods[k - 1].production_time == all_goods[k].production_time && k == unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								new_unclear.push_back(k);
								break;
							}
						}
					}
					else if (order[i] == 7) {
						for (size_t k = unclear[j] + 1; k < unclear[j + 1]+1; k++) {
							if (all_goods[k - 1].number == all_goods[k].number && k != unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								k++;
								bool finish = false;
								while (all_goods[k].number == all_goods[k - 1].number) {
									if (k == unclear[j + 1]) {
										new_unclear.push_back(k);
										finish = true;
										break;
									}
									k++;
								}
								if (!finish) {
									new_unclear.push_back(k - 1);
								}
							}
							else if (all_goods[k - 1].number == all_goods[k].number && k == unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								new_unclear.push_back(k);
								break;
							}
						}
					}
					else if (order[i] == 8) {
						for (size_t k = unclear[j] + 1; k < unclear[j + 1]+1; k++) {
							if (all_goods[k - 1].id == all_goods[k].id && k != unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								k++;
								bool finish = false;
								while (all_goods[k].id == all_goods[k - 1].id) {
									if (k == unclear[j + 1]) {
										new_unclear.push_back(k);
										finish = true;
										break;
									}
									k++;
								}
								if (!finish) {
									new_unclear.push_back(k - 1);
								}
							}
							else if (all_goods[k - 1].id == all_goods[k].id && k == unclear[j + 1]) {
								new_unclear.push_back(k - 1);
								new_unclear.push_back(k);
								break;
							}
						}
					}
				}
				unclear = new_unclear;
				new_unclear.clear();
			}
		}
		if (interactive) {
			system("cls");
			if (sorted_correctly(all_goods, order)) {
				std::cout << "Sorted correctly" << std::endl;
			}
			else {
				std::cout << std::endl << "Sorted incorrectly" << std::endl;
			}
		}
	}
}

size_t partition_quicksort(std::deque<goods>& Array, size_t begin, size_t end, int field) {
	begin++;
	end++;
	goods pivot = Array[begin - 1 + mersenne() % (end - begin)];
	size_t i = begin - 1;
	size_t j = end + 1;
	if (field == 1) {
		while (true) {
			do {
				i++;
			} while (Array[i - 1].name < pivot.name);
			do {
				j--;
			} while (Array[j - 1].name > pivot.name);
			if (i >= j) {
				return j - 1;
			}
			goods help = Array[i - 1];
			Array[i - 1] = Array[j - 1];
			Array[j - 1] = help;
		}
	}
	
	else if (field == 2||field==3) {
		while (true) {
			do {
				i++;
			} while (Array[i - 1].units_of_measurement < pivot.units_of_measurement);
			do {
				j--;
			} while (Array[j - 1].units_of_measurement > pivot.units_of_measurement);
			if (i >= j) {
				return j - 1;
			}
			goods help = Array[i - 1];
			Array[i - 1] = Array[j - 1];
			Array[j - 1] = help;
		}
	}
	
	else if (field == 4) {
		while (true) {
			do {
				i++;
			} while (Array[i - 1].production_time < pivot.production_time);
			do {
				j--;
			} while (Array[j - 1].production_time > pivot.production_time);
			if (i >= j) {
				return j - 1;
			}
			goods help = Array[i - 1];
			Array[i - 1] = Array[j - 1];
			Array[j - 1] = help;
		}
	}
	
	else if (field == 5||field==6) {
		while (true) {
			do {
				i++;
			} while (Array[i - 1].expiration_date < pivot.expiration_date);
			do {
				j--;
			} while (Array[j - 1].expiration_date > pivot.expiration_date);
			if (i >= j) {
				return j - 1;
			}
			goods help = Array[i - 1];
			Array[i - 1] = Array[j - 1];
			Array[j - 1] = help;
		}
	}

	else if (field == 7) {
		while (true) {
			do {
				i++;
			} while (Array[i - 1].number < pivot.number);
			do {
				j--;
			} while (Array[j - 1].number > pivot.number);
			if (i >= j) {
				return j - 1;
			}
			goods help = Array[i - 1];
			Array[i - 1] = Array[j - 1];
			Array[j - 1] = help;
		}
	}

	else if (field == 8) {
		while (true) {
			do {
				i++;
			} while (Array[i - 1].id < pivot.id);
			do {
				j--;
			} while (Array[j - 1].id > pivot.id);
			if (i >= j) {
				return j - 1;
			}
			goods help = Array[i - 1];
			Array[i - 1] = Array[j - 1];
			Array[j - 1] = help;
		}
	}
	else {
		return 0;
	}
}


void quicksort(std::deque<goods>& Array, size_t begin, size_t end, int field)
{
	if (begin < end) {
		size_t p = partition_quicksort(Array, begin, end, field);
		quicksort(Array, begin, p, field);
		quicksort(Array, p + 1, end, field);
	}
}

bool sorted_correctly(std::deque<goods>all_goods,std::deque<int>fields) {
	bool incorrect = false;
	for (size_t i = 1; i < all_goods.size(); i++) {
		bool correct = false;
		for (size_t j = 0; j < fields.size(); j++) {
			if (fields[j] == 1) {
				if (all_goods[i].name > all_goods[i - 1].name) {
					correct = true;
					break;
				}
				else if (all_goods[i - 1].name > all_goods[i].name) {
					std::cout << all_goods[i - 1]<<std::endl;
					std::cout << all_goods[i] << std::endl;
					incorrect = true;
				}
			}
			else if (fields[j] == 2||fields[j]==3) {
				if (all_goods[i].units_of_measurement > all_goods[i - 1].units_of_measurement) {
					correct = true;
					break;
				}
				else if (all_goods[i - 1].units_of_measurement > all_goods[i].units_of_measurement) {
					std::cout << all_goods[i - 1] << std::endl;
					std::cout << all_goods[i] << std::endl;
					incorrect = true;
				}
			}
			else if (fields[j] == 4) {
				if (all_goods[i].production_time > all_goods[i - 1].production_time) {
					correct = true;
					break;
				}
				else if (all_goods[i - 1].production_time > all_goods[i].production_time) {
					std::cout << all_goods[i - 1] << std::endl;
					std::cout << all_goods[i] << std::endl;
					incorrect = true;
				}
			}
			else if (fields[j] == 5||fields[j]==6) {
				if (all_goods[i].expiration_date > all_goods[i - 1].expiration_date) {
					correct = true;
					break;
				}
				else if (all_goods[i - 1].expiration_date > all_goods[i].expiration_date) {
					std::cout << all_goods[i - 1] << std::endl;
					std::cout << all_goods[i] << std::endl;
					incorrect = true;
				}
			}
			else if (fields[j] == 7) {
				if (all_goods[i].number > all_goods[i - 1].number) {
					correct = true;
					break;
				}
				else if (all_goods[i - 1].number > all_goods[i].number) {
					std::cout << all_goods[i - 1] << std::endl;
					std::cout << all_goods[i] << std::endl;
					incorrect = true;
				}
			}
			else if (fields[j] == 8) {
				if (all_goods[i].id > all_goods[i - 1].id) {
					correct = true;
					break;
				}
				else if (all_goods[i - 1].id > all_goods[i].id) {
					std::cout << all_goods[i - 1] << std::endl;
					std::cout << all_goods[i] << std::endl;
					incorrect = true;
				}
			}
		}
		if (correct) {
			continue;
		}
	}
	if (incorrect) {
		return false;
	}
	else {
		return true;
	}
}