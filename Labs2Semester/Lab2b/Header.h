#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include<time.h>
#include <cmath>
#include <deque>
#include <conio.h>
#include <string>

struct point {
	double x;
	double y;
	double z;

	friend std::ostream& operator<< (std::ostream& out, const point& point);
	friend bool operator== (const point& point1, const point& point2);
};


template <class T>
class HAT {
	T** head;
	int degree;
	int size;
public:
	HAT() {
		this->degree = 1;
		head = new T * [(int)pow(2, degree)];
		for (size_t i = 0; i < pow(2, degree); i++) {
			head[i] = new T[(int)pow(2, degree)];
		}
		size = 0;
	}
	HAT(int degree) {
		this->degree = degree;
		head = new T * [(int)pow(2, degree)];
		for (size_t i = 0; i < pow(2, degree); i++) {
			head[i] = new T[(int)pow(2, degree)];
		}
		size = 0;
	}
	~HAT() {
		for (size_t i = 0; i < pow(2, degree); i++) {
			delete[] head[i];
		}
		delete[] head;
	}

	void increase() {
		degree++;
		T** new_head = new T* [(int)pow(2, degree)];
		for (size_t i=0; i < pow(2, degree); i++) {
			new_head[i]=new T[(int)pow(2, degree)];
		}
		for (size_t i = 0; i < size; i++) {
			new_head[i / (int)pow(2, degree)][i % (int)pow(2, degree)] = head[i / (int)pow(2, degree - 1)][i % (int)pow(2, degree - 1)];
		}
		for (size_t i = 0; i < pow(2, degree -1); i++) {
			delete[] head[i];
		}
		delete[] head;
		head = new_head;
	}

	void push_back(T value) {
		if (size == pow(2, degree) * pow(2, degree)) {
			increase();
		}
		size++;
		(*this)[size-1] = value;
	}

	bool insert(int pos, T value) {
		if (size == 0) {
			std::cout<<"You can't insert in empty tree"<<std::endl;
			return 0;
		}
		else if (pos<0&&pos<-size || (size > 0 && pos > size - 1)) {
			std::cout << "Incorrect position" << std::endl;
			return 0;
		}
		else {
			if (pos < 0) {
				pos = size + pos;
			}
			if (size == pow(2, degree) * pow(2, degree)) {
				increase();
			}
			size++;
			for (size_t i = size-1; i > pos; i--) {
				(*this)[i] = (*this)[i - 1];
			}
			(*this)[pos] = value;
			return 1;
		}
	}

	void push_front(T value) {
		if (size == 0) {
			push_back(value);
		}
		else {
			insert(0, value);
		}
	}

	bool erase(int pos) {
		if (size == 0) {
			std::cout << "You can't remove from empty tree" << std::endl;
			return 0;
		}
		else if (pos < 0 && pos < -size || (size > 0 && pos > size - 1)) {
			std::cout << "Incorrect position" << std::endl;
			return 0;
		}
		else {
			if (pos < 0) {
				pos = size + pos;
			}
			for (size_t i = pos + 1; i < size; i++) {
				(*this)[i - 1] = (*this)[i];
			}
			size--;
			return 1;
		}
	}

	bool pop_front() {
		return erase(0);
	}

	bool pop_back() {
		return erase(size - 1);
	}

	bool set(int pos, T value) {
		if (size == 0) {
			std::cout << "Error. This tree is empty" << std::endl;
			return 0;
		}
		if (pos < 0 && pos < -size || (size > 0 && pos > size - 1)) {
			std::cout << "Incorrect position" << std::endl;
			return 0;
		}
		else {
			if (pos < 0) {
				pos = size + pos;
			}
			(*this)[pos] = value;
			return 1;
		}
	}

	int search(T value) {
		for (size_t i = 0; i < size; i++) {
			if ((*this)[i] == value) {
				return i;
			}
		}
		return -1;
	}

	int length() {
		return size;
	}

	T& operator[](int pos) {
		if (size == 0) {
			std::cout << "This tree is empty" << std::endl;
		}
		else if (pos < 0 && pos < -size || (size > 0 && pos > size - 1)) {
			std::cout << "Incorrect position" << std::endl;
		}
		else {
			if (pos < 0) {
				pos = size + pos;
			}
			return head[pos / (int)pow(2, degree)][pos % (int)pow(2, degree)];
		}
	}

	void show(int pos) {
		if (size == 0) {
			std::cout << "This tree is empty" << std::endl;
		}
		else if (pos < 0 && pos < -size || (size > 0 && pos > size - 1)) {
			std::cout << "Incorrect position" << std::endl;
		}
		else {
			if (pos < 0) {
				pos = size + pos;
			}
			std::cout << (*this)[pos]<<std::endl;
		}
	}
	void show() {
		if (size == 0) {
			std::cout<<"This tree is empty"<<std::endl;
		}
		else {
			for (size_t i = 0; i < size; i++) {
				std::cout << (*this)[i] << std::endl;
			}
		}
	}
};






struct message_struct {
	std::string message;
	tm current;
};

class messageList {
private:
	message_struct* list=nullptr;
	int max_size=0;
	int size=0;
	int oldest = 0;
public:
	messageList(int max) {
		if (max > 0) {
			list = new message_struct[max];
			max_size = max;
			this->size = 0;
			oldest=max-1;
		}
		else {
			std::cout << "Incorrect input" << std::endl;
		}
	}
	~messageList() {
		if (list != nullptr) {
			delete[] list;
			list = nullptr;
		}
	}

	void push_back(std::string value,tm what_time) {
		if (size == max_size) {
			list[oldest]= { value,what_time };
			oldest--;
			if (oldest == -1) {
				oldest = max_size - 1;
			}
		}
		else {
			size++;
			list[max_size-size] = { value,what_time };
		}
	}

	message_struct* get(int number) {
		if (number > size||number<=0) {
			std::cout << "Incorrect input";
			return 0;
		}
		else {
			return &list[max_size - size - 1 + number];
		}
	}

	void show_K(int K) {
		if (K < 1||K>size) {
			std::cout << "Incorrect input" << std::endl;
			return;
		}
		message_struct* start = get(K);
		for (int i = 0; i < K; i++) {
			std::cout << start[-i].message << std::endl;
		}
	}
};


void demomode1();
void demomode2();
void main_launch();
int main_menu1();
int main_menu2();
int menu();
point get_point();
void actions();
void actions2();
int menu2();