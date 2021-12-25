#include "Header.h"

std::string main_help = "\n\ndemomode - launch demomode\nbenchmark - launch benchmark\nlinked - create ordered list as linked list\narray number - create ordered list as array with max number of points = number\nbinary - create ordered list as binary tree\nAVL - create ordered list as AVL tree\n2-3 - create ordered list as 2-3 tree\nexit - close program\n\n";
std::string help_answer = "\n\npop back - erase last element\n\t\t(only for linked and array)\npop front - erase first element\n\t\t(only for linked and array)\npush x y z - push point with coordinates (x,y,z)\npush x y z number - push mumber points with coordinates (x,y,z)\n\t\t(isn't available for 2-3, AVL and binary)\npush random number - push number of random points\nquick push x y z - push point with coordinates (x,y,z)\n\t\t(only for array)\nquick push x y z number - push mumber points with coordinates (x,y,z)\n\t\t(only for array)\nerase x y z - erase point with coordinates (x, y, z)\nerase pos - erase point with position pos\n\t\t(unavailable for 2-3 tree, binary and AVL)\nerase begin end - erase points with positions from begin to end\n\t\t(isn't available for 2-3 tree, binary and AVL)\nshow - see ordered list\nshow pos - see point with position pos\n\t\t(isn't available for 2-3 tree)\nis value x y z - check if there is point with coordinates (x, y, z) in list\nvalue search x y z - see node abstraction (position) if point with this coordinates is in list\n\t\t(isn't available for 2-3 tree)\nrange search values x1 y1 z1 x2 y2 z2 - check what points from range A(x1, y1, z1) - B(x2, y2, z2) are in list\nrange search nodes x1 y1 z1 x2 y2 z2 - find out node abstractions (values and positions) of points from range A(x1, y1, z1) - B(x2, y2, z2) that are in list\n\t\t(isn't available for 2-3, binary and AVL)\naction x plus - increase x by 1 for all points\naction x minus - decrease x by 1 for all points\naction y plus - increase y by 1 for all points\naction y minus - decrease y by 1 for all points\naction z plus - increase z by 1 for all points\naction z minus - decrease z by 1 for all points\n";


bool operator>(const point& left, const point& right)
{
	return (left.x > right.x) || (left.x == right.x && left.y > right.y) || (left.x == right.x && left.y == right.y && left.z > right.z);
}

bool operator<(const point& left, const point& right)
{
	return right > left;
}

bool operator==(const point& left, const point& right)
{
	return !(right > left || left > right);
}

bool operator>=(const point& left, const point& right)
{
	return left > right || left == right;
}

bool operator<=(const point& left, const point& right)
{
	return right > left || left == right;
}

std::ostream& operator<<(std::ostream& out, const point& point)
{
	out << '(' << point.x << ", " << point.y << ", " << point.z << ')';
	return out;
}

void orderedListLinkedList::pop_back()
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (size == 1) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		size = 0;
	}
	else {
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		size--;
	}
}

void orderedListLinkedList::pop_front()
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (size == 1) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		size = 0;
	}
	else {
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		size--;
	}
}

void orderedListLinkedList::push(point value)
{
	ListNode* new_node = new ListNode(value);
	if (size == 0) {
		head = new_node;
		tail = head;
		size++;
	}
	else if (size == 1) {
		if (new_node->value < head->value) {
			tail->prev = new_node;
			new_node->next = tail;
			head = new_node;
		}
		else {
			head->next = new_node;
			new_node->prev = head;
			tail = new_node;
		}
		size++;
	}
	else
	{
		if (new_node->value < head->value) {
			head->prev = new_node;
			new_node->next = head;
			head = new_node;
		}
		else {
			ListNode* next_current = head;
			ListNode* current = head;
			while (next_current->next != nullptr && current->value < value)
			{
				current = next_current;
				next_current = next_current->next;
				if (next_current->next == nullptr && (next_current->value <= value))
				{
					tail->next = new_node;
					new_node->prev = tail;
					tail = new_node;
					break;
				}
				else if (value < next_current->value)
				{
					current->next = new_node;
					new_node->next = next_current;
					next_current->prev = new_node;
					new_node->prev = current;
					break;
				}
			}
		}
		size++;
	}
}

void orderedListLinkedList::push(point value, long long number)
{
	if (number < 1) {
		throw ListErr("Incorrect number");
	}
	else if (number == 1) {
		push(value);
	}
	else {
		ListNode** new_nodes = new ListNode * [number];
		for (long long i = 0; i < number; i++) {
			new_nodes[i] = new ListNode(value);
		}
		for (long long i = 1; i < number - 1; i++) {
			new_nodes[i]->next = new_nodes[i + 1];
			new_nodes[i]->prev = new_nodes[i - 1];
		}
		new_nodes[0]->next = new_nodes[1];
		new_nodes[number - 1]->prev = new_nodes[number - 2];
		if (size == 0) {
			head = new_nodes[0];
			tail = new_nodes[number - 1];
			size = number;
		}
		else if (size == 1) {
			if (value < head->value) {
				tail->prev = new_nodes[number - 1];
				new_nodes[number - 1]->next = tail;
				head = new_nodes[0];
			}
			else {
				head->next = new_nodes[0];
				new_nodes[0]->prev = head;
				tail = new_nodes[number - 1];
			}
			size+=number;
		}
		else
		{
			if (value < head->value) {
				head->prev = new_nodes[number - 1];
				new_nodes[number - 1]->next = head;
				head = new_nodes[0];
			}
			else {
				ListNode* next_current = head;
				ListNode* current = head;
				while (next_current->next != nullptr && current->value < value)
				{
					current = next_current;
					next_current = next_current->next;
					if (next_current->next == nullptr && (next_current->value < value))
					{
						tail->next = new_nodes[0];
						new_nodes[0]->prev = tail;
						tail = new_nodes[number - 1];
					}
					else if (value < next_current->value)
					{
						current->next = new_nodes[0];
						new_nodes[number - 1]->next = next_current;
						break;
					}
				}
			}
			size += number;
		}
		delete[] new_nodes;
	}
}

