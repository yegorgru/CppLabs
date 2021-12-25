/**
\file
\brief .h file with implementations of sortings
*/

#pragma once

#include <future>
#include <thread>
#include <random>
#include <vector>
#include <list>

/**
\brief class that implements quicksort sequence and parallel algorithms
*/
template <typename Iterator>
class QuickSort {
public:

    /**
    \brief class that implements partition for quicksort algorithm

    \param begin first element of range
    \param end next after last element of range
    \param pivot pivot element
    */
    static Iterator Partition(Iterator begin, Iterator end, Iterator pivot) {
        Iterator left = begin, right = end;
        while (true) {
            while (*(++left) < *begin) {
                if (left == end - 1) break;
            }
            while (*begin < *(--right)) {
                if (right == begin) break;
            }
            if (left >= right) break;
            std::swap(*left, *right);
        }
        std::swap(*begin, *right);
        return right;
    }

    /**
    \brief class that implements sequence quicksort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void Sort(Iterator begin, Iterator end) {
        if (end - begin > 1) {
            auto pivot = begin + rng()%(end-begin);
            auto p = Partition(begin, end, pivot);
            Sort(begin, p);
            Sort(p + 1, end);
        }
    }

    /**
    \brief class that implements parallel quicksort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void SortParallel(Iterator begin, Iterator end) {
        if (end - begin > 1) {
            auto pivot = begin;
            auto p = Partition(begin, end, pivot);
            if (end - begin > 5000) {
                std::future<void> f1 = std::async(std::launch::async, [begin, p]() {SortParallel(begin, p); });
                SortParallel(p + 1, end);
            }
            else {
                Sort(begin, p);
                Sort(p + 1, end);
            }
        }
    }

private:
    inline static std::mt19937 rng{ std::random_device()()};
};

/**
\brief class that implements mergesort sequence and parallel algorithms (in place available)
*/
template <typename Iterator>
class MergeSort {
public:

    /**
    \brief class that implements sequence mergesort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void Sort(Iterator begin, Iterator end) {
        if (begin < end - 1) {
            Iterator middle = begin + (end - begin) / 2;
            Sort(begin, middle);
            Sort(middle, end);
            Merge(begin, middle, end);
        }
    }

    /**
    \brief class that implements parallel mergesort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void SortParallel(Iterator begin, Iterator end) {
        if (begin < end - 1) {
            Iterator middle = begin + (end - begin) / 2;
            if (end - begin > 5000) {
                std::future<void> f1 = std::async(std::launch::async, [begin, middle]() {SortParallel(begin, middle); });
                SortParallel(middle, end);
            }
            else {
                Sort(begin, middle);
                Sort(middle, end);
            }
            Merge(begin, middle, end);
        }
    }

    /**
    \brief class that implements merge for mergesort algorithm

    \param begin first element of range
    \param middle middle element of range
    \param end next after last element of range
    */
    static void Merge(Iterator begin, Iterator middle, Iterator end) {
        using ValueType = typename std::iterator_traits<Iterator>::value_type;
        std::vector<ValueType> left(begin, middle);
        std::vector<ValueType> right(middle, end);
        Iterator i = left.begin();
        Iterator j = right.begin();
        Iterator current = begin;
        while (i < left.end() && j < right.end()) {
            if (*i < *j) {
                *current = *i;
                i++;
            }
            else {
                *current = *j;
                j++;
            }
            current++;
        }
        for (; i < left.end(); i++, current++) {
            *current = *i;
        }
        for (; j < right.end(); j++, current++) {
            *current = *j;
        }
    }

    /**
    \brief class that implements sequence mergesort algorithm in place

    \param begin first element of range
    \param end next after last element of range
    */
    static void SortInPlace(Iterator begin, Iterator end) {
        if (begin < end - 1) {
            Iterator middle = begin + (end - begin) / 2;
            SortInPlace(begin, middle);
            SortInPlace(middle, end);
            MergeInPlace(begin, middle, end);
        }
    }

