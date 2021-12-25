#pragma once
#include <algorithm>
#include <random>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>

//heapsort
template<typename T>
void copy(T* A, size_t begin, size_t end, T* B)
{
	for (size_t k = begin; k < end; k++) {
		B[k] = A[k];
	}
}

template<typename T>
void show(T* Array, size_t begin, size_t end) {
	for (size_t i = begin; i < end; i++) {
		std::cout << Array[i] << ' ';
	}
	std::cout << std::endl;
	Sleep(5000);
}


template<typename T>
void form_heap(T* Array, size_t n, size_t i) {
	size_t max = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;
	if (left < n && Array[max] < Array[left]) {
		max = left;
	}
	if (right < n&& Array[max] < Array[right]) {
		max = right;
	}
	if (max != i)
	{
		T help = Array[i];
		Array[i] = Array[max];
		Array[max] = help;
		form_heap(Array, n, max);
	}
}


template<typename T>
void heapsort(T* Array, size_t n,bool demo) {
	if (n > 1) {
		for (size_t i = n / 2; i > 0; i--) {
			form_heap(Array, n, i - 1);
			if (demo) {
				std::cout << "Next step:"<<std::endl;
				show(Array,0,n);
			}
		}
		for (size_t i = n; i > 0; i--)
		{
			T help = Array[0];
			Array[0] = Array[i - 1];
			Array[i - 1] = help;
			form_heap(Array, i - 1, 0);
			if (demo) {
				std::cout << "Next step:"<<std::endl;
				show(Array, 0, n);
			}
		}
	}
}

//binary tree sort---------------------------------------------

template <class T>
class binaryTree {
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

	binaryNode* root;
public:
	binaryTree() {
		root = nullptr;
	}

	~binaryTree() {
		delete_subtree(root);
	}

	void add(T item) {
		if (!root) {
			root = new binaryNode(item);
		}
		else {
			add(item, root);
		}
	}

	void show() {
		if (root) {
			show(root);
		}
	}

	void order(T* Array) {
		if (root) {
			size_t current = 0;
			order(root, Array, current);
		}
	}
private:
	void add(T value, binaryNode* node) {
		if (value < node->item) {
			if (node->left) {
				add(value, node->left);

			}
			else {
				node->left = new binaryNode(value);
			}
		}
		else {
			if (node->right) {
				add(value, node->right);
			}
			else {
				node->right = new binaryNode(value);
			}
		}
	}
	void delete_subtree(binaryNode*& node) {
		if (node) {
			if (node->left) {
				delete_subtree(node->left);
			}
			if (node->right) {
				delete_subtree(node->right);
			}
			delete node;
			node = nullptr;
		}
	}
	void order(binaryNode* node, T* Array, size_t& current) {
		if (node) {
			if (node->left) {
				order(node->left, Array, current);
			}
			Array[current] = node->item;
			current++;
			if (node->right) {
				order(node->right, Array, current);
			}
		}
	}
	void show(binaryNode* node) {
		if (node) {
			std::cout << node->item;
			if (node->left || node->right) {
				std::cout << '(';
				if (node->left) {
					show(node->left);
				}
				if (node->left && node->right) {
					std::cout << ", ";
				}
				if (node->right) {
					show(node->right);
				}
				std::cout << ')';
			}
		}
	}
};

template<typename T>
void binary_tree_sort(T* Array, size_t size,bool demo) {
	binaryTree<T>tree;
	for (size_t i = 0; i < size; i++) {
		tree.add(Array[i]);
	}
	if (demo) {
		std::cout << "Binary tree:" << std::endl;
		tree.show();
		std::cout << std::endl;
	}
	tree.order(Array);
}


void main_launch();

void demomode();

void benchmark();
void benchmark_piece(int* Array, std::ofstream& benchm);


void generate_numbers(int* Array, size_t size);