#include "Dealer.h"

Dealer::Dealer() : I_Participant("Dealer", 10000) {
}

void Dealer::addCard(std::shared_ptr<Card> card) {
    _hand.append(card);
}

QList<std::shared_ptr<Card> > Dealer::getHand() const {
    return I_Participant::getHand();
}

int Dealer::getHandValue() const {
    return I_Participant::getHandValue();
}

void Dealer::clearHand() {
    I_Participant::clearHand();
}

std::unique_ptr<Card> Dealer::getTopCard() const {
    if (_hand.empty()) {
        return nullptr;
    }
    return std::make_unique<Card>(*_hand.front());
}
