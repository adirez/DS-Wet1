//
// Created by adire on 01-Dec-17.
//

#include "Trainer.h"

Trainer::Trainer(int id) : id(id) {
    gladiators = new SplayTree<GladiatorLevel>;
}

Trainer::~Trainer() {
    delete gladiators;
}

bool Trainer::operator<(const Trainer &trainer2) const {
    return id < trainer2.id;
}

bool Trainer::operator>(const Trainer &trainer2) const {
    return id > trainer2.id;
}

bool operator==(const Trainer &trainer1, const Trainer &trainer2){
    return trainer1.id == trainer2.id;
}
bool operator!=(const Trainer &trainer1, const Trainer &trainer2){
    return !(trainer1 == trainer2);
}

Trainer::Trainer(const Trainer &trainer) : id(trainer.id){
    gladiators = new SplayTree<GladiatorLevel>;
}
