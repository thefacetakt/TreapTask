#ifndef __STUPID__
#define __STUPID__

#include "IPermutator.hpp"

#include <vector>


class Stupid : public IPermutator
{
    std::vector <int> elements;
    
public:
    Stupid();
    void insert(int value, size_t index);
    void assign(int value, size_t index);
    long long subsegmentSum(size_t left, size_t right);
    bool nextPermutation(size_t left, size_t right);
    
#ifdef _DEBUG
    void print() const;
#endif
};

#endif