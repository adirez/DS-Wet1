//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORLEVEL_H
#define WET1_GLADIATORLEVEL_H

/**
 * a class to hold a gladiator in a tree sorted by the level of the gladiators. a gladiator of this type only hold his id and level.
 */
class GladiatorLevel {
protected:
    int id;
    int level;

    friend bool operator==(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2);
public:
    /**
     * an empty constructor for GladiatorLevel. inits with id and level as -1.
     * the function only creates a gladiator and thus runs in a time complexity of O(1).
     */
    GladiatorLevel();
    /**
     * a full constructor for GladiatorLevel. receives all the parameteres and creates a gladiator with the fields accordingly.
     * the function only creates a gladiator and thus runs in a time complexity of O(1).
     * @param id - the id of the gladiator
     * @param level - the level of the gladiator
     */
    GladiatorLevel(int id, int level);
    /**
     * a copy constructor for GladiatorLevel. receives a gladiator and creates a new gladiator with fields similar to those of the one received.
     * the function only reads fields of the received gladiator and creates a new one and thus runs in a time complexity of O(1).
     * @param gladiatorLevel
     */
    GladiatorLevel(const GladiatorLevel &gladiatorLevel);
    /**
     * an empty destructor for the gladiator. empty and thus runs in a time complexity of O(1).
     */
    virtual ~GladiatorLevel() {};
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
     * an operator to determine out of two gladiators which is the 'smaller'. since the type is of GladiatorLevel, the 'smaller' gladiator will be the
     * one with the lower level. in case of identical levels, the smaller one will be the one with the bigger id. the operator directly accesses fields
     * of the class and thus runs in a time complexity of O(1).
     * @param gladiator2 - the gladiator to compare to
     * @return - true if the first gladiator is smaller than the second one and false otherwise.
     */
    virtual bool operator<(const GladiatorLevel &gladiator2) const;
    /**
     * an operator to determine out of two gladiators which is the 'bigger'. since the type is of GladiatorLevel, the 'bigger' gladiator will be the
     * one with the higher level. in case of identical levels, the smaller one will be the one with the lower id.the operator directly accesses fields
     * of the class and thus runs in a time complexity of O(1).
     * @param gladiator2 - the gladiator to compare to
     * @return - true if the first gladiator is bigger than the second one and false otherwise.
     */
    virtual bool operator>(const GladiatorLevel &gladiator2) const;
};

/**
 * a friend operator that receives two gladiators and checks whether they are equal. two gladiators will be equal in case the both have the same id,
 * since an id of a gladiator is unique. the operator is not defined within the class since it's symmetric. the operator directly accesses fields
 * of the class and thus runs in a time complexity of O(1).
 * @param gladiator1 - the first gladiator
 * @param gladiator2 - the second gladiator
 * @return - true if the gladiators are equal and false otherwise.
 */
bool operator==(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2);
/**
 * an operator that receives two gladiators and checks whether they are different. two gladiators will be different in case they are not similar. the
 * operator is not defined within the class since it's symmetric. the operator directly accesses fields of the class and thus runs in a time
 * complexity of O(1).
 * @param gladiator1 - the first gladiator
 * @param gladiator2 - the second gladiator
 * @return - true if the gladiators are different and false otherwise.
 */
bool operator!=(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2);

#endif //WET1_GLADIATORLEVEL_H