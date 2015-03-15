#ifndef __TESTER__
#define __TESTER__

#include "IPermutator.hpp"

#include <vector>

class Tester
{
    enum EQuery
    {
        INSERT,
        ASSIGN,
        SUBSEGMENT_SUM,
        NEXT_PERMUTATION,
        QUIT
    };
    
    size_t queryNumber;
    int minimalNumber;
    int maximalNumber;
    unsigned int seed;
    
    int rand();
public:
    Tester(size_t queryNumber, int minimalNumber, int maximalNumber);
    
    std::vector <int> operator()(IPermutator *testSubject);
    
    void srand(unsigned int seed);
};

#endif