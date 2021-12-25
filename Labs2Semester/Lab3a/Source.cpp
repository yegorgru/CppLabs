#include "Header.h"

extern std::mt19937 mersenne;

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

void generate_points(point* Array,long long size) {
	for (int i = 0; i < size; i++) {
		Array[i].x = mersenne() % (2 * size)-size + (mersenne() % (2 * size) - size)*pow(10,-rand() % 4);
		Array[i].y = mersenne() % (2 * size)-size + (mersenne() % (2 * size) - size)*pow(10,-rand() % 4);
		Array[i].z = mersenne() % (2 * size)-size + (mersenne() % (2 * size) - size)*pow(10,-rand() % 4);
	}
}

void demomode() {
	srand(time(NULL));
	point* Array = new point[15];
	generate_points(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array,0, 15);
	Sleep(5000);
	std::cout << "\nInsertion sorting :" << std::endl;
	Sleep(2000);
	insertion_sort(Array, 0, 14,1);
	Sleep(5000);
	system("cls");
	generate_points(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array,0, 15);
	Sleep(5000);
	std::cout << "\nQuick sorting :" << std::endl;
	Sleep(2000);
	quicksort(Array, 0, 14,1);
	std::cout << "Result:\n";
	show(Array, 0, 15);
	Sleep(5000);
	system("cls");
	generate_points(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array, 0,15);
	Sleep(5000);
	std::cout << "\nMerge sorting :" << std::endl;
	Sleep(2000);
	mergesort(Array, 15,1);
	Sleep(5000);
	system("cls");
	generate_points(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array,0,15);
	Sleep(5000);
	std::cout << "\nArray after library sorting :" << std::endl;
	Sleep(2000);
	library_sort(Array, 15);
	show(Array, 0,15);
	Sleep(5000);
	system("cls");
	generate_points(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array,0,15);
	Sleep(5000);
	std::cout << "\nQuick-insertion combined sorting, threshold = 3 :" << std::endl;
	Sleep(2000);
	combined_quick_insertion_sort(Array, 0, 14, 3, 1);
	std::cout << "Result:\n";
	show(Array, 0, 15);
	Sleep(5000);
	system("cls");
	generate_points(Array, 15);
	std::cout << "The initial array :" << std::endl;
	Sleep(2000);
	show(Array, 0,15);
	Sleep(5000);
	std::cout << "\nMerge-insertion combined sorting , threshold = 3 :" << std::endl;
	Sleep(2000);
	combined_merge_insertion_sort(Array, 15, 3,1);
	Sleep(5000);
	system("cls");
	std::cout << "Thank you for attention!" << std::endl;
	delete[] Array;
}


void benchmark_piece(point* for_copy, int threshold, std::ofstream& benchm, void(*fooPointer1)(point* Array, size_t begin, size_t end, bool demo), void(*fooPointer2)(point* Array, size_t n, bool demo), void(*fooPointer3)(point* Array, size_t begin, size_t end, int threshold, bool demo), void(*fooPointer4)(point* Array, size_t n, int threshold, bool demo), void(*fooPointer5)(point* Array, size_t n))
{
	clock_t start=0;
	clock_t finish=0;
	int Count = 10;
	clock_t Time = 0;
	point* Array = nullptr;
	while (Time < 500 && Count < 100001) {
		Count *= 10;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new point[Count];
		copy(for_copy, 0, Count, Array);
		if (fooPointer1 != nullptr) {
			start = clock();
			fooPointer1(Array, 0, Count - 1,0);
			finish = clock();
		}
		else if (fooPointer2 != nullptr){
			start = clock();
			fooPointer2(Array, Count,0);
			finish = clock();
		}
		else if (fooPointer3 != nullptr) {
			start = clock();
			fooPointer3(Array, 0, Count - 1, threshold,0);
			finish = clock();
		}
		else if (fooPointer4 != nullptr) {
			start = clock();
			fooPointer4(Array, Count, threshold,0);
			finish = clock();
		}
		else if (fooPointer5 != nullptr) {
			start = clock();
			fooPointer5(Array, Count);
			finish = clock();
		}
		Time = finish - start;
		benchm << Count << "\t\t" << Time << '\n';
	}
	while (Time < 10000 && Count < 500001) {
		Count *= 2;
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
		}
		Array = new point[Count];
		copy(for_copy, 0, Count, Array);
		if (fooPointer1 != nullptr) {
			start = clock();
			fooPointer1(Array, 0, Count - 1,0);
			finish = clock();
		}
		else if (fooPointer2 != nullptr) {
			start = clock();
			fooPointer2(Array, Count,0);
			finish = clock();
		}
		else if (fooPointer3 != nullptr) {
			start = clock();
			fooPointer3(Array, 0, Count - 1, threshold,0);
			finish = clock();
		}
		else if (fooPointer4 != nullptr) {
			start = clock();
			fooPointer4(Array, Count, threshold,0);
			finish = clock();
		}
		Time = finish - start;
		benchm << Count << "\t\t" << Time << '\n';
	}
	if (Array != nullptr) {
		delete[] Array;
		Array = nullptr;
	}
}

