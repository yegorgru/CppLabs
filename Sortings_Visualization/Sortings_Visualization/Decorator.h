#pragma once

#include "SortingProxy.h"

#include <QElapsedTimer>

#include <string>


namespace Sortings{
/// <summary>
/// The class that implements the "Decorator" parser. Sortings are complemented by the time of their work and also the theoretical complexity.
/// </summary>
    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class SortingAndTiming{
    public:
        /// <summary>
        /// The constructor does only one thing: sets the SortingProxy pointer.
        /// </summary>
        SortingAndTiming(SortingProxy<std::vector<uint32_t>>*sorting):
            m_Sorting(sorting) {}

        /// <summary>
        /// The method starts sorting and measures the running time.
        /// </summary>
        /// <returns>
        ///  Returns the running time of sorting
        /// </returns>
        float Sort(SortingName name, typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
             [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }){
            time.start();
            m_Sorting->Sort(name, begin, end, cmp);
            return (float)time.nsecsElapsed()/1000000;
        }

        /// <summary>
        /// The method is used to find out the theoretical complexity of a given sort.
        /// </summary>
        /// <returns>
        ///  Returns a vector of 3 elements: the complexity of the best sort, average, and worst.
        /// </returns>
        std::vector<std::string> ComplexityCheck(Sortings::SortingName name){
            std::vector<std::string> performance;
            if ((name == Sortings::SortingName::BUBBLESORT ) || (name == Sortings::SortingName::INSERTIONSORT) ||
                    (name == Sortings::SortingName::SELECTIONSORT) || (name == Sortings::SortingName::SHAKERSORT) ||
                    (name == Sortings::SortingName::GNOMESORT) || (name == Sortings::SortingName::ODDEVENSORT) ||
                    (name == Sortings::SortingName::PANCAKESORT) )
            {
                performance.push_back("Best-case performance: O(n)");
                performance.push_back("Average performance: O(n²)");
                performance.push_back("Worst-case performance: O(n²)");
            }
            else if ( (name == Sortings::SortingName::SELECTIONSORT) ) {
                performance.push_back("Best-case performance: O(n²)");
                performance.push_back("Average performance: O(n²)");
                performance.push_back("Worst-case performance: O(n²)");
            }
            else if ( name == Sortings::SortingName::STOOGESORT ) {
                performance.push_back("Best-case performance: n^2,71");
                performance.push_back("Average performance: n^2,71");
                performance.push_back("Worst-case performance: n^2,71");
            }
            else if (name == Sortings::SortingName::COMBSORT)
            {
                performance.push_back("Best-case performance: O(n log(n))");
                performance.push_back("Average performance: O(n²/2^p)");
                performance.push_back("Worst-case performance: O(n²)");
            }
            else if ((name == Sortings::SortingName::QUICKSORTPIVOTRANDOM) ||(name == Sortings::SortingName::QUICKSORTPIVOTMIDDLE) ||(name == Sortings::SortingName::QUICKSORTPIVOTLAST) || (name == Sortings::SortingName::QUICKSORTPIVOTFIRST) || (name == Sortings::SortingName::SHELLSORT)) {
                performance.push_back("Best-case performance: O(n log(n))");
                performance.push_back("Average performance: O(n log(n))");
                performance.push_back("Worst-case performance: O(n²)");
            }
            else if (name == Sortings::SortingName::TIMSORT) {
                performance.push_back("Best-case performance: O(n)");
                performance.push_back("Average performance: O(n log(n))");
                performance.push_back("Worst-case performance: O(n log(n))");
            }
            else if (name == Sortings::SortingName::BUCKETSORT) {
                performance.push_back("Best-case performance: O(n)");
                performance.push_back("Average performance: O(n log(n))");
                performance.push_back("Worst-case performance: O(n²)");
            }
            else if ((name == Sortings::SortingName::TREESORT) || (name == Sortings::SortingName::MERGESORT) || (name == Sortings::SortingName::MERGESORTINPLACE) ||
                     (name == Sortings::SortingName::HEAPSORT) || (name == Sortings::SortingName::INTROSORT)) {
                performance.push_back("Best-case performance: O(n log(n))");
                performance.push_back("Average performance: O(n log(n))");
                performance.push_back("Worst-case performance: O(n log(n))");
            }

            else if((name == Sortings::SortingName::PIGEONHOLESORT) || (name == Sortings::SortingName::COUNTINGSORT)) {
                performance.push_back("Best-case performance: O(n + Range)");
                performance.push_back("Average performance: O(n + Range)");
                performance.push_back("Worst-case performance: O(n + Range)");
            }
            else if (name == Sortings::SortingName::RADIXSORT) {
                performance.push_back("Best-case performance: O(n * Range)");
                performance.push_back("Average performance: O(n + Range)");
                performance.push_back("Worst-case performance: O(n + Range)");
            }

            else if(name == Sortings::SortingName::FLASHSORT) {
                performance.push_back("Best-case performance: O(n)");
                performance.push_back("Average performance: O(n + Range)");
                performance.push_back("Worst-case performance: O(n²)");
            }
            else if(name == Sortings::SortingName::BOGOSORT) {
                performance.push_back("Best-case performance: O(n)");
                performance.push_back("Average performance: O((n+1)!");
                performance.push_back("Worst-case performance: O((n+1)!");
            }
            else if(name == Sortings::SortingName::SLOWSORT) {
                performance.push_back("Best-case performance: O(n^((log 2 n) / (2 + ε))");
                performance.push_back("Average performance: O(n^((log 2 n) / (2 + ε))");
                performance.push_back("Worst-case performance: O^((n(log 2 n) / (2 + ε))");
            }
            else
                performance.push_back("Unrecognised");
            return performance;
        }

    private:
        QElapsedTimer time;
        SortingProxy<std::vector<uint32_t>>*m_Sorting;
    };
}
