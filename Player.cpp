#include "Player.h"

Player::Player(const QString &name, const int &balance)
    : I_Participant(name, balance) {
}

void Player::clearHand() {
    I_Participant::clearHand();
}
int Player::getHandValue() const {
    return I_Participant::getHandValue();
}

int Player::getBalance() const {
    return I_Participant::getBalance();
}

void Player::addCard(std::shared_ptr<Card> card) {
    I_Participant::addCard(card);
}

QList<std::shared_ptr<Card>> Player::getHand() const {
    return I_Participant::getHand();
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

void Player::adjustBalance(const int &amount) {
    I_Participant::adjustBalance(amount);
}

int Player::getBet() const {
    return _bet;
}