void orderedListLinkedList::push_random(long long number)
{
	std::vector<point> new_values;
	for (long long i = 0; i < number; i++) {
		new_values.push_back(point(number));
	}
	quicksort(new_values, 0, number - 1);
	long long counter = 0;
	push(new_values[0]);
	if (number != 1) {
		push(new_values[new_values.size() - 1]);
	}
	ListNode* node = tail;
	while (counter != number-1 && node != nullptr) {
		if (node->value < new_values[number - 2 - counter]) {
			ListNode* new_node = new ListNode(new_values[number - 2 - counter]);
			new_node->prev = node;
			if (node->next) {
				ListNode* help = node->next;
				help->prev = new_node;
				node->next = new_node;
				new_node->next = help;
			}
			else {
				node->next = new_node;
			}
			size++;
			counter++;
		}
		else {
			node = node->prev;
		}
	}
}

void orderedListLinkedList::erase(point value)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else {
		while (head->value == value) {
			pop_front();
		}
		ListNode* search = head;
		for (size_t i = 0; i < size - 1; i++) {
			search = search->next;
			if (search->value == value) {
				while (search && search->value == value) {
					if (search == tail) {
						pop_back();
					}
					else {
						ListNode* to_erase = search;
						search->prev->next = search->next;
						search->next->prev = search->prev;
						delete to_erase;
						size--;
					}
				}
				break;
			}
		}
	}
}

void orderedListLinkedList::erase(size_t pos)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (pos > size - 1) {
		throw ListErr("Incorrect pos");
	}
	else {
		if (pos == size - 1) {
			pop_back();
		}
		else if (pos == 0) {
			pop_front();
		}
		else if (pos > 0 && pos < size - 1) {
			ListNode* search = head;
			for (size_t i = 0; i < pos + 1; i++) {
				search = search->next;
			}
			ListNode* to_erase = search->prev;
			if (to_erase) {
				ListNode* prev = to_erase->prev;
				if (prev != nullptr) {
					prev->next = search;
				}
				search->prev = prev;
				delete to_erase;
				size--;
			}
		}
	}
}

void orderedListLinkedList::erase(size_t begin, size_t end)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	if (begin > end || end > size - 1) {
		throw ListErr("Incorrrect begin or end");
	}
	else if (begin == end) {
		erase(begin);
		return;
	}
	else {
		for (size_t i = begin; i <= end; i++) {
			erase(begin);
		}
		return;
	}
}

void orderedListLinkedList::show()
{
	if (size == 0) {
		std::cout<<"Empty list"<<std::endl;
	}
	else {
		ListNode* to_show = head;
		for (size_t i = 0; i < size; i++) {
			std::cout << to_show->value << std::endl;
			to_show = to_show->next;
		}
	}
}

void orderedListLinkedList::show(size_t pos)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (pos > size - 1) {
		throw ListErr("Incorrect pos");
	}
	else {
		ListNode* search = head;
		for (size_t i = 0; i < pos; i++) {
			search = search->next;
		}
		std::cout << search->value << std::endl;
	}
}

point orderedListLinkedList::operator[](size_t index)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	if (index > size - 1) {
		throw ListErr("Incorrect index");
	}
	else {
		ListNode* search = head;
		for (size_t i = 0; i < index; i++) {
			search = search->next;
		}
		return search->value;
	}
}

bool orderedListLinkedList::is_value(point value)
{
	if (size == 0) {
		return false;
	}
	else {
		ListNode* search = head;
		while(search->value<value && search->next) {
			search = search->next;
		}
		if (search->value == value) {
			return true;
		}
		else {
			return false;
		}
	}
}

node_abstraction orderedListLinkedList::value_search(point value)
{
	node_abstraction to_return(value, -1);
	ListNode* search = head;
	int pos=0;
	while (search->value < value && search->next) {
		search = search->next;
		pos++;
	}
	if (search->value == value) {
		to_return.position = pos;
	}
	return to_return;
}

std::vector<point> orderedListLinkedList::range_search_values(point down, point top)
{
	if (head && down < top) {
		std::vector<point>to_return;
		ListNode* search = head;
		while (search->value < top && search) {
			if (search->value > down) {
				to_return.push_back(search->value);
			}
			if (search->next) {
				search = search->next;
			}
			else {
				break;
			}
		}
		return to_return;
	}
	else {
		throw ListErr("Empty list or incorrect down and top");
	}
}

std::vector<node_abstraction> orderedListLinkedList::range_search_nodes(point down, point top)
{
	if (head && down < top) {
		std::vector<node_abstraction>to_return;
		ListNode* search = head;
		int i = 0;
		while (search->value < top && search) {
			if (search->value > down) {
				to_return.push_back({search->value, i});
			}
			if (search->next) {
				search = search->next;
				i++;
			}
			else {
				break;
			}
		}
		return to_return;
	}
	else {
		throw ListErr("Empty list or incorrect down and top");
	}
}

void orderedListLinkedList::action(void(*fooPointer)(point& a))
{
	ListNode* current = head;
	for (size_t i = 0; i < size; i++) {
		fooPointer(current->value);
		current = current->next;
	}
}

void orderedListArrayList::pop_back()
{
	if (size > 0) {
		size--;
	}
	else {
		throw ListErr("Empty list");
	}
}

void orderedListArrayList::pop_front()
{
	if (size == 1) {
		size = 0;
	}
	else if (size > 1) {
		for (size_t i = 1; i < size; i++) {
			list[i-1] = list[i];
		}
		size--;
	}
	else {
		throw ListErr("Empty list");
	}
}

