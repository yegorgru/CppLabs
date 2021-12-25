#include "mainwindow.h"

#include <QApplication>

#include <vector>
#include <iostream>
#include <algorithm>

#include "Sorting.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

template <typename T>
void TestSortingBasic(Sortings::Sorting<std::vector<T>>& sorting,
                      std::function<bool (T,T)> cmp =
                    [](T x, T y) -> bool { return x < y; }){
    Sortings::DefaultVisualizer<std::vector<T>>vis;
    sorting.SetVisualizer(&vis);
    std::vector<T> v = {5,2,1,4,3};
    std::vector<T> copy_v = v;
    sorting.Sort(v.begin(), v.end(), cmp);
    std::sort(copy_v.begin(), copy_v.end(), cmp);
    CHECK(v == copy_v);
}

template <typename T>
void TestSortingRandom(Sortings::Sorting<std::vector<T>>& sorting, T number,
                       std::function<bool (T,T)> cmp =
                     [](T x, T y) -> bool { return x < y; }){
    Sortings::DefaultVisualizer<std::vector<T>>vis;
    sorting.SetVisualizer(&vis);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<T>random_v;
    for(T i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.begin(), copy_random_v.end(), cmp);
    sorting.Sort(random_v.begin(), random_v.end(), cmp);
    CHECK(random_v == copy_random_v);
}

template <typename T>
void TestSortingAlmostSorted(Sortings::Sorting<std::vector<T>>& sorting, T number,
                             std::function<bool (T,T)> cmp =
                           [](T x, T y) -> bool { return x < y; }){
    Sortings::DefaultVisualizer<std::vector<T>>vis;
    sorting.SetVisualizer(&vis);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<T>random_v;
    for(T i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.begin(), copy_random_v.end(), cmp);
    for(T i = 0; i < number/100; i++){
        std::swap(*(copy_random_v.begin() + mersenne()%copy_random_v.size()),
                  *(copy_random_v.begin() + mersenne()%copy_random_v.size()));
    }
    sorting.Sort(copy_random_v.begin(), copy_random_v.end(), cmp);

    std::sort(random_v.begin(), random_v.end(), cmp);

    CHECK(random_v == copy_random_v);
}

template <typename T>
void TestSortingAlmostReverseSorted(Sortings::Sorting<std::vector<T>>& sorting, T number,
                             std::function<bool (T,T)> cmp =
                           [](T x, T y) -> bool { return x < y; }){
    Sortings::DefaultVisualizer<std::vector<T>>vis;
    sorting.SetVisualizer(&vis);
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::vector<T>random_v;
    for(T i=0;i<number; i++){
        random_v.push_back(mersenne() % number);
    }
    auto copy_random_v = random_v;
    std::sort(copy_random_v.rbegin(), copy_random_v.rend(), cmp);
    for(T i = 0; i < number/100; i++){
        std::swap(*(copy_random_v.begin() + mersenne()%copy_random_v.size()),
                  *(copy_random_v.begin() + mersenne()%copy_random_v.size()));
    }
    sorting.Sort(copy_random_v.begin(), copy_random_v.end(), cmp);

    std::sort(random_v.begin(), random_v.end(), cmp);

    CHECK(random_v == copy_random_v);
}

template <typename T>
void TestSorting(Sortings::Sorting<std::vector<T>>& sorting, T number,
                 std::function<bool (T,T)> cmp =
               [](T x, T y) -> bool { return x < y; }){
    TestSortingBasic<T>(sorting, cmp);
    TestSortingRandom<T>(sorting,number,cmp);
    TestSortingAlmostSorted<T>(sorting, number, cmp);
    TestSortingAlmostReverseSorted<T>(sorting, number, cmp);
}