    /**
    \brief class that implements parallel mergesort algorithm in place

    \param begin first element of range
    \param end next after last element of range
    */
    static void SortParallelInPlace(Iterator begin, Iterator end) {
        if (begin < end - 1) {
            Iterator middle = begin + (end - begin) / 2;
            if (end - begin > 5000) {
                std::future<void> f1 = std::async(std::launch::async, [begin, middle]() {SortParallelInPlace(begin, middle); });
                SortParallelInPlace(middle, end);
            }
            else {
                SortInPlace(begin, middle);
                SortInPlace(middle, end);
            }
            MergeInPlace(begin, middle, end);
        }
    }

    /**
    \brief class that implements merge for mergesort algorithm in place

    \param begin first element of range
    \param middle middle element of range
    \param end next after last element of range
    */
    static void MergeInPlace(Iterator begin, Iterator middle, Iterator end) {
        using ValueType = typename std::iterator_traits<Iterator>::value_type;
        Iterator begin2 = middle;
        while (begin < middle && begin2 < end) {
            if (*begin2 < *begin) {
                ValueType value = *begin2;
                Iterator cur = begin2;
                while (cur != begin) {
                    *cur = *(cur - 1);
                    cur--;
                }
                *begin = value;
                middle++;
                begin2++;
            }
            begin++;
        }
    }
};

/**
\brief class that implements slowsort sequence and parallel algorithms
*/
template <typename Iterator>
class SlowSort {
public:

    /**
    \brief class that implements sequence slowsort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void Sort(Iterator begin, Iterator end) {
        if (end - begin < 2) {
            return;
        }
        else {
            size_t middle = (end - begin) / 2;
            Sort(begin, begin + middle);
            Sort(begin + middle, end);
            end--;
            if (*end < *(begin + middle - 1)) {
                std::swap(*end, *(begin + middle - 1));
            }
            Sort(begin, end);
        }
    }

    /**
    \brief class that implements parallel slowsort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void SortParallel(Iterator begin, Iterator end) {
        if (end - begin < 50) {
            Sort(begin, end);
        }
        else {
            size_t middle = (end - begin) / 2;
            {
                std::future<void> f1 = std::async(std::launch::async, [begin, middle]() {SortParallel(begin, begin + middle); });
                SortParallel(begin + middle, end);
            }
            end--;
            if (*end < *(begin + middle - 1)) {
                std::swap(*end, *(begin + middle - 1));
            }
            SortParallel(begin, end);
        }
    }
};

/**
\brief class that implements samplesort sequence and parallel algorithms
*/
template <typename Iterator>
class SampleSort {
public:

    /**
    \brief class that implements sequence samplesort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void Sort(Iterator begin, Iterator end) {
        if (end - begin < 1000) {
            QuickSort<Iterator>::Sort(begin, end);
        }
        else {
            Iterator middle1 = begin + (end - begin) / 4;
            Iterator middle2 = begin + (end - begin) / 2;
            Iterator middle3 = begin + (end - begin) *3 / 4;
            Sort(begin, middle1);
            Sort(middle1, middle2);
            Sort(middle2, middle3);
            Sort(middle3, end);
            MergeSort<Iterator>::Merge(begin, middle1, middle2);
            MergeSort<Iterator>::Merge(middle2, middle3, end);
            MergeSort<Iterator>::Merge(begin, middle2, end);
        }
    }

    /**
    \brief class that implements parallel samplewsort algorithm

    \param begin first element of range
    \param end next after last element of range
    */
    static void SortParallel(Iterator begin, Iterator end) {
        if (end - begin < 5000) {
            Sort(begin, end);
        }
        else {
            Iterator middle1 = begin + (end - begin) / 4;
            Iterator middle2 = begin + (end - begin) / 2;
            Iterator middle3 = begin + (end - begin) * 3 / 4; 
            {
                std::future<void> f1 = std::async(std::launch::async, [begin, middle1]() {SortParallel(begin, middle1); });
                std::future<void> f2 = std::async(std::launch::async, [middle1, middle2]() {SortParallel(middle1, middle2); });
                std::future<void> f3 = std::async(std::launch::async, [middle2, middle3]() {SortParallel(middle2, middle3); });
                SortParallel(middle3, end);
            }
            MergeSort<Iterator>::Merge(begin, middle1, middle2);
            MergeSort<Iterator>::Merge(middle2, middle3, end);
            MergeSort<Iterator>::Merge(begin, middle2, end);
        }
    }
};