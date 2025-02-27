#include <random_array.h>
#include <algorithm>
#include <sorting.h>
#include <iostream>
#include <string>
#include <ctime>

#define DIGITS_COUNT 10 // lg(2^32)

// N orderliness
int main()
{
    int N = 0;
    std::cin >> N;
    if(N <= 0)
        throw std::runtime_error("N should be greater than 0.");
    float orderliness;
    std::cin >> orderliness;

    srand(time(0));
    CushyVector<uint32_t> array(N);
    RandomArray::fill(array.begin(), array.end(), OrderedIntGenerator(0, 10), orderliness);
    CushyVector<uint32_t> array_clone = array;

    auto predicate = [](uint32_t left, uint32_t right) { return left <= right; };
    RadixSorter::sort(array.begin(), array.end(), getDigit<uint32_t>, DIGITS_COUNT);
    std::sort(array_clone.begin(), array_clone.end(), predicate);
    std::cout << ((array == array_clone) ? "V" : "X") << std::endl;

    if(array != array_clone)
    {
        for(int i = 0; i < N; i++)
            std::cout << array[i] << ", ";
    }
}
