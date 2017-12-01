//
// Created by adire on 01-Dec-17.
//

#include "Trainer.h"

Trainer::Trainer(int id) : id(id) {}

bool Trainer::operator<(const Trainer &trainer2) const {
    return id < trainer2.id;
}

bool Trainer::operator>(const Trainer &trainer2) const {
    return id > trainer2.id;
}

bool Trainer::operator==(const Trainer &trainer2) const {
    return id == trainer2.id;
}

bool Trainer::operator!=(const Trainer &trainer2) const {
    return !this==trainer2;
}