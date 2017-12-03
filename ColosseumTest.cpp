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
    colosseum.getTopGladiator(-1);
    int *arr;
    int *arr1;
    int *arr2;
    int *arr3;
    int *arr4;
    int *arr5;
    int *arr6;
    int *arr7;
    int *arr8;
    int *arr9;
    int *arr10;
    int *arr11;
    int *arr12;
    int *arr13;
    int num;
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    int num8;
    int num9;
    int num10;
    int num11;
    int num12;
    int num13;
    colosseum.getAllGladiatorsByLevel(-1, &num, &arr);
    free(arr);
    colosseum.addTrainer(4);
    colosseum.addTrainer(3);
    colosseum.addTrainer(7);
    colosseum.addTrainer(15);
    colosseum.updateLevels(1,1);
    colosseum.getTopGladiator(-1);
    colosseum.buyGladiator(10,4,2);
    colosseum.getAllGladiatorsByLevel(3, &num1, &arr1);
    free(arr1);

    colosseum.freeGladiator(10);
    colosseum.getTopGladiator(-21);
    colosseum.getAllGladiatorsByLevel(4, &num2, &arr2);
    free(arr2);

    colosseum.addTrainer(0);
    colosseum.addTrainer(-3);
    colosseum.addTrainer(7);
    colosseum.buyGladiator(101,4,50);
    colosseum.buyGladiator(102,3,25);
    colosseum.buyGladiator(103,7,1);
    colosseum.buyGladiator(104,7,45);
    colosseum.getTopGladiator(15);
    colosseum.getAllGladiatorsByLevel(15, &num3, &arr3);
    free(arr3);

    colosseum.buyGladiator(0,4,50);
    colosseum.buyGladiator(-10,4,50);
    colosseum.buyGladiator(101,0,50);
    colosseum.buyGladiator(101,-3,50);
    colosseum.buyGladiator(101,4,0);
    colosseum.buyGladiator(101,4,-50);
    colosseum.buyGladiator(101,4,55);
    colosseum.buyGladiator(102,4,555);
    colosseum.buyGladiator(105,14,55);

    colosseum.freeGladiator(104);

    colosseum.freeGladiator(0);
    colosseum.freeGladiator(-9);

    colosseum.freeGladiator(104);

    colosseum.levelUp(102, 1);
    colosseum.levelUp(0, 2);
    colosseum.levelUp(-9, 2);
    colosseum.levelUp(102, 0);
    colosseum.levelUp(102, -6);
    colosseum.levelUp(110, 14);
    colosseum.levelUp(104, 15);

    colosseum.buyGladiator(104,3,50);
    colosseum.buyGladiator(105,4,55);
    colosseum.buyGladiator(106,7,100);
    colosseum.buyGladiator(109,3,50);
    colosseum.buyGladiator(107,4,50);
    colosseum.buyGladiator(108,7,50);

    colosseum.getTopGladiator(-1);

    colosseum.levelUp(105, 50);

    colosseum.getTopGladiator(-10);
    colosseum.getTopGladiator(3);
    colosseum.getTopGladiator(4);
    colosseum.getTopGladiator(7);
    colosseum.getTopGladiator(0);
    colosseum.getTopGladiator(14);

    colosseum.getAllGladiatorsByLevel(3, &num4, &arr4);
    free(arr4);

    colosseum.getAllGladiatorsByLevel(4, &num5, &arr5);
    free(arr5);

    colosseum.getAllGladiatorsByLevel(7, &num6, &arr6);
    free(arr6);

    colosseum.getAllGladiatorsByLevel(-1, &num7, &arr7);
    free(arr7);

    colosseum.getAllGladiatorsByLevel(0, &num8, &arr8);
    free(arr8);

    colosseum.getAllGladiatorsByLevel(14, &num9, &arr9);
    free(arr9);

    colosseum.updateGladiator(0, 110);
    colosseum.updateGladiator(-444, 110);

    colosseum.updateGladiator(101, 0);
    colosseum.updateGladiator(101, -34);
    colosseum.updateGladiator(101, 105);
    colosseum.updateGladiator(101, 101);
    colosseum.updateGladiator(111, 105);
    colosseum.updateGladiator(105, 110);
    colosseum.updateGladiator(105, 110);

    colosseum.freeGladiator(105);

    colosseum.getTopGladiator(4);

    colosseum.buyGladiator(105,4,115);
    colosseum.buyGladiator(111,7,1);
    colosseum.levelUp(115, 50);
    colosseum.buyGladiator(112,4,5);
    colosseum.buyGladiator(113,4,20);
    colosseum.buyGladiator(114,4,1);
    colosseum.levelUp(114, 50);
    colosseum.levelUp(113, 15);
    colosseum.levelUp(114, 50);
    colosseum.buyGladiator(115,4,200);
    colosseum.levelUp(115, 1);
    colosseum.buyGladiator(116,4,1);
    colosseum.levelUp(113, 15);
    colosseum.levelUp(116, 201);
    colosseum.buyGladiator(117,3,11);
    colosseum.buyGladiator(118,15,460);
    colosseum.levelUp(107, 100);

    colosseum.updateLevels(3, 4);
    colosseum.getAllGladiatorsByLevel(-1, &num10, &arr10);
    free(arr10);

    colosseum.getTopGladiator(-10);
    colosseum.getTopGladiator(3);
    colosseum.getTopGladiator(4);
    colosseum.getTopGladiator(7);
    colosseum.getTopGladiator(15);

    colosseum.updateLevels(1, 1);

    colosseum.updateLevels(100, 11);

    colosseum.getAllGladiatorsByLevel(-1, &num11, &arr11);
    free(arr11);

    colosseum.updateLevels(0, 1);
    colosseum.updateLevels(-1, 1);
    colosseum.updateLevels(1, 0);
    colosseum.updateLevels(1, -1);


    colosseum.freeGladiator(118);
    colosseum.freeGladiator(105);

    colosseum.getAllGladiatorsByLevel(15, &num12, &arr12);
    free(arr12);

    colosseum.getTopGladiator(15);

    colosseum.getAllGladiatorsByLevel(-1, &num13, &arr13);
    free(arr13);

    colosseum.getTopGladiator(-1);
    colosseum.getTopGladiator(4);

    return 0;
}