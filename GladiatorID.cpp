//
// Created by adire on 01-Dec-17.
//

#include "GladiatorID.h"

GladiatorID::GladiatorID() : id(-1), level(-1) {}

GladiatorID::GladiatorID(int id, int level, Trainer *ptr_to_trainer) : id(id), level(level) {
    this->trainer_ptr = ptr_to_trainer;
}

GladiatorID::GladiatorID(int id, int level) : id(id), level(level), trainer_ptr(NULL) {}

GladiatorID::GladiatorID(const GladiatorID &gladiatorID) : id(gladiatorID.id), level(gladiatorID.level) {
    trainer_ptr = gladiatorID.trainer_ptr;
}

int GladiatorID::getID() const {
    return id;
}

int GladiatorID::getLevel() const {
    return level;
}

Trainer *GladiatorID::getTrainerPtr() const {
    return trainer_ptr;
}

void GladiatorID::setTrainerPtr(Trainer *trainer) {
    trainer_ptr = trainer;
}

bool GladiatorID::operator<(const GladiatorID &gladiator2) const {
    return id < gladiator2.id;
}


bool GladiatorID::operator>(const GladiatorID &gladiator2) const {
    return id > gladiator2.id;
}

bool operator==(const GladiatorID &gladiator1, const GladiatorID &gladiator2){
    return gladiator1.id == gladiator2.id;
}

bool operator!=(const GladiatorID &gladiator1, const GladiatorID &gladiator2){
    return !(gladiator1 == gladiator2);
}