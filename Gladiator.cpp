//
// Created by adire on 01-Dec-17.
//

#include "Gladiator.h"

Gladiator::Gladiator(int id, int level) : id(id), level(level) {}

GladiatorID::GladiatorID(int id, int level, Trainer *ptr_to_trainer) : Gladiator(id, level), ptr_to_trainer(ptr_to_trainer) {}

GladiatorID::GladiatorID(int id, int level) : Gladiator(id, level) {}

bool GladiatorID::operator<(const Gladiator &gladiator2) const {
    return id < gladiator2.id;
}

bool GladiatorID::operator>(const Gladiator &gladiator2) const {
    return id > gladiator2.id;
}

bool Gladiator::operator==(const Gladiator &gladiator2) const {
    return id == gladiator2.id;
}

bool Gladiator::operator!=(const Gladiator &gladiator2) const {
    return !this == gladiator2;
}

int Gladiator::getID() const {
    return id;
}

bool GladiatorLevel::operator<(const Gladiator &gladiator2) const {
    if(level < gladiator2.level) return true;
    if(level == gladiator2.level){
        return id > gladiator2.id;
    }
    return false;
}

bool GladiatorLevel::operator>(const Gladiator &gladiator2) const {
    if(level > gladiator2.level) return true;
    if(level == gladiator2.level){
        return id < gladiator2.id;
    }
    return false;
}

GladiatorLevel::GladiatorLevel(int id, int level) : Gladiator(id, level) {}