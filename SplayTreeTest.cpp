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
    PrintTree() = default;
    void operator()(T n) const {
        cout << n << endl;
    }
};

int main(){
    SplayTree<int> tree;

    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);

    try{
        tree.find(4);
    } catch (KeyNotFound &e){
        cout << "success" << endl;
    }


    PrintTree<int> print;
    tree.inOrder(print);
    return 0;
}