#pragma once

#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

class Game : public QObject {
    Q_OBJECT
public:
    enum class Winner {
            PLAYER,
            DEALER,
            TIE
    };
    Game(QObject *parent = nullptr);
    void reset();
    void dealCards();
    void dealerTurn();
    Game::Winner determineWinner();
    Player *getPlayer() const { return _player.get(); }
    Dealer *getDealer() const { return _dealer.get(); }
    Deck *getDeck() const { return _deck.get(); }
private:
    std::unique_ptr<Deck> _deck;
    std::unique_ptr<Player> _player;
    std::unique_ptr<Dealer> _dealer;
};
