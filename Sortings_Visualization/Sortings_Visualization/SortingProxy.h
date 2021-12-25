/**
\file
\brief .h file with implementation of proxy pattern for sortings
*/

#pragma once

#include "Sorting.h"
#include "Factory.h"

namespace Sortings{

    /**
    \brief template class-implementation of sorting proxy

    \note inheritant of Sorting
    */
    template<
        typename Container,
        typename std::enable_if<HaveRandomAccessIterator<Container>::value>::type* = nullptr>
    class SortingProxy : public Sorting<Container>{
    public:

        /**
        \brief proxy ctor
        */
        SortingProxy(DefaultVisualizer<Container>* visualizer = nullptr):
            m_Sorting(new BubbleSort<Container>(visualizer)) {}

        /**
        \brief if it's necessary change sorting, than sorts

        \param name - name of sorting algorithm
        \param begin first iterator in sorted range
        \param end next after last iterator of sorted range
        \param cmp - optional function - comparator of elements, operator < by default
        */
        void Sort(Sortings::SortingName sorting, typename Container::iterator begin, typename Container::iterator end,
                  std::function<bool (
                  typename std::iterator_traits<typename Container::iterator>::value_type,
                  typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
             [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }){
            if(m_CurrentSortingName != sorting) {
                DefaultVisualizer<Container>* vis = nullptr;
                if(m_Sorting){
                    vis = m_Sorting->GetVisualizer();
                    delete m_Sorting;
                }
                m_Sorting = Factory<std::vector<uint32_t>>::CreateSorting(sorting);
                m_Sorting->SetVisualizer(vis);
                m_CurrentSortingName = sorting;
            }
            Sort(begin, end, cmp);
        }

        /**
        \brief overrides sorting's sort method
        */
        void Sort(typename Container::iterator begin, typename Container::iterator end,
                     std::function<bool (
                     typename std::iterator_traits<typename Container::iterator>::value_type,
                     typename std::iterator_traits<typename Container::iterator>::value_type)> cmp =
                [](typename std::iterator_traits<typename Container::iterator>::value_type x,
                   typename std::iterator_traits<typename Container::iterator>::value_type y) ->
                bool { return x < y; }) override{
            m_Sorting->Sort(begin, end, cmp);
        }

        /**
        \brief sets visualizer to current sorting

        \param visualizer
        */
        void SetVisualizer(DefaultVisualizer<Container>* visualizer) override{
            m_Sorting->SetVisualizer(visualizer);
        }
    protected:
        Sorting<Container>* m_Sorting;
        Sortings::SortingName m_CurrentSortingName;
    };
}
