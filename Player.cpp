#include "Player.h"

#include <qdebug.h>

Player::Player(const QString &name, int balance, QObject *parent)
    : QObject(parent), _name(name), _balance(balance) {
}

void Player::addCard(std::shared_ptr<Card> card) {
    _hand.push_back(card);
}
bool isAllowedBet(const int &bet, const int &balance) {
    return bet <= balance;
}

void Player::setBet(int bet) {
    if(isAllowedBet(bet, this->_balance)) {
        _bet = bet;
    } else {
        throw std::out_of_range("Can't set bet <= 0");
    }
}

int Player::getHandValue() const {
    const int MAX_VALUE_ACE = 11;
    auto value = 0;
    auto hasAce = false;

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
}

bool Player::isBust() const {
    const int POINTS_TO_WIN = 21;
    return getHandValue() > POINTS_TO_WIN;
}

bool Player::isBankrupt() const {
    return _balance < _bet;
}

void Player::changeBet(int amount) {
    _bet += amount;
}
