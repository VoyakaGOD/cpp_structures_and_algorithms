#include <random_array.h>
#include <cushy_vector.h>
#include <algorithm>
#include <sorting.h>
#include <iostream>
#include <chrono>
#include <ctime>

#define DIGITS_COUNT 4

void radixSort(uint32_t *first, uint32_t *last)
{
    RadixSorter::sort(first, last, getDigit<uint32_t>, DIGITS_COUNT);
}

void stdSort(uint32_t *first, uint32_t *last)
{
    // strict order required
    std::sort(first, last, [](uint32_t left, uint32_t right) { return left < right; });
}

template <typename Func>
double measure(Func sort, int N, float orderliness, int count)
{
    CushyVector<CushyVector<uint32_t> *> arrays(count);
    for(auto &array : arrays)
    {
        array = new CushyVector<uint32_t>(N);
        RandomArray::fill(array->begin(), array->end(), OrderedIntGenerator(0, 10), orderliness);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(auto array : arrays)
        sort(array->begin(), array->end());
    auto end = std::chrono::high_resolution_clock::now();

    for(auto array : arrays)
        delete array;

    return static_cast<std::chrono::duration<double>>(end - start).count() / count;
}

// N orderliness count
int main(int argc, char *argv[])
{
    if(argc < 4)
        throw std::runtime_error("There are should be 3 arguments at least.");
    int N = std::atoi(argv[1]);
    if(N <= 0)
        throw std::runtime_error("N should be greater than 0.");
    float orderliness = std::atof(argv[2]);
    int count = std::atoi(argv[3]);
    if(count <= 0)
        throw std::runtime_error("count of measurements should be greater than 0.");

    srand(time(0));
    std::cout << measure(radixSort, N, orderliness, count) << std::endl;
    std::cout << measure(stdSort, N, orderliness, count) << std::endl;
}
