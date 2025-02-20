// Implementation of bubble sorting algorithm

#ifndef SPECIAL_BUBBLE_SORT
#define SPECIAL_BUBBLE_SORT

#include <utility>

class BubbleSorter
{
public:
    template <typename RandomIt, typename CompFunc>
    static void sort(RandomIt firts, RandomIt last, CompFunc compare)
    {
        --last;
        bool were_swapped = false;
        do
        {
            were_swapped = false;
            for(RandomIt it = firts; it != last; ++it)
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
