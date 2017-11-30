//
// Created by adire on 29-Nov-17.
//

#include <iostream>
#include "SplayTree.h"

using std::cout;
using std::endl;

template <class T>
class PrintTree {
public:
    PrintTree() {};
    void operator()(T n) const {
        cout << n << endl;
    }
};

int main(){
    SplayTree<int> tree;

    tree.insert(1);
    tree.insert(14);
    tree.insert(2);
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(6);
    tree.find(5);
    tree.find(1);
    tree.find(3);
    tree.find(6);
    tree.find(2);
    tree.find(7);
    tree.remove(1);
    tree.remove(2);
    tree.remove(3);
    tree.insert(1);
    tree.insert(18);
    tree.remove(7);
    tree.remove(1);
    tree.remove(5);
    tree.remove(14);
    tree.remove(6);
    tree.remove(18);

    PrintTree<int> print;
    tree.inOrder(print);
    return 0;
}