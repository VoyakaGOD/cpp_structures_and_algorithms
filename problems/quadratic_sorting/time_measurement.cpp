#include <random_array.h>
#include <sorting.h>
#include <iostream>
#include <ctime>
#include <array>

int main()
{
    srand(time(0));

    std::array<int, 100> arr;
    RandomArray::fill(arr.begin(), arr.end(), OrderedIntGenerator(0, 10), 0.5f);
    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
    CombSorter::sort(arr.begin(), arr.end(), [](int left, int right) { return left > right; });

    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
}
