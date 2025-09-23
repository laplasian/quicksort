#ifndef QUICKSORT_SFINAE_HPP
#define QUICKSORT_SFINAE_HPP

#include <type_traits>
#include <iterator>

namespace quicksort {
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


    template <class It, class Compare = std::less<typename std::iterator_traits<It>::value_type>>
    std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag,
            typename std::iterator_traits<It>::iterator_category>, void> sort(It first, It last, Compare comp = {}) {
        random_access_impl::_sort(first, last, comp);
    }
}

#endif //QUICKSORT_SFINAE_HPP
