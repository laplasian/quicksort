#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <random>
#include <array>

// В зависимости от макроса, заданного в CMake, подключаем нужную реализацию
#if defined(USE_CONCEPTS)
    #include "quicksort.h"
#else
    #include "quicksort_SFINAE.h"
#endif

struct Person {
    std::string name;
    int age;

    bool operator<(const Person& other) const {
        return age < other.age;
    }
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << "{" << p.name << ", " << p.age << "}";
    }
};

// Создаем параметризованный тестовый набор
template <typename T>
class QuicksortTypedTest : public ::testing::Test {};

// Определяем типы, которые будут использоваться в тестах
using MyTypes = ::testing::Types<char, unsigned char, short, unsigned short, int, unsigned int, long, float, double>;
TYPED_TEST_SUITE(QuicksortTypedTest, MyTypes);

// Тесты, которые будут запущены для каждого типа из MyTypes
TYPED_TEST(QuicksortTypedTest, General) {
    std::vector<TypeParam> vec = {8, 2, 5, 3, 9, 4, 7, 6, 1};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, AlreadySorted) {
    std::vector<TypeParam> vec = {1, 2, 3, 4, 5, 6};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, ReverseSorted) {
    std::vector<TypeParam> vec = {10, 9, 8, 7, 6};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, WithDuplicates) {
    std::vector<TypeParam> vec = {5, 2, 8, 2, 5, 5, 9, 8};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, AllSame) {
    std::vector<TypeParam> vec = {7, 7, 7, 7, 7};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, Empty) {
    std::vector<TypeParam> vec = {};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, SingleElement) {
    std::vector<TypeParam> vec = {42};
    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, SortDescending) {
    std::vector<TypeParam> vec = {8, 2, 5, 3, 9, 4, 7, 6, 1};
    quicksort::sort(vec.begin(), vec.end(), std::greater<TypeParam>());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end(), std::greater<TypeParam>()));
}

TYPED_TEST(QuicksortTypedTest, CArray) {
    std::array<int,10> vec = {8, 2, 5, 3, 9, 4, 7, 6, 1};
    quicksort::sort(vec.begin(), vec.end(), std::greater<TypeParam>());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end(), std::greater<TypeParam>()));
}

TEST(QuicksortRandomTest, RandomAccessWithRandomData) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-1000, 1000);

    std::vector<int> vec(5000);
    for(int& i : vec) {
        i = distrib(gen);
    }

    quicksort::sort(vec.begin(), vec.end());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}


TEST(QuicksortCustomTypeTest, SortPeopleByAge) {
    std::vector<Person> people = {
        {"Eve", 30},
        {"Alice", 25},
        {"Charlie", 35},
        {"Bob", 20}
    };

    auto by_age = [](const Person& a, const Person& b) {
        return a.age < b.age;
    };

    quicksort::sort(people.begin(), people.end(), by_age);
    ASSERT_TRUE(std::is_sorted(people.begin(), people.end(), by_age));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}