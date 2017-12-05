//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORID_H
#define WET1_GLADIATORID_H

#include "Trainer.h"
#include "GladiatorLevel.h"

/**
 * a class to hold a gladiator in a tree sorted by the id of the gladiators. a gladiator of this type will inherit from GladiatorLevel the id & level
 * fields and hold a pointer to his trainer.
 */
class GladiatorID : public GladiatorLevel{
private:
    Trainer *trainer_ptr;

public:
    /**
     * an empty constructor for GladiatorID. inits with id and level as -1 and ptr to the trainer as NULL.
     * the function only creates a gladiator and thus runs in a time complexity of O(1).
     */
    GladiatorID();
    /**
     * a full constructor for GladiatorID. receives all the parameteres and creates a gladiator with the fields accordingly.
     * the function only creates a gladiator and thus runs in a time complexity of O(1).
     * @param id - the id of the gladiator
     * @param level - the level of the gladiator
     * @param ptr_to_trainer - the pointer to the trainer
     */
    GladiatorID(int id, int level, Trainer *ptr_to_trainer);
    /**
     * a full constructor for GladiatorID. receives all the parameteres and creates a gladiator with the fields accordingly.
     * the function only creates a gladiator and thus runs in a time complexity of O(1).
     * @param id - the id of the gladiator
     * @param level - the level of the gladiator
     * @param ptr_to_trainer - a pointer to the trainer to whom the gladiator belongs
     */
    GladiatorID(int id, int level);
    /**
     * a copy constructor for GladiatorLevel. receives a gladiator and creates a new gladiator with fields similar to those of the one received.
     * the function only reads fields of the received gladiator and creates a new one and thus runs in a time complexity of O(1).
     * @param gladiatorID
     */
    GladiatorID(const GladiatorID &gladiatorID);
    /**
     * an empty destructor for the gladiator. Empty and thus runs in a time complexity of O(1).
     */
    ~GladiatorID() {};
    /**
    * receives a pointer to a trainer and places it in the field of the pointer to a trainer. directly changes a field in the class and thus runs in
    * a time complexity of O(1).
    * @param trainer - a pointer to the trainer to set
    */

    void setLevel(int factor);

    void setTrainerPtr(Trainer *trainer);
    /**
     * a function that finds the pointer of a gladiator's trainer and returns it. directly accesses a field of the class and thus runs in a time
     * complexity of O(1).
     * @return - the pointer to the gladiator's trainer
     */
    Trainer* getTrainerPtr() const;
    /**
     * an operator to determine out of two gladiators which is the 'smaller'. since the type is of GladiatorID, the 'smaller' gladiator will be the
     * one with the lower id. the operator directly accesses fields of the class and thus runs in a time complexity of O(1).
     * @param gladiator2 - the gladiator to compare to
     * @return - true if the first gladiator is smaller than the second one and false otherwise.
     */
    bool operator<(const GladiatorID &gladiator2) const;
    /**
      * an operator to determine out of two gladiators which is the 'bigger'. since the type is of GladiatorID, the 'bigger' gladiator will be the
      * one with the higher id. the operator directly accesses fields of the class and thus runs in a time complexity of O(1).
      * @param gladiator2 - the gladiator to compare to
      * @return - true if the first gladiator is bigger than the second one and false otherwise.
      */
    bool operator>(const GladiatorID &gladiator2) const;
};

#endif //WET1_GLADIATORID_H