void orderedListArrayList::push(point value)
{
	if (size == max_size) {
		throw ListErr("List is full");
	}
	else {
		if (value > list[size - 1]) {
			list[size] = value;
		}
		else if (value < list[0]) {
			for (int i = size; i > 0; i--) {
				list[i] = list[i - 1];
			}
			list[0] = value;
		}
		else {
			for (int i = size; i > 0; i--) {
				if (list[i - 1] > value) {
					list[i] = list[i - 1];
				}
				else {
					list[i] = value;
					break;
				}
			}
		}
		size++;
	}
}

void orderedListArrayList::quick_push(point value)
{
	if (size == max_size) {
		throw ListErr("List is full");
	}
	else {
		if (value > list[size - 1]) {
			list[size] = value;
			size++;
		}
		else if (value < list[0]) {
			for (int i = size; i > 0; i--) {
				list[i] = list[i - 1];
			}
			list[0] = value;
		}
		else {
			int pos = 0;
			int down = 0;
			int top = size - 1;
			bool was = false;
			while (!was) {
				int pivot = (top + down) / 2;
				if (list[pivot] > value) {
					top = pivot;
				}
				else {
					down = pivot;
				}
				if (top - down < 2) {
					was = true;
					pos = top;
				}
			}
			for (int i = size; i > pos - 1; i--) {
				list[i] = list[i - 1];
			}
			list[pos] = value;
		}
		size++;
	}
}

void orderedListArrayList::push(point value, long long number)
{
	if (size + number > max_size) {
		throw ListErr("List is full or too big number");
	}
	else {
		if (value > list[size - 1]) {
			for (int i = 0; i < number; i++) {
				list[size + i] = value;
			}
		}
		else if (value < list[0]) {
			for (int i = size - 1; i > -1; i--) {
				list[i + number] = list[i];
			}
			for (int i = 0; i < number; i++) {
				list[i] = value;
			}
		}
		else {
			for (int i = size - 1; i > 0; i--) {
				if (list[i] > value) {
					list[i + number] = list[i];
				}
				else {
					for (int j = 0; j < number; j++) {
						list[i + 1 + j] = value;
					}
					break;
				}
			}
		}
		size += number;
	}
}

void orderedListArrayList::quick_push(point value, long long number)
{
	if (size + number > max_size) {
		throw ListErr("List is full or too big number");
	}
	else {
		if (value > list[size - 1]) {
			for (int i = 0; i < number; i++) {
				list[size + i] = value;
			}
			size += number;
		}
		else if (value < list[0]) {
			for (int i = size - 1; i > -1; i--) {
				list[i + number] = list[i];
			}
			for (int i = 0; i < number; i++) {
				list[i] = value;
			}
		}
		else {
			int pos = 0;
			int down = 0;
			int top = size - 1;
			bool was = false;
			while (!was) {
				int pivot = (top + down) / 2;
				if (list[pivot] > value) {
					top = pivot;
				}
				else {
					down = pivot;
				}
				if (top - down < 2) {
					was = true;
					pos = top;
				}
			}
			for (int i = size; i > pos - 1; i--) {
				list[i + number - 1] = list[i - 1];
			}
			for (int i = 0; i < number; i++) {
				list[pos + i] = value;
			}
		}
		size += number;
	}
}

void orderedListArrayList::push_random(long long number)
{
	if (size + number > max_size) {
		throw ListErr("List is full or too big number");
	}
	else {
		push(point(number));
		number--;
		std::vector<point>new_values;
		for (long long i = 0; i < number; i++) {
			new_values.push_back(point(number));
		}
		if (number > 0) {
			quicksort(new_values, 0, number - 1);
		}
		long long counter = number - 1;
		long long position = size - 1;
		while (counter >= 0) {
			if (list[position] < new_values[counter]) {
				list[position + counter + 1] = new_values[counter];
				counter--;
			}
			else {
				list[position + counter + 1] = list[position];
				position--;
				if (position < 0) {
					for (long long i = 0; i < counter+1; i++) {
						list[i] = new_values[i];
					}
					break;
				}
			}
		}
		size += number;
	}
}

void orderedListArrayList::erase(point value)
{
	size_t pos = 0;
	size_t difference = 0;
	for (size_t i = 0; i < size; i++) {
		if (list[i] == value) {
			pos = i;
			while (list[i] == value && i<size) {
				i++;
			}
			difference = i - pos;
			break;
		}
	}
	for (size_t i = pos; i < size - 1; i++) {
		list[i] = list[i + difference];
	}
	size -= difference;
}

void orderedListArrayList::erase(size_t pos)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (pos > size - 1) {
		throw ListErr("Incorrect pos");
	}
	else {
		for (size_t i = pos; i < size - 1; i++) {
			list[i] = list[i + 1];
		}
		size--;
	}
}

void orderedListArrayList::erase(size_t begin, size_t end)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (end < begin || end > size - 1) {
		throw ListErr("Incorrect begin or end");
	}
	else {
		for (size_t i = begin; i < size - end + begin - 1; i++) {
			list[i] = list[i + end - begin + 1];
		}
		size -= end - begin + 1;
	}
}

void orderedListArrayList::show()
{
	if (size == 0) {
		std::cout << "This list is empty" << std::endl;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			std::cout << list[i] << std::endl;
		}
	}
}

void orderedListArrayList::show(size_t pos)
{
	if (size == 0) {
		 std::cout<<"Empty list"<<std::endl;
	}
	else if (pos > size - 1) {
		throw ListErr("Incorrect pos");
	}
	else {
		std::cout << list[pos];
	}
}

point orderedListArrayList::operator[](size_t index)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	if (index > size - 1) {
		throw ListErr("Incorrect index");
	}
	else {
		return list[index];
	}
}

bool orderedListArrayList::is_value(point value)
{
	if (size == 0) {
		return false;
	}
	else {
		for (size_t i = 0; i < size; i++) {
			if (list[i] == value) {
				return true;
			}
		}
		return false;
	}
}

node_abstraction orderedListArrayList::value_search(point value)
{
	node_abstraction to_return(value, -1);
	for (size_t i = 0; i < size; i++) {
		if (list[i] == value) {
			to_return.position = i;
			return to_return;
		}
	}
	return to_return;
}

