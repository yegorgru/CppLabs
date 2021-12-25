#pragma once

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <fstream>
#include <ctime>

extern std::mt19937 mersenne;

class ListErr :public std::logic_error
{
public:
	explicit ListErr(const char* message) :logic_error(message) {}
};

void commands();
void demomode();
void benchmark();

bool is_int(const std::string& str);

struct point {
	double x;
	double y;
	double z;

	point() {
		x = 0;
		y = 0;
		z = 0;
	}

	point(long long diapason) {
		this->x = mersenne() % (2 * diapason) - diapason + (mersenne() % (2 * diapason) - diapason) * pow(10, -(rand() % 4));
		this->y = mersenne() % (2 * diapason) - diapason + (mersenne() % (2 * diapason) - diapason) * pow(10, -(rand() % 4));
		this->z = mersenne() % (2 * diapason) - diapason + (mersenne() % (2 * diapason) - diapason) * pow(10, -(rand() % 4));
	}

	point(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	friend bool operator>(const point& left, const point& right);
	friend bool operator<(const point& left, const point& right);
	friend bool operator==(const point& left, const point& right);
	friend bool operator>=(const point& left, const point& right);
	friend bool operator<=(const point& left, const point& right);
	friend std::ostream& operator<< (std::ostream& out, const point& point);
};

struct node_abstraction {
	point value;
	long long position;

	node_abstraction(point value, long long position) {
		this->value = value;
		this->position = position;
	}
};

class orderedListLinkedList {
	struct ListNode {
		point value;
		ListNode* prev;
		ListNode* next;
		ListNode() {
			this->value = 0;
			prev = next = nullptr;
		}
		ListNode(point value) {
			this->value = value;
			prev = next = nullptr;
		}
	};
	ListNode* head;
	ListNode* tail;
	size_t size;

public:

	size_t length() {
		return this->size;
	}

