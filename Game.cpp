#include "Game.h"
#include <QDebug>
#include <qstring.h>

Game::Game(QObject *parent) : QObject(parent) {
    _deck = std::make_unique<Deck>();
    _player = std::make_unique<Player>("Player", 100);
    _dealer = std::make_unique<Dealer>();
}
static QString suitToString(Card::Suit suit) {
    switch (suit) {
        case Card::Suit::CLUBS: return "C";
        case Card::Suit::DIAMONDS: return "D";
        case Card::Suit::HEARTS: return "H";
        case Card::Suit::SPADES: return "S";
        default: return "";
    }
}



const int POINTS_TO_WIN = 21;

void Game::start() {
    //TODO: implement multithreading
    _deck->pushCards();
    _deck->shuffle();

    dealCards();
    qDebug() << "LIST:";
    for(const auto &x : _deck->getCards()) {
        qDebug() << x.getValue() << " " << suitToString(x.getSuit());
    }

    playerTurn();

    dealerTurn();

    determineWinner();
}

void Game::dealCards() {
    _player->addCard(_deck->dealCard());
    qDebug() << "Random value: (P)" << _player->getHand()[0]->getValue();


    _player->addCard(_deck->dealCard());
    qDebug() << "Random value: (P)" << _player->getHand()[1]->getValue();
    qDebug() << "Hand Value: (P)" << _player->getHandValue();


    _dealer->addCard(_deck->dealCard());
    qDebug() << "Random value: (D) " << _dealer->getHand()[0]->getValue();
    _dealer->addCard(_deck->dealCard());
    qDebug() << "Random value: (D)" << _dealer->getHand()[1]->getValue();
    qDebug() << "Hand Value: (D)" << _dealer->getHandValue();
}

void Game::playerTurn() {
    while (_player->getHandValue() < POINTS_TO_WIN) {
        qDebug() << "Player hand:" << _player->getHandValue();
        qDebug() << "Dealer hand:" << _dealer->getHandValue();
//        qDebug() << "Dealer top card:" << _dealer->getHand().front()->getValue();
        bool hit = true;

        if (hit) {
            auto cardToAdd = _deck->dealCard();
            _player->addCard(cardToAdd);
            qDebug() << " + " << cardToAdd->getValue() << "to player";
        } else {
            // Stands
            break;
        }
    }

    qDebug() << "Player hand(last):" << _player->getHandValue();
}

void Game::dealerTurn() {
    while (_dealer->getHandValue() < 17) { // we can calculate the % of win by putting different numbers
        auto cardToAdd = _deck->dealCard();
        _dealer->addCard(cardToAdd);

        qDebug() << "Dealer + " << cardToAdd->getValue();
        qDebug() << "Dealer hand:" << _dealer->getHandValue();
    }

    qDebug() << "Dealer hand(last):" << _dealer->getHandValue();
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
