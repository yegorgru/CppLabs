#pragma once

#include <iostream>
#include <string>
#include <deque>
#include <Windows.h>
#include <string>
#include <cmath>
#include <conio.h>
#include <stdlib.h>


class TreeErr :public std::logic_error
{
public:
	explicit TreeErr(const char* message) :logic_error(message) {}
};

template <class T>
struct binaryNode {
	T item;
	binaryNode* left;
	binaryNode* right;

	binaryNode(T value) {
		item = value;
		left = nullptr;
		right = nullptr;
	}
};

template <class T>
class binaryTree {
	binaryNode<T>* root;
public:
	binaryTree() {
		root = nullptr;
	}

	binaryTree(T value) {
		root = new binaryNode<T>(value);
	}

	~binaryTree() {
		delete_subtree(root);
	}

	void clear() {
		delete_subtree(root);
	}

	void add(T item) {
		if (!root) {
			root = new binaryNode<T>(item);
		}
		else {
			add(item, root);
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

	void show_in_order() {
		if (root) {
			show_in_order(root);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}

	binaryNode<T>* get_root() {
		return this->root;
	}
private:
	void add(T value, binaryNode<T>* node);
	void delete_subtree(binaryNode<T>*& node);
	void show(binaryNode<T>* node);
	void show_in_order(binaryNode<T>* node);
};


template <class T>
class threadedBinaryTree{
	struct Node {
		T item;
		Node* left;
		Node* right;
		bool isl;
		bool isr;
		Node(T value) {
			item = value;
			left = nullptr;
			right = nullptr;
			isl = false;
			isr = false;
		}
	};

	Node* root;

public:
	threadedBinaryTree(binaryTree<T>& binary_tree) {
		if (binary_tree.get_root()) {
			this->root = form_tree(binary_tree.get_root(), nullptr, nullptr);
		}
		else {
			this->root = nullptr;
		}
	}
	~threadedBinaryTree() {
		delete_subtree(root);
	}
	void show() {
		if (root) {
			show(root,1);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}
private:
	void delete_subtree(Node*& node)
	{
		if (node) {
			if (node->left&&node->isl) {
				delete_subtree(node->left);
			}
			if (node->right&&node->isr) {
				delete_subtree(node->right);
			}
			delete node;
			node = nullptr;
		}
	}
	void show(Node* node,bool show_next) {
		if (node) {
			std::cout << node->item;
			if (show_next) {
				if (node->left||node->right) {
					std::cout << '(';
					if (node->left && node->isl) {
						show(node->left,1);
					}
					else if (node->left && !(node->isl)) {
						show(node->left, 0);
					}
					if (node->left && node->right) {
						std::cout << ", ";
					}
					if (node->right && node->isr) {
						show(node->right,1);
					}
					else if (node->right && !(node->isr)) {
						show(node->right, 0);
					}
					std::cout << ')';
				}
			}
		}
	}
	Node* form_tree(binaryNode<T>* p, Node* syml, Node* symr) {
		Node* t = new Node(p->item);
		if (p->left != nullptr) {
			t->left = form_tree(p->left, syml, t);
			t->isl = true;
		}
		else {
			t->left = syml;
			t->isl = false;
		}
		if (p->right != nullptr) {
			t->right = form_tree(p->right, t, symr);
			t->isr = true;
		}
		else {
			t->right = symr;
			t->isr = false;
		}
		return t;
	}
};

template <class T>
class Tree {
	struct Node {
		Node* parent;
		std::deque<Node*>children;
		T item;

		Node(T value) {
			item = value;
			children = {};
			parent = nullptr;
		}
	};

	Node* root;
	size_t length;
public:
	


	Tree() {
		root = nullptr;
		length = 0;
	}
	Tree(T item) {
		root = new Node(item);
		length = 1;
	}
	~Tree() {
		delete_subtree(root);
	}

	size_t size() {
		return this->length;
	}

	T& operator[](size_t index);

	void add(T item,std::deque<size_t>way) {
		if (!root && way.size() == 0) {
			root = new Node(item);
			length = 1;
		}
		else if (root && way.size() == 0) {
			Node* new_item = new Node(item);
			new_item->parent = root;
			root->children.push_back(new_item);
			length++;
		}
		else {
			try
			{
				Node* parent = get_node(root, way);
				if (parent) {
					Node* to_add = new Node(item);
					to_add->parent = parent;
					parent->children.push_back(to_add);
					length++;
				}
				else {
					throw TreeErr("Parent don't exist");
				}
			}
			catch (const std::exception&)
			{
				throw TreeErr("Incorrect way");
			}
		}
	}

	void add(T item,size_t min, size_t max) {
		if (min > max) {
			throw TreeErr("Error. Min > max");
		}
		length++;
		if (!root) {
			root = new Node(item);
		}
		else {
			add(item, min, max, root);
		}
	}

	Node* get_node(std::deque<size_t>way) {
		if (way.size() == 0) {
			return root;
		}
		return get_node(root, way);
	}

	void remove(std::deque<size_t>way,Tree<T>& for_return) {
		if (for_return.root) {
			delete_subtree(for_return.root);
		}
		if (way.size() == 0) {
			for_return.root = &(*(this->root));
			root = nullptr;
			for_return.length = this->length;
			this->length = 0;
		}
		else {
			try
			{
				size_t last_step = way[way.size() - 1];
				way.pop_back();
				Node* parent = get_node(root, way);
				if (parent) {
					if (last_step<parent->children.size()) {
						for_return.root = parent->children[last_step];
						parent->children.erase(parent->children.begin() + last_step);
						size_t counter = 0;
						count_posterity(for_return.root, counter);
						for_return.length = counter;
						this->length -= counter;
					}
					else {
						throw TreeErr("Incorrect way!");
					}
				}
			}
			catch (const std::exception&)
			{
				throw TreeErr("Incorrect way");
			}
		}
	}

	void remove(T some) {
		if (root) {
			if (root->item == some) {
				delete_subtree(root);
				length = 0;
			}
			else {
				while (root) {
					if (!remove(root, some)) {
						break;
					}
				}
			}
		}
		else {
			std::cout << "This tree is empty" << std::endl;
		}
	}

	void clear() {
		delete_subtree(root);
		this->length = 0;
	}

	void show() {
		if (root) {
			show(root);
		}
		else {
			std::cout << "Nothing"<<std::endl;
		}
	}

	void interactive_browsing() {
		if (root) {
			interactive_browsing(root);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}

	std::deque<size_t> get_way(size_t index);
	T& get_element(std::deque<size_t>way);

private:
	void delete_subtree(Node*& node);
	void add(T value,size_t min,size_t max, Node* node);
	Node* pre_order(Node* node, size_t index, size_t& current)
	{
		Node* to_return = nullptr;
		if (current == index) {
			return node;
		}
		else if (node) {
			current++;
			for (size_t i = 0; i < node->children.size(); i++) {
				to_return = pre_order(node->children[i], index, current);
				if (to_return) {
					break;
				}
			}
		}
		return to_return;
	}
	bool part_way(Node* node,Node* to_return, std::deque<size_t>& way);
	T& get_element(Node* node,std::deque<size_t>way);
	Node* get_node(Node* node, std::deque<size_t>way) {
		if (node) {
			if (way.size() == 0) {
				return node;
			}
			if (way.size() == 1) {
				if (way[0] < node->children.size()) {
					return node->children[way[0]];
				}
				else {
					throw TreeErr("Incorrect way");
					return 0;
				}
			}
			else {
				if (node->children.size() > way[0]) {
					size_t current = way[0];
					way.pop_front();
					return get_node(node->children[current], way);
				}
				else {
					throw TreeErr("Incorrect way");
					return nullptr;
				}
			}
		}
		else {
			throw TreeErr("This node don't exist");
			return nullptr;
		}
	}
	void show(Node* node);
	void interactive_browsing(Node* node);
	bool remove(Node*& node,T some);
	void count_posterity(Node* node, size_t& count);
};


class expTree {
	struct Node {
		std::string name;
		double value;
		Node* left;
		Node* right;
		Node(std::string name, double value) {
			this->name = name;
			this->value = value;
			left = nullptr;
			right = nullptr;
		}
		Node(std::string name) {
			this->name = name;
			this->value = 0;
			left = nullptr;
			right = nullptr;
		}
		Node(Node* other) {
			this->name = other->name;
			this->value = other->value;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;

public:
	expTree() {
		root = nullptr;
	}

	expTree(const expTree& other) {
		this->root = construct_subtree(this->root, other.root);
	}

	~expTree() {
		delete_subtree(root);
	}

	bool operator==(const expTree& other)
	{
		return equal_node(this->root, other.root);
	}

	double calculate() {
		try
		{
			return calculation(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
	}

	void show_min() {
		if (root) {
			show_min(root,0);
		}
		else {
			std::cout << "Nothing" << std::endl;
		}
	}

	void form_tree(std::string main_string);
	void show() {
		if (root) {
			show(root);
		}
		else {
			std::cout << std::endl;
		}
	}
	void fill(std::deque<std::string>& variables) {
		if (root) {
			fill(root,variables);
		}
	}

	void fill_values(std::deque<double>& values,std::deque<std::string>& variables) {
		if (root) {
			fill_values(root, values,variables);
			values.clear();
		}
	}

	void simplification() {
		try
		{
			error_checking(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		try
		{
			calc_simplification(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		try
		{
			error_checking(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		try
		{
			logic_simplification(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		try
		{
			error_checking(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
		second_calc_simplification(root);
		last_simplification(root);
		try
		{
			error_checking(root);
		}
		catch (const std::exception& ex)
		{
			throw ex;
		}
	}

	void fill_demo(std::deque<std::string>for_fill, std::deque<int>for_fill2) {
		size_t counter = 0;
		size_t counter2 = 0;
		fill_demo(for_fill,for_fill2, counter,counter2, root);
	}
private:
	expTree(Node* node) {
		this->root = construct_subtree(this->root, node);
	}

	bool equal_node(Node* node1, Node* node2) {
		if ((node1->left && !(node2->left)) || (node2->left && !(node1->left)) || (node1->right && !(node2->right)) || (node2->right && !(node1->right))) {
			return false;
		}
		if (node1->left && node2->left) {
			if (!equal_node(node1->left, node2->left)) {
				return false;
			}
		}
		if (node1->right && node2->right) {
			if (!equal_node(node1->right, node2->right)) {
				return false;
			}
		}
		if (node1->name != node2->name) {
			return false;
		}
		if (node1->name == "" && node2->name == "" && node1->value!=node2->value) {
			return false;
		}
		return true;
	}

	Node* construct_subtree(Node* node, Node* other_node)
	{
		node = new Node(other_node);
		if (other_node->left) {
			node->left = construct_subtree(node->left, other_node->left);
		}
		if (other_node->right) {
			node->right = construct_subtree(node->right, other_node->right);
		}
		return node;
	}
	Node* form_subtree(Node* node, std::string for_form, size_t start, size_t end)
	{
		node = new Node("");
		if (start == end) {
			return node;
		}
		if (for_form[start] == '(' && for_form[end-1] == ')') {
			delete node;
			node = form_subtree(node, for_form, start + 1, end - 1);
		}
		int bracket_counter = 0;
		for (size_t i = end; i > start; i--) {
			if (bracket_counter == 0) {
				if (for_form[i-1] == '-' || for_form[i-1] == '+') {
					node->name = for_form[i-1];
					node->left = form_subtree(node->left, for_form, start, i-1);
					node->right = form_subtree(node->right, for_form, i, end);
					return node;
				}
			}
			if (for_form[i-1] == ')') {
				bracket_counter++;
			}
			else if (for_form[i-1] == '(') {
				bracket_counter--;
			}
		}
		bracket_counter = 0;
		for (size_t i = end; i > start; i--) {
			if (bracket_counter == 0) {
				if (for_form[i-1] == '*' || for_form[i-1] == '/') {
					node->name = for_form[i-1];
					node->left = form_subtree(node->left, for_form, start, i-1);
					node->right = form_subtree(node->right, for_form, i, end);
					return node;
				}
			}
			if (for_form[i-1] == ')') {
				bracket_counter++;
			}
			else if (for_form[i-1] == '(') {
				bracket_counter--;
			}
		}
		bracket_counter = 0;
		for (size_t i = end; i > start; i--) {
			if (bracket_counter == 0) {
				if (for_form[i-1] == '^') {
					node->name = for_form[i-1];
					node->left = form_subtree(node->left, for_form, start, i-1);
					node->right = form_subtree(node->right, for_form, i, end);
					return node;
				}
			}
			if (for_form[i-1] == ')') {
				bracket_counter++;
			}
			else if (for_form[i-1] == '(') {
				bracket_counter--;
			}
		}
		return node;
	}

	void delete_subtree(Node*& node);

	int subtree_height(Node* node);

	void error_checking(Node* node);
	void logic_simplification(Node*& node);
	void second_calc_simplification(Node* node);
	void calc_simplification(Node* node);
	void last_simplification(Node* node);

	double calculation(Node* node);

	void show(Node* node);
	void show_min(Node* node,int priority);
	void fill(Node* node, std::deque<std::string>& variables);
	void fill_values(Node* node,std::deque<double>& values, std::deque<std::string>& variables);
	void fill_demo(std::deque<std::string> for_fill,std::deque<int>for_fill2, size_t& counter,size_t& counter2, Node* node) {
		if (node) {
			fill_demo(for_fill,for_fill2, counter,counter2, node->left);
			if (node->name == ""){
				node->name = for_fill[counter];
				counter++;
			}
			if (node->name == "") {
				node->value = for_fill2[counter2];
				counter2++;
			}
			fill_demo(for_fill, for_fill2, counter, counter2, node->right);
		}
	}
};

std::string form_string();
void form_signs(std::string& to_return);
void add_brackets(std::string& to_return, size_t begin, size_t end);



void main_launch();

int main_menu();

void interactive_mode();

void demomode();

int interactive_menu();

void ordinary();
int ordinary_menu();

void binary();
int binary_menu();

void expression();
int expression_menu();

void get_way(std::deque<size_t>&way);

void show_menu(int what_show);
void show_menu1(int choise);
void show_menu2(int choise);