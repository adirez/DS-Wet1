//
// Created by adire on 01-Dec-17.
//

#ifndef WET1_GLADIATOR_H
#define WET1_GLADIATOR_H

class Gladiator{
protected:
    friend class Stimulant;
    friend class Colosseum;

    int id;
    int level;
    virtual bool operator<(const Gladiator &gladiator2) const = 0;
    virtual bool operator>(const Gladiator &gladiator2) const = 0;

public:
    Gladiator() : id(0), level(0) {}
    Gladiator(int id, int level);
    virtual ~Gladiator() {};
    int getID() const;
};

bool operator==(const Gladiator &gladiator1, const Gladiator &gladiator2);
bool operator!=(const Gladiator &gladiator1, const Gladiator &gladiator2);


#endif //WET1_GLADIATOR_H
