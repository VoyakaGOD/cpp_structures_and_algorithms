// Implementation of comb sorting algorithm

#ifndef SPECIAL_COMB_SORT
#define SPECIAL_COMB_SORT

#include <utility>
#include <cassert>

class CombSorter
{
public:
    template <typename RandomIt, typename CompFunc>
    static void sort(RandomIt first, RandomIt last, CompFunc compare, float shrink_factor = 1.25f)
    {
        assert(first < last);
        assert(shrink_factor > 1.0f);

        bool were_swapped = false;
        size_t step = (last - first) - 1;
        while((step > 1) || were_swapped)
        {
            step = static_cast<size_t>(step / shrink_factor);
            if(step < 1) 
                step = 1;
            were_swapped = false;
            for(RandomIt it = first; (it + step) < last; it += step)
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
