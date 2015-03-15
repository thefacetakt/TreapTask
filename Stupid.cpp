#include "Stupid.hpp"

#include <vector>
#include <algorithm>

Stupid::Stupid()
{
}

void Stupid::insert(int value, size_t index)
{
    elements.insert(elements.begin() + index, value);
}

void Stupid::assign(int value, size_t index)
{
    elements[index] = value;
}

long long Stupid::subsegmentSum(size_t left, size_t right)
{
    return std::accumulate(elements.begin() + left, elements.begin() + right, 0LL);
}

bool Stupid::nextPermutation(size_t left, size_t right)
{
    return std::next_permutation(elements.begin() + left, elements.begin() + right);
}