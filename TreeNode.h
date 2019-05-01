#include <iostream>

using namespace std;

template <class T>
class TreeNode
{
    public:
        TreeNode();
        TreeNode(T k);
        ~TreeNode();

        T key;
        TreeNode *left;
        TreeNode *right;
};

template<class T>
TreeNode<T>::TreeNode() {}

template<class T>
TreeNode<T>::TreeNode(T k)
{
    left = NULL;
    right = NULL;
    key = k;
}

template<class T>
TreeNode<T>::~TreeNode()
{
    //left = NULL;
    //right = NULL;
}
