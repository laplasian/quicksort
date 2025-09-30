#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <type_traits>
#include <iterator>
#include <concepts>

namespace quicksort {
    template <class It>
    concept random_access_iterator = std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<It>::iterator_category>
        && requires(It i, It j, int n)
    {
        i + n; i!=j;
        ++i; *i; i - j;
        std::iter_swap(i,j);
    };
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

    template <random_access_iterator It, class Compare = std::less<>>
    void sort(It first, It last, Compare comp = {}) {
        random_access_impl::_sort(first, last, comp);
    }
}

#endif //QUICKSORT_H
