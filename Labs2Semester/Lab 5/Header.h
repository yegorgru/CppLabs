#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>
#include <conio.h>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

extern std::mt19937 mersenne;
extern std::string help_answer;

class GraphErr :public std::logic_error
{
public:
	explicit GraphErr(const char* message) :logic_error(message) {}
};

struct node_struct {
	int weight;
	size_t node;
};

struct way_struct
{
	int weight;
	size_t begin;
	size_t end;
};

struct edge_struct {
	size_t begin;
	size_t end;
};


class adjacencyStructure;

class adjacencyMatrix {

	std::vector<std::vector<int>>matrix;

	bool weighted;
	bool directed;
	bool structure;
public:

	bool what_structure() {
		return structure;
	}

	adjacencyMatrix(bool weighted, bool directed) {
		this->weighted = weighted;
		this->directed = directed;
		this->structure = 0;
	}

	adjacencyMatrix(bool weighted, bool directed, size_t number_of_nodes, size_t number_of_edges);

	adjacencyMatrix(adjacencyStructure& another);

	void add_redge(size_t first_node,size_t second_node);
	void add_redge(size_t first_node, size_t second_node,int weight);
	void add_node();
	void show();
	void show_structure();

	int delete_redge(size_t first_node, size_t second_node);
	void delete_node(size_t node);

	size_t get_number_of_nodes() const
	{
		return matrix.size();
	}

	int get_number_of_edges() const {
		int counter = 0;
		for (size_t i = 0; i < matrix.size(); i++) {
			for (size_t j = 0; j < matrix.size(); j++) {
				if (matrix[i][j] != INT_MAX && i!=j) {
					counter++;
				}
			}
		}
		if (!directed) {
			counter /= 2;
		}
		return counter;
	}

	int get_weight() {
		int answer = 0;
		for (auto& i : matrix) {
			for (auto j : i) {
				if (j != INT_MAX) {
					answer += j;
				}
			}
		}
		if (!directed) {
			answer /= 2;
		}
		return answer;
	}

	bool is_weighted() const
	{
		return this->weighted;
	}

	bool is_directed() const
	{
		if (this->directed) {
			return true;
		}
		else {
			return false;
		}
	}

	adjacencyStructure get_adjacencyStructure();

	bool is_acyclic();
	bool check_cyclic(size_t node,std::vector<char>&checked,size_t parent);

	std::string is_connected_graph();

	bool is_tree() {
		std::string connected_check = this->is_connected_graph();
		if (this->is_acyclic() && (connected_check == "strongly connected graph" || connected_check == "connected graph")) {
			return true;
		}
		else {
			return false;
		}
	}

	void find_nodes(size_t node, std::vector<bool>& for_check, std::vector<size_t>& component);
	void find_components(std::vector<std::vector<size_t>>& for_components);
	void find_strong_components(std::vector<std::vector<size_t>>& for_components);

	std::vector<int> dijkstra_algorithm(size_t node);

	adjacencyMatrix build_reverse() const;

	std::vector<std::vector<int>>floyd_algorithm();

	std::vector<int>bellman_ford_algorithm(size_t node);

	std::vector<size_t> depth_first(bool important_weight);
	void depth_first(size_t node, std::vector<bool>& checked, bool important_weight, std::vector<size_t>& order);

	adjacencyMatrix depth_first_spanning_tree(bool important_weight);
	adjacencyMatrix minimum_spanning_tree_kruskal();
	adjacencyMatrix minimum_spanning_reverse_delete();

	std::vector<size_t> topological_sorting_kahn();
	std::vector<size_t> topological_sorting_depth_first() {
		if (directed && is_acyclic()) {
			return depth_first(0);
		}
		else {
			throw GraphErr("Topological sorting is possible only for directed and acyclic graphs");
		}
	}

	friend adjacencyStructure;
	friend void dfs1(const adjacencyMatrix& graph, size_t v, std::vector<bool>& used, std::vector<size_t>& order);
	friend void dfs2(const adjacencyMatrix& graph, size_t v, std::vector<bool>& used, std::vector<size_t>& order, std::vector<size_t>& component);
};

class adjacencyStructure {
	std::vector<std::vector<size_t>>nodes;

	std::vector<std::vector<int>>weights;

	bool weighted;
	bool directed;
	bool structure;
public:
	bool what_structure() {
		return structure;
	}

	adjacencyStructure(bool weighted, bool directed) {
		this->weighted = weighted;
		this->directed = directed;
		this->structure = 1;
	}

