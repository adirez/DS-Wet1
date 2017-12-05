//
// Created by adire on 05-Dec-17.
//

#ifndef WET1_STIMULANT_H
#define WET1_STIMULANT_H

#include "GladiatorLevel.h"
#include "Trainer.h"

/**
 * a function object to be used in Stimulant for gladiators of type GladiatorLevel.
 * contains the stimulant code and factor to operate with, two arrays to which we will sort the gladiators (one for those who have used the drug and
 * one for those who haven't) and index for each of the arrays.
 */
class Stimulant {
private:
    int code;
    int factor;
    GladiatorLevel *gladiators1;
    GladiatorLevel *gladiators2;
    int i;
    int j;
    int num_of_gladiators;

    friend class Colosseum;
    friend class StimulantTrainers;

public:
    /**
     * a constructor for the function object. receiving the parameters and allocating the arrays to which we will sort the gladiators by the stimulant
     * code. index i and index j are initialized to 0 in order to start from the beginning of the arrays. the constructor only allocates arrays and
     * thus runs in a time complexity of O(1).
     * @param code - the code to check the gladiators by
     * @param factor - the factor to increase the level of the relevant gladiators by
     * @param num_of_gladiators - the number of gladiators to sort
     */
    Stimulant(int code, int factor, int num_of_gladiators);
    Stimulant(const Stimulant& stimulant);

    /**
     * a destructor for the function object. deletes both of the allocated arrays. the destructor only deletes two arrays and thus runs in a time
     * complexity of O(1).
     */
    ~Stimulant();

    /**
     * the operator sent to inOrder by Stimulant function. the action will be done through operator(). each gladiator sent to () will be
     * checked with the stimulant code and according to that sent to the relevant allocated array and increase the relevant index. the gladiators sent
     * to the first array are the ones that have been using the drug and therefore their level will be increased according to the factor. the function
     * calls a constructor and uses 'get' functions and thus runs in a time complexity of O(1).
     * @param gladiator - the gladiator found at inOrder which will be copied to one of the arrays
     */
    void operator()(GladiatorLevel *gladiator);

};





/**
 * a function object to be used in Stimulant for trainers to sort gladiators of type GladiatorLevel. receives as a parameter the function object of
 * GladiatorLevel since the gladiators in the trainers' tree are of type GladiatorLevel. the function goes through a trainer at a time and for each
 * trainer calls StimulantLevel for the tree in order to sort it's own tree of gladiators.
 */
class StimulantTrainers {
private:
    Stimulant *stimulant;
public:

    /**
     * a constructor for the function object. receives a StimulantLevel in order to call for each of the trainers for their own trees of gladiators.
     * @param stimulant - the function object called for the trainers' trees
     */
    explicit StimulantTrainers(Stimulant *stimulant) : stimulant(stimulant) {}

    /**
     * empty destructor for the function object
     */
    ~StimulantTrainers() {}

    /**
     * the operator sent to inOrder by Stimulant function. the action will be done through operator(). each trainer sent to () will have it's
     * gladiators tree sent to stimulant compatible for GladiatorLevel. the tree will then be checked with the stimulant code and according to
     * that gladiators will be sent to the relevant allocated array and increase the relevant index of StimulantLevel. StimulantLevel runs in a time
     * complexity of O(1) per single gladiator. therefore, in the worst case scenario a trainer will have 'n' gladiators and thus the function will
     * run in a time complexity of O(n).
     * @param trainer - the trainer whose tree will be sent to StimulateLevel
     */
    void operator()(Trainer *trainer);
};


#endif //WET1_STIMULANT_H
