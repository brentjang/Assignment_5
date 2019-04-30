#include "GenDDLNode.h"
#include <iostream>

using namespace std;

template <class T>
class GenDDL
{
public:
    GenDDL();
    ~GenDDL();
    void insertFront(T data);
    T removeFront();
    void insertBack(T data);
    T removeBack();
    T deletePosition(int pos);
    int find(T val); //search for value return if it exisits
    bool isEmpty();
    unsigned int getSize();
    void printList();

    GenDDLNode<T> *front;
    GenDDLNode<T> *back;
    unsigned int size; //unsigned cant be negative
};


template<class T>
GenDDL<T>::GenDDL()
{
    //default constructor for stack of type T
    size = 0;
    front = NULL;
    back = NULL;
}

template<class T>
GenDDL<T>::~GenDDL()
{
}

template<class T>
void GenDDL<T>::insertFront(T data)
{
    GenDDLNode<T> *node = new GenDDLNode<T>(data);
    if(size == 0)
    {
        back = node;
    }
    else
    {
        node->next = front;
        front->prev = node;
    }
    front = node;
    size++;
}


template<class T>
T GenDDL<T>::removeFront()
{
    //check if empty
    if(!isEmpty())
    {
        GenDDLNode<T> *ft = front;
        if(front->next == NULL)
        {
            back = NULL;
        }
        else
        {
            front->next->prev = NULL;
        }
        front = front->next;
        T temp = ft->data;
        ft->next = NULL;
        delete ft;
        size--;

        return temp;
    }
    else
    {
        cout << "List is Empty" << endl;
    }
}

template<class T>
void GenDDL<T>::insertBack(T data)
{
    GenDDLNode<T> *node = new GenDDLNode<T>(data);
    if(size == 0)
    {
        front = node;
    }
    else
    {
        back->next = node;
        node->prev = back;
    }
    back = node;
    size++;
}

template<class T>
T GenDDL<T>::removeBack()
{
    //do this
    if(!isEmpty())
    {
        if(back->prev == NULL)
        {
            front = NULL;
        }
        else
        {
            back->prev->next = NULL;
        }
        T temp = back->data;
        GenDDLNode<T> *bk = back;
        back = back->prev;
        bk->prev = NULL;
        delete bk;
        size--;
        return temp;
    }
    else
    {
        cout << "List is Empty" << endl;
    }
}

template<class T>
int GenDDL<T>::find(T val)
{
    int idx = -1;
    GenDDLNode<T> *curr = front;

    while(curr != NULL)
    {
        ++idx;
        if(curr->data == val)
        {
            break;
        }
        else
        {
            curr = curr->next;
        }
    }

    if(curr == NULL)
    {
        idx = -1;
    }
    return idx;
}

template<class T>
T GenDDL<T>::deletePosition(int pos)
{
    //check if pos is valid (>=0)
    if(pos >= 0 && !isEmpty())
    {
        GenDDLNode<T> *curr = front;
        GenDDLNode<T> *prev = back;

        while(curr->data != pos)
        {
            curr = curr->next;
            if(curr == NULL)
            {
                cout << pos << " does not exisit in List" << endl;
                return 0;
            }
        }
        //when found correct pos update pointers
        if(curr == front)
        {
            front = curr->next;
            front->prev = NULL;
        }
        else
        {
            curr->prev->next = curr->next;
        }

        if(curr == prev)
        {
            prev = curr->prev;
            prev->next = NULL;
        }
        else
        {
            curr->next->prev = curr->prev;
        }
        curr->prev = NULL;
        curr->next = NULL;
        T temp = curr->data;
        delete curr;
        size--;

        return temp;
    }
}

template<class T>
bool GenDDL<T>::isEmpty()
{
    return (size == 0);
}

template<class T>
unsigned int GenDDL<T>::getSize()
{
    return size;
}

template<class T>
void GenDDL<T>::printList()
{
    GenDDLNode<T> *curr = front;
    while(curr)
    {
        cout << curr->data << endl;
        curr = curr->next;
    }
}
