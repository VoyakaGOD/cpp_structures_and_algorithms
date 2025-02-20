#include <random_array.h>

OrderedIntGenerator::OrderedIntGenerator(int start, int step)
{
    assert(step != 0);

    value = start;
    this->step = step;
}

int OrderedIntGenerator::operator()()
{
    value += rand() % step;
    return value;
}
