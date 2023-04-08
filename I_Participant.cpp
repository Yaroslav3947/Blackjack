#include "I_Participant.h"

I_Participant::I_Participant(const QString &name, int balance) :
    _name(name), _balance(balance) {
}

void I_Participant::adjustBalance(int amount) {
    _balance += amount;
}
