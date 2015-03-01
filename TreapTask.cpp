#include "Treap.h"
#include <cstdio>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main()
{
    NTreap::Treap T;
    string query;
    cin >> query;
    while (query != "exit")
    {
        if (query == "insert")
        {
            int value;
            size_t index;
            cin >> value >> index;
            cout << value << index << endl;
            T.insert(value, index);
            T.print();
        }
        else if (query == "sum")
        {
            size_t i, j;
            cin >> i >> j;
            cout << T.sum(i, j) << endl;
            T.print();
        }
        else if (query == "change")
        {
            size_t i;
            int newValue;
            cin >> i >> newValue;
            T.change(i, newValue);
            T.print();
        }
        else if (query == "next_permutation")
        {
            size_t i, j;
            cin >> i >> j;
            T.next_permutation(i, j);
            T.print();
            
        }
        cin >> query;
    }
    return 0;
}