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
    } catch (KeyAlreadyExists &e){
        cout << "print" << endl;
    }
    colosseum.buyGladiator(102, 5, 25);
    colosseum.getTopGladiator(-1);
    colosseum.levelUp(102, 26);
    int *arr;
    int *arr1;
    int *arr2;
    int *arr3;
    int *arr4;
    int *arr5;
    int num_of_gladiators = 0;
    colosseum.getAllGladiatorsByLevel(-1,&num_of_gladiators, &arr);
    colosseum.freeGladiator(102);
    colosseum.getAllGladiatorsByLevel(-1,&num_of_gladiators, &arr1);
    colosseum.getTopGladiator(5);
    colosseum.updateGladiator(101, 105);
    colosseum.getTopGladiator(-1);
    colosseum.updateGladiator(105, 101);
    colosseum.buyGladiator(105, 4, 5);
    colosseum.buyGladiator(120, 5, 15);
    colosseum.getAllGladiatorsByLevel(-1, &num_of_gladiators, &arr2);
    colosseum.getAllGladiatorsByLevel(4, &num_of_gladiators, &arr3);
    colosseum.getAllGladiatorsByLevel(5, &num_of_gladiators, &arr4);
    colosseum.updateLevels(5, 4);
    colosseum.getAllGladiatorsByLevel(-1, &num_of_gladiators, &arr5);

    free(arr);
    free(arr1);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);

    return 0;
}