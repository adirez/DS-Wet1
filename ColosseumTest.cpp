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
    cout << "success." << endl;
/*    try {
        colosseum.addTrainer(1);
    } catch (KeyAlreadyExists &e) { cout << "Trainer already exists." << endl; }*/


}