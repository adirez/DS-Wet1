//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_TRAINER_H
#define WET1_TRAINER_H

#include "SplayTree.h"
#include "GladiatorLevel.h"

/**
 * a class to hold a trainer of gladiators in the data structure. the class has an integer field to hold the id of the trainer and a splay tree of type
 * GladiatorLevel to hold the gladiators of the trainer.
 */
class Trainer {
private:
    int id;
    SplayTree<GladiatorLevel> *gladiators;

    /**
     * the function is declared within the private section and not implemented in order to prevent it from being used (since c++98 does not allow
     * the usage of '= delete'.
     */
    Trainer &operator=(const Trainer &trainer);

    /**
     * colosseum and stimulantTrainers both directly access the field of a trainer and are thus declared as friends.
     */
    friend class Colosseum;
    friend class StimulantTrainers;

    friend bool operator==(const Trainer &trainer1, const Trainer &trainer2);
    friend bool operator!=(const Trainer &trainer1, const Trainer &trainer2);
public:
    /**
     * a constructor for a trainer. receives an id, creates a trainer with a similar id and allocates a new splay tree for the trainer's gladiators.
     * the tree is initialized empty and thus the function runs in a time complexity of O(1).
     * @param id - the id of the trainer
     */
    explicit Trainer(int id);
    /**
     * a destructor for a trainer. deletes the gladiators tree. since it does not remove each gladiator and only frees the tree, it runs in a time
     * complexity of O(1).
     */
    ~Trainer();
    /**
     * finds the id of a trainer and returns it. the function directly accesses a class field and thus runs in a time complexity of O(1).
     * @return - theid of the gladiator
     */
    int getID();
    /**
     * an operator to determine out of two trainers which is the 'smaller'. the 'smaller' trainer will be the one with the lower id. the operator
     * directly accesses fields of the class and thus runs in a time complexity of O(1).
     * @param trainer2 - the trainer to compare to
     * @return - true if the first trainer is smaller than the second one and false otherwise.
     */
    bool operator<(const Trainer &trainer2) const;
    /**
     * an operator to determine out of two trainers which is the 'bigger'. the 'bigger' trainer will be the one with the higher id. the operator
     * directly accesses fields of the class and thus runs in a time complexity of O(1).
     * @param trainer2 - the trainer to compare to
     * @return - true if the first trainer is bigger than the second one and false otherwise.
     */
    bool operator>(const Trainer &trainer2) const;
    /**
     * a partial copy constructor for a trainer. receives an existing trainer and creates a new trainer with an identical id, though only allocated
     * an empty tree for the new trainer (since there is no use of it). since the tree is initialized empty, the function runs in a time complexity
     * of O(1).
     * @param trainer - the trainer to 'copy'
     */
    Trainer(const Trainer& trainer);
};
/**
 * a friend operator that receives two trainers and checks whether they are equal. two trainers will be equal in case the both have the same id,
 * since an id of a trainer is unique. the operator is not defined within the class since it's symmetric. the operator directly accesses fields
 * of the class and thus runs in a time complexity of O(1).
 * @param trainer1 - the first trainer
 * @param trainer2 - the second trainer
 * @return - true if the trainers are equal and false otherwise.
 */
bool operator==(const Trainer &trainer1, const Trainer &trainer2);
/**
 * a friend operator that receives two trainers and checks whether they are different. two trainers will be different in case they are not equal.
 * the operator is not defined within the class since it's symmetric. the operator directly accesses fields of the class and thus runs in a time
 * complexity of O(1).
 * @param trainer1 - the first trainer
 * @param trainer2 - the second trainer
 * @return - true if the trainers are different and false otherwise.
 */
bool operator!=(const Trainer &trainer1, const Trainer &trainer2);

#endif //WET1_TRAINER_H
