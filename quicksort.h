#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <type_traits>
#include <iterator>
#include <concepts>

namespace quicksort {
    template <class It>
    concept random_access_iterator = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<It>::iterator_category>
        && requires(It i, It j, int n, int k)
    {
        i + n; i - n; n + 1; i[n];
        k += n; k -= n;
        i < j; i > j; i <= j; i >= j;
        ++i; --i; *i;
    };
    namespace random_access_impl {
        template <class It, class Compare>
        void _sort(It first, It last, Compare comp) {
            if (std::distance(first, last) <= 1) return;
            auto pivot_value = *(first + std::distance(first, last) / 2);
            It left = first;
            It right = last - 1;
            while (left <= right) {
                while (comp(*left, pivot_value)) ++left;
                while (comp(pivot_value, *right)) --right;

                if (left <= right) {
                    std::iter_swap(left, right);
                    ++left;
                    --right;
                }
            }
            if (first < right + 1) _sort(first, right + 1, comp);
            if (left < last) _sort(left, last, comp);
        }
    }

    template <random_access_iterator It, class Compare = std::less<typename std::iterator_traits<It>::value_type>>
    void sort(It first, It last, Compare comp = {}) {
        random_access_impl::_sort(first, last, comp);
    }
}

#endif //QUICKSORT_H
