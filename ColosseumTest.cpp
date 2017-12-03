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
    int *arr;
    int num;

    colosseum.addTrainer(1);
    colosseum.addTrainer(2);

    colosseum.buyGladiator(11, 1 ,5);
    colosseum.buyGladiator(15, 1, 2);
    colosseum.buyGladiator(21, 2, 4);
    colosseum.buyGladiator(22, 2, 5);
    colosseum.buyGladiator(13, 1, 12);

    colosseum.updateLevels(5, 10);
    colosseum.getAllGladiatorsByLevel(1, &num, &arr);

    cout << num << endl;
    for (int i = 0; i < num; ++i) {
        cout << arr[i] << "||";
    }
    cout << endl;
    free(arr);




    return 0;
}