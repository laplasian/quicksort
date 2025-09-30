#ifndef QUICKSORT_SFINAE_HPP
#define QUICKSORT_SFINAE_HPP

#include <type_traits>
#include <iterator>

namespace quicksort {
    namespace random_access_impl {
        template <class It, class Compare>
        void _sort(It first, It last, Compare comp) {
            using std::iter_swap;
            auto n = last - first;
            if (n < 2) return;

            It pivot_it = last - 1;
            const auto& pivot = *pivot_it;

            It i = first;
            for (It j = first; j != pivot_it; ++j) {
                if (comp(*j, pivot)) {
                    iter_swap(i, j);
                    ++i;
                }
            }
            iter_swap(i, pivot_it);

            _sort(first, i, comp);
            _sort(++i, last, comp);
        }
    }


    template <class It, class Compare = std::less<>>
    std::enable_if_t<std::is_base_of_v<std::random_access_iterator_tag,
            typename std::iterator_traits<It>::iterator_category>, void> sort(It first, It last, Compare comp = {}) {
        random_access_impl::_sort(first, last, comp);
    }
}

#endif //QUICKSORT_SFINAE_HPP