std::vector<point> orderedListArrayList::range_search_values(point down, point top)
{
	if (down < top) {
		std::vector<point>to_return;
		for (size_t i = 0; i < size; i++) {
			if (down < list[i] && list[i] < top) {
				to_return.push_back(list[i]);
			}
			else if (top < list[i]) {
				break;
			}
		}
		return to_return;
	}
	else {
		throw ListErr("Incorrect top and down");
	}
}

std::vector<node_abstraction> orderedListArrayList::range_search_nodes(point down, point top)
{
	if (down < top) {
		std::vector<node_abstraction>to_return;
		for (size_t i = 0; i < size; i++) {
			if (down < list[i] && list[i] < top) {
				to_return.push_back({ list[i], (int)i });
			}
			else if (top < list[i]) {
				break;
			}
		}
		return to_return;
	}
	else {
		throw ListErr("Incorrect top and down");
	}
}

void orderedListArrayList::action(void(*fooPointer)(point& a))
{
	for (size_t i = 0; i < size; i++) {
		fooPointer(list[i]);
	}
}


void binaryTree::push(point item)
{
	if (!root) {
		root = new binaryNode(item);
		size = 1;
	}
	else {
		push(item, root);
	}
}

void binaryTree::push_random(long long number)
{
	for (long long i = 0; i < number; i++) {
		push(point(number));
	}
}

void binaryTree::show(size_t pos)
{
	if (size == 0) {
		std::cout<<"Empty list"<<std::endl;
	}
	else if (pos > size - 1) {
		throw ListErr("Incorrect pos");
	}
	else {
		size_t counter = 0;
		binaryNode* to_show = get_node(pos, counter, root);
		if (to_show) {
			std::cout << to_show->item;
		}
	}
}

point binaryTree::operator[](size_t index)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (index > size - 1) {
		throw ListErr("Incorrect index");
	}
	else {
		size_t counter = 0;
		binaryNode* to_return = get_node(index, counter, root);
		if (to_return) {
			return to_return->item;
		}
	}
}

node_abstraction binaryTree::value_search(point value)
{
	if (size == 0) {
		return { value,-1 };
	}
	else {
		long long counter = 0;
		long long index = value_search(value, counter, root);
		return { value, index };
	}
}

std::vector<point> binaryTree::range_search_values(point down, point top)
{
	std::vector<point>to_return;
	size_t position = 0;
	range_search_values(down, top, to_return, root);
	return to_return;
}

bool binaryTree::is_value(point value, binaryNode* node)
{
	if (node) {
		if (node->item > value) {
			return is_value(value, node->left);
		}
		else if (node->item == value) {
			return true;
		}
		else {
			return is_value(value, node->right);
		}
	}
	else {
		return false;
	}
}

long long binaryTree::value_search(point value, long long& counter, binaryNode* node)
{
	if (node) {
		if (node->item > value) {
			return value_search(value, counter, node->left);
		}
		else if (node->item == value) {
			return counter;
		}
		else {
			counter++;
			value_search(value, counter, node->left);
			return value_search(value, counter, node->right);
		}
	}
	else {
		return -1;
	}
}

void binaryTree::range_search_values(point down, point top, std::vector<point>& to_return, binaryNode* node)
{
	if (node) {
		if (down < node->item && node->item < top) {
			to_return.push_back(node->item);
			range_search_values(down, top, to_return, node->left);
			range_search_values(down, top, to_return, node->right);
		}
		else if (node->item < down) {
			range_search_values(down, top, to_return, node->right);
		}
		else if (node->item > top) {
			range_search_values(down, top, to_return, node->left);
		}
	}
}

void binaryTree::push(point value, binaryNode* node)
{
	if (node) {
		if (value < node->item) {
			if (node->left) {
				push(value, node->left);
			}
			else {
				node->left = new binaryNode(value);
				size++;
			}
		}
		else {
			if (node->right) {
				push(value, node->right);
			}
			else {
				node->right = new binaryNode(value);
				size++;
			}
		}
	}
}

void binaryTree::delete_subtree(binaryNode*& node)
{
	if (node != nullptr) {
		delete_subtree(node->left);
		delete_subtree(node->right);
		delete node;
		node = nullptr;
	}
}

void binaryTree::show(binaryNode* node)
{
	if (node) {
		if (node->left) {
			show(node->left);
		}
		std::cout << node->item;
		std::cout << std::endl;
		if (node->right) {
			show(node->right);
		}
	}
}

void binaryTree::action(void(*fooPointer)(point& a), binaryNode* node)
{
	if (node) {
		if (node->left) {
			action(fooPointer, node->left);
		}
		fooPointer(node->item);
		if (node->right) {
			action(fooPointer, node->right);
		}
	}
}


void AVL_tree::push(point item)
{
	if (!root) {
		root = new Node(item);
		size = 1;
	}
	else {
		root = push(item, root);
		root = balance(root);
	}
}

void AVL_tree::push_random(long long number)
{
	if (number > 0) {
		for (long long i = 0; i < number; i++) {
			push(point(number));
		}
	}
	else {
		throw ListErr("Incorrect number");
	}
}

void AVL_tree::show(size_t pos)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (pos > size - 1) {
		throw ListErr("Incorrect pos");
	}
	else {
		size_t counter = 0;
		Node* to_show = get_node(pos, counter, root);
		if (to_show) {
			std::cout << to_show->item;
		}
	}
}

point AVL_tree::operator[](size_t index)
{
	if (size == 0) {
		throw ListErr("Empty list");
	}
	else if (index > size - 1) {
		throw ListErr("Incorrect index");
	}
	else {
		size_t counter = 0;
		Node* to_return = get_node(index, counter, root);
		if (to_return) {
			return to_return->item;
		}
		else {
			throw ListErr("Nothing");
		}
	}
}

