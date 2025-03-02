// Implementation of comb sorting algorithm

#ifndef SPECIAL_COMB_SORT
#define SPECIAL_COMB_SORT

#include <utility>
#include <cassert>

#define SHRINK_FACTOR 1.25f

class CombSorter
{
public:
    template <typename RandomIt, typename CompFunc>
    static void sort(RandomIt first, RandomIt last, CompFunc compare)
    {
        assert(first < last);

        bool were_swapped = false;
        size_t step = last - first;
        while((step > 1) || were_swapped)
        {
            step = static_cast<size_t>(step / SHRINK_FACTOR);
            if(step < 1) 
                step = 1;
            were_swapped = false;
            for(RandomIt it = first; (it + step) < last; ++it)
            {
                RandomIt next = it + step;
                if(compare(*it, *next))
                {
                    std::swap(*it, *next);
                    were_swapped = true;
                }
            }
        }
    }
};

#endif //SPECIAL_COMB_SORT
