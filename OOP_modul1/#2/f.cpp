#include <iostream>
#include <cstdint>
#include <cmath>
#include <string>
#include <utility>
#include <list>
#include <vector>
#include <map>
#include <set>

#include "TestFramework.h"

//Використав: https://stackoverflow.com/questions/12042824/how-to-write-a-type-trait-is-container-or-is-vector
template<typename T, typename _ = void>
struct is_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_container<
    T,
    std::conditional_t<
    false,
    is_container_helper<
    typename T::value_type,
    typename T::size_type,
    typename T::allocator_type,
    typename T::iterator,
    typename T::const_iterator,
    decltype(std::declval<T>().size()),
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end()),
    decltype(std::declval<T>().cbegin()),
    decltype(std::declval<T>().cend())
    >,
    void
    >
> : public std::true_type{};

template <typename T>
struct is_string
    :public
    std::is_same<std::string, typename std::decay<T>::type> {

};

//дефолтна функція
template <typename T, std::enable_if_t<!is_container<T>::value, int> = 0>
double f(T x) {
    return 12.35;
}

//специфікація для int
template<> double f<int>(int n) {
    if (n > 0) {
        return std::cos(5 * n + 135);
    }
    else if (n < 0) {
        return std::log10(std::abs(std::pow(n, 5) + 235));
    }
    else {
        return 12.35;
    }
}

//специфікація для uint64_t
template <> double f<uint64_t>(uint64_t n) {
    if (n > 0) {
        return std::cos(5 * n + 135);
    }
    else {
        return 12.35;
    }
}

//специфікація для int64_t
template <> double f<int64_t>(int64_t n) {
    if (n > 0) {
        return std::cos(5 * n + 135);
    }
    else if (n < 0) {
        return std::log10(std::abs(std::pow(n, 5) + 235));
    }
    else {
        return 12.35;
    }
}

//специфікація для uint32_t
template <> double f<uint32_t>(uint32_t n) {
    if (n > 0) {
        return std::cos(5 * n + 135);
    }
    else {
        return 12.35;
    }
}

//специфікація для uint16_t
template <> double f<uint16_t>(uint16_t n) {
    if (n > 0) {
        return std::cos(5 * n + 135);
    }
    else {
        return 12.35;
    }
}

//специфікація для int16_t
template <> double f<int16_t>(int16_t n) {
    if (n > 0) {
        return std::cos(5 * n + 135);
    }
    else if (n < 0) {
        return std::log10(std::abs(std::pow(n, 5) + 235));
    }
    else {
        return 12.35;
    }
}

////специфікація для double
template <> double f<double>(double d) {
    return d / (d - 335);
}

//специфікація для float
template <> double f<float>(float d) {
    return f(double(d));
}

//специфікація для char*
template <> double f<char*>(char* s) {
    size_t number = 0;
    size_t pos = 0;
    while (pos != strlen(s)) {
        if (s[pos] > 64 && s[pos] < 91 || s[pos] > 96 && s[pos] < 123) {
            number++;
        }
    }
    if (pos == 0) {
        return 0.0;
    }
    else {
        return std::pow((double)number / pos, 3);
    }
}

//специфікація для const char*
template <> double f<const char*>(const char* s) {
    size_t number = 0;
    size_t pos = 0;
    for(;pos<strlen(s);pos++){
        if (s[pos] > 64 && s[pos] < 91 || s[pos] > 96 && s[pos] < 123) {
            number++;
        }
    }
    if (pos == 0) {
        return 0.0;
    }
    else {
        return std::pow((double)number / pos, 3);
    }
}

//для std::string
template <typename T, std::enable_if_t<is_container<T>::value && is_string<T>::value, int> = 0>
double f(T s) {
    size_t number = 0;
    for (char ch : s) {
        if (ch > 64 && ch < 91 || ch>96 && ch < 123) {
            number++;
        }
    }
    if (s.size() == 0) {
        return 0.0;
    }
    else {
        return std::pow((double)number / s.size(), 3);
    }
}

template <typename Container, std::enable_if_t<is_container<Container>::value && !is_string<Container>::value, int> = 0>
double f(Container l);

//для пари
template <typename a, typename b>
double f(std::pair<a, b> p) {
    return std::pow(f(p.second), std::sin(535 * f(p.first)));
}

//для пари
template <typename a, typename b>
double f(std::pair<const a, const b> p) {
    return std::pow(f(p.second), std::sin(535 * f(p.first)));
}

//для пари
template <typename a, typename b>
double f(std::pair<const a, b> p) {
    return std::pow(f(p.second), std::sin(535 * f(p.first)));
}

//для пари
template <typename a, typename b>
double f(std::pair<a, const b> p) {
    return std::pow(f(p.second), std::sin(535 * f(p.first)));
}

