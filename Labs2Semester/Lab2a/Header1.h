#pragma once
#include "Header.h"


namespace firstList {
	template <class T>
	class List {
	private:
		T* list;
		size_t max_size;
		size_t size;
	public:
		List(int max) {
			list = new T[max];
			max_size = max;
			this->size = 0;
		}
		List(int size,T value) {
			list = new T[size];
			max_size = size;
			for (int i = 0; i < size; i++) {
				list[i] = value;
			}
			max_size = size;
			this->size = size;
		}
		~List() {
			if (list != nullptr) {
				delete[] list;
				list = nullptr;
			}
		}

		bool append(T value) {
			if (size >= max_size) {
				std::cout << "Error. List is full" << std::endl;
				return 0;
			}
			else {
				list[size] = value;
				size++;
				return 1;
			}
		}

		bool push_front(T value) {
			if (size >= max_size) {
				std::cout << "Error. List is full" << std::endl;
				return 0;
			}
			else {
				for (int i = size; i > 0; i--) {
					list[i] = list[i - 1];
				}
				list[0] = value;
				size++;
				return 1;
			}
		}

		bool pop_back() {
			if (size > 0) {
				size--;
				return 1;
			}
			else {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
		}


		bool pop_front() {
			if (size == 1) {
				size = 0;
				return 1;
			}
			else if (size > 1) {
				for (size_t i = 1; i < size; i++) {
					list[i - 1] = list[i];
				}
				size--;
				return 1;
			}
			else {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
		}

		bool insert(size_t pos, T value) {
			if (size == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				return 0;
			}
			else if (size >= max_size) {
				std::cout << "Error. This list is full" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				for (size_t i = size; i > pos; i--) {
					list[i] = list[i-1];
				}
				list[pos] = value;
				size++;
				return 1;
			}
		}

		bool insert(size_t pos, int number, T value) {
			if (size == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				return 0;
			}
			else if (size + number >= max_size) {
				std::cout << "Error. This list is full or you want to insert too many elements" << std::endl;
				return 0;
			}
			else if (number <= 0) {
				std::cout << "Incorrect number" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				for (size_t i = size+number-1; i > pos+number-1; i--) {
					list[i] = list[i-number];
				}
				for (int i = 0; i < number; i++) {
					list[pos + i] = value;
				}
				size += number;
				return 1;
			}
		}

		bool remove(size_t pos) {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position\n";
				return 0;
			}
			else {
				for (size_t i = pos; i < size; i++) {
					list[i] = list[i + 1];
				}
				size--;
				return 1;
			}
		}

		bool remove(size_t begin, size_t end) {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			else if (begin < 0 || (size > 0 && end > size - 1)) {
				std::cout << "Incorrect position\n";
				return 0;
			}
			else {
				for (size_t i = begin; i < size - end + begin - 1; i++) {
					list[i] = list[i + end - begin + 1];
				}
				size -= end - begin + 1;
				return 1;
			}
		}

		size_t length() {
			return size;
		}

		T* get(size_t pos) {
			if (size == 0) {
				std::cout << "This list is empty. You can't get point from here\n";
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect positions\n";
				return 0;
			}
			else {
				return &(list[pos]);
			}
		}

		bool set(size_t pos, T value) {
			if (size == 0) {
				std::cout << "Error. This list is empty" << std::endl;
				return 0;
			}
			if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				list[pos] = value;
				return 1;
			}
		}

