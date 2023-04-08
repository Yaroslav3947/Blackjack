#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

signals:

public slots:
    void start();

private:
    std::unique_ptr<Deck> m_deck;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<Dealer> m_dealer;

    void dealCards();
    void playerTurn();
    void dealerTurn();
    void determineWinner();
};

#endif // GAME_H
