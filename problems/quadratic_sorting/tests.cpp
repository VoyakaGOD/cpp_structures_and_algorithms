#include <random_array.h>
#include <sorting.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <ctime>

// alg_name N orderliness
int main()
{
    std::string alg;
    std::cin >> alg;
    int N = 0;
    std::cin >> N;
    if(N <= 0)
        throw std::runtime_error("N should be greater than 0.");
    float orderliness;
    std::cin >> orderliness;

    srand(time(0));
    std::vector<int> array(N);
    RandomArray::fill(array.begin(), array.end(), OrderedIntGenerator(0, 10), orderliness);
    auto arr_clone = array;

    auto comp_func = [](int left, int right) { return left > right; };
    auto predicate = [comp_func](int left, int right) { return !comp_func(left, right); };
    if(alg == "bubble")
        BubbleSorter::sort(array.begin(), array.end(), comp_func);
    else if(alg == "shaker")
        ShakerSorter::sort(array.begin(), array.end(), comp_func);
    else if(alg == "comb")
        CombSorter::sort(array.begin(), array.end(), comp_func);
    else
        throw std::runtime_error("Algorithm[" + alg + "] is not supported.");
    std::sort(arr_clone.begin(), arr_clone.end(), predicate);
    std::cout << ((array == arr_clone) ? "V" : "X") << std::endl;
}