	adjacencyStructure(bool weighted, bool directed, size_t number_of_nodes, size_t number_of_edges);

	adjacencyStructure(const adjacencyMatrix& another);

	bool find(size_t first_node, size_t second_node) const;

	void add_redge(size_t first_node, size_t second_node);
	void add_redge(size_t first_node, size_t second_node, int weight);
	void add_node();
	void show();
	void show_structure();

	int delete_redge(size_t first_node, size_t second_node);
	void delete_node(size_t node);

	size_t get_number_of_nodes() const
	{
		return nodes.size();
	}

	int get_number_of_edges() const {
		int counter = 0;
		for (size_t i = 0; i < nodes.size(); i++) {
			counter += nodes[i].size();
		}
		if (!directed) {
			counter /= 2;
		}
		return counter;
	}

	int get_weight() {
		int answer = 0;
		if (!weighted) {
			return get_number_of_edges();
		}
		else {
			for (auto& i : weights) {
				for (auto j : i) {
					answer += j;
				}
			}
		}
		if (!directed) {
			answer /= 2;
		}
		return answer;
	}

	bool is_weighted() const
	{
		return this->weighted;
	}

	bool is_directed() const
	{
		if (directed) {
			return true;
		}
		else {
			return false;
		}
	}

	adjacencyMatrix get_adjacencyMatrix() {
		return adjacencyMatrix(*this);
	}

	bool is_acyclic();
	bool check_cyclic(size_t node, std::vector<char>& checked, size_t parent);

	bool is_tree() {
		std::string connected_check = this->is_connected_graph();
		if (this->is_acyclic() && (connected_check == "strongly connected graph" || connected_check == "connected graph")) {
			return true;
		}
		else {
			return false;
		}
	}

	std::string is_connected_graph();

	void find_nodes(size_t node, std::vector<bool>& for_check, std::vector<size_t>& component);
	void find_components(std::vector<std::vector<size_t>>& for_components);
	void find_strong_components(std::vector<std::vector<size_t>>& for_components);

	adjacencyStructure build_reverse() const;

	std::vector<int> dijkstra_algorithm(size_t node);

	std::vector<std::vector<int>>floyd_algorithm();
	std::vector<int>bellman_ford_algorithm(size_t node);

	std::vector<size_t> depth_first(bool important_weight);
	void depth_first(size_t node, std::vector<bool>& checked, bool important_weight, std::vector<size_t>& order);

	adjacencyStructure depth_first_spanning_tree(bool important_weight);
	adjacencyStructure minimum_spanning_tree_kruskal();
	adjacencyStructure minimum_spanning_reverse_delete();

	std::vector<size_t> topological_sorting_kahn();
	std::vector<size_t> topological_sorting_depth_first() {
		if (directed && is_acyclic()) {
			return depth_first(0);
		}
		else {
			throw GraphErr("Topological sorting is possible only for directed and acyclic graphs");
		}
	}

	friend adjacencyMatrix;
	friend void dfs1(const adjacencyStructure& graph, size_t v, std::vector<bool>& used, std::vector<size_t>& order);
	friend void dfs2(const adjacencyStructure& graph, size_t v, std::vector<bool>& used, std::vector<size_t>& order, std::vector<size_t>& component);
};

void commands();

void main_launch_menu();
int main_menu();

void demomode();
void benchmark();
void benchmark_piece_matrix(bool weighted, bool directed, std::ofstream& benchm);
void benchmark_piece_structure(bool weighted, bool directed, std::ofstream& benchm);
int menu();
int what_graph_menu();
int what_distance_menu();
int what_distance_algorithm_menu();

bool is_int(const std::string& str);

template<typename T>
void insertion_sort(std::vector<T>& Array, size_t begin, size_t end)
{
	for (size_t i = begin + 1; i < end + 1; i++) {
		T key = Array[i];
		size_t j = i;
		while (j > begin && Array[j - 1].weight > key.weight) {
			Array[j] = Array[j - 1];
			j--;
		}
		Array[j] = key;
	}
}

template <typename T>
size_t partition_quicksort(std::vector<T>& Array, size_t begin, size_t end) {
	begin++;
	end++;
	T pivot = Array[begin - 1 + mersenne() % (end - begin)];
	size_t i = begin - 1;
	size_t j = end + 1;
	while (true) {
		do {
			i++;
		} while (Array[i - 1].weight < pivot.weight);
		do {
			j--;
		} while (Array[j - 1].weight > pivot.weight);
		if (i >= j) {
			return j - 1;
		}
		T help = Array[i - 1];
		Array[i - 1] = Array[j - 1];
		Array[j - 1] = help;
	}
}

