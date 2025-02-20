#include <random_array.h>
#include <sorting.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

auto comp_func = [](int left, int right) { return left > right; };

template <typename Func>
double measure(Func sort, int N, float orderliness)
{
    std::vector<int> array(N);
    RandomArray::fill(array.begin(), array.end(), OrderedIntGenerator(0, 10), orderliness);

    auto start = std::chrono::high_resolution_clock::now();
    sort(array.begin(), array.end(), comp_func);
    auto end = std::chrono::high_resolution_clock::now();
    return static_cast<std::chrono::duration<double>>(end - start).count();
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
    double bubble_time = 0;
    double shaker_time = 0;
    double comb_time = 0;

    for(int i = 0; i < count; i++)
    {
        bubble_time += measure(BubbleSorter::sort<std::vector<int>::iterator, decltype(comp_func)>, 
            N, orderliness);
        shaker_time += measure(ShakerSorter::sort<std::vector<int>::iterator, decltype(comp_func)>, 
            N, orderliness);
        comb_time += measure(CombSorter::sort<std::vector<int>::iterator, decltype(comp_func)>, 
            N, orderliness);
    }

    std::cout << (bubble_time / count) << std::endl;
    std::cout << (shaker_time / count) << std::endl;
    std::cout << (comb_time / count) << std::endl;
}
