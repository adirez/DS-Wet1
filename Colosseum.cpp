//
// Created by adire on 30-Nov-17.
//

#include "Colosseum.h"

Gladiator::Gladiator(int id, int level, Gladiator *ptr_to_level, Trainer *ptr_to_trainer) : id(id), level(level),
                                                                                              ptr_to_level(ptr_to_level),
                                                                                              ptr_to_trainer(ptr_to_trainer) {}

/*bool Gladiator::operator<(const Gladiator &gladiator2) const {
    if(id < gladiator2.id) return true;
    if(id == gladiator2.id){
        return
    }
    return ;
}*/

Trainer::Trainer(int id) : id(id) {}


Colosseum::Colosseum() : num_gladiators(0), num_trainers(0){}

void Colosseum::addTrainer(int trainer_id) {
    if(trainer_id <= 0){
        throw InvalidParameter();
    }
    trainers_tree.insert(Trainer(trainer_id));
}

void Colosseum::buyGladiator(int gladiator_id, int trainer_id, int level) {
    if(gladiator_id <= 0 || trainer_id <= 0 || level <=0){
        throw InvalidParameter();
    }
    Trainer trainer = trainers_tree.find(Trainer(trainer_id));
    trainer.gladiators.insert(Gladiator(gladiator_id, level, NULL, NULL));
    Gladiator gladiator_level(gladiator_id, level, NULL, NULL);
    gladiators_id_tree.insert(Gladiator(gladiator_id, level, &gladiator_level, &trainer));

}

void Colosseum::freeGladiator(int gladiator_id) {
    if(gladiator_id <= 0){
        throw InvalidParameter();
    }

}
