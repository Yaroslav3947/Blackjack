#include "Game.h"
#include <QDebug>

Game::Game(QObject *parent) : QObject(parent) {
    _deck = std::make_unique<Deck>();
    _player = std::make_unique<Player>("Player", 100);
    _dealer = std::make_unique<Dealer>();
}

const int POINTS_TO_WIN = 21;

void Game::start() {
    _deck->shuffle();

    dealCards();

    playerTurn();

    dealerTurn();

    determineWinner();
}

void Game::dealCards() {
    _player->addCard(_deck->dealCard());
    _player->addCard(_deck->dealCard());

    _dealer->addCard(_deck->dealCard());
    _dealer->addCard(_deck->dealCard());
}

void Game::playerTurn() {
    while (_player->getHandValue() < POINTS_TO_WIN) {
        qDebug() << "Player hand:" << _player->getHandValue();
        qDebug() << "Dealer hand:" << _dealer->getHand().front()->getValue();

        bool hit = true;

        if (hit) {
            _player->addCard(_deck->dealCard());
        } else {
            // Stands
            break;
        }
    }

    qDebug() << "Player hand:" << _player->getHandValue();
}

void Game::dealerTurn() {
    while (_dealer->getHandValue() < 17) { // we can calculate the % of win by putting different numbers
        _dealer->addCard(_deck->dealCard());

        qDebug() << "Dealer hand:" << _dealer->getHandValue();
    }

    qDebug() << "Dealer hand:" << _dealer->getHandValue();
}

void Game::determineWinner() {
    int playerHandValue = _player->getHandValue();
    int dealerHandValue = _dealer->getHandValue();

    if (playerHandValue > POINTS_TO_WIN) {
        qDebug() << "Player busts, dealer wins";
        _player->adjustBalance(-10);
    } else if (dealerHandValue > POINTS_TO_WIN) {
        qDebug() << "Dealer busts, player wins";
        _player->adjustBalance(10);
    } else if (playerHandValue > dealerHandValue) {
        qDebug() << "Player wins, Dealer busts";
        _player->adjustBalance(10);
    }
    else if (dealerHandValue > playerHandValue) {
        qDebug() << "Dealer wins, Player busts";
        _player->adjustBalance(-10);
    } else {
        qDebug() << "Tie";
    }
    emit _player->balanceChanged(_player->getBalance());
}
