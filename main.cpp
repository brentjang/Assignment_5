#include "GenTree.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    GenTree<int> tree;
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    cout << tree.contains(1) << endl;
    tree.printTree();
    return 0;
}
