#include <iostream>

using namespace std;

template <class T>
class GenDDLNode
{
    public:
        GenDDLNode();
        GenDDLNode(T d);
        ~GenDDLNode();
        T data;
        GenDDLNode *next;
        GenDDLNode *prev;
};

template<class T>
GenDDLNode<T>::GenDDLNode()
{

}

template<class T>
GenDDLNode<T>::GenDDLNode(T d)
{
    data = d;
    next = NULL;
    prev = NULL;
}

template<class T>
GenDDLNode<T>::~GenDDLNode()
{
    next = NULL;
    prev = NULL;
    //no delete
}
