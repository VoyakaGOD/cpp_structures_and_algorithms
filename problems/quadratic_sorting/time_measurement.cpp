#include <sorting.h>
#include <iostream>

int main()
{
    int arr[] = {5, 2, 5, 1, 5, 6, 10, 3};
    BubbleSorter::sort(arr,
        arr + sizeof(arr) / sizeof(int),
        [](int left, int right) { return left > right; });

    for(int item : arr)
        std::cout << item << ", ";
    std::cout << std::endl;
}
