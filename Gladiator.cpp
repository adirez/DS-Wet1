//
// Created by adire on 01-Dec-17.
//

#include "Gladiator.h"

Gladiator::Gladiator(int id, int level) : id(id), level(level) {}

int Gladiator::getID() const {
    return id;
}

int Gladiator::getLevel() const {
    return level;
}

bool operator==(const Gladiator &gladiator1, const Gladiator &gladiator2){
    return gladiator1.getID() == gladiator2.getID();
}

bool operator!=(const Gladiator &gladiator1, const Gladiator &gladiator2){
    return !(gladiator1 == gladiator2);
}