node_abstraction AVL_tree::value_search(point value)
{
	if (size == 0) {
		return { value,-1 };
	}
	else {
		long long counter = 0;
		long long index = value_search(value, counter, root);
		return { value, index };
	}
}

std::vector<point> AVL_tree::range_search_values(point down, point top)
{
	std::vector<point>to_return;
	range_search_values(down, top, to_return, root);
	return to_return;
}

bool AVL_tree::is_value(point value, Node* node)
{
	if (node) {
		if (node->item > value) {
			return is_value(value, node->left);
		}
		else if (node->item == value) {
			return true;
		}
		else {
			return is_value(value, node->right);
		}
	}
	else {
		return false;
	}
}

long long AVL_tree::value_search(point value, long long& counter, Node* node)
{
	if (node) {
		if (node->item > value) {
			return value_search(value, counter, node->left);
		}
		else if (node->item == value) {
			return counter;
		}
		else {
			counter++;
			value_search(value, counter, node->left);
			return value_search(value, counter, node->right);
		}
	}
	else {
		return -1;
	}
}

void AVL_tree::range_search_values(point down, point top, std::vector<point>& to_return, Node* node)
{
	if (down < top) {
		if (node) {
			if (down < node->item && node->item < top) {
				to_return.push_back(node->item);
				range_search_values(down, top, to_return, node->left);
				range_search_values(down, top, to_return, node->right);
			}
			else if (node->item < down) {
				range_search_values(down, top, to_return, node->right);
			}
			else if (node->item > top) {
				range_search_values(down, top, to_return, node->left);
			}
		}
	}
	else {
		throw ListErr("Incorrect down and top");
	}
}

void AVL_tree::delete_subtree(Node*& node)
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

void AVL_tree::show(Node* node)
{
	if (node) {
		if (node->left) {
			show(node->left);
		}
		std::cout << node->item;
		std::cout << std::endl;
		if (node->right) {
			show(node->right);
		}
	}
}

void AVL_tree::action(void(*fooPointer)(point& a), Node* node)
{
	if (node) {
		if (node->left) {
			action(fooPointer, node->left);
		}
		fooPointer(node->item);
		if (node->right) {
			action(fooPointer, node->right);
		}
	}
}


void Tree_2_3::delete_subtree(Node*& node)
{
	if (node) {
		delete_subtree(node->first);
		delete_subtree(node->second);
		delete_subtree(node->third);
		delete node;
		node = nullptr;
	}
}

bool Tree_2_3::is_value(point value)
{
	if (size == 0) {
		return false;
	}
	else {
		if (get_node(root, value)) {
			return true;
		}
		else {
			return false;
		}
	}
}

std::vector<point> Tree_2_3::range_search_values(point down, point top)
{
	if (down < top) {
		std::vector<point>to_return;
		range_search_values(down, top, to_return, root);
		return to_return;
	}
	else {
		throw ListErr("Incorrect down and top");
	}
}

void Tree_2_3::range_search_values(point down, point top, std::vector<point>& to_return, Node* node)
{
	if (node) {
		if (node->size == 1) {
			if (down < node->key[0] && node->key[0] < top) {
				to_return.push_back(node->key[0]);
				range_search_values(down, top, to_return, node->first);
				range_search_values(down, top, to_return, node->second);
			}
			else if (node->key[0] < down) {
				range_search_values(down, top, to_return, node->second);
			}
			else if (node->key[0] > top) {
				range_search_values(down, top, to_return, node->first);
			}
		}
		else if (node->size == 2) {
			if (down < node->key[0] && node->key[0] < top) {
				to_return.push_back(node->key[0]);
				range_search_values(down, top, to_return, node->first);
				range_search_values(down, top, to_return, node->second);
				if (node->key[1] < top) {
					to_return.push_back(node->key[1]);
					range_search_values(down, top, to_return, node->third);
				}
			}
			else if (down < node->key[1] && node->key[1] < top) {
				to_return.push_back(node->key[1]);
				range_search_values(down, top, to_return, node->second);
				range_search_values(down, top, to_return, node->third);
			}
			else if (node->key[0] > top) {
				range_search_values(down, top, to_return, node->first);
			}
			else if (node->key[1] < down) {
				range_search_values(down, top, to_return, node->third);
			}
			else if (node->key[0] < down && node->key[1] > top) {
				range_search_values(down, top, to_return, node->second);
			}
		}
	}
}

void Tree_2_3::show(Node* node)
{
	if (node) {
		if (node->first) {
			show(node->first);
		}
		if (node->size > 0) {
			std::cout << node->key[0] << std::endl;
		}
		if (node->second) {
			show(node->second);
		}
		if (node->size > 1) {
			std::cout << node->key[1] << std::endl;
		}
		if (node->third) {
			show(node->third);
		}
	}
}

void Tree_2_3::action(void(*fooPointer)(point& a), Node* node)
{
	if (node) {
		if (node->first) {
			action(fooPointer, node->first);
		}
		if (node->size > 0) {
			fooPointer(node->key[0]);
		}
		if (node->second) {
			action(fooPointer, node->second);
		}
		if (node->size > 1) {
			fooPointer(node->key[1]);
		}
		if (node->third) {
			action(fooPointer, node->third);
		}
	}
}

void Tree_2_3::push_random(long long number)
{
	if (number > 0) {
		for (long long i = 0; i < number; i++) {
			push(point(number));
		}
	}
	else {
		throw ListErr("Incorrect number");
	}
}

void demomode()
{
	std::ifstream in("in.txt");
	if (in) {
		std::streambuf* cinbuf = std::cin.rdbuf();
		std::cin.rdbuf(in.rdbuf());

		commands();

		std::cin.rdbuf(cinbuf);
	}
	else {
		std::cout << "Problems with file" << std::endl;
	}
}