TEST_CASE("testing sortings"){
    Sortings::BubbleSort<std::vector<long>>bubble;
    TestSorting<long>(bubble, 1000);
    TestSorting<long>(bubble, 1000, [](long x, long y){return x > y;});
    Sortings::InsertionSort<std::vector<long>>insertion;
    TestSorting<long>(insertion, 1000);
    TestSorting<long>(insertion, 1000, [](long x, long y){return x > y;});
    Sortings::SelectionSort<std::vector<long>>selection;
    TestSorting<long>(selection, 1000);
    TestSorting<long>(selection, 1000, [](long x, long y){return x > y;});
    Sortings::CycleSort<std::vector<long>>cycle;
    TestSorting<long>(cycle, 1000);
    TestSorting<long>(cycle, 1000, [](long x, long y){return x > y;});

    Sortings::ShakerSort<std::vector<long>>shaker;
    TestSorting<long>(shaker, 1000);
    TestSorting<long>(shaker, 1000, [](long x, long y){return x > y;});
    Sortings::CombSort<std::vector<long>>comb;
    TestSorting<long>(comb, 1000);
    TestSorting<long>(comb, 1000, [](long x, long y){return x > y;});
    Sortings::GnomeSort<std::vector<long>>gnome;
    TestSorting<long>(gnome, 1000);
    TestSorting<long>(gnome, 1000, [](long x, long y){return x > y;});
    Sortings::OddEvenSort<std::vector<long>>oddEven;
    TestSorting<long>(oddEven, 1000);
    TestSorting<long>(oddEven, 1000, [](long x, long y){return x > y;});
    Sortings::QuickSortPivotFirst<std::vector<long>>quickFirst;
    TestSorting<long>(quickFirst, 10000);
    TestSorting<long>(quickFirst, 10000, [](long x, long y){return x > y;});
    Sortings::QuickSortPivotLast<std::vector<long>>quickLast;
    TestSorting<long>(quickLast, 10000);
    TestSorting<long>(quickLast, 10000, [](long x, long y){return x > y;});
    Sortings::QuickSortPivotMiddle<std::vector<long>>quickMiddle;
    TestSorting<long>(quickMiddle, 10000);
    TestSorting<long>(quickMiddle, 10000, [](long x, long y){return x > y;});
    Sortings::QuickSortPivotRandom<std::vector<long>>quickRandom;
    TestSorting<long>(quickRandom, 10000);
    TestSorting<long>(quickRandom, 10000, [](long x, long y){return x > y;});
    Sortings::MergeSort<std::vector<long>>merge;
    TestSorting<long>(merge, 10000);
    TestSorting<long>(merge, 10000, [](long x, long y){return x > y;});

    Sortings::HeapSort<std::vector<long>>heap;
    TestSorting<long>(heap, 10000);
    TestSorting<long>(heap, 10000, [](long x, long y){return x > y;});

    Sortings::TimSort<std::vector<long>>tim;
    TestSorting<long>(tim, 10000);
    TestSorting<long>(tim, 10000, [](long x, long y){return x > y;});

    Sortings::IntroSort<std::vector<long>>intro;
    TestSorting<long>(intro, 10000);
    TestSorting<long>(intro, 10000, [](long x, long y){return x > y;});

    Sortings::ShellSort<std::vector<long>>shell;
    TestSorting<long>(shell, 10000);
    TestSorting<long>(shell, 10000, [](long x, long y){return x > y;});

    Sortings::MergeSortInPlace<std::vector<long>>inplace;
    TestSorting<long>(inplace, 10000);
    TestSorting<long>(inplace, 10000, [](long x, long y){return x > y;});

    Sortings::PigeonholeSort<std::vector<long>>pigeonhole;
    TestSorting<long>(pigeonhole, 1000);

    Sortings::BucketSort<std::vector<long>>bucket;
    TestSorting<long>(bucket, 1000);

    Sortings::CountingSort<std::vector<long>>counting;
    TestSorting<long>(counting, 1000);

    Sortings::RadixSort<std::vector<long>>radix;
    TestSorting<long>(radix, 10000);

    Sortings::FlashSort<std::vector<long>>flash;
    TestSorting<long>(flash, 10000);

    Sortings::PancakeSort<std::vector<long>>pancake;
    TestSorting<long>(pancake, 1000);
    TestSorting<long>(pancake, 1000, [](long x, long y){return x > y;});

    Sortings::BogoSort<std::vector<long>>bogo;
    TestSorting<long>(bogo, 10);
    TestSorting<long>(bogo, 10, [](long x, long y){return x > y;});

    Sortings::StoogeSort<std::vector<long>>stooge;
    TestSorting<long>(stooge, 100);
    TestSorting<long>(stooge, 100, [](long x, long y){return x > y;});

    Sortings::SlowSort<std::vector<long>>slow;
    TestSorting<long>(slow, 100);
    TestSorting<long>(slow, 100, [](long x, long y){return x > y;});

    Sortings::TreeSort<std::vector<long>>tree;
    TestSorting<long>(tree, 100);
    TestSorting<long>(tree, 100, [](long x, long y){return x > y;});
}

/// <summary>
/// Sort Visualization
/// </summary>
int main(int argc, char *argv[])
{
    doctest::Context context;
    int res = context.run();

    QApplication a(argc, argv);
    MainWindow* w = MainWindow::Create();
    w->setWindowState(Qt::WindowMaximized);
    w->show();
    return a.exec();
}