	orderedListLinkedList() {
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	
	~orderedListLinkedList() {
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

	void pop_back();

	void pop_front();

	void push(point value);

	void push(point value, long long number);

	void push_random(long long number);

	void erase(point value);

	void erase(size_t pos);

	void erase(size_t begin, size_t end);

	void show();

	void show(size_t pos);

	point operator[](size_t index);

	bool is_value(point value);

	node_abstraction value_search(point value);

	std::vector<point> range_search_values(point down, point top);

	std::vector<node_abstraction> range_search_nodes(point down, point top);

	void action(void (*fooPointer)(point& a));
};

class orderedListArrayList {
private:
	point* list;
	size_t max_size;
	size_t size;
public:
	orderedListArrayList(size_t max) {
		list = new point[max];
		max_size = max;
		size = 0;
	}
	
	orderedListArrayList() {
		list = nullptr;
		max_size = 10;
		size = 0;
	}

	~orderedListArrayList() {
		if (list != nullptr) {
			delete[] list;
			list = nullptr;
		}
	}

	size_t length() {
		return this->size;
	}

	void pop_back();

	void pop_front();

	void push(point value);

	void quick_push(point value);

	void push(point value, long long number);

	void quick_push(point value, long long number);

	void push_random(long long number);

	void erase(point value);

	void erase(size_t pos);

	void erase(size_t begin, size_t end);

	void show();

	void show(size_t pos);

	point operator[](size_t index);

	bool is_value(point value);

	node_abstraction value_search(point value);

	std::vector<point> range_search_values(point down, point top);

	std::vector<node_abstraction> range_search_nodes(point down, point top);

	void action(void (*fooPointer)(point& a));
};

class binaryTree {
	struct binaryNode {
		point item;
		binaryNode* left;
		binaryNode* right;

		binaryNode(point value) {
			item = value;
			left = nullptr;
			right = nullptr;
		}
	};

	binaryNode* root;
	size_t size;
public:
	binaryTree() {
		root = nullptr;
		size = 0;
	}

	binaryTree(point value) {
		root = new binaryNode(value);
		size = 1;
	}

	~binaryTree() {
		delete_subtree(root);
	}

	size_t length() {
		return this->size;
	}

	void clear() {
		delete_subtree(root);
	}

	void push(point item);

	void push_random(long long number);

	void erase(point value) {
		root = erase(value, root);
	}

	void show() {
		if (root) {
			show(root);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}

	void show(size_t pos);

	point operator[](size_t index);

	bool is_value(point value) {
		if (size == 0) {
			return false;
		}
		else {
			return is_value(value, root);
		}
	}

	node_abstraction value_search(point value);

	std::vector<point> range_search_values(point down, point top);

	void action(void (*fooPointer)(point& a)) {
		action(fooPointer, root);
	}

private:
	binaryNode* get_node(size_t pos,size_t& counter,binaryNode* node) {
		if (node) {
			binaryNode* check_return = nullptr;
			if (node->left) {
				check_return = get_node(pos, counter, node->left);
				if (check_return) {
					return check_return;
				}
			}
			if (counter == pos) {
				return node;
			}
			counter++;
			if (node->right) {
				check_return = get_node(pos, counter, node->right);
				if (check_return) {
					return check_return;
				}
			}
		}
		return nullptr;
	}

	bool is_value(point value, binaryNode* node);

	long long value_search(point value, long long& counter, binaryNode* node);

	void range_search_values(point down, point top, std::vector<point>& to_return, binaryNode* node);

	void push(point value, binaryNode* node);

	binaryNode* erase(point value, binaryNode*& node) {
		if (node == nullptr) {
			return node;
		}
		else if (value < node->item) {
			node->left = erase(value, node->left);
		}
		else if (value > node->item) {
			node->right = erase(value, node->right);
		}
		else if (node->left != nullptr && node->right != nullptr) {
			binaryNode* search = node->right;
			while (search->left) {
				search = search->left;
			}
			node->item = search->item;
			node->right = erase(node->item, node->right);
		}
		else {
			if (node->left != nullptr) {
				binaryNode* help = node->left;
				node->item = help->item;
				node->right = help->right;
				node->left = help->left;
				delete help;
			}
			else if (node->right != nullptr) {
				binaryNode* help = node->right;
				node->item = help->item;
				node->right = help->right;
				node->left = help->left;
				delete help;
			}
			else {
				delete node;
				node = nullptr;
			}
		}
		return node;
	}

	void delete_subtree(binaryNode*& node);

	void show(binaryNode* node);

	void action(void (*fooPointer)(point& a), binaryNode* node);
};

class AVL_tree {
	struct Node {
		point item;
		unsigned char height;
		Node* left;
		Node* right;

		Node(point value) {
			item = value;
			height = 1;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;
	size_t size;

public:
	AVL_tree() {
		root = nullptr;
		size = 0;
	}

	AVL_tree(point value) {
		root = new Node(value);
		size = 1;
	}

	~AVL_tree() {
		delete_subtree(root);
	}

	size_t length() {
		return this->size;
	}

	void clear() {
		delete_subtree(root);
	}

	void push(point item);

	void push_random(long long number);

	void erase(point value) {
		if (root) {
			root = erase(value, root);
		}
	}

	void show() {
		if (root) {
			show(root);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}

	void show(size_t pos);

	point operator[](size_t index);

	bool is_value(point value) {
		if (size == 0) {
			return false;
		}
		else {
			return is_value(value, root);
		}
	}

	node_abstraction value_search(point value);

	std::vector<point> range_search_values(point down, point top);

	void action(void (*fooPointer)(point& a)) {
		action(fooPointer, root);
	}

private:

	Node* erase_min(Node* node)
	{
		if (node->left == 0) {
			return node->right;
		}
		else {
			node->left = erase_min(node->left);
			return balance(node);
		}
	}

	Node* erase(point value, Node*& node) {
		if (!node) {
			return nullptr;
		}
		if (value < node->item) {
			node->left = erase(value, node->left);
		}
		else if (value > node->item) {
			node->right = erase(value, node->right);
		}
		else
		{
			Node* left = node->left;
			Node* right = node->right;
			delete node;
			if (!right) {
				return left;
			}
			Node* min = right;
			while (min->left != nullptr) {
				min = min->left;
			}
			min->right = erase_min(right);
			min->left = left;
			return balance(min);
		}
		return balance(node);
	}

	unsigned char height(Node* node)
	{
		if (node) {
			return node->height;
		}
		else {
			return 0;
		}
	}

	int balance_factor(Node* node)
	{
		return height(node->right) - height(node->left);
	}

	void calculate_height(Node* node)
	{
		unsigned char height_left = height(node->left);
		unsigned char height_right = height(node->right);
		node->height = (height_left > height_right ? height_left : height_right) + 1;
	}

	Node* rotate_right(Node* node) {
		Node* to_return = node->left;
		node->left = to_return->right;
		to_return->right = node;
		calculate_height(node);
		calculate_height(to_return);
		return to_return;
	}

	Node* rotate_left(Node* node) {
		Node* to_return = node->right;
		node->right = to_return->left;
		to_return->left = node;
		calculate_height(node);
		calculate_height(to_return);
		return to_return;
	}

	Node* balance(Node* node)
	{
		calculate_height(node);
		if (balance_factor(node) == 2)
		{
			if (balance_factor(node->right) < 0) {
				node->right = rotate_right(node->right);
			}
			return rotate_left(node);
		}
		else if (balance_factor(node) == -2)
		{
			if (balance_factor(node->left) > 0) {
				node->left = rotate_left(node->left);
			}
			return rotate_right(node);
		}
		else {
			return node;
		}
	}

	Node* get_node(size_t pos, size_t& counter, Node* node) {
		if (node) {
			Node* check_return = nullptr;
			if (node->left) {
				check_return = get_node(pos, counter, node->left);
				if (check_return) {
					return check_return;
				}
			}
			if (counter == pos) {
				return node;
			}
			counter++;
			if (node->right) {
				check_return = get_node(pos, counter, node->right);
				if (check_return) {
					return check_return;
				}
			}
		}
		return nullptr;
	}

	bool is_value(point value, Node* node);

	long long value_search(point value, long long& counter, Node* node);

	void range_search_values(point down, point top, std::vector<point>& to_return, Node* node);

	Node* push(point value, Node* node)
	{
		if (value < node->item) {
			if (node->left) {
				node->left = push(value, node->left);
			}
			else {
				node->left = new Node(value);
				size++;
			}
		}
		else {
			if (node->right) {
				node->right = push(value, node->right);
			}
			else {
				node->right = new Node(value);
				size++;
			}
		}
		return balance(node);
	}

	void delete_subtree(Node*& node);

	void show(Node* node);

	void action(void (*fooPointer)(point& a), Node* node);
};

class Tree_2_3 {
	struct Node {
		int size;
		point key[3];
		Node* first;
		Node* second;
		Node* third;
		Node* fourth;
		Node* parent;

		bool is_value(point value) {
			for (int i = 0; i < size; i++) {
				if (key[i] == value) {
					return true;
				}
			}
			return false;
		}

		void sort() {
			if (size == 1) {
				return;
			}
			else if (size == 2) {
				if (key[0] > key[1]) {
					point help = key[0];
					key[0] = key[1];
					key[1] = help;
				}
			}
			else if (size == 3) {
				if (key[0] > key[1]) {
					point help = key[0];
					key[0] = key[1];
					key[1] = help;
				}
				if (key[0] > key[2]) {
					point help = key[0];
					key[0] = key[2];
					key[2] = help;
				}
				if (key[1] > key[2]) {
					point help = key[1];
					key[1] = key[2];
					key[2] = help;
				}
			}
		}

		void insert_to_node(point value) {
			key[size] = value;
			size++;
			sort();
		}

		void erase_from_node(point value) {
			if (size > 0 && key[0] == value) {
				key[0] = key[1];
				key[1] = key[2];
				size--;
			}
			else if (size == 2 && key[1] == value) {
				key[1] = key[2];
				size--;
			}
		}

		void transform_in_node2(point value, Node* first, Node* second) {
			key[0] = value;
			this->first = first;
			this->second = second;
			third = nullptr;
			fourth = nullptr;
			parent = nullptr;
			size = 1;
		}

		bool is_leaf() {
			return (first == nullptr) && (second == nullptr) && (third == nullptr);
		}

		Node(point value) {
			size = 1;
			key[0] = value;
			key[1] = { 0,0,0 };
			key[2] = { 0,0,0 };
			first = nullptr;
			second = nullptr;
			third = nullptr;
			fourth = nullptr;
			parent = nullptr;
		};

		Node(point value, Node* first, Node* second, Node* third, Node* fourth, Node* parent) {
			size = 1;
			key[0] = value;
			key[1] = {0,0,0};
			key[2] = { 0,0,0 };
			this->first = first;
			this->second = second;
			this->third = third;
			this->fourth = fourth;
			this->parent = parent;
		}
	};

	Node* root;
	size_t size;

public:
	Tree_2_3() {
		root = nullptr;
		size = 0;
	}

	~Tree_2_3() {
		delete_subtree(root);
	}

	size_t length() {
		return this->size;
	}

	void delete_subtree(Node*& node);

	void push(point value) {
		root = insert(root, value);
	}

	void erase(point value) {
		if (root) {
			root = erase(root, value);
		}
	}

	void show() {
		if (root) {
			show(root);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}

	bool is_value(point value);

	std::vector<point> range_search_values(point down, point top);

	void push_random(long long number);

	void action(void (*fooPointer)(point& a)) {
		action(fooPointer, root);
	}
private:
	void range_search_values(point down, point top, std::vector<point>& to_return, Node* node);

	Node* split(Node* item) {
		if (item->size < 3) {
			return item;
		}
		else {
			Node* split1 = new Node(item->key[0], item->first, item->second, nullptr, nullptr, item->parent);
			Node* split2 = new Node(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);
			if (split1->first) {
				split1->first->parent = split1;
			}
			if (split1->second) {
				split1->second->parent = split1;
			}
			if (split2->first) {
				split2->first->parent = split2;
			}
			if (split2->second) {
				split2->second->parent = split2;
			}
			if (item->parent) {
				item->parent->insert_to_node(item->key[1]);
				if (item->parent->first == item) {
					item->parent->first = nullptr;
				}
				else if (item->parent->second == item) {
					item->parent->second = nullptr;
				}
				else if (item->parent->third == item) {
					item->parent->third = nullptr;
				}
				if (item->parent->first == nullptr) {
					item->parent->fourth = item->parent->third;
					item->parent->third = item->parent->second;
					item->parent->second = split2;
					item->parent->first = split1;
				}
				else if (item->parent->second == nullptr) {
					item->parent->fourth = item->parent->third;
					item->parent->third = split2;
					item->parent->second = split1;
				}
				else {
					item->parent->third = split1;
					item->parent->fourth = split2;
				}
				Node* to_return = item->parent;
				delete item;
				return to_return;
			}
			else {
				split1->parent = item;
				split2->parent = item;
				item->transform_in_node2(item->key[1], split1, split2);
				return item;
			}
		}
	}

	Node* insert(Node* node, point value) {
		if (!node) {
			size++;
			return new Node(value);
		}
		if (node->is_leaf()) {
			size++;
			node->insert_to_node(value);
		}
		else if (value <= node->key[0]) {
			insert(node->first, value);
		}
		else if ((node->size == 1) || ((node->size == 2) && value <= node->key[1])) {
			insert(node->second, value);
		}
		else {
			insert(node->third, value);
		}
		return split(node);
	}

	Node* get_node(Node* node, point value) {
		if (!node) {
			return nullptr;
		}
		else if (node->is_value(value)) {
			return node;
		}
		else if (value < node->key[0]) {
			return get_node(node->first, value);
		}
		else if ((node->size == 2) && (value < node->key[1]) || (node->size == 1)) {
			return get_node(node->second, value);
		}
		else if (node->size == 2) {
			return get_node(node->third, value);
		}
		return nullptr;
	}

	Node* regain(Node* node) {
		if (node->size == 0 && node->parent == nullptr) {
			delete node;
			return nullptr;
		}
		else if (node->size != 0) {
			if (node->parent) {
				return regain(node->parent);
			}
			else {
				return node;
			}
		}
		Node* parent = node->parent;
		if ((parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) || (parent->size == 2 && parent->third->size == 2)) {
			node = redistribute(node);
		}
		else {
			node = merge(node);
		}
		return regain(node);
	}

	Node* redistribute(Node* node) {
		Node* parent = node->parent;
		Node* first = parent->first;
		Node* second = parent->second;
		Node* third = parent->third;
		if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
			if (first == node) {
				parent->first = parent->second;
				parent->second = parent->third;
				parent->third = nullptr;
				parent->first->insert_to_node(parent->key[0]);
				parent->first->third = parent->first->second;
				parent->first->second = parent->first->first;
				if (node->first != nullptr) {
					parent->first->first = node->first;
				}
				else if (node->second != nullptr) {
					parent->first->first = node->second;
				}
				if (parent->first->first != nullptr) {
					parent->first->first->parent = parent->first;
				}
				parent->erase_from_node(parent->key[0]);
				delete first;
			}
			else if (second == node) {
				first->insert_to_node(parent->key[0]);
				parent->erase_from_node(parent->key[0]);
				if (node->first != nullptr) {
					first->third = node->first;
				}
				else if (node->second != nullptr) {
					first->third = node->second;
				}
				if (first->third != nullptr) {
					first->third->parent = first;
				}
				parent->second = parent->third;
				parent->third = nullptr;
				delete second;
			}
			else if (third == node) {
				second->insert_to_node(parent->key[1]);
				parent->third = nullptr;
				parent->erase_from_node(parent->key[1]);
				if (node->first != nullptr) second->third = node->first;
				else if (node->second != nullptr) {
					second->third = node->second;
				}
				if (second->third != nullptr) {
					second->third->parent = second;
				}
				delete third;
			}
		}
		else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
			if (third == node) {
				if (node->first != nullptr) {
					node->second = node->first;
					node->first = nullptr;
				}
				node->insert_to_node(parent->key[1]);
				if (second->size == 2) {
					parent->key[1] = second->key[1];
					second->erase_from_node(second->key[1]);
					node->first = second->third;
					second->third = nullptr;
					if (node->first != nullptr) node->first->parent = node;
				}
				else if (first->size == 2) {
					parent->key[1] = second->key[0];
					node->first = second->second;
					second->second = second->first;
					if (node->first != nullptr) {
						node->first->parent = node;
					}
					second->key[0] = parent->key[0];
					parent->key[0] = first->key[1];
					first->erase_from_node(first->key[1]);
					second->first = first->third;
					if (second->first != nullptr) {
						second->first->parent = second;
					}
					first->third = nullptr;
				}
			}
			else if (second == node) {
				if (third->size == 2) {
					if (node->first == nullptr) {
						node->first = node->second;
						node->second = nullptr;
					}
					second->insert_to_node(parent->key[1]);
					parent->key[1] = third->key[0];
					third->erase_from_node(third->key[0]);
					second->second = third->first;
					if (second->second != nullptr) {
						second->second->parent = second;
					}
					third->first = third->second;
					third->second = third->third;
					third->third = nullptr;
				}
				else if (first->size == 2) {
					if (node->second == nullptr) {
						node->second = node->first;
						node->first = nullptr;
					}
					second->insert_to_node(parent->key[0]);
					parent->key[0] = first->key[1];
					first->erase_from_node(first->key[1]);
					second->first = first->third;
					if (second->first != nullptr) {
						second->first->parent = second;
					}
					first->third = nullptr;
				}
			}
			else if (first == node) {
				if (node->first == nullptr) {
					node->first = node->second;
					node->second = nullptr;
				}
				first->insert_to_node(parent->key[0]);
				if (second->size == 2) {
					parent->key[0] = second->key[0];
					second->erase_from_node(second->key[0]);
					first->second = second->first;
					if (first->second != nullptr) {
						first->second->parent = first;
					}
					second->first = second->second;
					second->second = second->third;
					second->third = nullptr;
				}
				else if (third->size == 2) {
					parent->key[0] = second->key[0];
					second->key[0] = parent->key[1];
					parent->key[1] = third->key[0];
					third->erase_from_node(third->key[0]);
					first->second = second->first;
					if (first->second != nullptr) {
						first->second->parent = first;
					}
					second->first = second->second;
					second->second = third->first;
					if (second->second != nullptr) {
						second->second->parent = second;
					}
					third->first = third->second;
					third->second = third->third;
					third->third = nullptr;
				}
			}
		}
		else if (parent->size == 1) {
			node->insert_to_node(parent->key[0]);
			if (first == node && second->size == 2) {
				parent->key[0] = second->key[0];
				second->erase_from_node(second->key[0]);
				if (node->first == nullptr) {
					node->first = node->second;
				}
				node->second = second->first;
				second->first = second->second;
				second->second = second->third;
				second->third = nullptr;
				if (node->second != nullptr) {
					node->second->parent = node;
				}
			}
			else if (second == node && first->size == 2) {
				parent->key[0] = first->key[1];
				first->erase_from_node(first->key[1]);
				if (node->second == nullptr) {
					node->second = node->first;
				}
				node->first = first->third;
				first->third = nullptr;
				if (node->first != nullptr) {
					node->first->parent = node;
				}
			}
		}
		return parent;
	}

	Node* merge(Node* node) {
		Node* parent = node->parent;
		if (parent->first == node) {
			parent->second->insert_to_node(parent->key[0]);
			parent->second->third = parent->second->second;
			parent->second->second = parent->second->first;
			if (node->first != nullptr) {
				parent->second->first = node->first;
			}
			else if (node->second != nullptr) {
				parent->second->first = node->second;
			}
			if (parent->second->first != nullptr) {
				parent->second->first->parent = parent->second;
			}
			parent->erase_from_node(parent->key[0]);
			delete parent->first;
			parent->first = nullptr;
		}
		else if (parent->second == node) {
			parent->first->insert_to_node(parent->key[0]);
			if (node->first != nullptr) {
				parent->first->third = node->first;
			}
			else if (node->second != nullptr) {
				parent->first->third = node->second;
			}
			if (parent->first->third != nullptr) {
				parent->first->third->parent = parent->first;
			}
			parent->erase_from_node(parent->key[0]);
			delete parent->second;
			parent->second = nullptr;
		}
		if (parent->parent == nullptr) {
			Node* to_return = nullptr;
			if (parent->first != nullptr) {
				to_return = parent->first;
			}
			else {
				to_return = parent->second;
			}
			if (to_return) {
				to_return->parent = nullptr;
			}
			delete parent;
			return to_return;
		}
		return parent;
	}

	Node* erase(Node* node, point value) {
		Node* item = get_node(node, value);
		if (!item) {
			return node;
		}
		Node* min = nullptr;
		if (item->key[0] == value) {
			if (item->second) {
				min = item->second;
				while (min->first != nullptr) {
					min = min->first;
				}
			}
		}
		else {
			if (item->third) {
				min = item->third;
				while (min->first != nullptr) {
					min = min->first;
				}
			}
		}
		if (min) {
			if (value == item->key[0]) {
				point help = item->key[0];
				item->key[0] = min->key[0];
				min->key[0] = help;
			}
			else {
				point help = item->key[1];
				item->key[1] = min->key[0];
				min->key[0] = help;
			}
			item = min;
		}
		item->erase_from_node(value);
		return regain(item);
	}

	void show(Node* node);

	void action(void (*fooPointer)(point& a), Node* node);
};

void commands(int what_structure, long long number);

template<typename T>
size_t partition_quicksort(std::vector<T>& Array, size_t begin, size_t end) {
	begin++;
	end++;
	T pivot = Array[begin - 1 + mersenne() % (end - begin)];
	size_t i = begin - 1;
	size_t j = end + 1;
	while (true) {
		do {
			i++;
		} while (Array[i - 1] < pivot);
		do {
			j--;
		} while (Array[j - 1] > pivot);
		if (i >= j) {
			return j - 1;
		}
		T help = Array[i - 1];
		Array[i - 1] = Array[j - 1];
		Array[j - 1] = help;
	}
}

template<typename T>
void quicksort(std::vector<T>& Array, size_t begin, size_t end)
{
	if (begin < end) {
		size_t p = partition_quicksort(Array, begin, end);
		quicksort(Array, begin, p);
		quicksort(Array, p + 1, end);
	}
}

void x_plus(point& P);
void x_minus(point& P);
void y_plus(point& P);
void y_minus(point& P);
void z_plus(point& P);
void z_minus(point& P);