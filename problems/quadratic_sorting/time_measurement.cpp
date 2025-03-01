#include <random_array.h>
#include <cushy_vector.h>
#include <sorting.h>
#include <iostream>
#include <chrono>
#include <ctime>

auto cmp = [](int left, int right) { return left > right; };

void bubbleSort(int *first, int *last)
{
    BubbleSorter::sort(first, last, cmp);
}

void shakerSort(int *first, int *last)
{
    ShakerSorter::sort(first, last, cmp);
}

void combSort(int *first, int *last)
{
    CombSorter::sort(first, last, cmp);
}

template <typename Func>
double measure(Func sort, int N, float orderliness, int count)
{
    CushyVector<CushyVector<int> *> arrays(count);
    for(auto &array : arrays)
    {
        array = new CushyVector<int>(N);
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
    std::cout << measure(bubbleSort, N, orderliness, count) << std::endl;
    std::cout << measure(shakerSort, N, orderliness, count) << std::endl;
    std::cout << measure(combSort, N, orderliness, count) << std::endl;
}
