#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>

class Treap
{
private:
    struct Node
    {
        int value;
        
        size_t priority;
        size_t size;
        long long sum;
        size_t longestNonDecreasingPrefix;
        size_t longestNonIncreasingSuffix;
        bool reverseNeeded;


        Node *left, *right;
        
        Node(int value) : 
                            value(value),
                            priority(rand()),
                            size(1U),
                            sum(value),
                            longestNonDecreasingPrefix(1U),
                            longestNonIncreasingSuffix(1U),
                            reverseNeeded(false),
                            left(nullptr),
                            right(nullptr)
        {    
        }
    };

    Node *root;

    size_t sizeOf(Node *node)
    {
        return (node ? node->size : 0U);
    }

    long long sumOf(Node *node)
    {
        return (node ? node->sum : 0U);
    }

    Node * leftChildOf(Node *node)
    {
        return node->left;
    }

    Node * rightChildOf(Node *node)
    {
        return node->right;
    }

    void recalcLongestEnd(Node *node, size_t & (*lengthAccess) (Node *), Node * (*lessGetter) (Node *), Node * (*largerGetter) (Node *))
    {
        lengthAccess(node) = 0U;
        bool longestEndStoppesInLessChild = false;
        
        if (lessGetter(node))
        {
            lengthAccess(node) += lengthAccess(lessGetter(node));
            longestEndStoppesInLessChild = !(lessGetter(node)->value <= node->value);
        }

        if (!longestEndStoppesInLessChild)
        {
            lengthAccess(node) += 1U;
            if (largerGetter(node) && node->value <= largerGetter(node)->value)
            {
                lengthAccess(node) += lengthAccess(largerGetter(node));
            }
        }
    }

    void recalc(Node *node)
    {
        if (node)
        {
            node->size = sizeOf(node->left) + sizeOf(node->right) + 1U;
            node->sum = sumOf(node->left) + sumOf(node->right) + node->value;
            recalcLongestEnd(node, 
                            [] (Node *) -> size_t
                            {
                                return node->longestNonDecreasingPrefix;
                            },
                            leftChildOf,
                            rightChildOf
            );
            recalcLongestEnd(node, 
                            [] (Node *) -> size_t
                            {
                                return node->longestNonIncreasingSuffix;
                            },
                            rightChildOf,
                            leftChildOf
            );
        }
    }

    void changeReverseNeededStatus(Node *node, Node * (*childOf) (Node *))
    {
        if (node)
        {
            node->reverseNeeded ^= true;
        }
    }

    void push(Node *node)
    {
        if (node && node->reverseNeeded)
        {
            node->reverseNeeded = false;
            
            std::swap(node->longestNonIncreasingSuffix, node->longestNonDecreasingPrefix);
            std::swap(node->left, node->right);

            changeReverseNeededStatus(node->left);
            changeReverseNeededStatus(node->right);
        }
    }

    //i values goes to left
    std::pair<Node *, Node *> split(Node *node, size_t i)
    {
        if (!node)
        {
            return std::pair<Node *, Node *>(nullptr, nullptr);
        }

        push(node);

        if (sizeOf(node->left) >= i)
        {
            std::pair<Node *, Node *> temp = split(node->left, i);
            node->left = temp.second;
            recalc(node);
            return std::pair<Node *, Node *>(temp.first, node);
        }
        std::pair<Node *, Node *> temp = split(node->right, i - sizeOf(node->left) - 1U);
        node->right = temp.first;
        recalc(node);
        return std::pair<Node *, Node *>(node, temp.second);
    }

    Node * merge(Node *left, Node *right)
    {
        if (!left || !right)
        {
            return (left ? left : right);
        }
        
        push(left);
        push(right);

        if (left->priority > right->priority)
        {
            left->right = merge(left->right, right);
            recalc(left);
            return left;
        }
        right->left = merge(left, right->left);
        recalc(right);
        return right;
    }

    void reverse(size_t i, size_t j)
    {
        auto T1 = split(root, i);
        auto T2 = split(T1.second, j - i + 1);
        changeReverseNeededStatus(T2.first);
        root = merge(T1.first, merge(T2.first, T2.second));
    }

public:
    long long sum(size_t i, size_t j)
    {
        auto T1 = split(root, i);
        auto T2 = split(T1.second, j - i + 1);
        long long returnValue = T2.first->sum;
        root = merge(T1.first, merge(T2.first, T2.second));
        return returnValue;
    }

    void insert(int value, size_t i)
    {
        auto T = split(root, i);
        root = merge(T.first, merge(new Node(value), T.second));
    }

    void change(size_t i, int newValue)
    {
        auto T1 = split(root, i);
        auto T2 = split(T1.second, 1U);
        T2.first->value = newValue;
        root = merge(T1.first, merge(T2.first, T2.second));
    }

};

