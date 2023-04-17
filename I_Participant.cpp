#include "I_Participant.h"

I_Participant::I_Participant(const QString &name, const int &balance) :
    _name(name), _balance(balance) {
}

QList<std::shared_ptr<Card> > I_Participant::getHand() const {
    return _hand;
}

void I_Participant::clearHand() {
    _hand.clear();
}

int I_Participant::getHandValue() const {
    const int MAX_HAND_VALUE = 21;
    int handValue = 0;
    int aceCount = 0;

    for (const auto& card : _hand) {
        int cardValue = card->getValue();
        if (cardValue == 1) {
            ++aceCount;
        }
        handValue += cardValue;
    }

    while (aceCount > 0 && handValue + 10 <= MAX_HAND_VALUE) {
        handValue += 10;
        --aceCount;
    }

    return handValue;
}

void I_Participant::addCard(std::shared_ptr<Card> card) {
    _hand.push_back(card);
}

void I_Participant::adjustBalance(const int &amount) {
    _balance += amount;
}

int I_Participant::getBalance() const {
    return _balance;
}

QString I_Participant::getName() const {
    return _name;
}