//для контейнерів крім std::string
template <typename Container,std::enable_if_t<is_container<Container>::value && !is_string<Container>::value, int> = 0>
double f(Container l) {
    if (l.size() == 0) {
        return 0.0;
    }
    auto it = l.begin();
    double max = f(std::sin(f(*it) - 735));
    while (it != l.end()) {
        double check = f(std::sin(f(*it) - 735));
        if (max < check) {
            max = check;
        }
        it++;
    }
    return max;
}


void Tests()
{
    {
        //дефолт
        char ch = 'a';
        ASSERT_EQUAL(f(ch), 12.35);
    }
    {
        //int
        ASSERT_EQUAL(f(5), std::cos(5 * 5 + 135));
        ASSERT_EQUAL(f(-5), std::log10(std::abs(std::pow(-5, 5) + 235)));
    }
    {
        //інші цілі типи
        ASSERT_EQUAL(f((uint64_t)6), std::cos(5 * 6 + 135));
        ASSERT_EQUAL(f((int64_t)7), std::cos(5 * 7 + 135));
        ASSERT_EQUAL(f(int64_t(-8)), std::log10(std::abs(std::pow(-8, 5) + 235)));

        ASSERT_EQUAL(f((uint32_t)9), std::cos(5 * 9 + 135));

        ASSERT_EQUAL(f((uint16_t)9), std::cos(5 * 9 + 135));
        ASSERT_EQUAL(f((int16_t)10), std::cos(5 * 10 + 135));
        ASSERT_EQUAL(f(int16_t(-11)), std::log10(std::abs(std::pow(-11, 5) + 235)));
    }
    {
        //дійсні
        ASSERT_EQUAL(f(6.5), 6.5 / (6.5 - 335));
        ASSERT_EQUAL(f(-6.5), -6.5 / (-6.5 - 335));
        ASSERT_EQUAL(f(double(7.5)), 7.5 / (7.5 - 335));
        ASSERT_EQUAL(f(double(-7.5)), -7.5 / (-7.5 - 335));
        ASSERT_EQUAL(f(float(8.5)), 8.5 / (8.5 - 335));
        ASSERT_EQUAL(f(float(-8.5)), -8.5 / (-8.5 - 335));
    }
    {
        //рядки
        ASSERT_EQUAL(f("abc"), 1);
        ASSERT_EQUAL(f(std::string("abc")), 1);
        ASSERT_EQUAL(f("a!b!c!"), 0.125);
        ASSERT_EQUAL(f(std::string("a!b!c!")), 0.125);
        ASSERT_EQUAL(f("a!b!c"), std::pow(0.6,3));
        ASSERT_EQUAL(f(std::string("a!b!c")), std::pow(0.6, 3));
        ASSERT_EQUAL(f("!"), 0.0);
        ASSERT_EQUAL(f(std::string("!")), 0.0);
    }
    {
        //пари
        ASSERT_EQUAL(f(std::pair<int, int>{1, 2}), std::pow(f(2), std::sin(535 * f(1))));
        ASSERT_EQUAL(f(std::pair<double,std::string>{5.6, "!a"}), std::pow(f(std::string("!a")), std::sin(535 * f(5.6))));
    }
    //контейнери
    {
        std::vector<int>v{1,2,3,4,5};
        double max = f(std::sin(f(1) - 735));
        for (size_t i = 0;i<5;i++) {
            double check = f(std::sin(f(v[i]) - 735));
            if (max < check) {
                max = check;
            }
        }
        ASSERT_EQUAL(f(v), max);
    }
    {
        std::list<int>v{ 1,2,3,4,5 };
        double max = f(std::sin(f(1) - 735));
        for (auto it = v.begin(); it !=v.end(); it++) {
            double check = f(std::sin(f(*it) - 735));
            if (max < check) {
                max = check;
            }
        }
        ASSERT_EQUAL(f(v), max);
    }
    {
        std::set<int>v{ 1,2,3,4,5 };
        double max = f(std::sin(f(1) - 735));
        for (auto it = v.begin(); it != v.end(); it++) {
            double check = f(std::sin(f(*it) - 735));
            if (max < check) {
                max = check;
            }
        }
        ASSERT_EQUAL(f(v), max);
    }
    {
        std::map<double,std::string>v{ {1.4,"f"},{2.2,"43"},{3.1,"!!!d"},{56.0,"gg##"},{5.4,""} };
        double max = f(std::sin(f(std::pair<double, std::string>{1.4, "f"}) - 735));
        for (auto it = v.begin(); it != v.end(); it++) {
            double check = f(std::sin(f(*it) - 735));
            if (max < check) {
                max = check;
            }
        }
        ASSERT_EQUAL(f(v), max);
    }
}

int main()
{
    //запуск тестів
    TestRunner tr;
    RUN_TEST(tr, Tests);
}