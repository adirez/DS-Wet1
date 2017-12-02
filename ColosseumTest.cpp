//
// Created by Shahak on 01/12/2017.
//
#include <cstdlib>
#include "Colosseum.h"
#include "iostream"

using std::cout;
using std::endl;

int main() {
    Colosseum colosseum;
    colosseum.addTrainer(4);
    colosseum.addTrainer(3);
    colosseum.buyGladiator(101, 4, 50);
    colosseum.addTrainer(5);
    try{
        colosseum.buyGladiator(101, 5, 25);
    } catch (KeyAlreadyExists &e){}

    colosseum.buyGladiator(102, 5, 25);
    colosseum.getTopGladiator(-1);
    colosseum.buyGladiator(105, 4, 5);
    colosseum.buyGladiator(120, 5, 15);
    colosseum.updateLevels(5, 4);

    return 0;
}