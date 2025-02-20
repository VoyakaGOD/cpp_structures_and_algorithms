// Algorithm for generating a pseudo-random array with partial ordering

#ifndef RANDOM_ARRAY
#define RANDOM_ARRAY

#include <cstdlib>
#include <utility>
#include <cassert>

class OrderedIntGenerator
{
private:
    int value;
    int step;

public:
    OrderedIntGenerator(int start, int step);
    int operator()();
};

class RandomArray
{
public:
    template <typename RandomIt, typename OrderedGenerator>
    static void fill(RandomIt first, RandomIt last, OrderedGenerator gen, float orderliness = 0)
    {
        assert(orderliness >= 0);
        assert(orderliness <= 1);
        assert(first < last);

        for(RandomIt it = first; it < last; ++it)
            *it = gen();
        
        size_t size = last - first;
        size_t swaps_count = static_cast<size_t>(size * (1 - orderliness));
        while((swaps_count--) > 0)
            std::swap(first[std::rand() % size], first[std::rand() % size]);
    }
};

#endif //RANDOM_ARRAY
