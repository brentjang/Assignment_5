#include "TreeNode.h"
#include <iostream>

using namespace std;

template <class T>
class GenTree
{
public:
    GenTree();
    virtual ~GenTree(); //figure this out
    void insert(T value);
    bool contains(T value);
    bool deleteNode(T value);
    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    bool deleter(T k);

    TreeNode<T>* getMin();
    TreeNode<T>* getMax();
    bool isEmpty();
    void printTree();
    void recPrint(TreeNode<T>* node);

    TreeNode<T> *root;
};

template<class T>
GenTree<T>::GenTree()
{
    root = NULL;
}

template<class T>
GenTree<T>::~GenTree()
{
    //iterate and delete
}

template<class T>
void GenTree<T>::insert(T value)
{
    //check if value exists, if not continue
    TreeNode<T> *node = new TreeNode<T>(value);

    if(isEmpty())
    {
        root = node;
    }
    else //not empty treee
    {
        TreeNode<T> *curr = root;
        TreeNode<T> *parent;

        while(true) //look for insertion point
        {
            parent = curr;
            if(value < curr->key) //go left
            {
                curr = curr->left;
                if(curr == NULL) //found location
                {
                    parent->left = node;
                    break;
                }
            }
            else
            {
                curr = curr->right;
                if(curr == NULL)
                {
                    parent->right = node;
                    break;
                }
            }
        }
    }
}

template<class T>
bool GenTree<T>::contains(T value)
{
    if(isEmpty())
    {
        return false;
    }
    TreeNode<T> *curr = root;
    while(curr->key != value)
    {
        if(value < curr->key) //go left
        {
            curr = curr->left;
        }
        else //go right
        {
            curr = curr->right;
        }
        if(curr == NULL) //value not in tree
        {
            return false;
        }
    }
    return true;
}

template<class T>
bool GenTree<T>::deleteNode(T value)
{

}

template<class T>
bool GenTree<T>::deleter(T k)
{
    if(isEmpty())
    {
        return false;
    }
    //check if key/value exists

    TreeNode<T> *curr = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    //iterate and update pointers
    while(curr->key != k)
    {
        parent = curr;

        if(k < curr->key)
        {
            isLeft = true;
            curr = curr->left;
        }
        else
        {
            isLeft = false;
            curr = curr->right;
        }

        if(curr == NULL)
        {
            return false;
        }
    }

    //at this point, found the node to be deleted

    if(curr->left == NULL && curr->right == NULL) //left no children
    {
        if(curr == root)
        {
            root = NULL;
        }
        else if(isLeft)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
    }

    //check if it has one child
    else if(curr->right == NULL)
    {
        if(curr == root)
        {
            root = curr->left;
        }
        else if(isLeft)
        {
            parent->left = curr->left;
        }
        else
        {
            parent->right = curr->left;
        }
    }

    else if(curr->left == NULL)
    {
        if(curr == root)
        {
            root = curr->right;
        }
        else if(isLeft)
        {
            parent->left = curr->right;
        }
        else
        {
            parent->right = curr->right;
        }
    }

    //node to be deleted has 2 children
    else
    {
        //find successor of the node to be deleted (curr)
        TreeNode<T> *successor = getSuccessor(curr);

        if(curr == root)
        {
            root = successor;
        }
        else if(isLeft)
        {
            parent->left = successor;
        }
        else
        {
            parent->right = successor;
        }

        successor->left = curr->left;
    }

    return true;

}

//one right and all the way left
template<class T>
TreeNode<T>* GenTree<T>::getSuccessor(TreeNode<T>* d) //where d is node deleted
{
    TreeNode<T> *sp = d; //successor parent
    TreeNode<T> *successor = d;
    TreeNode<T> *curr = d->right;

    while(curr != NULL)
    {
        sp = successor;
        successor = curr;
        curr = curr->left;
    }

    //need to check if successor is descendant of right child
    if(successor != d->right)
    {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

template<class T>
TreeNode<T>* GenTree<T>::getMin()
{

}

template<class T>
TreeNode<T>* GenTree<T>::getMax()
{

}

template<class T>
bool GenTree<T>::isEmpty()
{
    return root == NULL;
}

template<class T>
void GenTree<T>::printTree()
{
    recPrint(root);
}

template<class T>
void GenTree<T>::recPrint(TreeNode<T>* node)
{
    if(isEmpty())
    {
        return;
    }
    else
    {
        recPrint(node->left);
        cout << node->key << endl;
        recPrint(node->right);
    }
}
