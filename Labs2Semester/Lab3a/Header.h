#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <random>
#include <conio.h>
extern std::mt19937 mersenne;

struct point {
	double x=0;
	double y=0;
	double z=0;
	friend bool operator>(const point& left, const point& right);
	friend bool operator<(const point& left, const point& right);
	friend bool operator==(const point& left, const point& right);
	friend bool operator>=(const point& left, const point& right);
	friend bool operator<=(const point& left, const point& right);
	friend std::ostream& operator<< (std::ostream& out, const point& point);
};

template<typename T>
void show(T* Array, size_t begin, size_t end) {
	for (size_t i = begin; i < end; i++) {
		std::cout << Array[i] << std::endl;
	}
	Sleep(5000);
}

template<typename T>
void insertion_sort(T* Array,size_t begin, size_t end, bool demo)
{
	for (size_t i = begin+1; i < end+1; i++) {
		T key = Array[i];
		size_t j= i;
		while (j > begin && Array[j-1]>key) {
			Array[j] = Array[j-1];
			j--;
		}
		Array[j] = key;
		if (demo) {
			std::cout << "\nNext step:\n";
			show(Array, begin, end+1);
			Sleep(3000);
		}
	}
}


template<typename T>
size_t partition_quicksort(T* Array, size_t begin, size_t end, bool demo) {
	begin++;
	end++;
	T pivot = Array[begin-1+ mersenne()%(end-begin)];
	size_t i = begin - 1;
	size_t j = end + 1;
	while (true) {
		do {
			i++;
		} while (Array[i-1] < pivot);
		do {
			j--;
		} while (Array[j-1] > pivot);
		if (i >= j) {
			if (demo) {
				std::cout << "\nNext step:\n";
				show(Array, begin-1, end);
			}
			return j-1;
		}
		T help = Array[i-1];
		Array[i-1] = Array[j-1];
		Array[j-1] = help;
	}
}

template<typename T>
void quicksort(T* Array, size_t begin, size_t end, bool demo)
{
	if (begin < end) {
		size_t p = partition_quicksort(Array, begin, end,demo);
		quicksort(Array, begin, p, demo);
		quicksort(Array, p + 1, end, demo);
	}	
}



template<typename T>
void copy(T* A, size_t begin, size_t end, T* B)
{
	for (size_t k = begin; k < end; k++) {
		B[k] = A[k];
	}
}

template<typename T>
void merge(T* A, size_t begin, size_t middle, size_t end, T* B, bool demo)
{
	size_t i = begin;
	size_t j = middle;
	for (size_t k = begin; k < end; k++) {
		if (i < middle && (j >= end || A[i] <= A[j])) {
			B[k] = A[i];
			i++;
		}
		else {
			B[k] = A[j];
			j++;
		}
	}
	if (demo) {
		std::cout << "\nNext step:\n";
		show(B, begin, end);
		Sleep(3000);
	}
}

template<typename T>
void split(T* B, size_t begin, size_t end, T* A, bool demo)
{
	if (end - begin < 2) {
		return;
	}
	size_t middle = (begin + end) / 2;
	split(A, begin, middle, B,demo);
	split(A, middle, end, B,demo);
	merge(B, begin, middle, end, A,demo);
}

template<typename T>
void mergesort(T* Array, size_t n, bool demo)
{
	if (n > 1) {
		T* B = new T[n];
		copy(Array, 0, n, B);
		split(B, 0, n, Array, demo);
		delete[] B;
	}
}


template <typename T>
void library_sort(T* Array,size_t n) {
	std::vector<T> vector_array(Array, Array + n);
	sort(vector_array.begin(), vector_array.end());
	for (size_t i = 0; i < n; i++) {
		Array[i] = vector_array[i];
	}
}


template <typename T>
void combined_quick_insertion_sort(T* Array, size_t begin, size_t end, int threshold,bool demo) {
	if (begin < end) {
		if ((int)(end - begin) < threshold) {
			insertion_sort(Array,begin,end, demo);
			return;
		}
		size_t p = partition_quicksort(Array, begin, end, demo);
		combined_quick_insertion_sort(Array, begin, p, threshold, demo);
		combined_quick_insertion_sort(Array, p + 1, end, threshold, demo);
	}
}


template<typename T>
void combined_split(T* B, size_t begin, size_t end, T* A,int threshold,bool demo)
{
	if ((int)(end - begin) < threshold+1) {
		insertion_sort(A, begin, end-1,demo);
		return;
	}
	size_t middle = (begin + end) / 2;
	combined_split(A, begin, middle, B, threshold,demo);
	combined_split(A, middle, end, B, threshold,demo);
	merge(B, begin, middle, end, A,demo);
}

template<typename T>
void combined_merge_insertion_sort(T* Array, size_t n,int threshold,bool demo)
{
	if (n > 1) {
		T* B = new T[n];
		copy(Array, 0, n, B);
		combined_split(B, 0, n, Array, threshold,demo);
		delete[] B;
	}
}


void main_launch();
void generate_points(point* Array, long long size);
void demomode();
void benchmark_piece(point* for_copy, int threshold, std::ofstream& benchm, void(*fooPointer1)(point* Array, size_t begin, size_t end,bool demo), void(*fooPointer2)(point* Array, size_t n, bool demo), void(*fooPointer3)(point* Array, size_t begin, size_t end, int threshold, bool demo), void(*fooPointer4)(point* Array, size_t n, int threshold, bool demo),void(*fooPointer5)(point* Array, size_t n));
void benchmark_big_piece(point* Array, int quick_threshold, int merge_threshold, std::ofstream& benchm);
void benchmark();