		bool show() {
			system("cls");
			if (size == 0) {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
			else {
				for (size_t i = 0; i < size; i++) {
					std::cout << list[i] << std::endl;
				}
				return 1;
			}
		}

		bool show(size_t pos) {
			system("cls");
			if (size == 0) {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				std::cout << list[pos];
				return 1;
			}
		}
	};
}

namespace secondList {
	template <class T>
	class List {
	private:
		std::deque<T>list;
	public:
		List(int size, T value) {
			list.push_front(value);
			list.insert(list.begin(), size-1, value);
		}
		List() {

		}
		bool append(T value) {
			list.push_back(value);
			return 1;
		}
		bool push_front(T value) {
			list.push_front(value);
			return 1;
		}
		bool pop_back() {
			if (list.size() > 0) {
				list.pop_back();
				return 1;
			}
			else {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
		}
		bool pop_front() {
			if (list.size() > 0) {
				list.pop_front();
				return 1;
			}
			else {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
		}
		bool insert(size_t pos, T value) {
			if (list.size() == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				return 0;
			}
			else {
				list.insert(pos, value);
				return 1;
			}
		}
		bool insert(size_t pos,int number, T value) {
			if (list.size() == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				return 0;
			}
			else {
				list.insert(list.begin()+pos,number, value);
				return 1;
			}
		}
		bool remove(size_t pos) {
			if (list.size() == 0) {
				std::cout << "You can't remove from empty list" << std::endl;
				return 0;
			}
			else if (pos < 0 || pos > list.size()-1) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				list.erase(list.begin()+pos);
				return 1;
			}
		}
		bool remove(size_t begin,size_t end) {
			if (list.size() == 0) {
				std::cout << "You can't remove from empty list" << std::endl;
				return 0;
			}
			else if (begin>end||begin < 0 || begin > list.size() - 1||end < 0 || end > list.size() - 1) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else if (begin == end) {
				list.erase(list.begin()+begin);
				return 1;
			}
			else {
				list.erase(list.begin()+begin,list.begin()+end);
				return 1;
			}
		}
		size_t length() {
			return list.size();
		}
		T* get(size_t pos) {
			if (pos < 0 || pos > list.size() - 1) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				return &list[pos];
			}
		}
		bool set(size_t pos, T value) {
			if (list.size() == 0) {
				std::cout << "Error. This list is empty" << std::endl;
				return 0;
			}
			else if (pos < 0 || (list.size() > 0 && pos > list.size() - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				list[pos] = value;
				return 1;
			}
		}
		void show() {
			if (list.size() == 0) {
				std::cout << "This list is empty" << std::endl;
			}
			system("cls");
			for (size_t i = 0; i < list.size(); i++) {
				std::cout << list[i] << std::endl;
			}
		}
		void show(size_t pos) {
			system("cls");
			if (list.size() == 0) {
				std::cout << "Error. This list is empty" << std::endl;
			}
			else if (pos < 0 || (list.size() > 0 && pos > list.size() - 1)) {
				std::cout << "Incorrect position" << std::endl;
			}
			else {
				std::cout << list[pos] << std::endl;
			}
		}
	};
}

namespace thirdList {
	template <class T>
	class List {
		struct ListNode {
			T value;
			ListNode* prev;
			ListNode* next;
			ListNode(T value) {
				this->value = value;
				prev = next = nullptr;
			}
		};
		ListNode* head;
		ListNode* tail;
		size_t size;
	public:
		List() {
			head = nullptr;
			tail = nullptr;
			size = 0;
		}
		List(int size,T value) {
			head = nullptr;
			tail = nullptr;
			for (int i = 0; i < size; i++) {
				append(value);
			}
			this->size = size;
		}
		~List() {
			ListNode* current = head;
			if (current != nullptr) {
				while (current->next != nullptr)
				{
					ListNode* garbage = current;
					current = current->next;
					current->prev = nullptr;
					delete garbage;
				}
				current = nullptr;
				delete tail;
			}
		}

		bool append(T value) {
			ListNode* node = new ListNode(value);
			node->prev = tail;
			if (tail) {
				tail->next = node;
			}
			tail = node;
			if (!head) {
				head = node;
			}
			size++;
			return 1;
		}

		bool push_front(T value) {
			ListNode* node = new ListNode(value);
			node->next = head;
			if (head) {
				head->prev = node;
			}
			head = node;
			if (!tail) {
				tail = node;
			}
			size++;
			return 0;
		}

		bool pop_back() {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			if (size == 1) {
				delete tail;
				tail = nullptr;
				head = nullptr;
				size = 0;
				return 0;
			}
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
			size--;
			return 1;
		}

		bool pop_front() {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			else if (size == 1) {
				delete tail;
				tail = nullptr;
				head = nullptr;
				size = 0;
				return 1;
			}
			else {
				head = head->next;
				delete head->prev;
				head->prev = nullptr;
				size--;
				return 1;
			}
		}

