//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORID_H
#define WET1_GLADIATORID_H

#include "Trainer.h"
/**
 * a class to hold a gladiator in a tree sorted by the id of the gladiators. a gladiator of this type holds his id, level and a pointer to his trainer.
 */
class GladiatorID {
private:
    int id;
    int level;
    Trainer *trainer_ptr;

    friend bool operator==(const GladiatorID &gladiator1, const GladiatorID &gladiator2);
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
     * a function that finds the id of a gladiator and returns it. directly accesses a field of the class and thus runs in a time complexity of O(1).
     * @return - the id of the gladiator
     */
    int getID() const;
    /**
     * a function that finds the level of a gladiator and returns it. directly accesses a field of the class and thus runs in a time complexity of O(1).
     * @return - the level of the gladiator
     */
    int getLevel() const;
    /**
     * receives a pointer to a trainer and places it in the field of the pointer to a trainer. directly changes a field in the class and thus runs in
     * a time complexity of O(1).
     * @param trainer - a pointer to the trainer to set
     */
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
/**
 * a friend operator that receives two gladiators and checks whether they are equal. two gladiators will be equal in case the both have the same id,
 * since an id of a gladiator is unique. the operator is not defined within the class since it's symmetric. the operator directly accesses fields
 * of the class and thus runs in a time complexity of O(1).
 * @param gladiator1 - the first gladiator
 * @param gladiator2 - the second gladiator
 * @return - true if the gladiators are equal and false otherwise.
 */
bool operator==(const GladiatorID &gladiator1, const GladiatorID &gladiator2);
/**
 * an operator that receives two gladiators and checks whether they are different. two gladiators will be different in case they are not similar. the
 * operator is not defined within the class since it's symmetric. the operator directly accesses fields of the class and thus runs in a time
 * complexity of O(1).
 * @param gladiator1 - the first gladiator
 * @param gladiator2 - the second gladiator
 * @return - true if the gladiators are different and false otherwise.
 */
bool operator!=(const GladiatorID &gladiator1, const GladiatorID &gladiator2);


#endif //WET1_GLADIATORID_H
