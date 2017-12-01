//
// Created by adire on 29-Nov-17.
//

#include <iostream>
#include "SplayTree.h"
#include "Colosseum.h"

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
    SplayTree<Trainer> tree;
    tree.insert(Trainer(1));
    tree.insert(Trainer(3));
    tree.insert(Trainer(2));
    tree.insert(Trainer(4));

    return 0;
}