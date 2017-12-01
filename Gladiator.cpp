//
// Created by adire on 01-Dec-17.
//

#include "Gladiator.h"

Gladiator::Gladiator(int id, int level) : id(id), level(level) {}

bool Gladiator::operator==(const Gladiator &gladiator2) const {
    return id == gladiator2.id;
}

bool Gladiator::operator!=(const Gladiator &gladiator2) const {
    return !this == gladiator2;
}

int Gladiator::getID() const {
    return id;
}
