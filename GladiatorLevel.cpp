//
// Created by adire on 01-Dec-17.
//

#include "GladiatorLevel.h"

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

int GladiatorLevel :: GetID() {
    return Gladiator :: getID();
}

GladiatorLevel::GladiatorLevel(int id, int level) : Gladiator(id, level) {}