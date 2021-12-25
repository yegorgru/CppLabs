/**
\file
\brief .h file with implementation of sorting algorithms
*/

#pragma once

#include <type_traits>
#include <iterator>
#include <algorithm>
#include <functional>
#include <optional>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <random>
#include <set>

/**
\brief helps to find out what categoty iterator has
*/
template<typename Container>
using IteratorCategoryOf =
    typename std::iterator_traits<typename Container::iterator>::iterator_category;

/**
\brief helps to find out if iterator has random access iterator
*/
template<typename Container>
using HaveRandomAccessIterator =
    std::is_base_of<std::random_access_iterator_tag, IteratorCategoryOf<Container>>;

namespace Sortings{
    /**
    \brief enum for operation types in sortings
    */
    enum class Operation{
        COMPARISON = 0,
        ACCESS,
        CHANGE,
        END
    };

    /**
    \brief enum with name of every implemented sorting
    */
    enum class SortingName{
        BUBBLESORT,
        INSERTIONSORT,
        SELECTIONSORT,
        CYCLESORT,
        SHAKERSORT,
        COMBSORT,
        GNOMESORT,
        ODDEVENSORT,
        QUICKSORTPIVOTFIRST,
        QUICKSORTPIVOTLAST,
        QUICKSORTPIVOTMIDDLE,
        QUICKSORTPIVOTRANDOM,
        MERGESORT,
        MERGESORTINPLACE,
        HEAPSORT,
        TIMSORT,
        INTROSORT,
        SHELLSORT,
        PIGEONHOLESORT,
        BUCKETSORT,
        COUNTINGSORT,
        RADIXSORT,
        FLASHSORT,
        PANCAKESORT,
        BOGOSORT,
        STOOGESORT,
        SLOWSORT,
        TREESORT
    };

    /**
    \brief basic class for visualizers that can be passed in sortings
    */
    template <typename T>
    class DefaultVisualizer{
    public:
        /**
        \brief visualizes some operation in sorting

        \param operation kind of Operation
        \param first first iterator to visualize
        \param seconf optional parameter - second iterator to visualize
        \return always true in order to be able be passed in loop or if
        */
        virtual bool Visualize(Operation operation, typename T::iterator first, std::optional<typename T::iterator> second = std::nullopt){
            return true;
        }
    };

