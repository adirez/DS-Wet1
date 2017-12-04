//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATORLEVEL_H
#define WET1_GLADIATORLEVEL_H


class GladiatorLevel {
protected:
    int id;
    int level;

    friend bool operator==(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2);
public:
    GladiatorLevel();
    GladiatorLevel(int id, int level);
    GladiatorLevel(const GladiatorLevel &gladiatorLevel);

    virtual ~GladiatorLevel() {};
    int getID() const;
    int getLevel() const;

    virtual bool operator<(const GladiatorLevel &gladiator2) const;
    virtual bool operator>(const GladiatorLevel &gladiator2) const;
};

bool operator==(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2);
bool operator!=(const GladiatorLevel &gladiator1, const GladiatorLevel &gladiator2);

#endif //WET1_GLADIATORLEVEL_H