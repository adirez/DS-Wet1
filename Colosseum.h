//
// Created by adire on 30-Nov-17.
//

#ifndef WET1_COLOSSEUM_H
#define WET1_COLOSSEUM_H

#include "GladiatorID.h"
#include "Stimulant.h"


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

    void merge(Stimulant *stimulant);
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
     * receives a trainer id, a pointer to an integer and a pointer to an integer array, allocates the array and inserts the IDs of the gladiators belong
     * to the trainer (if trainerID > 0, otherwise all of the gladiators) sorted by level and returns through the int pointer the number of gladiators in
     * the array. using the function object we have (GladiatorsByLevel, which contains explanations in the class itself) we will allocate the array and
     * move the IDs into it. once the creator for the function object is called, it allocates the array and inits an index (an object field) to 0.  if
     * trainerID < 0, we will then  call inOrderReverse (reverse since we want the sorting to be from high to low) function to iterate through the
     * gladiators by their level in gladiators_level_tree and send the initialized function object to inOrder so it will be called upon each gladiator.
     * each gladiator will be sent to the object, have his ID copied into the array and progress the index until inOrder is done. since inOrder will iterate
     * through all of the gladiators, the time complexity will be O(n). if trainerID > 0, we will have a new trainer temporarily created by the creator
     * with the given ID (in O(1)) and send it to 'find' function and find the trainer in O(log k). after the trainer is found, we will create the function
     * object with the given number of gladiators the trainer holds and call inOrderReverse on the trainer's gladiators tree the same way we previously
     * explained. the iteration through the gladiators will also run in O(n) and since we had to find the trainer, the function will run in a total
     * complexity of O(n + log k).
     * @param trainer_id - the id of the trainer
     * @param numOfGladiators - a pointer to receive the number of gladiators in the array
     * @param gladiators - a pointer to the array to be allocated
     */
    void getAllGladiatorsByLevel(int trainer_id, int *numOfGladiators, int **gladiators);
    /**
     * receives an id of a current gladiator and upgrades his id into a new id. first, we create a temporary gladiator with the upgraded id in O(1) and
     * send it to 'find' in order to see if a gladiator with this id already exists. the find runs in O(log n). if the received id is allowed, we will
     * send to 'find' a gladiator with the current id using the constructor (in O(1)) and find him in O(log n). then, we will get his level in O(1)
     * using getLevel and save it. since we got him through the gladiators_id_tree we have a ptr to his trainer and we'll save it as well. now
     * we remove the gladiator from the level tree by sending a temp gladiator to 'remove' which runs at log(n) and insert it back with the new level.
     * since we have a ptr to the trainer, we do the same proccess for the trainer's tree (remove and insert using the constructor with the current id and
     * level of the gladiator) which will also run in O(log n). last, we remove the gladiator from the id tree and create a new gladiator with the
     * constructor (by providing the id, level and a ptr to the trainer) and insert it back. since any remove, insert or find in gladiator trees run at
     * O(log n) the function will run in O(log n).
     * @param gladiator_id - the current id of the gladiator
     * @param upgrade_id - the new id of the gladiator
     */
    void updateGladiator(int gladiator_id, int upgrade_id);
    /**
     * the function receives a stimulant code and a stimulant factor and has to update the levels of the relevant gladiators accordingly and re-sort them
     * as needed. the function uses functors in order to re-sort the gladiators and update their levels. there are a few steps for the function:
     * the first step is updating the gladiators_by_id tree. in this case we will use the functor StimulantID. the functor's fields are the code & factor,
     * two arrays of GladiatorID and an index for each of the arrays. to begin, we call the constructor of the functor which will allocate both of the arrays
     * and init the indexes to 0. once the init is done, we will call inOrder (since we want to keep the sorting in this tree by id, we will use regular
     * inOrder) and sent the functor to inOrder. this way, every gladiator inOrder will get to will be sent to the functor where he will be checked with
     * the stimulant code. gladiators which will be found using the drug will be moved to one of the arrays and have their level multiplied by the factor,
     * and the others will be moved to the second array. once the iteration is done, we have been iterating over n gladiators and thus the time complexity
     * so far will be of O(n). when the iteration is over, meaning we have all the gladiators of the tree sorted in the arrays, we will delete the tree
     * which is O(n) since it is deleted in postOrder. then we will init a new splay tree for the gladiators in O(1) since it's empty. now we will follow
     * an algorithm based on merge - run on both of the arrays simultaniously and each time insert to the tree the gladiator with the lower id. since we
     * insert into the tree in a sorted way, and any gladiator inserted to the tree gets to the root, the insertion will done in O(1) per each gladiator
     * because we will immediately find his place and there will be no need to splay (the splay function will exit in the terms check). so, eventually,
     * we will get a sorted tree in O(n). the same proccess will happen with gladiators_level_tree with the functor StimulantLevel and with sorting by levels
     * in O(n).
     * finally, we will only be left with the trainers' gladiators trees. for this case, first of all we will init a StimulantLevel functor since the gladiators
     * in the trainers' trees are of type GladiatorLevel. next, we have the functor StimulantTrainers which will be used to sort the gladiators. the
     * functor receives as a parameter the function object of GladiatorLevel and goes through a trainer at a time. for each trainer the functor calls
     * StimulantLevel for the trainer's tree in order to sort it's own tree of gladiators. each trainer in this functor will have his tree of gladiators sent
     * to inOrder by StimulantLevel function. the process in this stage is similar to the one in gladiators_level_tree and the trainer's gladiators will be
     * sorted to two arrays by their code and then sorted to a new tree. per single trainer, the complexity will be O(n). however, when we look at the final
     * result, we have iterated over 'k' trainers and for each of them we have iterated over 'n(trainer)' gladiators. the sum of all 'n(trainer)' is simply
     * 'n' so eventually we've iterated over 'k' trainers and 'n' gladiators. therefore, the function will have it's action done in O(n+k).
     * @param stimulantCode - the code the gladiators will be checked with
     * @param stimulantFactor - the factor the gladiators' level will be multiplied by (in case needed)
     */
    void updateLevels(int stimulantCode, int stimulantFactor);
};


#endif //WET1_COLOSSEUM_H