		bool insert(size_t pos, T value) {
			if (size == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else if (pos == 0) {
				push_front(value);
				return 1;
			}
			else if (pos > 0 && pos < size) {
				ListNode* node = new ListNode(value);
				ListNode* search = head;
				for (size_t i = 0; i < pos; i++) {
					search = search->next;
				}
				node->next = search;
				node->prev = search->prev;
				search->prev->next = node;
				search->prev = node;
				size++;
				return 1;
			}
			else return 0;
		}

		bool insert(size_t pos, int number, T value) {
			if (size == 0) {
				std::cout << "You can't insert in empty list" << std::endl;
				return 0;
			}
			else if (number <= 0) {
				std::cout << "Incorrect number\n";
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position\n";
				return 0;
			}
			else {
				for (int i = 0; i < number; i++) {
					insert(pos, value);
				}
				return 1;
			}
		}

		bool remove(size_t pos) {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position\n";
				return 0;
			}
			else {
				if (pos == size - 1) {
					pop_back();
					return 1;
				}
				else if (pos == 0) {
					pop_front();
					return 1;
				}
				else if (pos > 0 && pos < size - 1) {
					ListNode* search = head;
					for (size_t i = 0; i < pos + 1; i++) {
						search = search->next;
					}
					ListNode* to_erase = search->prev;
					ListNode* help = to_erase->prev;
					to_erase->prev->next = search;
					search->prev = to_erase->prev;
					delete to_erase;
					size--;
					return 1;
				}
				else return 0;
			}
		}

		bool remove(size_t begin, size_t end) {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			if (begin > end || begin < 0 || (size > 0 && end > size - 1)) {
				std::cout << "Incorrect positions\n";
				return 0;
			}
			else if (begin == end) {
				return remove(begin);
			}
			else {
				for (size_t i = begin; i <= end; i++) {
					remove(begin);
				}
				return 1;
			}
		}

		size_t length() {
			return size;
		}


		T* get(size_t pos) {
			if (size == 0) {
				std::cout << "This list is empty. You can't get point from here\n";
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect positions\n";
				return 0;
			}
			else {
				ListNode* search = head;
				for (size_t i = 0; i < pos; i++) {
					search = search->next;
				}
				return &(search->value);
			}
		}

		bool set(size_t pos, T value) {
			if (size == 0) {
				std::cout << "Error. This list is empty" << std::endl;
				return 0;
			}
			if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect positions\n";
				return 0;
			}
			else {
				ListNode* search = head;
				for (size_t i = 0; i < pos; i++) {
					search = search->next;
				}
				search->value = value;
				return 1;
			}
		}

		bool show() {
			system("cls");
			if (size == 0) {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
			else {
				ListNode* to_show = head;
				for (size_t i = 0; i < size; i++) {
					std::cout << to_show->value << std::endl;
					to_show = to_show->next;
				}
				return 1;
			}
		}

		bool show(size_t pos) {
			system("cls");
			if (size == 0) {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				ListNode* search = head;
				for (size_t i = 0; i < pos; i++) {
					search = search->next;
				}
				std::cout << search->value << std::endl;
				return 1;
			}
		}

		T* operator[](size_t value) {
			if (size == 0) {
				std::cout << "Error. This list is empty" << std::endl;
				return 0;
			}
			if (value > this->size - 1 || value < 0) {
				std::cout << "Error. Out of range" << std::endl;
				return 0;
			}
			else {
				ListNode* search = head;
				for (size_t i = 0; i < value; i++) {
					search = search->next;
				}
				return &search->value;
			}
		}
	};
}

namespace fourthList {
	template <class T>
	class List {
		size_t size;
		T* list;
	public:
		List() {
			list = {};
			size = 0;
			list = nullptr;
		}
		List(int size,T value) {
			append(value);
			insert(0, size, value);
			this->size = size;
		}
		~List() {
			if (list != nullptr) {
				delete[] list;
				list = nullptr;
			}
		}

		bool append(T value) {
			if (size == 0) {
				list = new T(value);
				size = 1;
				return 1;
			}
			else {
				size++;
				T* newArr = new T[size];
				for (size_t i = 0; i < size-1; i++) {
					newArr[i] = list[i];
				}
				newArr[size - 1] = value;
				delete[] this->list;
				this->list = newArr;
				newArr = nullptr;
				return 1;
			}
		}

