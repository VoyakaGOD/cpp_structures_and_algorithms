// Algorithm for generating a pseudo-random array with partial ordering

#ifndef RANDOM_ARRAY
#define RANDOM_ARRAY

#include <cstdlib>
#include <utility>
#include <cassert>
#include <algorithm>
#include <stdint.h>

class OrderedIntGenerator
{
private:
    int value;
    int step;

public:
    OrderedIntGenerator(int start, int step);
    int operator()();
    bool isOrdered();
};

class UnorderedIntGenerator
{
private:
    int value;
    int min;
    int max;

public:
    UnorderedIntGenerator(int min, int max);
    int operator()();
    bool isOrdered();
};

class UnorderedULLGenerator
{
private:
    uint64_t value;
    uint64_t min;
    uint64_t max;

public:
    UnorderedULLGenerator(uint64_t min, uint64_t max);
    uint64_t operator()();
    bool isOrdered();
};

class RandomArray
{
public:
    template <typename RandomIt, typename Generator>
    static void fill(RandomIt first, RandomIt last, Generator gen, float orderliness = 0)
    {
        assert(orderliness >= 0);
        assert(orderliness <= 1);
        assert(first < last);

        for(RandomIt it = first; it < last; ++it)
            *it = gen();

        if(!gen.isOrdered())
            std::sort(first, last);
        
        size_t size = last - first;
        size_t swaps_count = static_cast<size_t>(size * (1 - orderliness));
        while((swaps_count--) > 0)
            std::swap(first[std::rand() % size], first[std::rand() % size]);
    }
};

#endif //RANDOM_ARRAY
