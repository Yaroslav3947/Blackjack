#include "Game.h"

Game::Game(QObject *parent) :
    QObject(parent),
    _deck(std::make_unique<Deck>()),
    _player(std::make_unique<Player>("Player", 1000)),
    _dealer(std::make_unique<Dealer>()) {
}

void Game::reset() {
    _player->clearHand();
    _player->setBet(0);
    _dealer->clearHand();
    _deck->pushCards();
}

void Game::dealCards() {
    _player->addCard(_deck->dealCard());
    _player->addCard(_deck->dealCard());
    _dealer->addCard(_deck->dealCard());
}

void Game::dealerTurn() {
    const int DEALER_MIN_HAND_VALUE = 18; // we can calculate the % of win by putting different numbers

    while (_dealer->getHandValue() < DEALER_MIN_HAND_VALUE) {
        _dealer->addCard(_deck->dealCard());
    }
}
Game::Winner Game::determineWinner() {
    const int POINTS_TO_WIN = 21;

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

