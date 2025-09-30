#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <random>
#include <array>
#include <deque>


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
};

template <typename T>
class QuicksortTypedTest : public ::testing::Test {};

#define GENERATE_CONTAINER_TYPES(CONTAINER) \
CONTAINER<char>, CONTAINER<unsigned char>, CONTAINER<short>, \
CONTAINER<unsigned short>, CONTAINER<int>, CONTAINER<unsigned int>, \
CONTAINER<long>, CONTAINER<float>, CONTAINER<double>

template<class Typeparam>
using Array =  std::array<Typeparam, 11>;

using MyTypes = ::testing::Types<
    GENERATE_CONTAINER_TYPES(std::vector),
    GENERATE_CONTAINER_TYPES(Array),
    GENERATE_CONTAINER_TYPES(std::deque)
>;
TYPED_TEST_CASE(QuicksortTypedTest, MyTypes);

TYPED_TEST(QuicksortTypedTest, General) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec;

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'N','O','V','O','S','I','B','I','R','S','K'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {5, 2, 8, 3, 9, 4, 7, 6, 1};
    } else if constexpr (std::is_same_v<paramtype, int>) {
        vec = {255, 2, 13, 144, 9, 4, 55, 6, 1};
    } else if constexpr (std::is_same_v<paramtype, unsigned int>) {
        vec = {500, 2, 13, 144, 9, 4, 77, 6, 1};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {5L, 2L, 8L, 3L, 9L, 4L, 7L, 6L, 1L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {5.5f, 2.2f, 8.8f, 3.3f, 9.9f, 4.4f, 7.7f, 6.6f, 1.1f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {5.5, 2.2, 8.8, 3.3, 9.9, 4.4, 7.7, 6.6, 1.1};
    }
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, AlreadySorted) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'a', 'b', 'c', 'd', 'e'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {1, 2, 3, 4, 5, 6};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {10, 20, 30, 40, 50};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {100L, 200L, 300L, 400L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {1.1, 2.2, 3.3, 4.4, 5.5};
    }
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, ReverseSorted) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'z', 'y', 'x', 'w'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {10, 9, 8, 7, 6};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {50, 40, 30, 20, 10};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {400L, 300L, 200L, 100L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {5.5f, 4.4f, 3.3f, 2.2f, 1.1f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {5.5, 4.4, 3.3, 2.2, 1.1};
    }
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, WithDuplicates) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'d', 'a', 'd', 'c', 'a', 'b'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {5, 2, 8, 2, 5, 5, 9, 8};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {10, 20, 10, 30, 20, 10};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {100L, 200L, 100L, 300L, 200L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {5.5f, 2.2f, 8.8f, 2.2f, 5.5f, 5.5f, 9.9f, 8.8f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {5.5, 2.2, 8.8, 2.2, 5.5, 5.5, 9.9, 8.8};
    }
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, AllSame) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'k', 'k', 'k', 'k', 'k'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {7, 7, 7, 7, 7};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {77, 77, 77, 77, 77};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {777L, 777L, 777L, 777L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {7.7f, 7.7f, 7.7f, 7.7f, 7.7f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {7.7, 7.7, 7.7, 7.7, 7.7};
    }
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, Empty) {
    std::vector<TypeParam> vec; // Инициализация пустого вектора одинакова для всех типов
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, SingleElement) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'X'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {42};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {42};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {42L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {42.42f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {42.42};
    }
    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, SortDescending) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'h', 'b', 'e', 'c', 'i', 'd', 'g', 'f', 'a'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {8, 2, 5, 3, 9, 4, 7, 6, 1};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {80, 20, 50, 30, 90, 40, 70, 60, 10};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {8L, 2L, 5L, 3L, 9L, 4L, 7L, 6L, 1L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {8.8f, 2.2f, 5.5f, 3.3f, 9.9f, 4.4f, 7.7f, 6.6f, 1.1f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {8.8, 2.2, 5.5, 3.3, 9.9, 4.4, 7.7, 6.6, 1.1};
    }
    quicksort::sort(vec.begin(), vec.end(), std::greater<paramtype>());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end(), std::greater<>()));
}

TYPED_TEST(QuicksortTypedTest, CArray) {
    using paramtype = typename TypeParam::value_type;
    TypeParam vec {};

    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        vec = {'h', 'b', 'e', 'c', 'i', 'd', 'g', 'f', 'a'};
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        vec = {8, 2, 5, 3, 9, 4, 7, 6, 1};
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        vec = {80, 20, 50, 30, 90, 40, 70, 60, 10};
    } else if constexpr (std::is_same_v<paramtype, long>) {
        vec = {8L, 2L, 5L, 3L, 9L, 4L, 7L, 6L, 1L};
    } else if constexpr (std::is_same_v<paramtype, float>) {
        vec = {8.8f, 2.2f, 5.5f, 3.3f, 9.9f, 4.4f, 7.7f, 6.6f, 1.1f};
    } else if constexpr (std::is_same_v<paramtype, double>) {
        vec = {8.8, 2.2, 5.5, 3.3, 9.9, 4.4, 7.7, 6.6, 1.1};
    }
    quicksort::sort(vec.begin(), vec.end(), [](auto a, auto b) {return a > b;});
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end(), std::greater<paramtype>()));
}

TEST(QuicksortRandomTest, RandomAccessWithRandomData) {
    std::default_random_engine gen(123);
    std::uniform_int_distribution<> distrib(-1000, 1000);

    std::vector<int> vec(5000);
    for(int& i : vec) {
        i = distrib(gen);
    }

    quicksort::sort(vec.begin(), vec.end());
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TYPED_TEST(QuicksortTypedTest, CStyleArray) {
    using paramtype = typename TypeParam::value_type;
    paramtype arr[9] = {};
    if constexpr (std::is_same_v<paramtype, char> || std::is_same_v<paramtype, unsigned char>) {
        paramtype arr_[9] = {'h', 'b', 'e', 'c', 'i', 'd', 'g', 'f', 'a'};
        memcpy(arr, arr_, sizeof(arr));
    } else if constexpr (std::is_same_v<paramtype, short> || std::is_same_v<paramtype, unsigned short>) {
        paramtype arr_[9] = {8, 2, 5, 3, 9, 4, 7, 6, 1};
        memcpy(arr, arr_, sizeof(arr));
    } else if constexpr (std::is_same_v<paramtype, int> || std::is_same_v<paramtype, unsigned int>) {
        paramtype arr_[9] = {80, 20, 50, 30, 90, 40, 70, 60, 10};
        memcpy(arr, arr_, sizeof(arr));
    } else if constexpr (std::is_same_v<paramtype, long>) {
        paramtype arr_[9] = {8L, 2L, 5L, 3L, 9L, 4L, 7L, 6L, 1L};
        memcpy(arr, arr_, sizeof(arr));
    } else if constexpr (std::is_same_v<paramtype, float>) {
        paramtype arr_[9] = {8.8f, 2.2f, 5.5f, 3.3f, 9.9f, 4.4f, 7.7f, 6.6f, 1.1f};
        memcpy(arr, arr_, sizeof(arr));
    } else if constexpr (std::is_same_v<paramtype, double>) {
        paramtype arr_[9] = {8.8, 2.2, 5.5, 3.3, 9.9, 4.4, 7.7, 6.6, 1.1};
        memcpy(arr, arr_, sizeof(arr));
    }

    quicksort::sort(std::begin(arr), std::end(arr), std::less<>());
    EXPECT_TRUE(std::is_sorted(std::begin(arr), std::end(arr)));
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
    EXPECT_TRUE(std::is_sorted(people.begin(), people.end(), by_age));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}