template <typename T>
void quicksort(std::vector<T>& Array, size_t begin, size_t end)
{
	if (begin < end) {
		if ((end - begin) < 30) {
			insertion_sort(Array, begin, end);
			return;
		}
		size_t p = partition_quicksort(Array, begin, end);
		quicksort(Array, begin, p);
		quicksort(Array, p + 1, end);
	}
}

template <typename T>
void actions(T graph) {
	int choise = menu();
	while (choise != 21) {
		if (choise == 0) {
			size_t first_node, second_node;
			int weight = 0;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter first node" << std::endl;
				std::cin >> first_node;
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
			while (!correct) {
				std::cout << "Enter second node" << std::endl;
				std::cin >> second_node;
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
			try
			{
				if (graph.is_weighted()) {
					correct = false;
					while (!correct) {
						std::cout << "Enter first node" << std::endl;
						std::cin >> weight;
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
					graph.add_redge(first_node, second_node, weight);
				}
				else {
					graph.add_redge(first_node, second_node);
				}
				std::cout << "Successfully added" << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 1) {
			graph.add_node();
			std::cout << "Successfully added" << std::endl;
		}
		if (choise == 2) {
			size_t first_node, second_node;
			int weight = 0;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter first node" << std::endl;
				std::cin >> first_node;
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
			while (!correct) {
				std::cout << "Enter second node" << std::endl;
				std::cin >> second_node;
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
			try
			{
				graph.delete_redge(first_node, second_node);
				std::cout << "Successfully added" << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 3) {
			size_t node;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter node" << std::endl;
				std::cin >> node;
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
			try
			{
				graph.delete_node(node);
				std::cout << "Successfully added" << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 4) {
			graph.show();
		}
		else if (choise == 5) {
			graph.show_structure();
		}
		else if (choise == 6) {
			std::cout << graph.get_weight() << std::endl;
		}
		else if (choise == 7) {
			size_t number_of_nodes, number_of_edges;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter number of nodes" << std::endl;
				std::cin >> number_of_nodes;
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
			while (!correct) {
				std::cout << "Enter number of edges" << std::endl;
				std::cin >> number_of_edges;
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
			try
			{
				T new_graph(graph.is_weighted(), graph.is_directed(), number_of_nodes, number_of_edges);
				graph = new_graph;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 8) {
			std::cout << graph.is_connected_graph() << std::endl;
		}
		else if (choise == 9) {
			std::vector<std::vector<size_t>> for_components;
			try
			{
				if (graph.is_directed()) {
					graph.find_strong_components(for_components);
				}
				else {
					graph.find_components(for_components);
				}
				if (for_components.size() > 0) {
					for (size_t i = 0; i < for_components.size(); i++) {
						std::cout << i + 1 << "component: " << std::endl;
						for (size_t j = 0; j < for_components[i].size(); j++) {
							std::cout << " " << for_components[i][j];
						}
						std::cout << std::endl;
					}
				}
				else {
					std::cout << "There isn't any component" << std::endl;
				}
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 10) {
			if (graph.is_acyclic()) {
				std::cout << "Acyclic";
			}
			else {
				std::cout << "Cyclic";
			}
			std::cout << std::endl;
		}
		else if (choise == 11) {
			if (graph.is_tree()) {
				std::cout << "This is tree";
			}
			else {
				std::cout << "This isn't tree";
			}
			std::cout << std::endl;
		}
		else if (choise == 12) {
			int what_distance = what_distance_menu();
			int what_algorithm = what_distance_algorithm_menu();
			if (what_distance == 0) {
				size_t node1;
				bool correct = false;
				char ch;
				while (!correct) {
					std::cout << "Enter first node" << std::endl;
					std::cin >> node1;
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
				size_t node2;
				correct = false;
				while (!correct) {
					std::cout << "Enter second node" << std::endl;
					std::cin >> node2;
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
				try
				{
					if (what_algorithm == 0) {
						try
						{
							std::vector<int>distances = graph.dijkstra_algorithm(node1);
							if (node1 < distances.size() && node2 < distances.size()) {
								if(distances[node2]==INT_MAX){
									std::cout << "Another componenet" << std::endl;
								}
								else {
									std::cout << distances[node2] << std::endl;
								}
							}
							else {
								std::cout << "Incorrect first or second node" << std::endl;
							}
						}
						catch (const std::exception& ex)
						{
							throw ex;
						}
					}
					else if (what_algorithm == 1) {
						std::vector<std::vector<int>>distances = graph.floyd_algorithm();
						if (node1 < distances.size() && node2 < distances.size()) {
							if (distances[node1][node2] == INT_MAX) {
								std::cout << "Another component" << std::endl;
							}
							else {
								std::cout << distances[node1][node2] << std::endl;
							}
						}
						else {
							std::cout << "Incorrect first or second node" << std::endl;
						}
					}
					else if (what_algorithm == 2) {
						try
						{
							std::vector<int>distances = graph.bellman_ford_algorithm(node1);
							if (node1 < distances.size() && node2 < distances.size()) {
								if (distances[node2] == INT_MAX) {
									std::cout << "Another component" << std::endl;
								}
								else {
									std::cout << distances[node2] << std::endl;
								}
							}
							else {
								std::cout << "Incorrect first or second node" << std::endl;
							}
						}
						catch (const std::exception& ex)
						{
							throw ex;
						}
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (what_distance == 1) {
				size_t node1;
				bool correct = false;
				char ch;
				while (!correct) {
					std::cout << "Enter node" << std::endl;
					std::cin >> node1;
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
				try
				{
					if (what_algorithm == 0) {
						std::vector<int>distances = graph.dijkstra_algorithm(node1);
						for (size_t i = 0; i < distances.size(); i++) {
							if (distances[i] != INT_MAX) {
								std::cout << "Node " << i << ": " << distances[i] << std::endl;
							}
							else {
								std::cout << "Node " << i << " in another component" << std::endl;
							}
						}
					}
					else if (what_algorithm == 1) {
						if (node1 < graph.get_number_of_nodes()) {
							std::vector<std::vector<int>>distances = graph.floyd_algorithm();
							for (size_t i = 0; i < distances.size(); i++) {
								if (distances[node1][i] != INT_MAX) {
									std::cout << "Node " << i << ": " << distances[node1][i] << std::endl;
								}
								else {
									std::cout << "Node " << i << " in another component" << std::endl;
								}
							}
						}
						else {
							std::cout << "Incorrect node" << std::endl;
						}
					}
					else if (what_algorithm == 2) {
						std::vector<int>distances = graph.bellman_ford_algorithm(node1);
						for (size_t i = 0; i < distances.size(); i++) {
							if (distances[i] != INT_MAX) {
								std::cout << "Node " << i << ": " << distances[i] << std::endl;
							}
							else {
								std::cout << "Node " << i << " in another component" << std::endl;
							}
						}
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (what_distance == 2) {
				try
				{
					std::vector<std::vector<int>>distances(graph.get_number_of_nodes());
					if (what_algorithm == 0) {
						for (size_t i = 0; i < distances.size(); i++) {
							distances[i] = graph.dijkstra_algorithm(i);
						}
					}
					else if (what_algorithm == 1) {
						distances = graph.floyd_algorithm();
					}
					else if (what_distance == 2) {
						for (size_t i = 0; i < distances.size(); i++) {
							distances[i] = graph.bellman_ford_algorithm(i);
						}
					}
					std::cout << "Nodes";
					std::cout << "\t\t" << 0;
					for (size_t i = 1; i < distances.size(); i++) {
						std::cout << '\t' << i;
					}
					std::cout << std::endl;
					for (size_t i = 0; i < distances.size(); i++) {
						std::cout << "Node " << i << ": ";
						for (size_t j = 0; j < distances.size(); j++) {
							if (distances[i][j] != INT_MAX) {
								std::cout << '\t' << distances[i][j];
							}
							else {
								std::cout << '\t' << "ac";
							}
						}
						std::cout << std::endl;
					}
					std::cout << "ac = in another component" << std::endl;
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
		}
		else if (choise == 13) {
			std::vector<size_t>order;
			bool important = false;
			if (graph.is_weighted()) {
				int important_weight = 0;
				int code;
				do {
					system("cls");
					std::cout << "Important weight?\n";
					important_weight = (important_weight + 2) % 2;
					if (important_weight == 0) std::cout << "-> important weight" << std::endl;
					else  std::cout << "   important weight" << std::endl;
					if (important_weight == 1) std::cout << "-> unimportant weight" << std::endl;
					else  std::cout << "   unimportant weight" << std::endl;
					code = _getch();
					if (code == 224)
					{
						code = _getch();
						if (code == 80) important_weight++;
						if (code == 72) important_weight--;
					}
				} while (code != 13);
				system("cls");
				important = !important_weight;
			}
			order = graph.depth_first(important);
			for (size_t i = 0; i < order.size(); i++) {
				std::cout << order[i] << " ";
			}
			std::cout << std::endl;
		}
		else if (choise == 14) {
			std::vector<size_t>order;
			try
			{
				order = graph.topological_sorting_kahn();
				for (size_t i = 0; i < order.size(); i++) {
					std::cout << order[i] << " ";
				}
				std::cout << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 15) {
			std::vector<size_t>order;
			try
			{
				order = graph.topological_sorting_depth_first();
				for (size_t i = 0; i < order.size(); i++) {
					std::cout << order[i] << " ";
				}
				std::cout << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 16) {
			bool important = false;
			if (graph.is_weighted()) {
				int important_weight = 0;
				int code;
				do {
					system("cls");
					std::cout << "Important weight?\n";
					important_weight = (important_weight + 2) % 2;
					if (important_weight == 0) std::cout << "-> important weight" << std::endl;
					else  std::cout << "   important weight" << std::endl;
					if (important_weight == 1) std::cout << "-> unimportant weight" << std::endl;
					else  std::cout << "   unimportant weight" << std::endl;
					code = _getch();
					if (code == 224)
					{
						code = _getch();
						if (code == 80) important_weight++;
						if (code == 72) important_weight--;
					}
				} while (code != 13);
				system("cls");
				important = !important_weight;
			}
			try
			{
				T spanning_tree = graph.depth_first_spanning_tree(important);
				spanning_tree.show();
				std::cout << std::endl;
				std::cout << "Weight of tree: " << spanning_tree.get_weight() << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 17) {
			try
			{
				T spanning_tree = graph.minimum_spanning_tree_kruskal();
				spanning_tree.show();
				std::cout << std::endl << "Weight of minimum spanning tree: " << spanning_tree.get_weight() << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 18) {
			try
			{
				T spanning_tree = graph.minimum_spanning_reverse_delete();
				spanning_tree.show();
				std::cout << std::endl << "Weight of minimum spanning tree: " << spanning_tree.get_weight() << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 19) {
			try
			{
				T reverse = graph.build_reverse();
				actions(reverse);
				return;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (choise == 20) {
			if (graph.what_structure() == 0) {
				adjacencyStructure structure(graph);
				return actions(structure);
			}
			else if (graph.what_structure() == 1) {
				adjacencyMatrix matrix(graph);
				return actions(matrix);
			}
		}
		system("pause");
		choise = menu();
	}
}

template <typename T>
void commands(T& graph) {
	std::cout << "\help for reference" << std::endl;
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss;
		ss.str(input);
		std::string part;
		std::vector<std::string> all_commands;
		while (ss >> part) all_commands.push_back(part);
		if (all_commands.size() == 1 && all_commands[0] == "help") {
			std::cout << help_answer << std::endl;
		}
		else if ((all_commands.size() == 4 || all_commands.size() == 5) && all_commands[0] == "add" && all_commands[1] == "redge") {
			std::vector<int>arguments;
			bool correct = true;
			for (size_t i = 2; i < all_commands.size(); i++) {
				if (is_int(all_commands[i])) {
					int to_push = atoi(all_commands[i].c_str());
					arguments.push_back(to_push);
				}
				else {
					correct = false;
					break;
				}
			}
			if (arguments[0] < 0 || arguments[1] < 0) {
				correct = false;
			}
			if (correct) {
				if (arguments.size() == 3) {
					try
					{
						graph.add_redge((size_t)arguments[0], (size_t)arguments[1], arguments[2]);
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else if (arguments.size() == 2) {
					try
					{
						graph.add_redge(size_t(arguments[0]), size_t(arguments[1]));
						std::cout << "Successfully added" << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what()<<std::endl;
					}
				}
				else {
					std::cout << "Unclear command" << std::endl;
				}
			}
			else {
				std::cout << "Incorrect argument. help for reference" << std::endl;
			}
		}
		else  if (all_commands.size() == 2 && all_commands[0] == "add" && all_commands[1] == "node") {
			graph.add_node();
			std::cout << "Successfully added" << std::endl;
		}
		else if (all_commands.size() == 4 && all_commands[0] == "delete" && all_commands[1] == "redge") {
			std::vector<int>arguments;
			bool correct = true;
			for (size_t i = 2; i < all_commands.size(); i++) {
				if (is_int(all_commands[i])) {
					int to_push = atoi(all_commands[i].c_str());
					arguments.push_back(to_push);
				}
				else {
					correct = false;
					break;
				}
			}
			if (arguments[0] < 0 || arguments[1] < 0) {
				correct = false;
			}
			if (correct) {
				try
				{
					graph.delete_redge((size_t)arguments[0], (size_t)arguments[1]);
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;;
				}
			}
			else {
				std::cout << "Incorrect argument. help for reference" << std::endl;
			}
		}
		else if (all_commands.size() == 3 && all_commands[0] == "delete" && all_commands[1] == "node") {
			int argument=-1;
			bool correct = true;
			if (is_int(all_commands[2])) {
				argument = atoi(all_commands[2].c_str());
			}
			if (argument < 0) {
				correct = false;
			}
			if (correct) {
				try
				{
					graph.delete_node(argument);
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else {
				std::cout << "Incorrect argument. help for reference" << std::endl;
			}
		}
		else if (all_commands.size() == 2 && all_commands[0] == "show" && all_commands[1] == "graph") {
			graph.show();
			std::cout << std::endl;
		}
		else if (all_commands.size() == 2 && all_commands[0] == "show" && all_commands[1] == "structure") {
			graph.show_structure();
			std::cout << std::endl;
		}
		else if (all_commands.size() == 1 && all_commands[0] == "weight") {
			std::cout << "Weight: " << graph.get_weight()<<std::endl;
		}
		else if (all_commands.size() == 3 && all_commands[0] == "random") {
			std::vector<int>arguments;
			bool correct = true;
			for (size_t i = 1; i < all_commands.size(); i++) {
				if (is_int(all_commands[i])) {
					int to_push = atoi(all_commands[i].c_str());
					arguments.push_back(to_push);
				}
				else {
					correct = false;
					break;
				}
			}
			if (arguments[0] < 0 || arguments[1] < 0) {
				correct = false;
			}
			if (correct) {
				try
				{
					T new_graph(graph.is_weighted(), graph.is_directed(), arguments[0], arguments[1]);
					graph = new_graph;
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;;
				}
			}
			else {
				std::cout << "Incorrect argument. help for reference" << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "connectivity") {
			std::cout << graph.is_connected_graph() << std::endl;
		}
		else if (all_commands.size() == 1 && all_commands[0] == "components") {
			std::vector<std::vector<size_t>> for_components;
			try
			{
				if (graph.is_directed()) {
					graph.find_strong_components(for_components);
				}
				else {
					graph.find_components(for_components);
				}
				if (for_components.size() > 0) {
					for (size_t i = 0; i < for_components.size(); i++) {
						std::cout << i + 1 << "component: " << std::endl;
						for (size_t j = 0; j < for_components[i].size(); j++) {
							std::cout << " " << for_components[i][j];
						}
						std::cout << std::endl;
					}
				}
				else {
					std::cout << "There isn't any component" << std::endl;
				}
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "acyclicity") {
			if (graph.is_acyclic()) {
				std::cout << "Acyclic";
			}
			else {
				std::cout << "Cyclic";
			}
			std::cout << std::endl;
		}
		else if (all_commands.size() == 2 && all_commands[0] == "check" && all_commands[1] == "tree") {
			if (graph.is_tree()) {
				std::cout << "This is tree";
			}
			else {
				std::cout << "This isn't tree";
			}
			std::cout << std::endl;
		}
		else if ((all_commands.size() == 1 || all_commands.size() == 2 || all_commands.size() == 3) && all_commands[0] == "Dijkstra") {
			if (all_commands.size() == 1) {
				std::vector<std::vector<int>>distances(graph.get_number_of_nodes());
				try
				{
					for (size_t i = 0; i < distances.size(); i++) {
						distances[i] = graph.dijkstra_algorithm(i);
					}
					std::cout << "Nodes";
					std::cout << "\t\t" << 0;
					for (size_t i = 1; i < distances.size(); i++) {
						std::cout << '\t' << i;
					}
					std::cout << std::endl;
					for (size_t i = 0; i < distances.size(); i++) {
						std::cout << "Node " << i << ": ";
						for (size_t j = 0; j < distances.size(); j++) {
							if (distances[i][j] != INT_MAX) {
								std::cout << '\t' << distances[i][j];
							}
							else {
								std::cout << '\t' << "ac";
							}
						}
						std::cout << std::endl;
					}
					std::cout << "ac = in another component" << std::endl;
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2) {
				int argument = -1;
				bool correct = true;
				if (is_int(all_commands[1])) {
					argument = atoi(all_commands[1].c_str());
				}
				if (argument < 0) {
					correct = false;
				}
				if (correct) {
					try
					{
						std::vector<int>distances = graph.dijkstra_algorithm(argument);
						for (size_t i = 0; i < distances.size(); i++) {
							if (distances[i] != INT_MAX) {
								std::cout << "Node " << i << ": " << distances[i] << std::endl;
							}
							else {
								std::cout << "Node " << i << " in another component" << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3) {
				std::vector<int>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					if (is_int(all_commands[i])) {
						int to_push = atoi(all_commands[i].c_str());
						arguments.push_back(to_push);
					}
					else {
						correct = false;
						break;
					}
				}
				if (arguments[0] < 0 || arguments[1] < 0) {
					correct = false;
				}
				if (correct) {
					try
					{
						std::vector<int>distances = graph.dijkstra_algorithm(arguments[0]);
						if (arguments[1] < (int)distances.size()) {
							if (distances[arguments[1]] == INT_MAX) {
								std::cout << "Another component" << std::endl;
							}
							else {
								std::cout << distances[arguments[1]] << std::endl;
							}

						}
						else {
							std::cout << "Incorrect argument. help for reference" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
		}
		else if ((all_commands.size() == 1 || all_commands.size() == 2 || all_commands.size() == 3) && all_commands[0] == "Floyd") {
			if (all_commands.size() == 1) {
				try
				{
					std::vector<std::vector<int>>distances = graph.floyd_algorithm();
					std::cout << "Nodes";
					std::cout << "\t\t" << 0;
					for (size_t i = 1; i < distances.size(); i++) {
						std::cout << '\t' << i;
					}
					std::cout << std::endl;
					for (size_t i = 0; i < distances.size(); i++) {
						std::cout << "Node " << i << ": ";
						for (size_t j = 0; j < distances.size(); j++) {
							if (distances[i][j] != INT_MAX) {
								std::cout << '\t' << distances[i][j];
							}
							else {
								std::cout << '\t' << "ac";
							}
						}
						std::cout << std::endl;
					}
					std::cout << "ac = in another component" << std::endl;
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2) {
				int argument = -1;
				bool correct = true;
				if (is_int(all_commands[1])) {
					argument = atoi(all_commands[1].c_str());
				}
				if (argument < 0) {
					correct = false;
				}
				if (correct) {
					try
					{
						std::vector<std::vector<int>>distances = graph.floyd_algorithm();
						if (argument < (int)distances.size()) {
							for (size_t i = 0; i < distances[argument].size(); i++) {
								if (distances[argument][i] != INT_MAX) {
									std::cout << "Node " << i << ": " << distances[argument][i] << std::endl;
								}
								else {
									std::cout << "Node " << i << " in another component" << std::endl;
								}
							}
						}
						else {
							std::cout << "Incorrect argument. help for reference" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 3) {
				std::vector<int>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					if (is_int(all_commands[i])) {
						int to_push = atoi(all_commands[i].c_str());
						arguments.push_back(to_push);
					}
					else {
						correct = false;
						break;
					}
				}
				if (arguments[0] < 0 || arguments[1] < 0) {
					correct = false;
				}
				if (correct) {
					try
					{
						std::vector<std::vector<int>>distances = graph.floyd_algorithm();
						if (arguments[1] < (int)distances.size() && arguments[0] < (int)distances.size()) {
							if (distances[arguments[0]][arguments[1]] == INT_MAX) {
								std::cout << "Another component" << std::endl;
							}
							else {
								std::cout << distances[arguments[0]][arguments[1]] << std::endl;
							}
						}
						else {
							std::cout << "Incorrect argument. help for reference" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
		}
		else if ((all_commands.size() == 2 || all_commands.size() == 3 || all_commands.size() == 4) && all_commands[0] == "Bellman" && all_commands[1] == "Ford") {
			if (all_commands.size() == 2) {
				std::vector<std::vector<int>>distances(graph.get_number_of_nodes());
				try
				{
					for (size_t i = 0; i < distances.size(); i++) {
						distances[i] = graph.bellman_ford_algorithm(i);
					}
					std::cout << "Nodes";
					std::cout << "\t\t" << 0;
					for (size_t i = 1; i < distances.size(); i++) {
						std::cout << '\t' << i;
					}
					std::cout << std::endl;
					for (size_t i = 0; i < distances.size(); i++) {
						std::cout << "Node " << i << ": ";
						for (size_t j = 0; j < distances.size(); j++) {
							if (distances[i][j] != INT_MAX) {
								std::cout << '\t' << distances[i][j];
							}
							else {
								std::cout << '\t' << "ac";
							}
						}
						std::cout << std::endl;
					}
					std::cout << "ac = in another component" << std::endl;
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 3) {
				int argument = -1;
				bool correct = true;
				if (is_int(all_commands[2])) {
					argument = atoi(all_commands[2].c_str());
				}
				if (argument < 0) {
					correct = false;
				}
				if (correct) {
					try
					{
						std::vector<int>distances = graph.bellman_ford_algorithm(argument);
						for (size_t i = 0; i < distances.size(); i++) {
							if (distances[i] != INT_MAX) {
								std::cout << "Node " << i << ": " << distances[i] << std::endl;
							}
							else {
								std::cout << "Node " << i << " in another component" << std::endl;
							}
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4) {
				std::vector<int>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					if (is_int(all_commands[i])) {
						int to_push = atoi(all_commands[i].c_str());
						arguments.push_back(to_push);
					}
					else {
						correct = false;
						break;
					}
				}
				if (arguments[0] < 0 || arguments[1] < 0) {
					correct = false;
				}
				if (correct) {
					try
					{
						std::vector<int>distances = graph.bellman_ford_algorithm(arguments[0]);
						if (arguments[1] < (int)distances.size()) {
							if (distances[arguments[1]] == INT_MAX) {
								std::cout << "Another component" << std::endl;
							}
							else {
								std::cout << distances[arguments[1]] << std::endl;
							}
						}
						else {
							std::cout << "Incorrect argument.help for reference" << std::endl;
						}
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
		}
		else if ((all_commands.size() == 3 || all_commands.size() == 4 || all_commands.size() == 5) && all_commands[0] == "depth" && all_commands[1] == "first") {
			//topological and spanning tree here too
			if (all_commands.size() == 3) {
				int argument=-1;
				bool correct = true;
				if (is_int(all_commands[2])) {
					argument = atoi(all_commands[2].c_str());
				}
				else {
					correct = false;
				}
				if (argument != 0 && argument !=1) {
					correct = false;
				}
				if (correct) {
					std::vector<size_t>order;
					try
					{
						order = graph.depth_first(argument);
						for (size_t i = 0; i < order.size(); i++) {
							std::cout << order[i] << " ";
						}
						std::cout << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[2] == "topological" && all_commands[3] == "sorting") {
				std::vector<size_t>order;
				try
				{
					order = graph.topological_sorting_depth_first();
					for (size_t i = 0; i < order.size(); i++) {
						std::cout << order[i] << " ";
					}
					std::cout << std::endl;
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[2] == "spanning" && all_commands[3] == "tree") {
				int argument = -1;
				bool correct = true;
				if (is_int(all_commands[4])) {
					argument = atoi(all_commands[4].c_str());
				}
				else {
					correct = false;
				}
				if (argument != 0 && argument != 1) {
					correct = false;
				}
				if (correct) {
					try
					{
						T spanning_tree = graph.depth_first_spanning_tree(argument);
						spanning_tree.show();
						std::cout << std::endl;
						std::cout << "Weight of tree: " << spanning_tree.get_weight() << std::endl;
					}
					catch (const std::exception& ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					std::cout << "Incorrect argument. help for reference" << std::endl;
				}
			}
			else {
				std::cout << "Unclear command. help for reference" << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "Kahn") {
			std::vector<size_t>order;
			try
			{
				order = graph.topological_sorting_kahn();
				for (size_t i = 0; i < order.size(); i++) {
					std::cout << order[i] << " ";
				}
				std::cout << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "Kruskal") {
			try
			{
				T spanning_tree = graph.minimum_spanning_tree_kruskal();
				spanning_tree.show();
				std::cout << std::endl << "Weight of minimum spanning tree: " << spanning_tree.get_weight() << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (all_commands.size() == 2 && all_commands[0] == "reverse" && all_commands[1] == "delete") {
			try
			{
				T spanning_tree = graph.minimum_spanning_reverse_delete();
				spanning_tree.show();
				std::cout << std::endl << "Weight of minimum spanning tree: " << spanning_tree.get_weight() << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "reverse") {
			try
			{
				T reverse = graph.build_reverse();
				return commands(reverse);
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "another") {
			if (graph.what_structure() == 0) {
				adjacencyStructure structure(graph);
				return commands(structure);
			}
			else if (graph.what_structure() == 1) {
				adjacencyMatrix matrix(graph);
				return commands(matrix);;
			}
		}
		else if (all_commands.size() == 1 && all_commands[0] == "end") {
			return;
		}
		else {
			std::cout << "Unclear command. help for reference" << std::endl;
		}
	}
}