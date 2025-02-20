#include <random_array.h>
#include <sorting.h>
#include <iostream>
#include <ctime>
#include <array>

#define N 100

int main()
{
    srand(time(0));

    std::array<int, N> arr;
    RandomArray::fill(&arr[0], N, OrderedIntGenerator(0, 10), 0.5f);
    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
    CombSorter::sort(arr.begin(), arr.end(), [](int left, int right) { return left > right; });

    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
}
