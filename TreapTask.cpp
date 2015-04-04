#include "Tester.hpp"
#include "Treap.hpp"
#include "Stupid.hpp"

#include <vector>
#include <cstdio>


//arguments: number of queries, minimal number, maximal number, test number (used as seed)

int main(int argc, char **argv)
{
    
    Tester test(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    test.generateQueries(atoi(argv[4]));
    std::vector <long long> treapResult = test(new NTreap::Treap());
    
#ifdef _COMPARE_
    std::vector <long long> stupidResult = test(new Stupid());
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
