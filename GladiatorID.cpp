//
// Created by adire on 01-Dec-17.
//

#include "GladiatorID.h"

GladiatorID::GladiatorID(int id, int level, Trainer *ptr_to_trainer) : Gladiator(id, level), ptr_to_trainer(ptr_to_trainer) {}


GladiatorID::GladiatorID(int id, int level) : Gladiator(id, level), ptr_to_trainer(NULL) {}

GladiatorID::GladiatorID(const GladiatorID &gladiator) : Gladiator(gladiator.id, gladiator.level) {
    this->ptr_to_trainer = gladiator.ptr_to_trainer;
}

bool GladiatorID::operator<(const Gladiator &gladiator2) const {
    return id < gladiator2.getID();
}

bool GladiatorID::operator>(const Gladiator &gladiator2) const {
    return id > gladiator2.getID();
}

int GladiatorID::getID() const {
    return id;
    //return Gladiator::getID();
}

int GladiatorID::getLevel() const {
    return level;
    //return Gladiator::getLevel();
}

Trainer *GladiatorID::getTrainerPtr() const {
    return ptr_to_trainer;
}
