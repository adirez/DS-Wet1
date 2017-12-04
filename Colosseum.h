//
// Created by adire on 30-Nov-17.
//

#ifndef WET1_COLOSSEUM_H
#define WET1_COLOSSEUM_H

#include "GladiatorID.h"
#include "GladiatorLevel.h"

/**
 * the head class of the data structure. contains integers to hold the number of gladiators and the number of trainers in the system and all of the
 * required trees: the gladiator id tree which is a tree of all the gladiators sorted by id, the gladiator level tree which is a tree of all the
 * gladiators stored by their level and a trainers tree which is a tree of all the trainers sorted by id, each of whom containes a gladiator level
 * tree for his own gladiators.
 */
class Colosseum {
private:
    int num_gladiators;
    int num_trainers;
    SplayTree<GladiatorID> *gladiators_id_tree;
    SplayTree<GladiatorLevel> *gladiators_level_tree;
    SplayTree<Trainer> *trainers_tree;

    /**
     * both functions (copy constructor and opterator '=') are defined as private and not implemented so they will not be used (since c++98 does not
     * allow '= delete'.
     */
    Colosseum(const Colosseum &colosseum);
    Colosseum &operator=(const Colosseum &colosseum);
public:
    /**
     * an empty constructor for colosseum will init with 0 gladiators and 0 trainers
     */
    Colosseum();
    /**
     * a destructor for colosseum will delete all of it's trees
     */
    ~Colosseum();
    /**
     * receives the id of a trainer, creates a new trainer with the given id in O(1) as previously shown, and then sends it to insert function of the
     * trainers tree. finally, increases the number of trainers. insert function uses the tree's 'find' and 'splay' and thus runs in a time complexity
     * of O(log k).
     * @param trainer_id - the id of the trainer to insert.
     */
    void addTrainer(int trainer_id);
    /**
     * receives an id and a level of a gladiator to be created and added to a trainer with a given id. the function first creates the requested gladiator
     * in O(1), once as GladiatorID and once as GladiatorLevel and creates a trainer with the given id in O(1) to be sent to find function. 'find'
     * searches the trainers tree for the requested trainer in O(log k). then, the gladiator is inserted to the gladiators_id_tree in O(log n) as shown
     * and similarly to gladiators_level_tree in O(log n) and since we have found the trainer, also the the trainer's gladiators tree directly at O(log n)
     * as well. finally, the function updates the right ptr to the gladiator's trainer in the id tree by finding him (which will run in O(1) since the
     * gladiator is now in the root) and increases the number of gladiators. by all the operations described, the function runs in a time complexitiy
     * of O(log n + log k).
     * @param gladiator_id - the id of the gladiator to insert
     * @param trainer_id - the id of the trainer to insert the gladiator for
     * @param level - the level of the gladiator
     */
    void buyGladiator(int gladiator_id, int trainer_id, int level);
    /**
     * receives an id of a gladiator to free. first, we'll create a copy of the gladiator with a similar id in O(1) and send it to 'find' function of
     * the gladiators_id_tree to get a pointer for the gladiator which will run in a time complexity of O(log n). after getting the gladiator, we will
     * save the pointer for his trainer and create a new gladiatorLevel in O(1) in order to send to remove functions for the trainer's level tree and
     * for the main level tree. finally, we'll remove the gladiator from the gladiator id tree (also in O(log n)). eventually, all of the find/remove
     * functions run in O(log n) and thus the function will run in O(log n).
     * @param gladiator_id - the id of the gladiator to remove.
     */
    void freeGladiator(int gladiator_id);
    /**
     *  receives an id of a gladiator and an integer to raise the level of the gladiator by. given the id of the gladiator, we will first find him in
     *  the gladiators_id_tree in O(log n). following that, we will call a remove function for the gladiators_level_tree using the constructor of the
     *  gladiator (O(1)) and remove him in O(log n). since we found the gladiator in the id tree, we will save the ptr to the trainer of the gladiator
     *  and remove him from the trainer's tree also in log(n). finally, we  will calculate the new level of the gladiator and remove him from the
     *  gladiators_id_tree also in O(log n). now that we have removed the gladiator from all of the trees and we have his new level, we can simply add
     *  him to all 3 of the trees (since we saved the ptr to the trainer's tree we can also directly add him to the trainer's tree). since any insert
     *  or remove function performs averagely in O(log n) the function will be completed in O(log n).
     * @param gladiator_id - the id of the gladiator
     * @param level_inc - the amount of levels to increase the gladiator's level by
     */
    void levelUp(int gladiator_id, int level_inc);
    /**
     * receives a trainer id and returns the id of the top gladiator of the trainer. if the id < 0 then we'll return the top gladiator in the entire
     * colosseum, which will be instant since we hold a max pointer in the gladiators tree. then we will use getMax and getID which both run in O(1).
     * if id > 0 we will search the trainers tree to find the trainer using a constructor for a temporary trainer (O(1)) and find him in O(log k). the
     * next step will be exactly as we did before and thus will also be in O(1) and total of O(log k).
     * @param trainer_id - the id of the trainer to find the maximum for
     * @return - the id of the top gladiator
     */
    int getTopGladiator(int trainer_id);
    /**
     *
     * @param trainer_id
     * @param numOfGladiators
     * @param gladiators
     */
    void getAllGladiatorsByLevel(int trainer_id, int *numOfGladiators, int **gladiators);
    void updateGladiator(int gladiator_id, int upgrade_id);
    void updateLevels(int stimulantCode, int stimulantFactor);
};


#endif //WET1_COLOSSEUM_H
