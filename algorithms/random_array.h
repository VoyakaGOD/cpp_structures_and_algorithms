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
    template <typename T, typename OrderedGenerator>
    static void fill(T *array, size_t size, OrderedGenerator gen, float orderliness = 0)
    {
        assert(orderliness >= 0);
        assert(orderliness <= 1);

        for(int i = 0; i < size; i++)
            array[i] = gen();

        size_t swaps_count = static_cast<size_t>(size * (1 - orderliness));
        while((swaps_count--) > 0)
            std::swap(array[std::rand() % size], array[std::rand() % size]);
    }
};

#endif //RANDOM_ARRAY
