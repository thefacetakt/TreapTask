#include "Tester.hpp"
#include <cstdlib>
#include <cstdio>

Tester::Tester(size_t queryNumber, int minimalNumber, int maximalNumber) : queryNumber(queryNumber), minimalNumber(minimalNumber), maximalNumber(maximalNumber)
{
    distributionOfNumber = std::uniform_int_distribution<int>(minimalNumber, maximalNumber);
    distributionOfQueryType = std::uniform_int_distribution<int>(0, QUERIES_NUMBER - 1);
}

void Tester::generateQueries(int seed)
{
    generator.seed(seed);
    size_t currentSize = 0;
    for (size_t i = 0; i < queryNumber; ++i)
    {
        int value;
        size_t position;
        size_t left;
        size_t right;
        switch((currentSize ? distributionOfQueryType(generator) : 0))
        {
            case INSERT:
                value = distributionOfNumber(generator);
                position = std::uniform_int_distribution<size_t>(0, currentSize)(generator);
                queries.push_back(Query(INSERT, value, position));
                ++currentSize;
            break; case ASSIGN:
                value = distributionOfNumber(generator);
                position = std::uniform_int_distribution<size_t>(0, currentSize - 1)(generator);
                queries.push_back(Query(ASSIGN, value, position));
            break; case SUBSEGMENT_SUM:
                right = std::uniform_int_distribution<size_t>(1, currentSize)(generator);
                left = std::uniform_int_distribution<size_t>(0, right - 1)(generator);
                queries.push_back(Query(SUBSEGMENT_SUM, left, right));
            break; case NEXT_PERMUTATION:
                right = std::uniform_int_distribution<size_t>(1, currentSize)(generator);
                left = std::uniform_int_distribution<size_t>(0, right - 1)(generator);
                queries.push_back(Query(NEXT_PERMUTATION, left, right));
        };
    }
}
std::vector <long long> Tester::operator()(IPermutator *testSubject)
{
    std::vector<long long> result;
    for (auto const &q: queries)
    {
#ifdef _DEBUG
        testSubject->print();
        switch(q.type)
        {
            case INSERT:
                printf("INSERT ");
            break; case ASSIGN:
                printf("ASSIGN ");
            break; case SUBSEGMENT_SUM:
                printf("SUBSEGMENT_SUM ");
            break; case NEXT_PERMUTATION:
                printf("NEXT_PERMUTATION ");
        };
        printf("%lld %lld\n", q.firstParameter, q.secondParameter);
#endif
        switch(q.type)
        {
            case INSERT:
                testSubject->insert(q.firstParameter, q.secondParameter);                
            break; case ASSIGN:
                testSubject->assign(q.firstParameter, q.secondParameter);                
            break; case SUBSEGMENT_SUM:
                result.push_back(testSubject->subsegmentSum(q.firstParameter, q.secondParameter));
            break; case NEXT_PERMUTATION:
                result.push_back(testSubject->nextPermutation(q.firstParameter, q.secondParameter));
        };
    }
    delete testSubject;
    return result;
}
