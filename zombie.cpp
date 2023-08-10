#include "zombie.h"

Zombie::Zombie() : type(' ') {}

Zombie::Zombie(char type) : type(type) {}

char Zombie::getType() const {
    return type;
}

bool Zombie::operator==(const Zombie& other) const {
    return type == other.type;
}

std::ostream& operator<<(std::ostream& os, const Zombie& zombie) {
    os << zombie.type;
    return os;
}

