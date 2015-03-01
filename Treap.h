#ifndef _TREAP_
#define _TREAP_

#include <algorithm>
#include <utility>
#include <cstdlib>
#include <climits>

#ifdef _DEBUG

#include <cstdio>

#endif

namespace NTreap
{
    class Treap
    {
    private:
        static size_t zero;
        struct Node
        {
            int value;
            
            int minimum;
            int maximum;
            size_t priority;
            size_t size;
            long long sum;
            size_t longestNonDecreasingPrefix;
            size_t longestNonIncreasingSuffix;
            bool reverseNeeded;

            Node *left, *right;
            
            Node(int value);
        };

        Node *root;

        size_t sizeOf(Node *node);

        long long sumOf(Node *node);

        static Node * leftChildOf(Node *node);

        static Node * rightChildOf(Node *node);
        
        int minOf(Node *node);
        
        int maxOf(Node *node);
        
        void recalcLongestEnd(Node *node, size_t & (*lengthAccess) (Node *), Node * (*lessGetter) (Node *), Node * (*largerGetter) (Node *));

        void recalc(Node *node);

        void changeReverseNeededStatus(Node *node);

        void push(Node *node);

        //i values goes to left
        std::pair<Node *, Node *> split(Node *node, size_t i);


        //is called only if node-referenced array is decreasingly sorted 
        //Greater (strictly) elements goes to left
        std::pair<Node *, Node *> splitByElement(Node *node, int element);

        Node * merge(Node *left, Node *right);

        void reverse(size_t i, size_t j);
        
#ifdef _DEBUG
        void _print(Node *node, bool reverseNeeded, int h) const;
#endif

    public:
        
        Treap();
                
        long long sum(size_t i, size_t j);

        void insert(int value, size_t i);

        void change(size_t i, int newValue);

        bool next_permutation(size_t i, size_t j);
        
#ifdef _DEBUG
        void print() const;
#endif
    };
    
};
#endif