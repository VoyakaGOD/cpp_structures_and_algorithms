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
        bool wereSwapped = false;
        do
        {
            wereSwapped = false;
            for(RandomIt it = firts; it != last; ++it)
            {
                RandomIt next = it + 1;
                if(compare(*it, *next))
                {
                    std::swap(*it, *next);
                    wereSwapped = true;
                }
            }
            --last;
        }
        while (wereSwapped);
    }
};

#endif //SPECIAL_BUBBLE_SORT
