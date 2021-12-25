#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <random>

extern std::mt19937 mersenne;

struct date_and_time
{
	int minutes = 0;
	int hours = 0;
	int day = 0;
	int month =0;
	int year = 0;

	friend std::ofstream& operator<< (std::ofstream& out, const date_and_time& date_and_time);
	friend std::ifstream& operator>> (std::ifstream& in, date_and_time& date_and_time);
	friend std::ostream& operator<< (std::ostream& out, const date_and_time& date_and_time);
	friend bool operator>(const date_and_time& date1, const date_and_time& date2);
	friend bool operator<(const date_and_time& date1, const date_and_time& date2);
	friend bool operator==(const date_and_time& date1, const date_and_time& date2);
};

struct goods
{
	std::string name;
	std::string units_of_measurement = "a";	//kg/kilogram/s, liter/s, package/s, piece/s
	date_and_time production_time;
	int expiration_date = -1;
	double number = -1;
	long long id=0;

	friend std::ostream& operator<< (std::ostream& out, const goods& goods);
	friend std::ofstream& operator<< (std::ofstream& out, const goods& goods);
	friend std::ifstream& operator>> (std::ifstream& in, goods& goods);
};


void main_launch();
int main_menu();
int storage();

date_and_time random_date();
goods random_goods();

bool correct_date(const date_and_time& if_correct);
bool correct_whole_date(const date_and_time& if_correct);

bool whether_correct_units(std::string& units);
std::string correct_var_units(const std::string& units, double number);
bool equal_units(std::string a, std::string b);

goods get_goods(std::string in_top);
void get_only_date(date_and_time& for_date);
date_and_time get_date_and_time();

void actions(std::deque<goods>& all_goods, std::deque<int>& searched);
int menu();


bool search(const std::deque<goods>& all_goods, std::deque<int>& searched, std::string what_search);
bool search(const std::deque<goods>& all_goods, std::deque<int>& searched, std::string units, int exp_date);
bool search(const std::deque<goods>& all_goods, std::deque<int>& searched, date_and_time less, date_and_time bigger);
bool string_in_end(std::string bigger, std::string less);




void add(std::deque<goods>& all_goods, goods to_add, bool benchmark);
void show(const std::deque<goods>& all_goods);
void show(const std::deque<goods>& all_goods, const std::deque<int>& searched);
void interactive_search(const std::deque<goods>& all_goods, std::deque<int>& searched);
int search_menu();
void edit_goods(std::deque<goods>& all_goods, std::deque<int>& searched, bool demo);
int edit_menu();
void remove_goods(std::deque<goods>& all_goods, std::deque<int>& searched);


void save_goods_in(const std::deque<goods>& all_goods, const char* place);
void get_goods_from(std::deque<goods>& all_goods, const char* place);

void demomode();
void benchmark();


void counting_sort(std::deque<goods>& all_goods, size_t begin, size_t end);

void radix_sort(std::deque<goods>& all_goods, size_t begin, size_t end);

void sorting(std::deque<goods>& all_goods,std::deque<int>& order,bool interactive);
bool sorted_correctly(std::deque<goods>all_goods, std::deque<int>fields);

size_t partition_quicksort(std::deque<goods>& Array, size_t begin, size_t end, int field);
void quicksort(std::deque<goods>& Array, size_t begin, size_t end, int field);
