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

public slots:
    void start();

private:
    std::unique_ptr<Deck> _deck;
    std::unique_ptr<Player> _player;
    std::unique_ptr<Dealer> _dealer;

    void dealCards();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
};

#endif // GAME_H
