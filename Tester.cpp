#include "Tester.hpp"
#include <cstdlib>

int Tester::rand()
{
    return seed = (1723 * seed + 817623);
}

Tester::Tester(size_t queryNumber, int minimalNumber, int maximalNumber) : queryNumber(queryNumber), minimalNumber(minimalNumber), maximalNumber(maximalNumber)
{
}

void Tester::srand(unsigned int seed)
{
    this->seed = seed;
}


std::vector <int> Tester::operator()(IPermutator *testSubject)
{
    std::vector<int> result;
    size_t currentSize = 0;
    for (size_t i = 0; i < queryNumber; ++i)
    {
        int value;
        size_t position;
        size_t left;
        size_t right;
        
        switch((currentSize ? rand() % 4 + 1 : 1))
        {
            case 1:
                value = rand() % (maximalNumber - minimalNumber + 1) + minimalNumber;
                position = rand() % (currentSize + 1);
                testSubject->insert(value, position);
                ++currentSize;
            break; case 2:
                value = rand() % (maximalNumber - minimalNumber + 1) + minimalNumber;
                position = rand() % currentSize;
                testSubject->assign(value, position);
            break; case 3:
                right = rand() % currentSize + 1;
                left = rand() % right;
                result.push_back(testSubject->subsegmentSum(left, right));
            break; case 4:
                right = rand() % currentSize + 1;
                left = rand() % right;
                result.push_back(testSubject->nextPermutation(left, right));
        };
    }
    return result;
}