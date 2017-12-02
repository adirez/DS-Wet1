//
// Created by adire on 01-Dec-17.
//

#include "GladiatorLevel.h"



bool GladiatorLevel::operator<(const GladiatorLevel &gladiator2) const {
    if(level < gladiator2.level) return true;
    if(level == gladiator2.level){
        return id > gladiator2.id;
    }
    return false;
}

bool GladiatorLevel::operator>(const GladiatorLevel &gladiator2) const {
    if(level > gladiator2.level) return true;
    if(level == gladiator2.level){
        return id < gladiator2.id;    }
    return false;
}

GladiatorLevel::GladiatorLevel(int id, int level) : id(id), level(level) {}

GladiatorLevel::GladiatorLevel() : id(0), level(0) {}

int GladiatorLevel::getLevel() const {
    return level;
}

int GladiatorLevel::getID() const {
    return id;
}

bool operator==(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2){
    return gladiator1.id == gladiator2.id;
}

bool operator!=(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2){
    return !(gladiator1 == gladiator2);
}