    /**
    \brief basic class of sorting

    pure virtual class
    */
    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class Sorting{
    public:

        /**
        \brief constructs
        */
        Sorting(DefaultVisualizer<Container>* visualizer = nullptr):
            visualizer(visualizer) {}

        /**
        \brief sets visualizer

        \param curVisualizer pointer on new visualizer
        \note virtual method
        */
        virtual void SetVisualizer(DefaultVisualizer<Container>* curVisualizer){
            visualizer = curVisualizer;
        }

        /**
        \brief visualizer getter

        \return pointer on current visualizer
        */
        DefaultVisualizer<Container>* GetVisualizer(){
            return visualizer;
        }

        /**
        \brief sorts given range

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \param cmp - optional function - comparator of elements, operator < by default
        */
        virtual void Sort(typename Container::iterator begin, typename Container::iterator end,
                     std::function<bool (
                     typename std::iterator_traits<typename Container::iterator>::value_type,
                     typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) = 0;
    protected:
        DefaultVisualizer<Container>* visualizer;   ///<pointer on current visualizer
    };

    /**
    \brief class that implements bubble sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BubbleSort : public Sorting<Container>{
    public:  
        BubbleSort(DefaultVisualizer<Container>* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (Iterator i = begin; i < end-1; i++){
                for (Iterator j = begin; j < end-i+begin-1; j++){
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j, j+1);
                    if (cmp(*(j + 1), *j)){
                        std::swap(*j, *(j + 1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, j, j+1);
                    }
                }
            }
        }
    };

    /**
    \brief class that implements insertion sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class InsertionSort : public Sorting<Container>{
    public:
        InsertionSort(DefaultVisualizer<Container>* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for ( Iterator i = begin+1; i < end; i++) {
                Iterator j= i;
                this->visualizer->Visualize(Operation::ACCESS, i);
                ValueType key = *i;
                while (j > begin && (this->visualizer != nullptr ?
                       this->visualizer->Visualize(Operation::COMPARISON, j-1) :true) &&
                       cmp(key,*(j-1))) {
                    *j = *(j-1);
                    if(this->visualizer) {
                        this->visualizer->Visualize(Operation::CHANGE, j);
                        this->visualizer->Visualize(Operation::ACCESS, j-1);
                    }
                    j--;
                }
                *j = key;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, j);
            }
        }
    };

    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class TreeSort : public Sorting<Container>{
    public:
        TreeSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            auto vis = this->visualizer;
            auto comp = [cmp, vis] (Iterator l, Iterator r){
                if(vis) vis->Visualize(Operation::COMPARISON, l, r);
                return cmp(*l, *r);
            };
            std::multiset<Iterator, decltype(comp)> tree(comp);
            for(auto i=begin; i < end; i++){
                tree.insert(i);
            }
            std::vector<ValueType> v;
            v.reserve(tree.size());
            for(auto i=tree.begin(); i != tree.end(); i++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, *i);
                v.push_back(**i);
            }
            for(auto i = begin; i < end; i++){
                *i = v[i-begin];
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i);
            }
        }
    };

    /**
    \brief class that implements selection sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class SelectionSort : public Sorting<Container>{
    public:
        SelectionSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (Iterator i = begin; i < end-1; i++) {
                Iterator min = i;
                for (Iterator j = i + 1; j < end; j++)
                {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j, min);
                    if (cmp(*j, *min))
                    {
                        min = j;
                        if(this->visualizer){
                            this->visualizer->Visualize(Operation::ACCESS, j);
                            this->visualizer->Visualize(Operation::CHANGE, min);
                        }
                    }
                }
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, min);
                if (min != i)
                {
                    std::swap(*i, *min);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, min);
                }
            }
        }
    };

    /**
    \brief class that implements cycle sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CycleSort : public Sorting<Container>{
    public:
        CycleSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for( Iterator i = begin; i < end - 1; i++ )
            {
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                ValueType cur = *i;
                size_t pos = i-begin;
                for( Iterator j = i + 1; j < end; j++ ){
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j);
                    if( cmp(*j,cur)){
                        pos++;
                    }
                }
                if( i-begin == pos ){
                    continue;
                }
                while((this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, begin+pos) : true) && *(begin+pos) == cur){
                    pos++;
                }
                std::swap( cur, *(begin+pos));
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+pos);
                while( i-begin != pos ){
                    pos = i-begin;
                    for( Iterator j = i + 1; j < end; j++ ){
                        if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, j);
                        if( cmp(*j, cur)) {
                            pos++;
                        }
                    }
                    while((this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, begin+pos) : true) && *(begin+pos) == cur){
                        pos++;
                    }
                    std::swap( cur, *(begin+pos) );
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+pos);
                }
            }
        }
    };

    /**
    \brief class that implements shaker sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class ShakerSort : public Sorting<Container>{
    public:
        ShakerSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            size_t border=end-begin;
            Iterator left = begin;
            Iterator right = end - 1;
            do {
                for (Iterator i = left; i < right; i++) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i+1, i);
                    if (cmp(*(i+1), *i)) {
                        std::swap(*i, *(i+1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i+1, i);
                        border=i-begin;
                    }
                }
                right=begin+border;
                for (Iterator i = right; i > left; i--) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i-1, i);
                    if (cmp(*i, *(i-1))) {
                        std::swap(*i, *(i-1));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i-1, i);
                        border=i-begin;
                    }
                }
                left=begin+border;
            } while (left < right);
        }
    };

    /**
    \brief class that implements comb sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CombSort : public Sorting<Container>{
    public:
        CombSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            const double factor = 1.2473309;
            size_t step = end-begin;
            bool swapped = true;
            while (step > 1 || swapped) {
                if (step > 1){
                    step /= factor;
                }
                swapped = false;
                for (Iterator i = begin; i + step < end; i++) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i+step, i);
                    if (cmp(*(i+step),*i)) {
                        std::swap(*i, *(i + step));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, i+step);
                        swapped = true;
                    }
                }
            }
        }
    };

    /**
    \brief class that implements gnome sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class GnomeSort : public Sorting<Container>{
    public:
        GnomeSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            Iterator i = begin+1;
            Iterator j = begin+2;
            while(i < end){
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i-1, i);
                if(cmp(*(i-1), *i)){
                    i = j;
                    j = j < end ? j+1 : j;
                }
                else{
                    std::swap(*(i-1), *i);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i-1, i);
                    i--;
                    if(i==begin){
                        i = j;
                        j = j < end ? j+1 : j;
                    }
                }
            }
        }
    };

    /**
    \brief class that implements odd even sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class OddEvenSort : public Sorting<Container>{
    public:
        OddEvenSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            for (size_t i = 0; i < end-begin; i++) {
                for (size_t j = (i % 2) ? 0 : 1; j + 1 < end-begin; j += 2) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, begin+j+1, begin+j);
                    if (cmp(*(begin+j+1), *(begin+j))) {
                        std::swap(*(begin+j+1), *(begin+j));
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+j+1, begin+j);
                    }
                }
            }
        }
    };

    /**
    \brief abstract class for quick sort algorithm

    \note Sorting inheritant
    */
    template<
            typename Container,
            typename Visualizer = DefaultVisualizer<Container>,
            typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class AbstractQuickSort : public Sorting<Container>{
    public:
        AbstractQuickSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            if (end - begin > 1){
                auto pivot = ChoosePivot(begin, end);
                auto p = Partition(begin, end, pivot, cmp);
                Sort(begin, p, cmp);
                Sort(p+1, end, cmp);
            }
        }

        /**
        \brief method that chooses pivot element

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \note pure virtual method
        */
        virtual typename  Container::iterator ChoosePivot(typename Container::iterator begin, typename Container::iterator end) = 0;

        /**
        \brief method that chooses pivot element

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \param pivot pivot element iterator
        \param cmp - optional function - comparator of elements, operator < by default
        \note virtual method
        \return iterator bound after partition
        */
        virtual typename Container::iterator Partition(typename Container::iterator begin, typename Container::iterator end,
                          typename Container::iterator pivot,
                          std::function<bool (
                          typename std::iterator_traits<typename Container::iterator>::value_type,
                          typename std::iterator_traits<typename Container::iterator>::value_type)> cmp){
            using Iterator = typename Container::iterator;
            Iterator left = begin, right = end;
            std::swap(*pivot, *begin);
            if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin, pivot);
            while(true){
                while(cmp(*(++left), *begin)){
                  if ( left == end-1) break;
                  if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, left, begin);
                }
                while (cmp(*begin, *(--right))){
                  if ( right == begin ) break;
                  if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, right, begin);
                }
                if (left >= right) break;
                std::swap(*left,*right);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, right);
            }
            std::swap(*begin,*right);
            if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, pivot, right);
            return right;
        }
    };

    /**
    \brief class that implements quicksort algorithm

    \note inheritant of AbstractQuickSort
    \note pivot - first element in range
    */
    template<
            typename Container,
            typename Visualizer = DefaultVisualizer<Container>,
            typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class QuickSortPivotFirst : public AbstractQuickSort<Container, Visualizer>{
    public:
        QuickSortPivotFirst(Visualizer* visualizer = nullptr):
            AbstractQuickSort<Container, Visualizer>(visualizer) {}

        /**
        \brief overrided method that chooses pivot

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \return begin
        */
        virtual typename Container::iterator ChoosePivot(typename Container::iterator begin, typename Container::iterator end) override {
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin);
            return begin;
        }
    };

    /**
    \brief class that implements quicksort algorithm

    \note inheritant of AbstractQuickSort
    \note pivot - random element of range
    */
    template<
            typename Container,
            typename Visualizer = DefaultVisualizer<Container>,
            typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class QuickSortPivotRandom : public AbstractQuickSort<Container, Visualizer>{
    public:
        QuickSortPivotRandom(Visualizer* visualizer = nullptr):
            AbstractQuickSort<Container, Visualizer>(visualizer),
            mersenne(rd()) {}

        /**
        \brief overrided method that chooses pivot

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \return random iterator from the rabge [begin, end)
        */
        virtual typename Container::iterator ChoosePivot(typename Container::iterator begin, typename Container::iterator end) override {
            size_t pivot = mersenne()%(end-begin);
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin+pivot);
            return begin + pivot;
        }

    private:
        std::random_device rd;
        std::mt19937 mersenne;
    };

    /**
    \brief class that implements quicksort algorithm

    \note inheritant of AbstractQuickSort
    \note pivot - last element in range
    */
    template<
            typename Container,
            typename Visualizer = DefaultVisualizer<Container>,
            typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class QuickSortPivotLast : public AbstractQuickSort<Container, Visualizer>{
    public:
        QuickSortPivotLast(Visualizer* visualizer = nullptr):
            AbstractQuickSort<Container, Visualizer>(visualizer) {}

        /**
        \brief overrided method that chooses pivot

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \return end-1
        */
        virtual typename Container::iterator ChoosePivot(typename Container::iterator begin, typename Container::iterator end) override {
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, end-1);
            return end-1;
        }
    };

    /**
    \brief class that implements quicksort algorithm

    \note inheritant of AbstractQuickSort
    \note pivot - middle element in range
    */
    template<
            typename Container,
            typename Visualizer = DefaultVisualizer<Container>,
            typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class QuickSortPivotMiddle : public AbstractQuickSort<Container, Visualizer>{
    public:
        QuickSortPivotMiddle(Visualizer* visualizer = nullptr):
            AbstractQuickSort<Container, Visualizer>(visualizer) {}

        /**
        \brief overrided method that chooses pivot

        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \return middle iterator in range [begin, end)
        */
        virtual typename Container::iterator ChoosePivot(typename Container::iterator begin, typename Container::iterator end) override {
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin + (end-begin)/2);
            return begin + (end-begin)/2;
        }
    };

    /**
    \brief abstract class for merge sort algorithm

    \note Sorting inheritant
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class AbstractMergeSort : public Sorting<Container>{
    public:
        AbstractMergeSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            if (begin < end-1) {
                Iterator middle = begin + (end - begin) / 2;
                Sort(begin , middle, cmp);
                Sort(middle, end, cmp);
                Merge(begin, middle, end, cmp);
            }
        }

        /**
        \brief method that chooses pivot element

        \param begin first iterator of first part
        \param begin first iterator of second part
        \param end next after last iterator of second part
        \param cmp - function - comparator of elements
        \note pure virtual method
        */
        virtual void Merge(typename Container::iterator begin, typename Container::iterator middle,
                   typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp) = 0;
    };

    /**
    \brief class that implements merge sort algorithm

    \note inheritant of AbstractMergeSort
    \note sorts not in place
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class MergeSort : public AbstractMergeSort<Container, Visualizer>{
    public:
        MergeSort(Visualizer* visualizer = nullptr):
            AbstractMergeSort<Container, Visualizer>(visualizer) {}

        /**
        \brief overrided merge method
        */
        void Merge(typename Container::iterator begin, typename Container::iterator middle,
                   typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp) override {
            using Iterator = typename Container::iterator;
            Container left(middle - begin);
            Container right(end - middle);
            for(Iterator i = begin, k=left.begin(); i<middle; i++, k++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                *k = *i;
            }
            for(Iterator i = middle, k=right.begin(); i<end; i++, k++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                *k = *i;
            }
            Iterator i = left.begin();
            Iterator j = right.begin();
            Iterator current = begin;
            while (i < left.end() && j < right.end()) {
                if (cmp(*i, *j)) {
                    *current = *i;
                    i++;
                } else {
                    *current = *j;
                    j++;
                }
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
                current++;
            }
            for(; i<left.end(); i++, current++){
                *current = *i;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
            }
            for(; j<right.end(); j++, current++){
                *current = *j;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
            }
        }
    };

    /**
    \brief class that implements merge sort algorithm

    \note inheritant of AbstractMergeSort
    \note sorts in place
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class MergeSortInPlace : public AbstractMergeSort<Container, Visualizer>{
    public:
        MergeSortInPlace(Visualizer* visualizer = nullptr):
            AbstractMergeSort<Container, Visualizer>(visualizer) {}

        /**
        \brief overrided merge method
        */
        void Merge(typename Container::iterator begin, typename Container::iterator middle,
                   typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            Iterator begin2 = middle;
            while (begin < middle && begin2 < end) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, begin2, begin);
                if (cmp(*begin2, *begin)) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin2);
                    ValueType value = *begin2;
                    Iterator cur = begin2;
                    while (cur != begin) {
                        if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, cur-1);
                        *cur = *(cur - 1);
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
                        cur--;
                    }
                    *begin = value;
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin);
                    middle++;
                    begin2++;
                }
                begin++;
            }
        }
    };

    /**
    \brief class that implements heap sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class HeapSort : public Sorting<Container>{
    public:
        HeapSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (Iterator i = begin + (end-begin) / 2 - 1; i >= begin; i--){
                Heapify(begin, end, i, cmp);
            }
            for (Iterator i=end-1; i>=begin; i--)
            {
                std::swap(*begin, *i);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, begin);
                Heapify(begin, i, begin, cmp);
            }
        }

    private:
        void Heapify(typename Container::iterator begin, typename Container::iterator end,
                     typename Container::iterator cur,
                     std::function<bool (
                     typename std::iterator_traits<typename Container::iterator>::value_type,
                     typename std::iterator_traits<typename Container::iterator>::value_type)> cmp)
        {
            using Iterator = typename Container::iterator;
            Iterator largest = cur;
            Iterator left = begin+2*(cur-begin) + 1;
            Iterator right = begin+2*(cur-begin) + 2;
            if (left < end &&
                (this->visualizer ?
                 this->visualizer->Visualize(Operation::COMPARISON, left, largest) : true)
                    && !cmp(*left, *largest)){
                largest = left;
            }
            if (right < end &&
               (this->visualizer ?
                this->visualizer->Visualize(Operation::COMPARISON, right, largest) : true)
                && !cmp(*right, *largest)){
                largest = right;
            }
            if (largest != cur)
            {
                std::swap(*cur, *largest);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur, largest);
                Heapify(begin, end, largest, cmp);
            }
        }
    };

    /**
    \brief class that implements tim sort algorithm, inheritant of Sorting

    \note combines merge sort and insertion sort, base for insertion sort = 32
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class TimSort : public Sorting<Container>{
    public:
        TimSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            const int RUN = 32;
            InsertionSort<Container> insertionSort(this->visualizer);
            MergeSort<Container> mergeSort(this->visualizer);
            for (Iterator i = begin; i < end; i+=RUN){
                insertionSort.Sort(i, std::min(i+RUN, end), cmp);
            }
            for (int size = RUN; size < end-begin; size *= 2) {
                for (Iterator left = begin; left < end; left += 2*size) {
                    Iterator middle = left + size;
                    Iterator right = std::min(left + 2*size, end);
                    if(middle < right){
                        mergeSort.Merge(left, middle, right, cmp);
                    }
                }
            }
        }
    };

    /**
    \brief class that implements intro sort algorithm, inheritant of Sorting

    \note combined with heap sort, base for heap sort = 32
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class IntroSort : public Sorting<Container>{
    public:
        IntroSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer),
            m_HeapSort(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            if(end - begin > 32){
                Iterator left  = begin;
                Iterator right = end;
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, left);
                Iterator pivot = left++;
                while( left != right ) {
                  if( (this->visualizer ? this->visualizer->Visualize(Operation::COMPARISON, left) : true) && cmp( *left, *pivot ) ) {
                     ++left;
                  } else {
                     while( left != --right &&
                            (this->visualizer ?
                             this->visualizer->Visualize(Operation::COMPARISON, right)
                             : true) && cmp( *pivot, *right ) );
                     std::swap( *left, *right );
                     if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, right);
                  }
                }
                --left;
                std::swap( *begin, *left );
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, left, begin);
                Sort( begin, left, cmp );
                Sort( right, end, cmp );
            }
            else{
                m_HeapSort.SetVisualizer(this->visualizer);
                m_HeapSort.Sort(begin, end, cmp);
            }
        }

    private:
        HeapSort<Container> m_HeapSort;
    };

    /**
    \brief class that implements shell sort algorithm, inheritant of Sorting
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class ShellSort : public Sorting<Container>{
    public:
        ShellSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            for (size_t gap = (end-begin)/2; gap > 0; gap /= 2){
                {
                    for (size_t i = gap; i < end-begin; i++)
                    {
                        if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin+i);
                        ValueType temp = *(begin+i);
                        size_t j;
                        for (j = i; j >= gap &&
                             (this->visualizer != nullptr ?
                                                    this->visualizer->Visualize(Operation::COMPARISON, begin + j - gap) :true)
                             && !cmp(*(begin + j - gap), temp); j -= gap){
                            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin + j - gap);
                            *(begin + j) = *(begin + j - gap);
                            if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+j);
                        }
                        *(begin + j) = temp;
                        if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin+j);
                    }
                }
            }
        }
    };

    /**
    \brief class that implements pigeonhole sort algorithm, inheritant of Sorting

    \note using cmp only for correct inheritance
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class PigeonholeSort : public Sorting<Container>{
    public:
        PigeonholeSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin);
            Iterator min = begin;
            Iterator max = begin;
            for (Iterator i = begin+1; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, min);
                if (*i < *min) min = i;
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, max);
                if (*max < *i) max = i;
            }
            size_t range = (*max > *min ? *max - *min : *min - *max) + 1;
            std::vector<ValueType>holes[range];
            for (Iterator i = begin; i < end; i++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i, min);
                if(*max > *min){
                    holes[*i - *min].push_back(*i);
                }
                else{
                    holes[*min - *i].push_back(*i);
                }
            }
            Iterator cur = begin;
            for (auto& hole:holes) {
                for (auto& item:hole){
                    *cur = item;
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
                    cur++;
                }
            }
        }
    };

    /**
    \brief class that implements bucket sort algorithm, inheritant of Sorting

    \note using cmp only for correct inheritance
    \note combined with insertion sort, base for insertion sort = 10
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BucketSort : public Sorting<Container>{
    public:
        BucketSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer),
            m_InsertionSort(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;

            if(end - begin < 11){
                m_InsertionSort.SetVisualizer(this->visualizer);
                m_InsertionSort.Sort(begin, end, cmp);
                return;
            }

            Iterator min = begin;
            Iterator max = begin;
            for (Iterator i = begin+1; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, min);
                if (*i < *min) min = i;
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, max);
                if (*max < *i) max = i;
            }

            std::vector<ValueType>buckets[end - begin + 1];

            for (Iterator i = begin; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i, max);
                size_t bi = double(*i) / *max * (end-begin);
                buckets[bi].push_back(*i);
            }

            Iterator cur = begin;
            for (std::vector<ValueType>& bucket: buckets){
                for (ValueType& item: bucket){
                    *cur = item;
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
                    cur++;
                }
            }

            cur = begin;

            for (const auto& bucket:buckets){
                Sort(cur, cur+bucket.size());
                cur+=bucket.size();
            }
        }

    private:
        InsertionSort<Container>m_InsertionSort;
    };

    /**
    \brief class that implements counting sort algorithm, inheritant of Sorting

    \note using cmp only for correct inheritance
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class CountingSort : public Sorting<Container>{
    public:
        CountingSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;

            Iterator max = begin;
            for (Iterator i = begin+1; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, max);
                if (*max < *i) max = i;
            }

            std::vector<int>count(*max + 1, 0);

            for (Iterator i = begin; i < end; i++){
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                count[*i]++;
            }

            for (size_t i = 1; i < count.size(); i++){
                count[i] += count[i - 1];
            }

            Container answer(end-begin);

            for (Iterator i = begin; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                answer[count[*i] - 1] = *i;
                count[*i]--;
            }

            for(Iterator cur = begin, a = answer.begin(); cur < end; cur++, a++){
                *cur = *a;
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, cur);
            }
        }
    };

    /**
    \brief class that implements radix sort algorithm, inheritant of Sorting

    \note using cmp only for correct inheritance
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class RadixSort : public Sorting<Container>{
    public:
        RadixSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            if(begin > end-2){
                return;
            }
            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;
            int m, p = 1;
            ValueType max = *begin;
            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin);
            for(Iterator i = begin+1; i < end; i++){
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i);
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                if(max < *i){
                    max = *i;
                }
            }

            int maxDigit = 0;
            while(max > 0){
                max/=10;
                maxDigit++;
            }

            std::list<ValueType> pocket[10];
            for(size_t i = 0; i < maxDigit; i++) {
               m = std::pow(10, i+1);
               p = pow(10, i);
               for(Iterator j = begin; j<end; j++) {
                   if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, j);
                   ValueType temp = *j%m;
                   size_t index = temp/p;
                   pocket[index].push_back(*j);
               }
               Iterator current = begin;
               for(size_t j = 0; j<10; j++) {
                  while(!pocket[j].empty()) {
                      *current = *(pocket[j].begin());
                      if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, current);
                      pocket[j].erase(pocket[j].begin());
                      current++;
                  }
               }
            }
        }
    };

    /**
    \brief class that implements flash sort algorithm, inheritant of Sorting

    \note using cmp only for correct inheritance
    \note combined with insertion sort, base for it = 32
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class FlashSort : public Sorting<Container>{
    public:
        FlashSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer),
            m_InsertionSort(visualizer) {}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {

            using Iterator = typename Container::iterator;
            using ValueType = typename std::iterator_traits<typename Container::iterator>::value_type;

            if(begin > end-2){
                return;
            }

            if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin);
            ValueType min = *begin;
            ValueType max = *begin;
            Iterator maxIt = begin;

            for(Iterator i = begin+1; i < end; i++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i);
                if(*i > max) {
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                    max = *i;
                    maxIt = i;
                }
                if(*i < min){
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, i);
                    min = *i;
                }
            }

            if(max == min) return;

            size_t m = (end-begin)/5 + 2;

            std::vector<int> L(m+1,0);

            double c = (m-1.0)/(max-min);
            size_t K;
            for(Iterator h=begin; h < end; h++) {
                if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, h);
                K = ((int)(((*h)-min)*c))+1;
                L[K]++;
            }

            for(K = 2; K < m+1; K++) {
                L[K] = L[K] + L[K-1];
            }

            std::swap(*maxIt, *begin);
            if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, maxIt, begin);

            int j = 0;
            K = m;
            size_t movesCounter = 0;

            while(movesCounter < end-begin) {
                while(j >= L[K]) {
                    j++;
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, begin+j);
                    K = ((int)((*(begin+j) - min) * c)) + 1;
                }

                Iterator evicted = begin+j;

                while(j < L[K])	{
                    if(this->visualizer) this->visualizer->Visualize(Operation::ACCESS, evicted);
                    K = size_t((*evicted-min)*c)+1;

                    int location = L[K] - 1;

                    std::swap(*(begin+location), *evicted);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, evicted, begin+location);

                    L[K]--;

                    movesCounter++;
                }
            }

            size_t threshold = (int)(1.25*(((end-begin)/m)+1));

            for(K = m - 1; K >= 1; K--) {
                int classSize = L[K+1] - L[K];

                if(classSize > threshold && classSize > 32) {
                    Sort(begin+L[K],begin+L[K]+classSize);
                } else if(classSize > 1){
                    m_InsertionSort.SetVisualizer(this->visualizer);
                    m_InsertionSort.Sort(begin+L[K],begin+L[K]+classSize);
                }
            }
        }

    private:
        InsertionSort<Container> m_InsertionSort;
    }; 

    /**
    \brief class that implements pancake sort algorithm, inheritant of Sorting

    \note try to minimize flips, not comparisons
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class PancakeSort : public Sorting<Container>{
    public:
        PancakeSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            using Iterator = typename Container::iterator;
            for (size_t curSize = end-begin; curSize > 1; curSize--) {
                size_t maxId = 0;

                for(Iterator it = begin; it < begin + curSize;it++){
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, begin + maxId, it);
                    if(cmp(*(begin + maxId), *it)){
                        maxId = it-begin;
                    }
                }

                if (maxId != curSize-1){
                    Flip(begin, begin+maxId+1);
                    Flip(begin, begin+curSize);
                }
            }
        }

    private:
        void Flip(typename Container::iterator begin, typename Container::iterator end) {
            size_t start = 0;
            size_t i = end-begin-1;
            while (start < i) {
                std::swap(*(begin+start),*(begin+i));
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin + start, begin+i);
                start++;
                i--;
            }
        }
    };

    /**
    \brief class that implements bogo sort algorithm, inheritant of Sorting

    \note very slow
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class BogoSort : public Sorting<Container>{
    public:
        BogoSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            if(IsSorted(begin, end, cmp)){
                return;
            }
            while (NextPermutation(begin, end)) {
                if(IsSorted(begin, end, cmp)){
                    return;
                }
            }
        }

    private:
        bool NextPermutation(typename Container::iterator begin, typename Container::iterator end) {
            using Iterator = typename Container::iterator;
            if (begin == end) return false;
            Iterator i = end;
            if (begin == --i) return false;

            while (true) {
                Iterator i1, i2;

                i1 = i;
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, i1);
                if (*--i < *i1) {
                    i2 = end;
                    while (!(*i < *--i2)){
                        if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, i2);
                    }
                    if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, i, i2);
                    std::swap(*i, *i2);
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, i, i2);
                    Reverse(i1, end);
                    return true;
                }
                if (i == begin) {
                    Reverse(begin, end);
                    return false;
                }
            }
        }

        void Reverse(typename Container::iterator begin, typename Container::iterator end)
        {
            while ((begin != end) && (begin != --end)) {
                std::swap(*begin, *end);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, begin, end);
                begin++;
            }
        }

        bool IsSorted(typename Container::iterator begin, typename Container::iterator end,
                      std::function<bool (
                      typename std::iterator_traits<typename Container::iterator>::value_type,
                      typename std::iterator_traits<typename Container::iterator>::value_type)> cmp){
            using Iterator = typename Container::iterator;
            if (begin < end) {
                Iterator next = begin;
                while (++next != end) {
                    if ((this->visualizer != nullptr ?
                         this->visualizer->Visualize(Operation::COMPARISON, next, begin) : true)
                            && cmp(*next, *begin)){
                        return false;
                    }
                    begin = next;
                }
            }
            return true;
        }
    };

    /**
    \brief class that implements stooge sort algorithm, inheritant of Sorting

    \note slow algorithm
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class StoogeSort : public Sorting<Container>{
    public:
        StoogeSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            size_t temp;
            if(end-begin > 2) {
                temp = (end-begin)/3;
                Sort(begin, end-temp, cmp);
                Sort(begin+temp, end, cmp);
                Sort(begin, end-temp, cmp);
            }
            if(cmp(*(--end), *begin)) {
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, end, begin);
                std::swap(*end, *begin);
                if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, end, begin);
            }
            if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, end, begin);
        }
    };

    /**
    \brief class that implements slow sort algorithm, inheritant of Sorting

    \note it's really slow:)
    */
    template<
        typename Container,
        typename Visualizer = DefaultVisualizer<Container>,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class SlowSort : public Sorting<Container>{
    public:
        SlowSort(Visualizer* visualizer = nullptr):
            Sorting<Container>(visualizer){}

        void Sort(typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override {
            if (end - begin < 2){
                return;
            }
            else{
                size_t middle = (end-begin)/2;
                Sort(begin, begin + middle, cmp);
                Sort(begin + middle, end, cmp);
                end--;
                if(this->visualizer) this->visualizer->Visualize(Operation::COMPARISON, end, begin+middle-1);
                if(cmp(*end, *(begin+middle-1))){
                    std::swap(*end, *(begin+middle-1));
                    if(this->visualizer) this->visualizer->Visualize(Operation::CHANGE, end, begin+middle-1);
                }
                Sort(begin, end, cmp);
            }
        }
    };
}
