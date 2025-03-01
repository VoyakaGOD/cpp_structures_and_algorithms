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

bool OrderedIntGenerator::isOrdered() { return true; }

UnorderedIntGenerator::UnorderedIntGenerator(int min, int max)
{
    assert(min < max);

    this->min = min;
    this->max = max;
    this->value = min;
}

int UnorderedIntGenerator::operator()()
{
    value = min + (rand() % (max - min));
    return value;
}

bool UnorderedIntGenerator::isOrdered() { return false; }
