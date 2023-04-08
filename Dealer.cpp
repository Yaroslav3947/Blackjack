#include "Dealer.h"

Dealer::Dealer() : I_Participant("Dealer", 100) {
}

void Dealer::addCard(std::shared_ptr<Card> card) {
    _hand.append(card);
}

int Dealer::getHandValue() const {
    const int POINTS_TO_WIN = 21;
    int value = 0;
    int aceCount = 0;

    for (const auto &card : _hand) {
        value += card->getValue();

        if (card->isAce()) {
            ++aceCount;
        }
    }

    while (value > POINTS_TO_WIN && aceCount > 0) {
        value -= 10;
        --aceCount;
    }

    return value;
}

void Dealer::clearHand() {
    _hand.clear();
}

std::unique_ptr<Card> Dealer::getTopCard() const {
    if (_hand.size() > 0) {
        return std::make_unique<Card>(*_hand[0]);
    } else {
        return nullptr;
    }
}
