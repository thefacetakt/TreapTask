#ifndef __IPERMUTATOR__
#define __IPERMUTATOR__

#include <cstddef>

class IPermutator
{
public:
    virtual void insert(int value, size_t index) = 0;
    virtual void assign(int value, size_t index) = 0;
    virtual long long subsegmentSum(size_t left, size_t right) = 0;
    virtual bool nextPermutation(size_t left, size_t right) = 0;
    virtual ~IPermutator(){}
    
#ifdef _DEBUG
    virtual void print() const = 0;
#endif
};

#endif