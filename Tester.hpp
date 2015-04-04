#ifndef __TESTER__
#define __TESTER__

#include "IPermutator.hpp"

#include <vector>
#include <random>

class Tester
{
    enum EQuery
    {
        INSERT,
        ASSIGN,
        SUBSEGMENT_SUM,
        NEXT_PERMUTATION,
        QUERIES_NUMBER
    };
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distributionOfNumber;
    std::uniform_int_distribution<int> distributionOfQueryType;
    
    struct Query
    {
        EQuery type;
        long long firstParameter;
        long long secondParameter;
        Query(EQuery type, long long firstParameter, long long secondParameter) : 
            type(type), firstParameter(firstParameter), secondParameter(secondParameter)
        {
        }
    };
    
    std::vector <Query> queries;
    
    size_t queryNumber;
    int minimalNumber;
    int maximalNumber;
    
public:
    Tester(size_t queryNumber, int minimalNumber, int maximalNumber);
    
    void generateQueries(int seed);
    
    std::vector <long long> operator()(IPermutator *testSubject);
};

#endif