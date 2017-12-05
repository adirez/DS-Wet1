//
// Created by adire on 01-Dec-17.
//

#include "GladiatorID.h"

GladiatorID::GladiatorID() : GladiatorLevel() {}

GladiatorID::GladiatorID(int id, int level, Trainer *ptr_to_trainer) : GladiatorLevel(id, level), trainer_ptr(ptr_to_trainer){}

GladiatorID::GladiatorID(int id, int level) : GladiatorLevel(id, level), trainer_ptr(NULL) {}

GladiatorID::GladiatorID(const GladiatorID &gladiatorID) : GladiatorLevel(gladiatorID), trainer_ptr(gladiatorID.trainer_ptr) {}

Trainer *GladiatorID::getTrainerPtr() const {
    return trainer_ptr;
}

void GladiatorID::setTrainerPtr(Trainer *trainer) {
    trainer_ptr = trainer;
}

void GladiatorID::setLevel(int factor) {
    level *= factor;
}

bool GladiatorID::operator<(const GladiatorID &gladiator2) const {
    return id < gladiator2.id;
}

bool GladiatorID::operator>(const GladiatorID &gladiator2) const {
    return id > gladiator2.id;
}
