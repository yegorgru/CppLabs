#include "Header.h"




template <class T>
void binaryTree<T>::add(T value, binaryNode<T>* node)
{
	if (value < node->item) {
		if (node->left) {
			add(value, node->left);
		}
		else {
			node->left = new binaryNode<T>(value);
		}
	}
	else {
		if (node->right) {
			add(value, node->right);
		}
		else {
			node->right = new binaryNode<T>(value);
		}
	}
}

template <class T>
void binaryTree<T>::delete_subtree(binaryNode<T>*& node)
{
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

template <class T>
void binaryTree<T>::show(binaryNode<T>* node)
{
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

template <class T>
void binaryTree<T>::show_in_order(binaryNode<T>* node)
{
	if (node) {
		if (node->left) {
			show_in_order(node->left);
		}
		std::cout << node->item;
		std::cout << ' ';
		if (node->right) {
			show_in_order(node->right);
		}
	}
}









template <class T>
void Tree<T>::delete_subtree(Node*& node) {
	if (node) {
		for (size_t i = 0; i < node->children.size(); i++) {
			delete_subtree(node->children[i]);
		}
		delete node;
		node = nullptr;
	}
}

template <class T>
void Tree<T>::add(T value, size_t min, size_t max, Node* node)
{
	Node* item = new Node(value);
	if (node->children.size() < min) {
		item->parent = node;
		node->children.push_back(item);
		return;
	}
	else if (node->children.size() > 0) {
		size_t minimal = node->children[0]->children.size();
		size_t min_number = 0;
		for (size_t i = 1; i < node->children.size(); i++) {
			if (node->children[i]->children.size() < minimal) {
				minimal = node->children[i]->children.size();
				min_number = i;
			}
		}
		if (node->children[min_number]->children.size() <= max) {
			delete item;
			this->add(value, min, max, node->children[min_number]);
		}
	}
	else if (node->children.size() <= max) {
		item->parent = node;
		node->children.push_back(item);
	}
	else if (node->children.size() > 0) {
		size_t minimal_subtree;
		size_t counter=0;
		this->count_posterity(node->children[0], counter);
		minimal_subtree = counter;
		size_t what_child = 0;
		for (size_t i = 1; i < node->children.size(); i++) {
			size_t count = 0;
			this->count_posterity(node->children[i], count);
			if (count < minimal_subtree) {
				minimal_subtree = count;
				what_child = i;
			}
		}
		delete item;
		this->add(value, min, max, node->children[what_child]);
	}
	else {
		item->parent = node;
		node->children.push_back(item);
		return;
	}
}


template <class T>
void Tree<T>::show(Node* node)
{
	std::cout << node->item;
	if (node->children.size() > 0) {
		std::cout << '(';
		for (size_t i = 0; i < node->children.size(); i++) {
			show(node->children[i]);
			if (i != node->children.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << ')';
	}
}


template<class T>
void Tree<T>::interactive_browsing(Node* node)
{
	int choise = 0;
	int code;
	bool isparent = false;
	int number = 1;
	if (node->parent) {
		number++;
		isparent = true;
	}
	if (node->children.size() > 0) {
		number += node->children.size();
	}
	do {
		system("cls");
		std::cout << "This item: " << node->item << std::endl;
		choise = (choise + number) % number;
		if (isparent) {
			if(choise==0) std::cout<<"-> see parent" << std::endl;
			else std::cout << "   see parent" << std::endl;
			for (int i = 1; i < number - 1; i++) {
				if (choise == i) std::cout << "-> see " << i - 1 << " child" << std::endl;
				else std::cout << "   see " << i - 1 << " child" << std::endl;
			}
		}
		else {
			for (int i = 0; i < number - 1; i++) {
				if (choise == i) std::cout << "-> see " << i << " child" << std::endl;
				else std::cout << "   see " << i << " child" << std::endl;
			}
		}
		if (choise == number - 1)  std::cout << "-> end" << std::endl;
		else  std::cout << "   end" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}

	} while (code != 13);
	system("cls");
	if (choise == number - 1) {
		return;
	}
	else if (isparent) {
		if (choise == 0) {
			interactive_browsing(node->parent);
		}
		else {
			interactive_browsing(node->children[choise - 1]);
		}
	}
	else {
		interactive_browsing(node->children[choise]);
	}
}

template<class T>
bool Tree<T>::remove(Node*& node,T some)
{
	bool to_return = false;
	if (node) {
		if (node->children.size() > 0) {
			for (size_t i = 0; i < node->children.size(); i++) {
				if (node->children[i]->item == some) {
					size_t counter = 0;
					count_posterity(node->children[i], counter);
					this->length -= counter;
					delete_subtree(node->children[i]);
					node->children.erase(node->children.begin() + i);
					to_return = true;
				}
			}
			if (!to_return) {
				for (size_t i = 0; i < node->children.size(); i++) {
					if (remove(node->children[i], some) == true) {
						to_return = true;
					}
				}
			}
		}
	}
	else {
		throw TreeErr("Incorrect node");
	}
	return to_return;
}

template <class T>
T& Tree<T>::operator[](size_t index)
{
	if (index == 0) {
		if (this->root) {
			return root->item;
		}
		else {
			throw TreeErr("Incorrect index");
		}
	}
	else {
		size_t current = 0;
		Node* to_return = pre_order(root, index, current);
		if (to_return == nullptr) {
			throw TreeErr("Incorrect index");
		}
		else {
			return to_return->item;
		}
	}
}


template <class T>
std::deque<size_t> Tree<T>::get_way(size_t index)
{
	if (index >= length) {
		throw TreeErr("Incorrect index");
		return {};
	}
	std::deque<size_t> way;
	size_t current = 0;
	Node* to_return = pre_order(root, index, current);
	part_way(root, to_return, way);
	return way;
}


template <class T>
bool Tree<T>::part_way(Node* node, Node* to_return, std::deque<size_t>& way)
{
	for (size_t i = 0; i < node->children.size(); i++) {
		if (to_return == node->children[i]) {
			way.push_back(i);
			return true;
		}
	}
	for (size_t i = 0; i < node->children.size(); i++) {
		if (part_way(node->children[i], to_return, way)) {
			way.push_front(i);
			return true;
		}
	}
	return false;
}

template <class T>
T& Tree<T>::get_element(std::deque<size_t> way)
{
	if (way.size() == 0) {
		return root->item;
	}
	else {
		try
		{
			return get_element(root, way);
		}
		catch (const std::exception&)
		{
			throw TreeErr("Incorrect way");
		}
	}
}


template <class T>
T& Tree<T>::get_element(Node* node, std::deque<size_t> way)
{
	if (node) {
		if (way.size() == 1) {
			if (way[0] < node->children.size()) {
				return node->children[way[0]]->item;
			}
			else {
				throw TreeErr("Incorrect way");
			}
		}
		else {
			if (node->children.size() > way[0]) {
				size_t current = way[0];
				way.pop_front();
				return get_element(node->children[current], way);
			}
			else {
				throw TreeErr("Incorrect way");
			}
		}
	}
	else {
		throw TreeErr("Incorrect node");
	}
}

template<class T>
void Tree<T>::count_posterity(Node* node, size_t& count)
{
	if (node) {
		count++;
		for (size_t i = 0; i < node->children.size(); i++) {
			count_posterity(node->children[i], count);
		}
	}
}


void expTree::show(Node* node)
{
	if (node) {
		if (node->left && node->right) {
			std::cout << '(';
			show(node->left);
			if (node->name == "+" && node->right && node->right->name == "" && node->right->value < 0) {
				std::cout << node->right->value;
				std::cout << ')';
				return;
			}
			if (node->name == "-" && node->right && node->right->name == "" && node->right->value < 0) {
				std::cout << "+"<<abs(node->right->value);
				std::cout << ')';
				return;
			}
			std::cout << node->name;
			show(node->right);
			std::cout << ')';
		}
		else if (node->name != "") {
			std::cout << node->name;
		}
		else {
			std::cout << node->value;
		}
	}
}

void expTree::show_min(Node* node, int priority)
{
	if (node) {
		int pr = 0;
		if (node->name == "+" || node->name == "-") {
			pr = 1;
		}
		else if (node->name == "*" || node->name == "/") {
			pr = 2;
		}
		else if (node->name == "^") {
			pr = 3;
		}
		if (node->left && node->right && pr<priority) {
			std::cout << '(';
			show_min(node->left,pr);
			if (node->name == "+" && node->right && node->right->name == "" && node->right->value < 0) {
				std::cout << node->right->value;
				std::cout << ')';
				return;
			}
			if (node->name == "-" && node->right && node->right->name == "" && node->right->value < 0) {
				std::cout << "+" << abs(node->right->value);
				std::cout << ')';
				return;
			}
			std::cout << node->name;
			show_min(node->right,pr);
			std::cout << ')';
		}
		else if (node->left && node->right) {
			show_min(node->left,pr);
			if (node->name == "+" && node->right && node->right->name == "" && node->right->value < 0) {
				std::cout << node->right->value;
				return;
			}
			if (node->name == "-" && node->right && node->right->name == "" && node->right->value < 0) {
				std::cout << "+" << abs(node->right->value);
				return;
			}
			std::cout << node->name;
			show_min(node->right,pr);
		}
		else if (node->name != "") {
			std::cout << node->name;
		}
		else {
			std::cout << node->value;
		}
	}
}

void expTree::fill_values(Node* node, std::deque<double>& values,std::deque<std::string>& variables)
{
	if (node) {
		fill_values(node->left, values,variables);
		fill_values(node->right, values,variables);
		for (size_t i = 0; i < variables.size(); i++) {
			if (node->name == variables[i]) {
				node->name = "";
				node->value = values[i];
			}
		}
	}
}

void expTree::fill(Node* node,std::deque<std::string>&variables)
{
	if (node) {
		fill(node->left,variables);
		if (node->name == "") {
			system("cls");
			std::cout << "Enter next item (marked x)" << std::endl;
			node->name = 'x';
			this->show();
			std::cout << std::endl;
			Sleep(5000);
			int choise = 0;
			int code;
			do {
				system("cls");
				choise = (choise + 2) % 2;
				if (choise == 0) std::cout << "-> variable" << std::endl;
				else  std::cout << "   variable" << std::endl;
				if (choise == 1) std::cout << "-> number" << std::endl;
				else  std::cout << "   number" << std::endl;
				code = _getch();
				if (code == 224)
				{
					code = _getch();
					if (code == 80) choise++;
					if (code == 72) choise--;
				}

			} while (code != 13);
			system("cls");
			if (choise == 0) {
				bool correct = false;
				while (!correct) {
					std::cout << "Enter name of variable" << std::endl;
					std::getline(std::cin, node->name);
					if (node->name != "+" && node->name != "-" && node->name != "*" && node->name != "/" && node->name != "^") {
						correct = true;
					}
					else {
						std::cout << "You can't name variable + - * / or ^" << std::endl;
						Sleep(3000);
						system("cls");
					}
				}
				bool already_was = false;
				for (size_t i = 0; i < variables.size(); i++) {
					if (node->name == variables[i]) {
						already_was = true;
						break;
					}
				}
				if (!already_was) {
					variables.push_back(node->name);
				}
			}
			else {
				bool correct = false;
				char ch;
				while (!correct) {
					std::cout << "Enter number" << std::endl;
					std::cin >> node->value;
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
				node->name = "";
			}
		}
		fill(node->right,variables);
	}
}

void expTree::form_tree(std::string main_string)
{
	expTree tree;
	if (main_string == "") {
		throw TreeErr("Error empty string");
		return;
	}
	else {
		root=tree.form_subtree(root, main_string, 0, main_string.length());
	}
}



std::string form_string()
{
	std::string to_return="";

	form_signs(to_return);
	if (to_return != "") {
		add_brackets(to_return, 0, to_return.length() - 1);
	}
	
	return to_return;
}

void form_signs(std::string& to_return) {
	int choise = 0;
	int code;
	while (choise != 5) {
		do {
			system("cls");
			std::cout << "Enter signs of your expression" << std::endl << std::endl;
			std::cout << to_return << std::endl<<std::endl;
			choise = (choise + 6) % 6;
			if (choise == 0) std::cout << "-> +" << std::endl;
			else  std::cout << "   +" << std::endl;
			if (choise == 1) std::cout << "-> -" << std::endl;
			else  std::cout << "   -" << std::endl;
			if (choise == 2) std::cout << "-> *" << std::endl;
			else  std::cout << "   *" << std::endl;
			if (choise == 3) std::cout << "-> /" << std::endl;
			else  std::cout << "   /" << std::endl;
			if (choise == 4) std::cout << "-> ^" << std::endl;
			else  std::cout << "   ^" << std::endl;
			if (choise == 5) std::cout << "-> break" << std::endl;
			else  std::cout << "   break" << std::endl;
			code = _getch();
			if (code == 224)
			{
				code = _getch();
				if (code == 80) choise++;
				if (code == 72) choise--;
			}

		} while (code != 13);
		if (choise == 0) {
			to_return += "+";
		}
		else if (choise == 1) {
			to_return += "-";
		}
		else if (choise == 2) {
			to_return += "*";
		}
		else if (choise == 3) {
			to_return += "/";
		}
		else if (choise == 4) {
			to_return += "^";
		}
	}
}

void add_brackets(std::string& to_return,size_t begin,size_t end) {
	size_t size = end - begin + 1;
	int choise = 0;
	int code;
	do {
		system("cls");
		std::cout << "If you want, you can add brackets" << std::endl << std::endl;
		std::cout << to_return << std::endl << std::endl;
		choise = (choise + size+1) % (size+1);
		for (size_t i = begin; i < end+1; i++) {
			if (begin+choise == i) std::cout << "-> insert ( before " << i+1 << " sign" << std::endl;
			else std::cout << "   insert ( before " << i+1 << " sign" << std::endl;
		}
		if (choise == size) std::cout << "-> break" << std::endl;
		else  std::cout << "   break" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}
	} while (code != 13);
	if ((size_t)choise < size) {
		int choise2 = 0;
		if (choise == size-1) {
			choise += begin;
			choise2 = choise;
		}
		else {
			choise += begin;
			code = -1;
			do {
				system("cls");
				std::cout << "Add ) after :" << std::endl << std::endl;
				std::cout << to_return << std::endl << std::endl;
				choise2 = (choise2 + end - choise+1) % (end - choise+1);
				for (size_t i = choise; i < end + 1; i++) {
					if (choise2 + choise == i) std::cout << "-> insert ) after " << i + 1 << " sign" << std::endl;
					else std::cout << "   insert ) after " << i + 1 << " sign" << std::endl;
				}
				code = _getch();
				if (code == 224)
				{
					code = _getch();
					if (code == 80) choise2++;
					if (code == 72) choise2--;
				}
			} while (code != 13);
			choise2 += choise;
		}
		if (!(choise == begin && choise2 == end)) {
			int counter = -1;
			std::string help = "";
			for (size_t i = 0; i < to_return.length(); i++) {
				if (to_return[i] == '+' || to_return[i] == '-' || to_return[i] == '*' || to_return[i] == '/' || to_return[i] == '^') {
					counter++;
				}
				if (counter == choise && counter == choise2) {
					help += "(";
					help += to_return[i];
					help += ")";
					counter++;
				}
				else if (counter == choise) {
					help += "(";
					help += to_return[i];
				}
				else if (counter == choise2) {
					help += to_return[i];
					help += ")";
					counter++;
				}
				else {
					help += to_return[i];
				}
			}
			to_return = help;
			if (choise2 != choise) {
				add_brackets(to_return, choise, choise2);
			}
			if (choise - begin > 1) {
				add_brackets(to_return, begin, choise - 1);
			}
			if (end - choise2 > 1) {
				add_brackets(to_return, choise2 + 1, end);
			}
		}
		else {
			add_brackets(to_return, begin, end);
		}
	}
	else {
		return;
	}
}

void expTree::delete_subtree(Node*& node)
{
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



double expTree::calculation(Node* node)
{
	if (node) {
		if (node->name == "") {
			return node->value;
		}
		else if (node->name == "+") {
			return calculation(node->left) + calculation(node->right);
		}
		else if (node->name == "-") {
			return calculation(node->left) - calculation(node->right);
		}
		else if (node->name == "*") {
			return calculation(node->left) * calculation(node->right);
		}
		else if (node->name == "/") {
			double r = calculation(node->right);
			if (r != 0.0) {
				return calculation(node->left) / r;
			}
			else {
				throw TreeErr("Division by 0");
				return 0.0;
			}
		}
		else if (node->name == "^") {
			return pow(calculation(node->left), calculation(node->right));
		}
		return 0.0;
	}
	throw TreeErr("node doesn't exist");
}

void expTree::error_checking(Node* node)
{
	if (node) {
		if (node->left && (node->left->name == "+" || node->left->name == "-" || node->left->name == "*" || node->left->name == "/" || node->left->name == "^")) {
			try
			{
				error_checking(node->left);
			}
			catch (const std::exception& ex)
			{
				throw ex;
				return;
			}
		}
		if (node->right && (node->right->name == "+" || node->right->name == "-" || node->right->name == "*" || node->right->name == "/" || node->right->name == "^")) {
			try
			{
				error_checking(node->right);
			}
			catch (const std::exception& ex)
			{
				throw ex;
				return;
			}
		}
		if (node->left && node->right) {
			if (node->name == "/" && node->right->name == "" && node->right->value == 0) {
				throw TreeErr("Division by 0");
			}
		}
	}
}

int expTree::subtree_height(Node* node)
{
	if (node) {
		int left=0;
		int right=0;
		if (node->left) {
			left = subtree_height(node->left);
		}
		if (node->right) {
			left = subtree_height(node->right);
		}
		if (right >= left) {
			return right + 1;
		}
		else {
			return left + 1;
		}
	}
	else {
		return 0;
	}
}

void expTree::logic_simplification(Node*& node)
{
	if (node) {
		logic_simplification(node->left);
		logic_simplification(node->right);
		int left_height = subtree_height(node->left);
		int right_height = subtree_height(node->right);
		if (left_height < right_height) {
			Node* help = node->left;
			node->left = node->right;
			node->right = help;
		}
		else if (left_height == 1 && right_height == 1) {
			if (node->left->name == "" && !(node->right->name == "" || node->right->name == "+" || node->right->name == "-" || node->right->name == "*" || node->right->name == "/" || node->right->name == "^")) {
				Node* help = node->left;
				node->left = node->right;
				node->right = help;
			}
		}
		logic_simplification(node->left);
		logic_simplification(node->right);
		if (node->name == "+"){
			expTree left(node->left);
			expTree right(node->right);
			if(node->left->right && node->left->name=="-"){
				expTree leftright(node->left->right);
				if (leftright == right) {
					Node* to_delete1 = node->left->right;
					Node* to_delete2 = node->right;
					node = node->left->left;
					delete to_delete1;
					delete to_delete2;
				}
			}
			else if (left.root->name == "*") {
				if (left.root->right->name == "") {
					expTree leftleft(node->left->left);
					if (leftleft == right) {
						Node* for_delete = node;
						node = node->left;
						node->right->value++;
						delete for_delete;
					}
				}
			}
		}
		if (node->name == "-") {
			expTree left(node->left);
			expTree right(node->right);
			if (left == right) {
				delete_subtree(node->left);
				delete_subtree(node->right);
				node->name = "";
				node->value = 0;
			}
			else if (left.root->name == "+") {
				expTree leftleft(node->left->left);
				expTree leftright(node->left->right);
				if (leftleft == right) {
					Node* to_delete1 = node->left->left;
					Node* to_delete2 = node->right;
					node = node->left->right;
					delete to_delete1;
					delete to_delete2;
				}
				else if (leftright == right) {
					Node* to_delete1 = node->left->right;
					Node* to_delete2 = node->right;
					node = node->left->left;
					delete to_delete1;
					delete to_delete2;
				}
			}
			else if (left.root->name == "*") {
				if (left.root->right->name == "") {
					expTree leftleft(node->left->left);
					if (leftleft == right) {
						Node* for_delete = node;
						node = node->left;
						node->right->value--;
						delete for_delete;
					}
				}
			}
		}
		if (node->name == "/") {
			expTree left(node->left);
			expTree right(node->right);
			if (node->right->name == "" && node->right->value == 0) {
				throw TreeErr("Division by 0");
			}
			else if (left == right) {
				delete_subtree(node->left);
				delete_subtree(node->right);
				node->name = "";
				node->value = 1;
			}
			else if (node->right->name == "" && node->right->value == 1) {
				Node* for_delete = node;
				node = node->left;
				delete for_delete;
			}
			else if (left.root->name == "*") {
				expTree leftleft(node->left->left);
				expTree leftright(node->left->right);
				if (leftleft == right) {
					Node* to_delete1 = node->left->left;
					Node* to_delete2 = node->right;
					node = node->left->right;
					delete to_delete1;
					delete to_delete2;
				}
				else if (leftright == right) {
					Node* to_delete1 = node->left->right;
					Node* to_delete2 = node->right;
					node = node->left->left;
					delete to_delete1;
					delete to_delete2;
				}
			}
			else if (left.root->name == "^") {
				if (left.root->right->name == "") {
					expTree leftleft(node->left->left);
					if (leftleft == right) {
						Node* for_delete = node;
						node = node->left;
						node->right->value--;
						delete for_delete;
						logic_simplification(node);
					}
				}
			}
		}
		if (node->name == "*") {
			expTree left(node->left);
			expTree right(node->right);
			if (node->left->right && node->left->name == "/") {
				expTree leftright(node->left->right);
				if (leftright == right) {
					Node* to_delete1 = node->left->right;
					Node* to_delete2 = node->right;
					node = node->left->left;
					delete to_delete1;
					delete to_delete2;
				}
			}
			if (node->left->name == "" && node->left->value == 0 || node->right->name == "" && node->right->value == 0) {
				delete_subtree(node->left);
				delete_subtree(node->right);
				node->name = "";
				node->value = 0;
			}
			else if (node->left->name == "" && node->left->value == 1) {
				Node* for_delete = node;
				node = node->right;
				delete for_delete;
			}
			else if (node->right->name == "" && node->right->value == 1) {
				Node* for_delete = node;
				node = node->left;
				delete for_delete;
			}
			else if (left.root->name == "^") {
				if (left.root->right->name == "") {
					expTree leftleft(node->left->left);
					if (leftleft == right) {
						Node* for_delete = node;
						node = node->left;
						node->right->value++;
						delete for_delete;
					}
				}
			}
		}
		if (node->name == "^") {
			if (node->right->name == "" && node->right->value==0) {
				delete_subtree(node);
				node = new Node("", 1);
			}
			else if (node->right->name == "" && node->right->value == 1) {
				Node* for_delete = node;
				delete node->right;
				node = node->left;
				delete for_delete;
			}
		}
	}
}

void expTree::last_simplification(Node* node)
{
	if (node) {
		last_simplification(node->left);
		last_simplification(node->right);
		if (node->name == "*") {
			expTree left(node->left);
			expTree right(node->right);
			if (left == right) {
				delete_subtree(node->right->left);
				delete_subtree(node->right->right);
				node->name = "^";
				node->right->name = "";
				node->right->value = 2;
			}
		}
	}
}


void expTree::calc_simplification(Node* node)
{
	if (node) {
		if (node->left&&(node->left->name == "+" || node->left->name == "-" || node->left->name == "*" || node->left->name == "/" || node->left->name == "^")) {
			try
			{
				calc_simplification(node->left);
			}
			catch (const std::exception& ex)
			{
				throw ex;
			}
		}
		if (node->right&&(node->right->name == "+" || node->right->name == "-" || node->right->name == "*" || node->right->name == "/" || node->right->name == "^")) {
			try
			{
				calc_simplification(node->right);
			}
			catch (const std::exception& ex)
			{
				throw ex;
			}
		}
		double l;
		double r;
		if (node->left && node->right) {
			if (node->left->name == "" && node->right->name == "") {
				l = node->left->value;
				delete node->left;
				node->left = nullptr;
				r = node->right->value;
				delete node->right;
				node->right = nullptr;
				if (node->name == "+") {
					node->name = "";
					node->value = l + r;
				}
				else if (node->name == "-") {
					node->name = "";
					node->value = l - r;
				}
				else if (node->name == "*") {
					node->name = "";
					node->value = l * r;
				}
				else if (node->name == "/") {
					node->name = "";
					if (r == 0) {
						throw TreeErr("Division by 0");
						return;
					}
					node->value = l / r;
				}
				else if (node->name == "^") {
					node->name = "";
					node->value = pow(l, r);
				}
			}
		}
	}
}

void expTree::second_calc_simplification(Node* node)
{
	if (node) {
		second_calc_simplification(node->left);
		second_calc_simplification(node->right);
		int left_height = subtree_height(node->left);
		int right_height = subtree_height(node->right);
		if (left_height < right_height) {
			Node* help = node->left;
			node->left = node->right;
			node->right = help;
		}
		else if (left_height==1 && right_height==1 ) {
			if (node->left->name == "" && !(node->right->name == "" || node->right->name == "+" || node->right->name == "-" || node->right->name == "*" || node->right->name == "/" || node->right->name == "^")) {
				Node* help = node->left;
				node->left = node->right;
				node->right = help;
			}
		}
		if (node->name == "*" && node->right->name == "") {
			if (node->left->name == "*" && node->left->right->name == "") {
				node->right->value *= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
			if (node->left->name == "/" && node->left->right->name == "") {
				node->right->value /= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
		}
		if (node->name=="/" && node->right->name == "") {
			if (node->left->name == "*" && node->left->right->name == "") {
				node->right->value /= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
			if (node->left->name == "/" && node->left->right->name == "") {
				node->right->value *= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
		}
		if (node->name == "+" && node->right->name == "") {
			if (node->left->name == "+" && node->left->right->name == "") {
				node->right->value += node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
			if (node->left->name == "-" && node->left->right->name == "") {
				node->right->value -= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
		}
		if (node->name == "-" && node->right->name == "") {
			if (node->left->name == "+" && node->left->right->name == "") {
				node->right->value -= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
			if (node->left->name == "-" && node->left->right->name == "") {
				node->right->value += node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
		}
		if (node->name == "^" && node->right->name == "") {
			if (node->left->name == "^" && node->left->right->name == "") {
				node->right->value *= node->left->right->value;
				Node* help = node->left->left;
				delete node->left;
				node->left = help;
			}
		}
	}
}

void main_launch()
{
	int mode = main_menu();
	if (mode == 0) {
		interactive_mode();
		main_launch();
	}
	else if (mode == 1) {
		demomode();
		main_launch();
	}
	else {
		std::cout << "goodby!" << std::endl;
		return;
	}
}

int main_menu()
{
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 3) % 3;
		if (choise == 0) std::cout << "-> interactive mode" << std::endl;
		else  std::cout << "   interactive mode" << std::endl;
		if (choise == 1) std::cout << "-> demomode" << std::endl;
		else  std::cout << "   demomode" << std::endl;
		if (choise == 2) std::cout << "-> exit" << std::endl;
		else  std::cout << "   exit" << std::endl;
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

void interactive_mode()
{
	int choise = interactive_menu();
	while (choise != 3) {
		if (choise == 0) {
			ordinary();
			choise = interactive_menu();
		}
		else if (choise == 1) {
			binary();
			choise = interactive_menu();
		}
		else if (choise == 2) {
			expression();
			choise = interactive_menu();
		}
	}

}

void demomode()
{
	std::cout << "-> ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(2000);
	system("cls");

	Tree<int>tree;

	show_menu(4);
	tree.show();
	Sleep(1000);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	tree.add(0, 2, 3);

	show_menu(4);
	tree.show();
	Sleep(2500);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	tree.add(1, 2, 3);

	show_menu(4);
	tree.show();
	Sleep(2500);
	system("cls");

	show_menu(1);
	std::cout << "Enter number to add" << std::endl;
	Sleep(300);
	std::cout << 3;
	Sleep(300);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "Enter way" << std::endl;
	std::cout << "-> type" << std::endl;
	std::cout << "   empty way" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter way" << std::endl;
	std::cout << "   type" << std::endl;
	std::cout << "-> empty way" << std::endl;
	Sleep(1500);
	system("cls");
	std::deque<size_t>my_way;
	tree.add(30, my_way);

	show_menu(4);
	tree.show();
	Sleep(3000);
	system("cls");

	show_menu(1);
	std::cout << "Enter number to add" << std::endl;
	Sleep(300);
	std::cout << 3;
	Sleep(300);
	std::cout << 1;
	Sleep(1500);
	system("cls");
	std::cout << "Enter way" << std::endl;
	std::cout << "-> type" << std::endl;
	std::cout << "   empty way" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter next step" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "-> continue typing" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   continue typing" << std::endl;
	std::cout << "-> break" << std::endl;
	Sleep(700);
	system("cls");
	my_way = { 0 };
	tree.add(31, my_way);

	show_menu(4);
	tree.show();
	Sleep(3000);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	system("cls");
	tree.add(2, 3, 4);

	show_menu(4);
	tree.show();
	Sleep(3000);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	tree.add(3, 0, 3);

	show_menu(4);
	tree.show();
	Sleep(3500);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	tree.add(4, 3, 3);

	show_menu(4);
	tree.show();
	Sleep(3500);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(1500);
	system("cls");
	tree.add(5, 2, 5);

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 6;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	system("cls");
	tree.add(6, 3, 4);

	show_menu(4);
	tree.show();
	Sleep(4000);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 7;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(1500);
	system("cls");
	tree.add(7, 0, 1);

	show_menu(4);
	tree.show();
	Sleep(4000);
	system("cls");

	show_menu(10);
	std::cout << tree.size();
	Sleep(2000);
	system("cls");

	show_menu(2);
	std::cout << "Enter index" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1000);
	system("cls");
	std::deque<size_t>way = tree.get_way(0);
	if (way.size() == 0) {
		std::cout << "This is root" << std::endl;
	}
	else {
		for (size_t i = 0; i < way.size(); i++) {
			std::cout << way[i] << " ";
		}
		std::cout << std::endl;
	}
	Sleep(2000);
	system("cls");

	show_menu(2);
	std::cout << "Enter index" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(1500);
	system("cls");
	way = tree.get_way(3);
	if (way.size() == 0) {
		std::cout << "This is root" << std::endl;
	}
	else {
		for (size_t i = 0; i < way.size(); i++) {
			std::cout << way[i] << " ";
		}
		std::cout << std::endl;
	}
	Sleep(2500);
	system("cls");
	way.clear();

	show_menu(3);
	std::cout << "Enter next step" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(1500);
	system("cls");
	std::cout << "-> continue typing" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter next step" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "-> continue typing" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(350);
	system("cls");
	std::cout << "   continue typing" << std::endl;
	std::cout << "-> break" << std::endl;
	Sleep(500);
	system("cls");
	way = { 1,0 };
	int searched = tree.get_element(way);
	std::cout << searched << std::endl;
	Sleep(2000);
	system("cls");

	show_menu(5);
	std::cout << "Enter index" << std::endl;
	Sleep(500);
	std::cout << 6;
	Sleep(700);
	system("cls");
	std::cout << tree[6];
	Sleep(1000);
	system("cls");

	show_menu(7);
	std::cout << "Enter next step" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "-> continue typing" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "Enter next step" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(1500);
	system("cls");
	std::cout << "-> continue typing" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(350);
	system("cls");
	std::cout << "   continue typing" << std::endl;
	std::cout << "-> break" << std::endl;
	Sleep(500);
	system("cls");
	way = { 0,0 };
	Tree<int>for_return;
	tree.remove(way, for_return);
	for_return.show();
	Sleep(4000);
	system("cls");

	show_menu(4);
	tree.show();
	Sleep(4000);
	system("cls");

	show_menu(10);
	std::cout << tree.size();
	Sleep(2500);
	system("cls");

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(250);
	std::cout<<0;
	Sleep(700);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(700);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(700);
	system("cls");
	tree.add(10, 2, 4);

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout <<1;
	Sleep(250);
	std::cout << 1;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	system("cls");
	tree.add(11, 2, 4);

	show_menu(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	system("cls");
	std::cout << "Enter min number of children" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(1500);
	system("cls");
	std::cout << "Enter max number of children" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	system("cls");
	tree.add(4, 2, 4);

	show_menu(4);
	tree.show();
	Sleep(6000);
	system("cls");

	show_menu(8);
	std::cout << "Enter number to delete" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(1500);
	tree.remove(4);
	system("cls");

	show_menu(4);
	tree.show();
	Sleep(6000);
	system("cls");

	show_menu(10);
	std::cout << tree.size();
	Sleep(3000);
	system("cls");

	show_menu(9);
	tree.clear();
	Sleep(250);

	show_menu(4);
	tree.show();
	Sleep(2000);
	system("cls");

	show_menu(10);
	std::cout << tree.size();
	Sleep(2000);
	system("cls");

	show_menu(11);



	std::cout << "-> ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   ordinary tree" << std::endl;
	std::cout << "-> binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(1000);
	system("cls");
	binaryTree<int>bin_tree;

	show_menu1(1);
	bin_tree.show();
	Sleep(1000);
	system("cls");
	show_menu1(2);
	bin_tree.show();
	Sleep(1000);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(700);
	bin_tree.add(5);
	system("cls");

	show_menu1(1);
	bin_tree.show();
	Sleep(1000);
	system("cls");
	show_menu1(2);
	bin_tree.show_in_order();
	Sleep(1000);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 3;
	Sleep(700);
	bin_tree.add(3);
	system("cls");

	show_menu1(1);
	bin_tree.show();
	Sleep(1500);
	system("cls");
	show_menu1(2);
	bin_tree.show_in_order();
	Sleep(1500);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 7;
	Sleep(700);
	bin_tree.add(7);
	system("cls");

	show_menu1(1);
	bin_tree.show();
	Sleep(1500);
	system("cls");
	show_menu1(2);
	bin_tree.show_in_order();
	Sleep(1500);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 5;
	Sleep(700);
	bin_tree.add(5);
	system("cls");

	show_menu1(1);
	bin_tree.show();
	Sleep(2000);
	system("cls");
	show_menu1(2);
	bin_tree.show_in_order();
	Sleep(2000);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 4;
	Sleep(700);
	bin_tree.add(4);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 9;
	Sleep(700);
	bin_tree.add(9);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(700);
	bin_tree.add(1);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 0;
	Sleep(700);
	bin_tree.add(0);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 2;
	Sleep(700);
	bin_tree.add(2);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 1;
	Sleep(250);
	std::cout << 0;
	Sleep(700);
	bin_tree.add(10);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 6;
	Sleep(700);
	bin_tree.add(6);
	system("cls");

	show_menu1(0);
	std::cout << "Enter number to add" << std::endl;
	Sleep(500);
	std::cout << 8;
	Sleep(700);
	bin_tree.add(8);
	system("cls");

	show_menu1(1);
	bin_tree.show();
	Sleep(5000);
	system("cls");
	show_menu1(2);
	bin_tree.show_in_order();
	Sleep(4000);
	system("cls");

	show_menu1(3);
	threadedBinaryTree<int>threaded(bin_tree);
	threaded.show();
	Sleep(7000);
	system("cls");

	show_menu1(4);
	bin_tree.clear();
	Sleep(250);

	show_menu1(1);
	bin_tree.show();
	Sleep(1500);
	system("cls");
	show_menu1(2);
	bin_tree.show_in_order();
	Sleep(1500);
	system("cls");

	show_menu1(5);



	system("cls");
	std::cout << "-> ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   ordinary tree" << std::endl;
	std::cout << "-> binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "-> expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");

	std::string main_string = "";

	system("cls");
	std::cout << "Enter signs of your expression" << std::endl << std::endl;
	std::cout << main_string << std::endl << std::endl;
	std::cout << "-> +" << std::endl;
	std::cout << "   -" << std::endl;
	std::cout << "   *" << std::endl;
	std::cout << "   /" << std::endl;
	std::cout << "   ^" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(250);
	system("cls");
	std::cout << "Enter signs of your expression" << std::endl << std::endl;
	std::cout << main_string << std::endl << std::endl;
	std::cout << "   +" << std::endl;
	std::cout << "-> -" << std::endl;
	std::cout << "   *" << std::endl;
	std::cout << "   /" << std::endl;
	std::cout << "   ^" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(250);
	system("cls");
	std::cout << "Enter signs of your expression" << std::endl << std::endl;
	std::cout << main_string << std::endl << std::endl;
	std::cout << "   +" << std::endl;
	std::cout << "   -" << std::endl;
	std::cout << "-> *" << std::endl;
	std::cout << "   /" << std::endl;
	std::cout << "   ^" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(500);
	system("cls");
	Sleep(2000);
	std::cout << "... few months later ...";
	Sleep(2000);
	system("cls");
	std::cout << "Enter signs of your expression" << std::endl << std::endl;
	std::cout << main_string << std::endl << std::endl;
	std::cout << "   +" << std::endl;
	std::cout << "-> -" << std::endl;
	std::cout << "   *" << std::endl;
	std::cout << "   /" << std::endl;
	std::cout << "   ^" << std::endl;
	std::cout << "   break" << std::endl;
	Sleep(2000);
	system("cls");
	main_string = "*+-+++*+-+^/+-^++^-";
	system("cls");
	std::cout << "If you want, you can add brackets" << std::endl << std::endl;
	std::cout << main_string << std::endl << std::endl;
	std::cout << "-> insert ( before 1 sign"<<std::endl;
	std::cout << "   insert ( before 2 sign" << std::endl;
	std::cout << "   insert ( before 3 sign" << std::endl;
	std::cout << "   insert ( before 4 sign" << std::endl;
	std::cout << "   insert ( before 5 sign" << std::endl;
	std::cout << "   insert ( before 6 sign" << std::endl;
	std::cout << "   insert ( before 7 sign" << std::endl;
	std::cout << "   insert ( before 8 sign" << std::endl;
	std::cout << "   insert ( before 9 sign" << std::endl;
	std::cout << "   insert ( before 10 sign" << std::endl;
	std::cout << "   insert ( before 11 sign" << std::endl;
	std::cout << "   insert ( before 12 sign" << std::endl;
	std::cout << "   insert ( before 13 sign" << std::endl;
	std::cout << "   insert ( before 14 sign" << std::endl;
	std::cout << "   insert ( before 15 sign" << std::endl;
	std::cout << "   insert ( before 16 sign" << std::endl;
	std::cout << "   insert ( before 17 sign" << std::endl;
	std::cout << "   insert ( before 18 sign" << std::endl;
	Sleep(2000);
	system("cls");
	Sleep(2000);
	std::cout << "... few months later ...";
	Sleep(2000);
	system("cls");
	main_string = "*(+)-(+)+(+)*(+)-(+)^/(+-^++^-";
	std::cout << "Add ) after:" << std::endl << std::endl;
	std::cout << main_string << std::endl << std::endl;
	std::cout << "   insert ) after 12 sign" << std::endl;
	std::cout << "   insert ) after 13 sign" << std::endl;
	std::cout << "   insert ) after 14 sign" << std::endl;
	std::cout << "   insert ) after 15 sign" << std::endl;
	std::cout << "   insert ) after 16 sign" << std::endl;
	std::cout << "   insert ) after 17 sign" << std::endl;
	std::cout << "-> insert ) after 18 sign" << std::endl;
	Sleep(2000);
	main_string = "(*(+)-(+))*((+)*(+)-(+)^/(+)-(^++^-))";

	expTree exp_tree;
	exp_tree.form_tree(main_string);
	exp_tree.show();
	Sleep(5000);
	std::deque<std::string>variables = {"y","z","a","b","c","k"};
	std::deque<std::string>for_fill = { "","y","z","y","z","a","b","a","b","a","c","","a","c","","","","k","","k" };
	std::deque<int>numbers = { 6,3,4,2,3,1 };

	system("cls");
	std::cout << "After a few months of filling:" << std::endl;
	Sleep(2000);
	system("cls");
	std::cout << "-> variable" << std::endl;
	std::cout << "   number" << std::endl;
	Sleep(700);
	system("cls");
	std::cout << "Enter name of variable" << std::endl;
	Sleep(500);
	std::cout << "k";
	Sleep(1000);
	system("cls");

	exp_tree.fill_demo(for_fill,numbers);

	show_menu2(0);
	exp_tree.show();
	Sleep(15000);
	system("cls");

	show_menu2(1);
	exp_tree.show_min();
	Sleep(15000);
	system("cls");

	show_menu2(2);
	expTree for_simpl(exp_tree);
	for_simpl.simplification();
	std::cout << "With max brackets: ";
	for_simpl.show();
	std::cout << "\nWith min brackets: ";
	for_simpl.show_min();
	Sleep(15000);
	system("cls");


	show_menu2(3);
	std::cout << "Enter value of y" << std::endl;
	Sleep(500);
	std::cout << "3"<<std::endl;
	Sleep(700);
	std::cout << "Enter value of z" << std::endl;
	Sleep(500);
	std::cout << "1" << std::endl;
	Sleep(700);
	std::cout << "Enter value of a" << std::endl;
	Sleep(500);
	std::cout << "-1" << std::endl;
	Sleep(700);
	std::cout << "Enter value of b" << std::endl;
	Sleep(500);
	std::cout << "4" << std::endl;
	Sleep(700);
	std::cout << "Enter value of c" << std::endl;
	Sleep(500);
	std::cout << "5" << std::endl;
	Sleep(700);
	std::cout << "Enter value of k" << std::endl;
	Sleep(500);
	std::cout << "-5" << std::endl;
	Sleep(700);
	std::deque<double>values = { 3,1,-1,4,5,-5 };
	exp_tree.fill_values(values, variables);
	system("cls");
	std::cout << exp_tree.calculate() << std::endl;
	Sleep(5000);
	system("cls");

	show_menu2(4);


	system("cls");
	std::cout << "-> ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   ordinary tree" << std::endl;
	std::cout << "-> binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "-> expression tree" << std::endl;
	std::cout << "   exit" << std::endl;
	Sleep(500);
	system("cls");
	std::cout << "   ordinary tree" << std::endl;
	std::cout << "   binary tree" << std::endl;
	std::cout << "   expression tree" << std::endl;
	std::cout << "-> exit" << std::endl;
	Sleep(1000);
	system("cls");

	std::cout << "Thanks for your attention" << std::endl;
	system("pause");
}

int interactive_menu()
{
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 4) % 4;
		if (choise == 0) std::cout << "-> ordinary tree" << std::endl;
		else  std::cout << "   ordinary tree" << std::endl;
		if (choise == 1) std::cout << "-> binary tree" << std::endl;
		else  std::cout << "   binary tree" << std::endl;
		if (choise == 2) std::cout << "-> expression tree" << std::endl;
		else  std::cout << "   expression tree" << std::endl;
		if (choise == 3) std::cout << "-> exit" << std::endl;
		else  std::cout << "   exit" << std::endl;
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

void ordinary()
{
	Tree<int>tree;
	int choise = ordinary_menu();
	while (choise != 11) {
		if (choise == 0) {
			int to_add;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter number to add" << std::endl;
				std::cin >> to_add;
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
			long long min;
			correct = false;
			while (!correct) {
				std::cout << "Enter min number of children" << std::endl;
				std::cin >> min;
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
				if (min < 0) {
					std::cout << "Error.Your min < 0" << std::endl;
					correct = false;
					Sleep(3000);
					system("cls");
					continue;
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
			long long max;
			correct = false;
			while (!correct) {
				std::cout << "Enter max number of children" << std::endl;
				std::cin >> max;
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
				if (max < 0) {
					std::cout << "Error.Your max < 0" << std::endl;
					correct = false;
					Sleep(3000);
					system("cls");
					continue;
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
				tree.add(to_add, (size_t)min, (size_t)max);
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 1) {
			std::deque<size_t>way;
			int to_add;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter number to add" << std::endl;
				std::cin >> to_add;
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
			if (tree.size() == 0) {
				tree.add(to_add, way);
				system("pause");
				choise = ordinary_menu();
			}
			else {
				int way_choise = 0;
				int code;
				do {
					system("cls");
					std::cout << "Enter way" << std::endl;
					way_choise = (way_choise + 2) % 2;
					if (way_choise == 0) std::cout << "-> type" << std::endl;
					else  std::cout << "   type" << std::endl;
					if (way_choise == 1) std::cout << "-> empty way" << std::endl;
					else  std::cout << "   empty way" << std::endl;
					code = _getch();
					if (code == 224)
					{
						code = _getch();
						if (code == 80) way_choise++;
						if (code == 72) way_choise--;
					}

				} while (code != 13);
				system("cls");
				if (way_choise == 0) {
					get_way(way);
				}
				try
				{
					tree.add(to_add, way);
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
				system("pause");
				choise = ordinary_menu();
			}
		}
		else if (choise == 2) {
			long long index;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter index" << std::endl;
				std::cin >> index;
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
				if (index < 0) {
					std::cout << "Error.Your index < 0" << std::endl;
					correct = false;
					Sleep(3000);
					system("cls");
					continue;
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
				std::deque<size_t>way = tree.get_way((size_t)index);
				if (way.size() == 0) {
					std::cout << "This is root" << std::endl;
				}
				else {
					for (size_t i = 0; i < way.size(); i++) {
						std::cout << way[i] << " ";
					}
					std::cout << std::endl;
				}
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what()<<std::endl;
			}
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 3) {
			std::deque<size_t>way;
			get_way(way);
			try
			{
				int searched = tree.get_element(way);
				std::cout << searched << std::endl;	
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 4) {
			tree.show();
			std::cout<<std::endl;
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 5) {
			long long index;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter index" << std::endl;
				std::cin >> index;
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
				if (index<0) {
					std::cout << "Error.Your index < 0" << std::endl;
					correct = false;
					Sleep(3000);
					system("cls");
					continue;
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
				std::cout << tree[(size_t)index] << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 6) {
			tree.interactive_browsing();
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 7) {
			std::deque<size_t>way;
			try
			{
				get_way(way);
				Tree<int>for_return;
				tree.remove(way, for_return);
				for_return.show();
				std::cout<<std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 8) {
			int to_delete;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter number to delete" << std::endl;
				std::cin >> to_delete;
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
			tree.remove(to_delete);
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 9) {
			std::deque<size_t>way = {};
			if (tree.size() > 0) {
				int root = tree.get_element(way);
				tree.remove(root);
			}
			else {
				std::cout << "This tree is already empty" << std::endl;
			}
			system("pause");
			choise = ordinary_menu();
		}
		else if (choise == 10) {
			std::cout << tree.size() << std::endl;
			system("pause");
			choise = ordinary_menu();
		}
	}
}

void binary()
{
	binaryTree<int>tree;
	int choise = binary_menu();
	while (choise != 5) {
		if (choise == 0) {
			int to_add;
			bool correct = false;
			char ch;
			while (!correct) {
				std::cout << "Enter number to add" << std::endl;
				std::cin >> to_add;
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
			tree.add(to_add);
			system("pause");
			choise = binary_menu();
		}
		else if (choise == 1) {
			tree.show();
			std::cout << std::endl;
			system("pause");
			choise = binary_menu();
		}
		else if (choise == 2) {
			tree.show_in_order();
			std::cout << std::endl;
			system("pause");
			choise = binary_menu();
		}
		else if (choise == 3) {
			threadedBinaryTree<int>threaded(tree);
			threaded.show();
			std::cout << std::endl;
			system("pause");
			choise = binary_menu();
		}
		else if (choise == 4) {
			tree.clear();
			system("pause");
			choise = binary_menu();
		}
	}
}

void expression()
{
	expTree tree;
	std::string for_tree = form_string();
	for (size_t i = 1; i < for_tree.length(); i++) {
		if (for_tree[i] == '(' && for_tree[i - 1] == ')') {
			for_tree.insert(i, std::string("*"));
		}
	}
	try
	{
		tree.form_tree(for_tree);
	}
	catch (const std::exception& ex)
	{
		system("cls");
		std::cout << ex.what() << std::endl;
		system("pause");
		return;
	}
	tree.show();
	Sleep(5000);
	std::deque<std::string>variables;
	tree.fill(variables);
	int choise = expression_menu();
	while (choise != 4) {
		if (choise == 0) {
			system("cls");
			tree.show();
			std::cout << std::endl;
			system("pause");
			choise = expression_menu();
		}
		else if (choise == 1) {
			system("cls");
			tree.show_min();
			std::cout << std::endl;
			system("pause");
			choise = expression_menu();
		}
		else if (choise==2) {
			expTree tree_for_simplification = tree;
			try
			{
				tree_for_simplification.simplification();
				std::cout << "With maximum of brackets: ";
				tree_for_simplification.show();
				std::cout << std::endl;
				std::cout << "With minimum of brackets: ";
				tree_for_simplification.show_min();
				std::cout << std::endl;
				system("pause");
				choise = expression_menu();
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
				system("pause");
				choise = expression_menu();
			}
		}
		else if (choise == 3) {
			std::deque<double>values;
			for (size_t i = 0; i < variables.size(); i++) {
				double to_push;
				bool correct = false;
				char ch;
				while (!correct) {
					std::cout << "Enter value of "<<variables[i] << std::endl;
					std::cin >> to_push;
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
				values.push_back(to_push);
			}
			expTree tree_for_calculation = tree;
			tree_for_calculation.fill_values(values, variables);
			system("cls");
			try
			{
				std::cout << tree_for_calculation.calculate() << std::endl;
				system("pause");
				choise = expression_menu();
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
				system("pause");
				choise = expression_menu();
			}
		}
	}
}

int ordinary_menu() {
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 12) % 12;
		if (choise == 0) std::cout << "-> add the number by min and max number of children" << std::endl;
		else  std::cout << "   add the number by min and max number of children" << std::endl;
		if (choise == 1)std::cout << "-> add the number by the way" << std::endl;
		else std::cout << "   add the number by the way" << std::endl;
		if (choise == 2) std::cout << "-> find out the way to the number with some index" << std::endl;
		else  std::cout << "   find out the way to the number with some index" << std::endl;
		if (choise == 3) std::cout << "-> find out the number by the way" << std::endl;
		else  std::cout << "   find out the number by the way" << std::endl;
		if (choise == 4) std::cout << "-> see tree" << std::endl;
		else  std::cout << "   see tree" << std::endl;
		if (choise == 5) std::cout << "-> see element by index" << std::endl;
		else  std::cout << "   see element by index" << std::endl;
		if (choise == 6) std::cout << "-> interactive tree view" << std::endl;
		else std::cout << "   interactive tree view" << std::endl;
		if (choise == 7) std::cout << "-> delete the number by the way and see removed subtree" << std::endl;
		else  std::cout << "   delete the number by the way and see removed subtree" << std::endl;
		if (choise == 8) std::cout << "-> delete all some numbers and their subtrees" << std::endl;
		else  std::cout << "   delete all some numbers and their subtrees" << std::endl;
		if (choise == 9) std::cout << "-> clear whole tree" << std::endl;
		else  std::cout << "   clear whole tree" << std::endl;
		if (choise == 10) std::cout << "-> find out size of tree" << std::endl;
		else  std::cout << "   find out size of tree" << std::endl;
		if (choise == 11) std::cout << "-> exit" << std::endl;
		else  std::cout << "   exit" << std::endl;
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

int binary_menu()
{
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 6) % 6;
		if (choise == 0) std::cout << "-> add number" << std::endl;
		else  std::cout << "   add number" << std::endl;
		if (choise == 1) std::cout << "-> see tree" << std::endl;
		else  std::cout << "   see tree" << std::endl;
		if (choise == 2) std::cout << "-> see tree in right order" << std::endl;
		else  std::cout << "   see tree in right order" << std::endl;
		if (choise == 3) std::cout << "-> form threaded tree and see it" << std::endl;
		else  std::cout << "   form threaded tree and see it" << std::endl;
		if (choise == 4) std::cout << "-> clear whole tree" << std::endl;
		else  std::cout << "   clear whole tree" << std::endl;
		if (choise == 5) std::cout << "-> end" << std::endl;
		else  std::cout << "   end" << std::endl;
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

int expression_menu() {
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 5) % 5;
		if (choise == 0) std::cout << "-> see tree with max brackets" << std::endl;
		else  std::cout << "   see tree with max brackets" << std::endl;
		if (choise == 1) std::cout << "-> see tree with min brackets" << std::endl;
		else  std::cout << "   see tree with min brackets" << std::endl;
		if (choise == 2) std::cout << "-> simplification" << std::endl;
		else  std::cout << "   simplification" << std::endl;
		if (choise == 3) std::cout << "-> calculate" << std::endl;
		else  std::cout << "   calculate" << std::endl;
		if (choise == 4) std::cout << "-> end" << std::endl;
		else  std::cout << "   end" << std::endl;
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

void get_way(std::deque<size_t>&way) {
	long long next_step;
	bool correct = false;
	char ch;
	while (!correct) {
		std::cout << "Enter next step" << std::endl;
		std::cin >> next_step;
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
		if (next_step < 0) {
			std::cout << "Error.Your next step < 0" << std::endl;
			correct = false;
			Sleep(3000);
			system("cls");
			continue;
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
	way.push_back((size_t)next_step);
	int choise = 0;
	int code;
	do {
		system("cls");
		choise = (choise + 2) % 2;
		if (choise == 0) std::cout << "-> continue typing" << std::endl;
		else  std::cout << "   continue typing" << std::endl;
		if (choise == 1) std::cout << "-> break" << std::endl;
		else  std::cout << "   break" << std::endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) choise++;
			if (code == 72) choise--;
		}

	} while (code != 13);
	system("cls");
	if (choise == 0) {
		get_way(way);
	}
	else {
		return;
	}
}

void show_menu(int choise) {
	std::string menu[] = { "add the number by min and max number of children",
		"add the number by the way",
	"find out the way to the number with some index","find out the number by the way",
	"see tree","see element by index","interactive tree view",
		"delete the number by the way and see removed subtree",
	"delete all some numbers and their subtrees", "clear whole tree","find out size of tree","exit" };
	for (int i = 0; i <= choise; i++) {
		for (int j = 0; j < 12; j++) {
			if (j == i) {
				std::cout << "-> " << menu[j] << std::endl;
			}
			else {
				std::cout << "   " << menu[j] << std::endl;
			}
		}
		Sleep(350);
		system("cls");
	}
}

void show_menu1(int choise) {
	std::string menu[] = { "add number","see tree","see tree in right order",
	"form threaded tree and see it","clear whole tree","end" };
	for (int i = 0; i <= choise; i++) {
		for (int j = 0; j < 6; j++) {
			if (j == i) {
				std::cout << "-> " << menu[j] << std::endl;
			}
			else {
				std::cout << "   " << menu[j] << std::endl;
			}
		}
		Sleep(350);
		system("cls");
	}
}

void show_menu2(int choise) {
	std::string menu[] = { "see tree with max brackets","see tree with min brackets",
	"simplification","calculate","end" };
	for (int i = 0; i <= choise; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) {
				std::cout << "-> " << menu[j] << std::endl;
			}
			else {
				std::cout << "   " << menu[j] << std::endl;
			}
		}
		Sleep(500);
		system("cls");
	}
}