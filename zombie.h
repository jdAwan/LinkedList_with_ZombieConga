#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <iostream>

class Zombie {
private:
    char type;

public:
    Zombie();
    Zombie(char type);
    char getType() const;
    bool operator==(const Zombie& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);
};

#endif  // ZOMBIE_H
