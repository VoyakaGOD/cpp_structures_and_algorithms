// Implementation of comb sorting algorithm

#ifndef SPECIAL_RADIX_SORT
#define SPECIAL_RADIX_SORT

#include <cushy_vector.h>
#include <utility>
#include <cassert>
#include <iterator>

#define RADIX_SORT_BASE 10u

unsigned long long pow10[] = 
{
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
    1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
    100000000000000, 1000000000000000, 10000000000000000, 100000000000000000,
    1000000000000000000, 10000000000000000000ull
};

template <typename UnsignedIntegerType>
uint8_t getDigit(UnsignedIntegerType number, size_t digit_index)
{
    return (number / pow10[digit_index]) % RADIX_SORT_BASE;
}

class RadixSorter
{
private:
    template <typename RandomIt, typename AnotherRandomIt, typename DigitExtractor>
    static void countingSort(RandomIt src_first, RandomIt src_last, AnotherRandomIt dst, DigitExtractor getDigit, size_t digit_index)
    {
        size_t count[RADIX_SORT_BASE] = {};
        for(RandomIt it = src_first; it < src_last; ++it)
            count[getDigit(*it, digit_index)]++;

        for(unsigned int i = 1; i < RADIX_SORT_BASE; i++)
            count[i] += count[i - 1];

        for(RandomIt it = src_last - 1; it >= src_first; --it)
        {
            uint8_t digit = getDigit(*it, digit_index);
            dst[--count[digit]] = std::move(*it);
        }
    }

public:
    template <typename RandomIt, typename DigitExtractor>
    static void sort(RandomIt first, RandomIt last, DigitExtractor getDigit, size_t digits_count)
    {
        assert(first < last);

        using T = typename std::iterator_traits<RandomIt>::value_type;
        CushyVector<T> buffer(last - first);

        for(int digit_index = 0; digit_index < digits_count; digit_index++)
        {
            if(digit_index & 0x1)
                countingSort(buffer.begin(), buffer.end(), first, getDigit, digit_index);
            else
                countingSort(first, last, buffer.begin(), getDigit, digit_index);
        }

        if(digits_count & 0x1)
        {
            size_t size = buffer.getSize();
            for(size_t i = 0; i < size; i++)
                first[i] = std::move(buffer[i]);
        }
    }
};

#endif //SPECIAL_RADIX_SORT
