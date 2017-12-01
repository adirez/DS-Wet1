//
// Created by Shahak on 01/12/2017.
//
#include "Colosseum.h"
#include "iostream"

using std::cin;
using std::cout;
using std::endl;

int main() {
    Colosseum colosseum;
    colosseum.addTrainer(1);
    colosseum.addTrainer(2);
    colosseum.addTrainer(3);
    try {
        colosseum.addTrainer(1);
    } catch (KeyAlreadyExists &e) { cout << "Trainer already exists" << endl; }
    colosseum.buyGladiator(11, 1, 1);
    colosseum.buyGladiator(12, 1, 2);
    colosseum.buyGladiator(13, 1, 1);
    colosseum.buyGladiator(21, 2, 1);
    colosseum.buyGladiator(22, 2, 7);
    colosseum.buyGladiator(23, 2, 4);

    try{
        colosseum.buyGladiator(33, 4, 10);
    } catch (KeyNotFound &e) {
        cout << "Not found" << endl;
    }

    return 0;

}