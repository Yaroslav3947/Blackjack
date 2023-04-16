#include "Game.h"
#include <QDebug>
#include <qstring.h>

Game::Game(QObject *parent) : QObject(parent) {
    _deck = std::make_unique<Deck>();
    _player = std::make_unique<Player>("Player");
    _dealer = std::make_unique<Dealer>();
}
void Game::reset() {
    _player->clearHand();
    _player->setBet(0);
    _dealer->clearHand();
    this->getDeck()->pushCards();
}

void Game::dealCards() {
    _player->addCard(_deck->dealCard());
    _player->addCard(_deck->dealCard());

    _dealer->addCard(_deck->dealCard());
}

void Game::dealerTurn() {
    while (_dealer->getHandValue() < 18) { // we can calculate the % of win by putting different numbers
        auto cardToAdd = _deck->dealCard();
        _dealer->addCard(cardToAdd);
    }
}
Game::Winner Game::determineWinner() {
    auto bet = _player->getBet();

    auto playerHandValue = _player->getHandValue();
    auto dealerHandValue = _dealer->getHandValue();

    if (playerHandValue > POINTS_TO_WIN) {
        _player->adjustBalance(-bet);
        return Winner::DEALER;
    } else if (dealerHandValue > POINTS_TO_WIN) {
        _player->adjustBalance(bet);
        return Winner::PLAYER;
    } else if (playerHandValue > dealerHandValue) {
        _player->adjustBalance(bet);
        return Winner::PLAYER;
    } else if (dealerHandValue > playerHandValue) {
        _player->adjustBalance(-bet);
        return Winner::DEALER;
    } else {
        return Winner::TIE;
    }
}

