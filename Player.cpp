#include "Player.h"

Player::Player(const QString &name, int balance, QObject *parent)
    : QObject(parent), _name(name), _balance(balance) {
}

void Player::addCard(std::shared_ptr<Card> card) {
    _hand.push_back(card);
}


int Player::getHandValue() const {
    const int MAX_VALUE_ACE = 11;
    int value = 0;
    bool hasAce = false;

    for (const auto &card : _hand) {
        if (card->getRank() == Card::Rank::ACE) {
            hasAce = true;
        }
        value += card->getValue();
    }

    if (hasAce && value <= MAX_VALUE_ACE) {
        value += 10;
    }

    return value;
}

void Player::clearHand() {
    _hand.clear();
}

void Player::adjustBalance(int amount) {
    _balance += amount;
    emit balanceChanged(_balance);
}
