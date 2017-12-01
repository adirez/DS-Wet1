//
// Created by adire on 01-Dec-17.
//

#include "GladiatorID.h"

GladiatorID::GladiatorID(int id, int level, Trainer *ptr_to_trainer) : Gladiator(id, level), ptr_to_trainer(ptr_to_trainer) {}


GladiatorID::GladiatorID(int id, int level) : Gladiator(id, level) {}

bool GladiatorID::operator<(const Gladiator &gladiator2) const {
    return id < gladiator2.id;
}

bool GladiatorID::operator>(const Gladiator &gladiator2) const {
    return id > gladiator2.id;
}

int GladiatorID :: GetID() {
    return Gladiator :: getID();
}