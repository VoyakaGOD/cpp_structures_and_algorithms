// Implementation of cocktail shaker sorting algorithm

#ifndef SPECIAL_SHAKER_SORT
#define SPECIAL_SHAKER_SORT

#include <utility>

class ShakerSorter
{
public:
    template <typename RandomIt, typename CompFunc>
    static void sort(RandomIt first, RandomIt last, CompFunc compare)
    {
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

            if(!were_swapped)
                return;

            were_swapped = false;
            for(RandomIt it = last; it != first; --it)
            {
                RandomIt next = it - 1;
                if(compare(*next, *it))
                {
                    std::swap(*it, *next);
                    were_swapped = true;
                }
            }
            ++first;
        }
        while (were_swapped);
    }
};

#endif //SPECIAL_SHAKER_SORT
