/**
\file
\brief .cpp file with main entry point
*/

#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <execution>
#include <fstream>

#include "Profile.h"
#include "Sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.h"

/**
\brief effective sorts tests

\note quicksort, mergesort, mergesort in place, sample sort tests
*/
TEST_CASE("testing effective sorts") {
    std::vector<long>v;
    v.reserve(100'000);
    static std::mt19937 rng{ std::random_device()() };
    static std::uniform_int_distribution<long> distr(-50'000, 50'000);
    for (long i = 0; i < 100'000; i++) {
        v.push_back(distr(rng));
    }
    auto copy_v = v;
    std::sort(copy_v.begin(), copy_v.end());
    auto almost_sorted = copy_v;
    for (int i = 0; i < 1000; i++) {
        std::swap(almost_sorted[rng() % 100'000], almost_sorted[rng() % 100'000]);
    }
    auto almost_reverse_sorted = almost_sorted;
    std::reverse(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    SUBCASE("quicksort sequence") {
        QuickSort<std::vector<long>::iterator>::Sort(v.begin(), v.end());
        QuickSort<std::vector<long>::iterator>::Sort(almost_sorted.begin(), almost_sorted.end());
        QuickSort<std::vector<long>::iterator>::Sort(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("quicksort parallel") {
        QuickSort<std::vector<long>::iterator>::SortParallel(v.begin(), v.end());
        QuickSort<std::vector<long>::iterator>::SortParallel(almost_sorted.begin(), almost_sorted.end());
        QuickSort<std::vector<long>::iterator>::SortParallel(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("mergesort sequence") {
        MergeSort<std::vector<long>::iterator>::Sort(v.begin(), v.end());
        MergeSort<std::vector<long>::iterator>::Sort(almost_sorted.begin(), almost_sorted.end());
        MergeSort<std::vector<long>::iterator>::Sort(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("mergesort parallel") {
        MergeSort<std::vector<long>::iterator>::SortParallel(v.begin(), v.end());
        MergeSort<std::vector<long>::iterator>::SortParallel(almost_sorted.begin(), almost_sorted.end());
        MergeSort<std::vector<long>::iterator>::SortParallel(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("mergesort in place sequence") {
        MergeSort<std::vector<long>::iterator>::SortInPlace(v.begin(), v.end());
        MergeSort<std::vector<long>::iterator>::SortInPlace(almost_sorted.begin(), almost_sorted.end());
        MergeSort<std::vector<long>::iterator>::SortInPlace(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("mergesort in place parallel") {
        MergeSort<std::vector<long>::iterator>::SortParallelInPlace(v.begin(), v.end());
        MergeSort<std::vector<long>::iterator>::SortParallelInPlace(almost_sorted.begin(), almost_sorted.end());
        MergeSort<std::vector<long>::iterator>::SortParallelInPlace(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("samplesort sequence") {
        SampleSort<std::vector<long>::iterator>::Sort(v.begin(), v.end());
        SampleSort<std::vector<long>::iterator>::Sort(almost_sorted.begin(), almost_sorted.end());
        SampleSort<std::vector<long>::iterator>::Sort(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("samplesort parallel") {
        SampleSort<std::vector<long>::iterator>::SortParallel(v.begin(), v.end());
        SampleSort<std::vector<long>::iterator>::SortParallel(almost_sorted.begin(), almost_sorted.end());
        SampleSort<std::vector<long>::iterator>::SortParallel(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    CHECK(almost_sorted == copy_v);
    CHECK(almost_reverse_sorted == copy_v);
    CHECK(v == copy_v);
}

/**
\brief non-effective sorts tests

\note slowsort tests
*/
TEST_CASE("testing non-effective sorts") {
    std::vector<long>v;
    v.reserve(100);
    static std::mt19937 rng{ std::random_device()() };
    static std::uniform_int_distribution<long> distr(-50'000, 50'000);
    for (long i = 0; i < 100; i++) {
        v.push_back(distr(rng));
    }
    auto copy_v = v;
    std::sort(copy_v.begin(), copy_v.end());
    auto almost_sorted = copy_v;
    for (int i = 0; i < 10; i++) {
        std::swap(almost_sorted[rng() % 100], almost_sorted[rng() % 100]);
    }
    auto almost_reverse_sorted = almost_sorted;
    std::reverse(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    SUBCASE("slowsort sequence") {
        SlowSort<std::vector<long>::iterator>::Sort(v.begin(), v.end());
        SlowSort<std::vector<long>::iterator>::Sort(almost_sorted.begin(), almost_sorted.end());
        SlowSort<std::vector<long>::iterator>::Sort(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    SUBCASE("slowsort parallel") {
        SlowSort<std::vector<long>::iterator>::SortParallel(v.begin(), v.end());
        SlowSort<std::vector<long>::iterator>::SortParallel(almost_sorted.begin(), almost_sorted.end());
        SlowSort<std::vector<long>::iterator>::SortParallel(almost_reverse_sorted.begin(), almost_reverse_sorted.end());
    }
    CHECK(almost_sorted == copy_v);
    CHECK(almost_reverse_sorted == copy_v);
    CHECK(v == copy_v);
}

/**
\brief logs durations of sequence and parallel versions of implemented sorts and std::sort

\note slowsort only for < 250 elements, merge sort in place only for < 100'000 elements
*/
void LogSortings(const std::vector<long long>& random_v) {
    std::cerr << std::endl << std::endl << "Elements: " + std::to_string(random_v.size()) << std::endl;
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("std::sort. Sequence");
        std::sort(copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("std::sort. Parallel");
        std::sort(std::execution::par, copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("QuickSort. Sequence");
        QuickSort<std::vector<long long>::iterator>::Sort(copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("QuickSort. Parallel");
        QuickSort<std::vector<long long>::iterator>::SortParallel(copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("MergeSort. Sequence");
        MergeSort<std::vector<long long>::iterator>::Sort(copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("MergeSort. Parallel");
        MergeSort<std::vector<long long>::iterator>::SortParallel(copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("SampleSort. Sequence");
        SampleSort<std::vector<long long>::iterator>::Sort(copy_r_v.begin(), copy_r_v.end());
    }
    {
        std::vector<long long> copy_r_v = random_v;
        LOG_DURATION("SampleSort. Parallel");
        SampleSort<std::vector<long long>::iterator>::SortParallel(copy_r_v.begin(), copy_r_v.end());
    }
    if (random_v.size() < 100'000) {
        {
            std::vector<long long> copy_r_v = random_v;
            LOG_DURATION("MergeSort in place. Sequence");
            MergeSort<std::vector<long long>::iterator>::SortInPlace(copy_r_v.begin(), copy_r_v.end());
        }
        {
            std::vector<long long> copy_r_v = random_v;
            LOG_DURATION("MergeSort in place. Parallel");
            MergeSort<std::vector<long long>::iterator>::SortParallelInPlace(copy_r_v.begin(), copy_r_v.end());
        }
    }
    if (random_v.size() < 250) {
        {
            std::vector<long long> copy_r_v = random_v;
            LOG_DURATION("SlowSort. Sequence");
            SlowSort<std::vector<long long>::iterator>::Sort(copy_r_v.begin(), copy_r_v.end());
        }
        {
            std::vector<long long> copy_r_v = random_v;
            LOG_DURATION("SlowSort. Parallel");
            SlowSort<std::vector<long long>::iterator>::SortParallel(copy_r_v.begin(), copy_r_v.end());
        }
    }
}

int main()
{
    doctest::Context context;
    int res = context.run();
    static std::random_device rd;
    static std::mt19937 mersenne(rd());

    std::streambuf* cerrbuf = std::cerr.rdbuf();

    std::ofstream out("benchmark.txt");

    std::cerr.rdbuf(out.rdbuf());

    std::cout << "Run sortings on random vector..." << std::endl;
    std::cerr << std::endl << std::endl << "RANDOM VECTOR" << std::endl;
    for (long long size = 100; size < 10'000'000; size *= 1.1) {
        std::vector<long long>random_v;
        random_v.reserve(size);
        for (long long i = 0; i < size; i++) {
            random_v.push_back(mersenne() % size);
        }
        LogSortings(random_v);
    }
    std::cout << "Run sortings on almost sorted vector..." << std::endl;
    std::cerr << std::endl << std::endl << "ALMOST SORTED VECTOR" << std::endl;
    for (long long size = 100; size < 1'000'000; size *= 1.1) {
        std::vector<long long>random_v;
        random_v.reserve(size);
        for (long long i = 0; i < size; i++) {
            random_v.push_back(mersenne() % size);
        }
        std::sort(random_v.begin(), random_v.end());
        for (long long i = 0; i < size / 100; i++) {
            std::swap(random_v[mersenne() % random_v.size()], random_v[mersenne() % random_v.size()]);
        }
        LogSortings(random_v);
    }
    std::cout << "Finished!" << std::endl;
    return 0;
}