void benchmark_big_piece(point* Array, int quick_threshold, int merge_threshold, std::ofstream& benchm)
{
	benchm << "Insertion sort\nCount\t\tTime (ms)\n";
	benchmark_piece(Array, 0, benchm, insertion_sort, 0, 0, 0,0);
	benchm << "Quicksort\nCount\t\tTime (ms)\n";
	benchmark_piece(Array, 0, benchm, quicksort, 0, 0, 0,0);
	benchm << "Mergesort\nCount\t\tTime (ms)\n";
	benchmark_piece(Array, 0, benchm,0, mergesort, 0, 0,0);
	benchm << "Library sort\nCount\t\tTime (ms)\n";
	benchmark_piece(Array, 0, benchm, 0, 0, 0, 0, library_sort);
	benchm << "Combined quick and insertion sort\nCount\t\tTime (ms)\n";
	benchmark_piece(Array, quick_threshold, benchm, 0, 0, combined_quick_insertion_sort, 0,0);
	benchm << "Combined merge and insertion sort\nCount\t\tTime (ms)\n";
	benchmark_piece(Array, merge_threshold, benchm, 0, 0,0, combined_merge_insertion_sort,0);
}

void benchmark()
{
	srand(time(NULL));
	clock_t start;
	clock_t finish;
	point* Array = nullptr;
	point* for_copy = nullptr;
	std::cout << "In process..."<<std::endl;
	std::ofstream benchm;
	benchm.open("benchmark.txt");
	
	int ideal_quick_threshold;
	clock_t minimal_quick_time = 10000000;

	Array = new point[100000];
	for_copy = new point[100000];
	generate_points(Array, 100000);
	copy(Array, 0, 100000, for_copy);
	benchm << "Choosing of ideal threshold for combined_quick_insertion_sort, length of array = 100000:\nThreshold\tTime\n";
	for (int i = 5; i < 71; i+=5) {
		start = clock();
		combined_quick_insertion_sort(Array, 0, 99999, i, 0);
		finish = clock();
		if ((finish - start) < minimal_quick_time) {
			ideal_quick_threshold = i;
			minimal_quick_time = finish - start;
		}
		copy(for_copy, 0, 100000, Array);
		benchm << i << "\t\t" << finish - start<<'\n';
	}
	int start_loop = ideal_quick_threshold - 4;
	minimal_quick_time = 10000000;
	for (int i = start_loop;i< start_loop+8;i++) {
		start = clock();
		combined_quick_insertion_sort(Array, 0, 99999, i, 0);
		finish = clock();
		if ((finish - start) < minimal_quick_time) {
			ideal_quick_threshold = i;
			minimal_quick_time = finish - start;
		}
		copy(for_copy, 0, 100000, Array);
		benchm << i << "\t\t" << finish - start << '\n';
	}
	benchm << "Ideal threshold for combined_quick_insertion_sort: " << ideal_quick_threshold << "\n\n";


	int ideal_merge_threshold;
	clock_t minimal_merge_time = 10000000;
	benchm << "Choosing of ideal threshold for combined_merge_insertion_sort, length of array = 100000:\nThreshold\tTime\n";
	for (int i = 5; i < 71; i += 5) {
		start = clock();
		combined_merge_insertion_sort(Array,100000, i,0);
		finish = clock();
		if ((finish - start) < minimal_merge_time) {
			ideal_merge_threshold = i;
			minimal_merge_time = finish - start;
		}
		copy(for_copy, 0, 100000, Array);
		benchm << i << "\t\t" << finish - start << '\n';
	}
	start_loop = ideal_merge_threshold - 4;
	minimal_merge_time = 10000000;
	for (int i = start_loop; i < start_loop + 8; i++) {
		start = clock();
		combined_merge_insertion_sort(Array, 100000, i,0);
		finish = clock();
		if ((finish - start) < minimal_merge_time) {
			ideal_merge_threshold = i;
			minimal_merge_time = finish - start;
		}
		copy(for_copy, 0, 100000, Array);
		benchm << i << "\t\t" << finish - start << '\n';
	}
	benchm << "Ideal threshold for combined_merge_insertion_sort: " << ideal_merge_threshold << "\n\n";
	
	delete[] Array;
	delete[] for_copy;
	Array = nullptr;
	for_copy = nullptr;

	benchm << "Random array\n";
	Array = new point[1000000];
	for_copy = new point[1000000];
	generate_points(Array, 1000000);
	copy(Array, 0, 1000000, for_copy);
	benchmark_big_piece(Array, ideal_quick_threshold, ideal_merge_threshold, benchm);


	benchm << "\nAn almost sorted array\n";
	point help;
	quicksort(Array, 0, 999999,0);
	copy(Array, 0, 1000000, for_copy);
	for (int i = 0; i < 100; i++) {
		size_t swap1 = mersenne() % 1000000;
		size_t swap2 = mersenne() % 1000000;
		help = Array[swap1];
		Array[swap1] = Array[swap2];
		Array[swap2] = help;
	}
	benchmark_big_piece(Array, ideal_quick_threshold, ideal_merge_threshold, benchm);

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
	benchmark_big_piece(Array, ideal_quick_threshold, ideal_merge_threshold, benchm);

	benchm.close();
	system("cls");
	delete[] Array;
	delete[] for_copy;
	std::cout << "Done!" << std::endl;
}