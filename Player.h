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
    explicit Player(const QString &name, int balance, QObject *parent = nullptr);
    ~Player() = default;

    void addCard(std::shared_ptr<Card> card);
    QList<std::shared_ptr<Card>> getHand() const {return this->_hand;};
    int getHandValue() const;
    void clearHand();
    int getBalance() const{return _balance;};
    void adjustBalance(int amount);
    bool isBust() const;

signals:
    void balanceChanged(int newBalance);

public slots:

private:
    QString _name;
    int _balance;
    QList<std::shared_ptr<Card>> _hand;
};

#endif // PLAYER_H
