#include <random_array.h>
#include <cushy_vector.h>
#include <algorithm>
#include <sorting.h>
#include <iostream>
#include <chrono>
#include <ctime>

size_t digits_count = 0;
void radixSort(uint64_t *first, uint64_t *last)
{
    RadixSorter::sort(first, last, getDigit<uint64_t>, digits_count);
}

void stdSort(uint64_t *first, uint64_t *last)
{
    // strict order required
    std::sort(first, last, [](uint64_t left, uint64_t right) { return left < right; });
}

template <typename Func>
double measure(Func sort, int N, float orderliness, int count)
{
    CushyVector<CushyVector<uint64_t> *> arrays(count);
    for(auto &array : arrays)
    {
        array = new CushyVector<uint64_t>(N);
        RandomArray::fill(array->begin(), array->end(), UnorderedULLGenerator(0, pow10[digits_count]), orderliness);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for(auto array : arrays)
        sort(array->begin(), array->end());
    auto end = std::chrono::high_resolution_clock::now();

    for(auto array : arrays)
        delete array;

    return static_cast<std::chrono::duration<double>>(end - start).count() / count;
}

// N orderliness count digits
int main(int argc, char *argv[])
{
    if(argc < 5)
        throw std::runtime_error("There are should be 4 arguments at least.");
    int N = std::atoi(argv[1]);
    if(N <= 0)
        throw std::runtime_error("N should be greater than 0.");
    float orderliness = std::atof(argv[2]);
    int count = std::atoi(argv[3]);
    if(count <= 0)
        throw std::runtime_error("count of measurements should be greater than 0.");
    digits_count = std::atoi(argv[4]);
    if(digits_count <= 0)
        throw std::runtime_error("count of digits should be greater than 0.");

    srand(time(0));
    std::cout << measure(radixSort, N, orderliness, count) << std::endl;
    std::cout << measure(stdSort, N, orderliness, count) << std::endl;
}
