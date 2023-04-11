#include "Game.h"
#include <QDebug>
#include <qstring.h>

Game::Game(QObject *parent) : QObject(parent) {
    _deck = std::make_unique<Deck>();
    _player = std::make_unique<Player>("Player", 100);
    _dealer = std::make_unique<Dealer>();
}
void Game::reset() {
    _player->clearHand();
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
    const int POINTS_FOR_VICTORY = 10;

    auto playerHandValue = _player->getHandValue();
    auto dealerHandValue = _dealer->getHandValue();

    if (playerHandValue > POINTS_TO_WIN) {
        _player->adjustBalance(-POINTS_FOR_VICTORY);
        return Winner::DEALER;
    } else if (dealerHandValue > POINTS_TO_WIN) {
        _player->adjustBalance(POINTS_FOR_VICTORY);
        return Winner::PLAYER;
    } else if (playerHandValue > dealerHandValue) {
        _player->adjustBalance(POINTS_FOR_VICTORY);
        return Winner::PLAYER;
    } else if (dealerHandValue > playerHandValue) {
        _player->adjustBalance(-POINTS_FOR_VICTORY);
        return Winner::DEALER;
    } else {
        return Winner::TIE;
    }
}

