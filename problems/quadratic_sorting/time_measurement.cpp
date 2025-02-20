#include <random_array.h>
#include <sorting.h>
#include <iostream>
#include <ctime>

#define N 100

int main()
{
    srand(time(0));

    int arr[N] = {};
    RandomArray::fill(arr, N, OrderedIntGenerator(0, 10), 0.5f);
    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
    BubbleSorter::sort(arr,
        arr + sizeof(arr) / sizeof(int),
        [](int left, int right) { return left > right; });

    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
}
