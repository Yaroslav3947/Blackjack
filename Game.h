#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

class Game : public QObject {
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void start();
    void dealCards();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
    const int POINTS_TO_WIN = 21;
    Player *getPlayer() const { return _player.get(); }
    Dealer *getDealer() const { return _dealer.get(); }
    Deck *getDeck() const { return _deck.get(); }
signals:
    void balanceChanged(int balance);
private:
    std::unique_ptr<Deck> _deck;
    std::unique_ptr<Player> _player;
    std::unique_ptr<Dealer> _dealer;
};


#endif // GAME_H
