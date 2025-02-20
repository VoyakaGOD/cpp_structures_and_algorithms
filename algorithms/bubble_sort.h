// Implementation of bubble sorting algorithm

#ifndef SPECIAL_BUBBLE_SORT
#define SPECIAL_BUBBLE_SORT

#include <utility>
#include <cassert>

class BubbleSorter
{
public:
    template <typename RandomIt, typename CompFunc>
    static void sort(RandomIt first, RandomIt last, CompFunc compare)
    {
        assert(first < last);

        --last;
        bool were_swapped = false;
        do
        {
            were_swapped = false;
            for(RandomIt it = first; it != last; ++it)
            {
                RandomIt next = it + 1;
                if(compare(*it, *next))
                {
                    std::swap(*it, *next);
                    were_swapped = true;
                }
            }
            --last;
        }
        while (were_swapped);
    }
};

#endif //SPECIAL_BUBBLE_SORT
