#include "Tester.hpp"
#include "Treap.hpp"
#include "Stupid.hpp"

#include <vector>
#include <cstdio>

int main(int argc, char **argv)
{
    
    Tester Test(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    Test.srand(atoi(argv[4]));
    std::vector <long long> treapResult = Test(new NTreap::Treap());
#ifdef _COMPARE_
    Test.srand(atoi(argv[4]));
    std::vector <long long> stupidResult = Test(new Stupid());
    if (treapResult != stupidResult)
    {
        printf("FAILED TEST %d\n", atoi(argv[4]));
        for (size_t i = 0; i < treapResult.size(); ++i)
        {
            printf("%lld %lld\n", treapResult[i], stupidResult[i]);
        }
    }
    else
    {
        printf("OK TEST %d\n", atoi(argv[4]));
    }
#endif
}