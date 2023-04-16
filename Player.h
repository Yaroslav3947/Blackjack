#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QList>
#include <memory>
#include "Card.h"

class Player : public QObject {
    Q_OBJECT
public:
    explicit Player(const QString &name, int balance = 1000, QObject *parent = nullptr);
    ~Player() = default;

    void addCard(std::shared_ptr<Card> card);
    QList<std::shared_ptr<Card>> getHand() const {return this->_hand;};
    int getHandValue() const;
    void clearHand();
    int getBalance() const{return _balance;};
    void adjustBalance(int amount);
    bool isBust() const;
    void setBalance(int balance);
    void setBet(int bet);
    int getBet() const {return _bet;};
    bool isBankrupt() const;
    void changeBet(int amount);
signals:
    void balanceChanged(int newBalance);

private:
    QString _name;
    int _balance;
    QList<std::shared_ptr<Card>> _hand;
    int _bet = 0;
};

#endif // PLAYER_H
