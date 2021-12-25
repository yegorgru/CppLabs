#include "Header.h"

extern std::mt19937 mersenne;

void main_launch() {
	int what_mode = 0;
	int code;
	do {
		system("cls");
		std::cout << "What mode?\n";
		what_mode = (what_mode + 3) % 3;
		if (what_mode == 0) std::cout << "-> demo mode" << std::endl;
		else  std::cout << "   demo mode" << std::endl;
		if (what_mode == 1) std::cout << "-> benchmark" << std::endl;
		else  std::cout << "   benchmark" << std::endl;
		if (what_mode == 2) std::cout << "-> exit" << std::endl;
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
	if (what_mode == 0) {
		demomode();
		system("pause");
		main_launch();
	}
	else if (what_mode == 1) {
		benchmark();
		system("pause");
		main_launch();
	}
	else {
		std::cout << "goodby!" << std::endl;
		return;
	}
}



void demomode() {
	int* Array = new int[15];
	generate_numbers(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array, 0, 15);
	Sleep(5000);
	std::cout << "\nHeapsort :" << std::endl;
	Sleep(2000);
	heapsort(Array, 15, 1);
	Sleep(5000);
	system("cls");
	generate_numbers(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array, 0, 15);
	Sleep(5000);
	std::cout << "\nBinary tree sorting :" << std::endl;
	Sleep(2000);
	binary_tree_sort(Array, 15, 1);
	Sleep(5000);
	std::cout << "Result :" << std::endl;
	show(Array, 0, 15);
	std::cout << "Thank you for attention!" << std::endl;
	delete[] Array;
}




void benchmark_piece(int* for_copy, std::ofstream& benchm)
{
	clock_t start = 0;
	clock_t finish = 0;
	int Count = 10;
	clock_t Time = 0;
	int* Array = nullptr;
	benchm << "Heapsort:\n";
	while (Time < 500 && Count < 100001) {
		Count *= 10;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		start = clock();
		heapsort(Array, Count, 0);
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish-start << '\n';
	}
	while (Time < 10000 && Count < 500001) {
		Count *= 2;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		start = clock();
		heapsort(Array, Count, 0);
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish-start << '\n';
	}
	if (Array != nullptr) {
		delete[] Array;
		Array = nullptr;
	}
	start = 0;
	finish = 0;
	Count = 10;
	Time = 0;
	benchm << "Library heapsort:\n";
	while (Time < 500 && Count < 100001) {
		Count *= 10;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		std::vector<int> v(Array, Array + Count);
		std::make_heap(v.begin(), v.end());
		start = clock();
		std::sort_heap(v.begin(), v.end());
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish - start << '\n';
	}
	while (Time < 10000 && Count < 500001) {
		Count *= 2;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		std::vector<int> v(Array, Array + Count);
		std::make_heap(v.begin(), v.end());
		start = clock();
		std::sort_heap(v.begin(), v.end());
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish - start << '\n';
	}
	if (Array != nullptr) {
		delete[] Array;
		Array = nullptr;
	}
	start = 0;
	finish = 0;
	Count = 10;
	Time = 0;
	benchm << "Binary tree sort:\n";
	while (Time < 500 && Count < 1000) {
		Count *= 10;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		start = clock();
		binary_tree_sort(Array, Count, 0);
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish - start << '\n';
	}
	while (Time < 10000 && Count < 1000) {
		Count *= 2;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		start = clock();
		binary_tree_sort(Array, Count, 0);
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish - start << '\n';
	}
	if (Array != nullptr) {
		delete[] Array;
		Array = nullptr;
	}
	start = 0;
	finish = 0;
	Count = 10;
	Time = 0;
	benchm << "Library quicksort :\n";
	while (Time < 500 && Count < 100001) {
		Count *= 10;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		std::vector<int> vector_array(Array, Array + Count);
		start = clock();
		sort(vector_array.begin(), vector_array.end());
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish - start << '\n';
	}
	while (Time < 10000 && Count < 500001) {
		Count *= 2;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new int[Count];
		copy(for_copy, 0, Count, Array);
		std::vector<int> vector_array(Array, Array + Count);
		start = clock();
		sort(vector_array.begin(), vector_array.end());
		finish = clock();
		Time = finish - start;
		benchm << Count << "\t\t" << finish - start << '\n';
	}
	if (Array != nullptr) {
		delete[] Array;
		Array = nullptr;
	}
}

void benchmark() {
	std::cout << "In process..." << std::endl;
	std::ofstream benchm;
	benchm.open("benchmark.txt");
	benchm << "Random array\n";
	int* Array = new int[1000000];
	int* for_copy = new int[1000000];
	generate_numbers(Array, 1000000);
	copy(Array, 0, 1000000, for_copy);
	benchmark_piece(Array, benchm);




	benchm << "\nAn almost sorted array\n";
	int help;
	heapsort(Array, 1000000, 0);
	copy(Array, 0, 1000000, for_copy);
	for (int i = 0; i < 100; i++) {
		size_t swap1 = mersenne() % 1000000;
		size_t swap2 = mersenne() % 1000000;
		help = Array[swap1];
		Array[swap1] = Array[swap2];
		Array[swap2] = help;
	}
	benchmark_piece(Array, benchm);



	benchm << "\nAn array, almost sorted in the opposite direction\n";
	for (int i = 0; i < 1000000; i++) {
		Array[i] = for_copy[999999 - i];
	}
	for (int i = 0; i < 100; i++) {
		size_t swap1 = mersenne() % 1000000;
		size_t swap2 = mersenne() % 1000000;
		help = Array[swap1];
		Array[swap1] = Array[swap2];
		Array[swap2] = help;
	}
	benchmark_piece(Array, benchm);

	benchm.close();
	system("cls");
	delete[] Array;
	delete[] for_copy;
	std::cout << "Done!" << std::endl;
}

void generate_numbers(int* Array, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		Array[i] = mersenne() % size;
	}
}