void benchmark()
{
	std::ofstream benchm("benchmark.txt");
	{benchm << "Linked list.\nCount\tsizeof\tpush random (count/100)\tpop back (count/100)\tpop front (count/100)\tpush 1(count/100 times)\tpush number (count/100, 1 time)\terase (count/100)\terase pos (count/100)\terase pos1 pos2\tis value (count/100)\tvalue search (count/100)\trange search values\trange search nodes\taction\n";
	clock_t start;
	clock_t finish;
	orderedListLinkedList structure;
	structure.push_random(100);
	double Time = 0;
	long long count = 100;
	while (Time < 1 && count < 100001) {
		structure.push_random(count * 8.9);
		start = clock();
		structure.push_random(count * 0.1);
		finish = clock();
		count *= 10;
		benchm << count << "\t";
		benchm << count * (sizeof(point) + 2 * sizeof(point*));
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_back();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_front();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.push(point(count / 2), count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(mersenne() % (count * 9 / 10));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		size_t num = mersenne() % (count * 9 / 10);
		structure.erase(num, num + count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		node_abstraction a({ 0,0,0 }, 0);
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			a = structure.value_search(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point b(count / 2);
		std::vector<node_abstraction>bb = structure.range_search_nodes(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	while (Time < 10 && count < 500001) {
		structure.push_random(count * 0.48);
		start = clock();
		structure.push_random(count * 0.02);
		finish = clock();
		count *= 2;
		benchm << count << "\t";
		benchm << count * (sizeof(point) + 2 * sizeof(point*));
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_back();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_front();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.push(point(count / 2), count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(mersenne() % (count * 9 / 10));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		size_t num = mersenne() % (count * 9 / 10);
		structure.erase(num, num + count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		node_abstraction a({ 0,0,0 }, 0);
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			a = structure.value_search(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point b(count / 2);
		std::vector<node_abstraction>bb = structure.range_search_nodes(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	}
	{
	benchm << "Array list.\nCount\tsizeof\tpush random (count/100)\tquick push (count/100 times)\tquick push (1 time, count/100)\tpop back (count/100)\tpop front (count/100)\tpush 1(count/100 times)\tpush number (count/100, 1 time)\terase (count/100)\terase pos (count/100)\terase pos1 pos2\tis value (count/100)\tvalue search (count/100)\trange search values\trange search nodes\taction\n";
	orderedListArrayList structure(1100000);
	structure.push_random(100);
	clock_t start;
	clock_t finish;
	double Time = 0;
	long long count = 100;
	while (Time < 1 && count < 100001) {
		structure.push_random(count * 8.7);
		start = clock();
		structure.push_random(count * 0.1);
		finish = clock();
		count *= 10;
		benchm << count << "\t";
		benchm << count * sizeof(point);
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.quick_push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.quick_push(point(count / 2), count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_back();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_front();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.push(point(count / 2), count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(mersenne() % (count * 9 / 10));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		size_t num = mersenne() % (count * 9 / 10);
		structure.erase(num, num + count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		node_abstraction a({ 0,0,0 }, 0);
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			a = structure.value_search(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point b(count / 2);
		std::vector<node_abstraction>bb = structure.range_search_nodes(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	while (Time < 10 && count < 500001) {
		structure.push_random(count * 0.44);
		start = clock();
		structure.push_random(count * 0.02);
		finish = clock();
		count *= 2;
		benchm << count << "\t";
		benchm << count * sizeof(point);
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.quick_push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.quick_push(point(count / 2), count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_back();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.pop_front();
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.push(point(count / 2), count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(mersenne() % (count * 9 / 10));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		size_t num = mersenne() % (count * 9 / 10);
		structure.erase(num, num + count / 100);
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		node_abstraction a({ 0,0,0 }, 0);
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			a = structure.value_search(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point b(count / 2);
		std::vector<node_abstraction>bb = structure.range_search_nodes(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	}
	{
		benchm << "Binary tree.\nCount\tsizeof\tpush random (count/100)\tpush 1(count/100 times)\terase (count/100)\tis value (count/100)\tvalue search (count/100)\trange search values\taction\n";
		clock_t start;
		clock_t finish;
		binaryTree structure;
		structure.push_random(100);
		double Time = 0;
		long long count = 100;
		while (Time < 1 && count < 100001) {
			structure.push_random(count * 8.9-(structure.length()-count));
			start = clock();
			structure.push_random(count * 0.1);
			finish = clock();
			count *= 10;
			benchm << count << "\t";
			benchm << count * (sizeof(point) + 2 * sizeof(point*));
			if (count < 1000000) {
				benchm << "\t\t\t";
			}
			else {
				benchm << "\t\t";
			}
			benchm << finish - start << "\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				structure.push(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				structure.erase(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if (count > structure.length()) {
				structure.push_random(count - structure.length());
			}
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				structure.is_value(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			node_abstraction a({ 0,0,0 }, 0);
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				a = structure.value_search(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			point aaa(count / 2);
			std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			structure.action(x_plus);
			finish = clock();
			benchm << finish - start << "\n";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
		}
		while (Time < 10 && count < 500001) {
			structure.push_random(count * 0.48 - (structure.length()-count));
			start = clock();
			structure.push_random(count * 0.02);
			finish = clock();
			count *= 2;
			benchm << count << "\t";
			benchm << count * (sizeof(point) + 2 * sizeof(point*));
			if (count < 1000000) {
				benchm << "\t\t\t";
			}
			else {
				benchm << "\t\t";
			}
			benchm << finish - start << "\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				structure.push(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				structure.erase(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if (count > structure.length()) {
				structure.push_random(count - structure.length());
			}
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				structure.is_value(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			node_abstraction a({ 0,0,0 }, 0);
			start = clock();
			for (long long i = 0; i < count / 100; i++) {
				a = structure.value_search(point(count / 2));
			}
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			point aaa(count / 2);
			std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
			finish = clock();
			benchm << finish - start << "\t\t\t";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
			start = clock();
			structure.action(x_plus);
			finish = clock();
			benchm << finish - start << "\n";
			if ((finish - start) / CLOCKS_PER_SEC > Time) {
				Time = (finish - start) / CLOCKS_PER_SEC;
			}
		}
	}
	{
	benchm << "AVL tree.\nCount\tsizeof\tpush random (count/100)\tpush 1(count/100 times)\terase (count/100)\tis value (count/100)\tvalue search (count/100)\trange search values\taction\n";
	clock_t start;
	clock_t finish;
	AVL_tree structure;
	structure.push_random(100);
	double Time = 0;
	long long count = 100;
	while (Time < 1 && count < 100001) {
		structure.push_random(count * 8.9 - (structure.length() - count));
		start = clock();
		structure.push_random(count * 0.1);
		finish = clock();
		count *= 10;
		benchm << count << "\t";
		benchm << count * (sizeof(point) + 2 * sizeof(point*));
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		node_abstraction a({ 0,0,0 }, 0);
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			a = structure.value_search(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	while (Time < 10 && count < 500001) {
		structure.push_random(count * 0.48 - (structure.length() - count));
		start = clock();
		structure.push_random(count * 0.02);
		finish = clock();
		count *= 2;
		benchm << count << "\t";
		benchm << count * (sizeof(point) + 2 * sizeof(point*));
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		node_abstraction a({ 0,0,0 }, 0);
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			a = structure.value_search(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	}
	{
	benchm << "2-3 tree.\nCount\tsizeof\tpush random (count/100)\tpush 1(count/100 times)\terase (count/100)\tis value (count/100)\trange search values\taction\n";
	clock_t start;
	clock_t finish;
	Tree_2_3 structure;
	structure.push_random(100);
	double Time = 0;
	long long count = 100;
	while (Time < 1 && count < 100001) {
		structure.push_random(count * 8.9 - (structure.length() - count));
		start = clock();
		structure.push_random(count * 0.1);
		finish = clock();
		count *= 10;
		benchm << count << "\t";
		benchm << count * (sizeof(point) + 2 * sizeof(point*));
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	while (Time < 10 && count < 500001) {
		structure.push_random(count * 0.48 - (structure.length() - count));
		start = clock();
		structure.push_random(count * 0.02);
		finish = clock();
		count *= 2;
		benchm << count << "\t";
		benchm << count * (sizeof(point) + 2 * sizeof(point*));
		if (count < 1000000) {
			benchm << "\t\t\t";
		}
		else {
			benchm << "\t\t";
		}
		benchm << finish - start << "\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.push(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.erase(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if (count > structure.length()) {
			structure.push_random(count - structure.length());
		}
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		for (long long i = 0; i < count / 100; i++) {
			structure.is_value(point(count / 2));
		}
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		point aaa(count / 2);
		std::vector<point>aa = structure.range_search_values(aaa, { aaa.x + count / 100,aaa.y,aaa.z });
		finish = clock();
		benchm << finish - start << "\t\t\t";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
		start = clock();
		structure.action(x_plus);
		finish = clock();
		benchm << finish - start << "\n";
		if ((finish - start) / CLOCKS_PER_SEC > Time) {
			Time = (finish - start) / CLOCKS_PER_SEC;
		}
	}
	}
	benchm.close();
}

void commands() {
	std::cout << "help for reference" << std::endl << std::endl;
	while (true) {
		std::string input;
		std::getline(std::cin, input);
		std::stringstream ss;
		ss.str(input);
		std::string part;
		std::vector<std::string> all_commands;
		while (ss >> part) all_commands.push_back(part);
		if (all_commands.size() == 1 && all_commands[0] == "help") {
			std::cout << main_help << std::endl;
		}
		else if (all_commands.size() == 1 && all_commands[0] == "demomode") {
			demomode();
		}
		else if (all_commands.size() == 1 && all_commands[0] == "benchmark") {
			benchmark();
		}
		else if (all_commands.size() == 1 && all_commands[0] == "linked") {
			commands(1, -1);
		}
		else if (all_commands.size() == 2 && all_commands[0] == "array") {
			long long argument;
			bool correct = true;
			if (is_int(all_commands[1])) {
				argument = atoi(all_commands[1].c_str());
			}
			else {
				correct = false;
				break;
			}
			if (argument < 1) {
				correct = false;
			}
			if (correct) {
				try
				{
					commands(2,argument);
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
		else if (all_commands.size() == 1 && all_commands[0] == "binary") {
			commands(3, -1);
		}
		else if (all_commands.size() == 1 && all_commands[0] == "AVL") {
			commands(4, -1);
		}
		else if (all_commands.size() == 1 && all_commands[0] == "2-3") {
			commands(5, -1);
		}
		else if (all_commands.size() == 1 && all_commands[0] == "exit") {
			std::cout << "goodby!" << std::endl;
			return;
		}
		else {
			std::cout << "Unclear command. help for reference" << std::endl;
		}
	}
}

bool is_int(const std::string& str)
{
	for (auto i : str) {
		if (i < 48 && i>57) {
			return false;
		}
	}
	return true;
}


void commands(int what_structure, long long number = -1)
{
	std::cout << "help for reference" << std::endl;
	if (what_structure == 1) {
		orderedListLinkedList structure;
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
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "front") {
				try
				{
					structure.pop_front();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "back") {
				try
				{
					structure.pop_back();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if(ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size()-1; i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				std::stringstream ss(all_commands[4]);
				long long a;
				if (!(ss >> a)) {
					correct = false;
				}
				if (correct && a>0) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]),a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a>0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
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
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
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
			else if (all_commands.size() == 3 && all_commands[0] == "erase") {
				std::stringstream ss1(all_commands[1]);
				bool correct = true;
				long long a;
				if (!(ss1 >> a)) {
					correct = false;
				}
				std::stringstream ss2(all_commands[2]);
				long long b;
				if (!(ss2 >> b)) {
					correct = false;
				}
				if (correct && a > -1 && b>-1) {
					try
					{
						structure.erase(a,b);
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
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
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
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: "<<node.position << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "nodes") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<node_abstraction> values = structure.range_search_nodes(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout <<"Position: " << values[i].position << " Value: "<< values[i].value << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
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
	else if(what_structure == 2) {
		orderedListArrayList structure(number);
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
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "front") {
				try
				{
					structure.pop_front();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "pop" && all_commands[1] == "back") {
				try
				{
					structure.pop_back();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size() - 1; i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				std::stringstream ss(all_commands[4]);
				long long a;
				if (!(ss >> a)) {
					correct = false;
				}
				if (correct && a > 0) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]), a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "quick" && all_commands[1] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.quick_push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 6 && all_commands[0] == "quick" && all_commands[1] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size() - 1; i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				std::stringstream ss(all_commands[5]);
				long long a;
				if (!(ss >> a)) {
					correct = false;
				}
				if (correct && a > 0) {
					try
					{
						structure.quick_push(point(arguments[0], arguments[1], arguments[2]), a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
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
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
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
			else if (all_commands.size() == 3 && all_commands[0] == "erase") {
				std::stringstream ss1(all_commands[1]);
				bool correct = true;
				long long a;
				if (!(ss1 >> a)) {
					correct = false;
				}
				std::stringstream ss2(all_commands[2]);
				long long b;
				if (!(ss2 >> b)) {
					correct = false;
				}
				if (correct && a > -1 && b > -1) {
					try
					{
						structure.erase(a, b);
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
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
						std::cout<< std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "nodes") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<node_abstraction> values = structure.range_search_nodes(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << "Position: " << values[i].position << " Value: " << values[i].value << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
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
	else if (what_structure == 3) {
		binaryTree structure;
		while (true) {
			std::string input;
			std::getline(std::cin, input);
			std::stringstream ss;
			ss.str(input);
			std::string part;
			std::vector<std::string> all_commands;
			while (ss >> part) all_commands.push_back(part);
			if (all_commands.size() == 1 && all_commands[0] == "help") {
				std::cout << help_answer  << std::endl;
			}
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
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
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
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
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
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
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position < 0) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
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
	else if (what_structure == 4) {
		AVL_tree structure;
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
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
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
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
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
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 2 && all_commands[0] == "show") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.show(a);
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
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
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
			else if (all_commands.size() == 5 && all_commands[0] == "value" && all_commands[1] == "search") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						node_abstraction node = structure.value_search(point(arguments[0], arguments[1], arguments[2]));
						if (node.position == -1) {
							std::cout << "This value isn't here" << std::endl;
						}
						else {
							std::cout << "Position of that value: " << node.position << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
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
	else if (what_structure == 5) {
		Tree_2_3 structure;
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
			else if (all_commands.size() == 4 && all_commands[0] == "push") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.push(point(arguments[0], arguments[1], arguments[2]));
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "push" && all_commands[1] == "random") {
				std::stringstream ss(all_commands[2]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > 0) {
					try
					{
						structure.push_random(a);
						std::cout << "Successfully added" << std::endl;
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
			else if (all_commands.size() == 4 && all_commands[0] == "erase") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 1; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						structure.erase(point(arguments[0], arguments[1], arguments[2]));
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
			else if (all_commands.size() == 2 && all_commands[0] == "erase") {
				std::stringstream ss(all_commands[1]);
				bool correct = false;
				long long a;
				if (ss >> a) {
					correct = true;
				}
				if (correct && a > -1) {
					try
					{
						structure.erase(a);
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
			else if (all_commands.size() == 1 && all_commands[0] == "show") {
				try
				{
					structure.show();
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
				}
			}
			else if (all_commands.size() == 5 && all_commands[0] == "is" && all_commands[1] == "value") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 2; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						if (structure.is_value(point(arguments[0], arguments[1], arguments[2]))) {
							std::cout << "Yes" << std::endl;
						}
						else {
							std::cout << "No" << std::endl;
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
			else if (all_commands.size() == 9 && all_commands[0] == "range" && all_commands[1] == "search" && all_commands[2] == "values") {
				std::vector<double>arguments;
				bool correct = true;
				for (size_t i = 3; i < all_commands.size(); i++) {
					std::stringstream ss(all_commands[i]);
					double a;
					if (ss >> a) {
						arguments.push_back(a);
					}
					else {
						correct = false;
						break;
					}
				}
				if (correct) {
					try
					{
						std::vector<point> values = structure.range_search_values(point(arguments[0], arguments[1], arguments[2]), point(arguments[3], arguments[4], arguments[5]));
						if (values.size() == 0) {
							std::cout << "Nothing isn't here" << std::endl;
						}
						else {
							for (size_t i = 0; i < values.size(); i++) {
								std::cout << values[i] << std::endl;
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
			else if (all_commands.size() == 3 && all_commands[0] == "action") {
				try
				{
					bool correct = true;
					if (all_commands[1] == "x") {
						if (all_commands[2] == "plus") {
							structure.action(x_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(x_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "y") {
						if (all_commands[2] == "plus") {
							structure.action(y_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(y_minus);
						}
						else {
							correct = false;
						}
					}
					else if (all_commands[1] == "z") {
						if (all_commands[2] == "plus") {
							structure.action(z_plus);
						}
						else if (all_commands[2] == "minus") {
							structure.action(z_minus);
						}
						else {
							correct = false;
						}
					}
					else {
						correct = false;
					}
					if (!correct) {
						std::cout << "Incorrect argument. help for reference" << std::endl;
					}
				}
				catch (const std::exception& ex)
				{
					std::cout << ex.what() << std::endl;
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
}

void x_plus(point& P)
{
	P.x += 1;
}

void x_minus(point& P)
{
	P.x -= 1;
}

void y_plus(point& P)
{
	P.y += 1;
}

void y_minus(point& P)
{
	P.y -= 1;
}

void z_plus(point& P)
{
	P.z += 1;
}

void z_minus(point& P)
{
	P.z -= 1;
}