		bool push_front(T value) {
			if (size == 0) {
				list = new T(value);
				size = 1;
				return 1;
			}
			else {
				size++;
				T* newArr = new T[size];
				for (size_t i = 1; i < size; i++) {
					newArr[i] = this->list[i - 1];
				}
				newArr[0] = value;
				delete[] this->list;
				list = newArr;
				newArr = nullptr;
				return 1;
			}
		}

		bool pop_back() {
			if (size == 1) {
				size--;
				delete[] this->list;
				list = nullptr;
				return 1;
			}
			else if (size > 1) {
				size--;
				T* newArr = new T[size];
				for (size_t i = 0; i < size; i++) {
					newArr[i] = this->list[i];
				}
				delete[] this->list;
				this->list = newArr;
				newArr = nullptr;
				return 1;
			}
			else {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
		}

		bool pop_front() {
			if (size == 1) {
				size--;
				delete[] this->list;
				list = nullptr;
				return 1;
			}
			else if (size > 1) {
				size--;
				T* newArr = new T[size];
				for (size_t i = 0; i < size; i++) {
					newArr[i] = this->list[i + 1];
				}
				delete[] this->list;
				this->list = newArr;
				newArr = nullptr;
				return 1;
			}
			else {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
		}

		bool insert(size_t pos, int number, T value) {
			if (number < 0) {
				std::cout << "ERROR. Incorrect number" << std::endl;
				return 0;
			}
			else if (size == 0) {
				std::cout << "ERROR. You can't insert in empty list" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "ERROR. Incorrect position" << std::endl;
				return 0;
			}
			else {
				size += number;
				T* newArr = new T[size];
				for (size_t i = 0; i < pos; i++) {
					newArr[i] = this->list[i];
				}
				for (size_t i = pos; i < pos + number; i++) {
					newArr[i] = value;
				}
				for (size_t i = pos + number; i < size; i++) {
					newArr[i] = this->list[i - number];
				}
				delete[] this->list;
				this->list = newArr;
				newArr = nullptr;
				return 1;
			}
		}

		bool insert(size_t pos, T value) {
			return insert(pos, 1, value);
		}

		bool remove(size_t pos) {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position\n";
				return 0;
			}
			else {
				remove(pos, pos);
				return 1;
			}
		}

		bool remove(size_t begin, size_t end) {
			if (size == 0) {
				std::cout << "ERROR. This list is empty.\n";
				return 0;
			}
			if (begin > end || begin < 0 || (size > 0 && end > size - 1)) {
				std::cout << "Incorrect positions\n";
				return 0;
			}
			else if (begin == 0 && end == size - 1) {
				delete[] this->list;
				size = 0;
				list = nullptr;
				return 1;
			}
			else {
				size_t copy_size = size;
				size -= end - begin;
				T* newArr = new T[size];
				for (size_t i = 0; i < begin; i++) {
					newArr[i] = this->list[i];
				}
				for (size_t i = 0; i < copy_size - end; i++) {
					newArr[begin + i] = this->list[end + i];
				}
				delete[] this->list;
				this->list = newArr;
				newArr = nullptr;
				return 1;
			}
		}

		size_t length() {
			return size;
		}

		T* get(size_t pos) {
			if (size == 0) {
				std::cout << "This list is empty. You can't get point from here" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect positions" << std::endl;
				return 0;
			}
			else {
				return &(list[pos]);
			}
		}

		bool set(size_t pos, T value) {
			if (size == 0) {
				std::cout << "Error. This list is empty" << std::endl;
				return 0;
			}
			if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect positions" << std::endl;
				return 0;
			}
			else {
				list[pos] = value;
				return 1;
			}
		}

		bool show() {
			system("cls");
			if (size == 0) {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
			else {
				for (int i = 0; i < size; i++) {
					std::cout << list[i] << std::endl;
				}
				return 1;
			}
		}

		bool show(size_t pos) {
			system("cls");
			if (size == 0) {
				std::cout << "This list is empty" << std::endl;
				return 0;
			}
			else if (pos < 0 || (size > 0 && pos > size - 1)) {
				std::cout << "Incorrect position" << std::endl;
				return 0;
			}
			else {
				std::cout << list[pos];
				return 1;
			}
		}
	};
}

