#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QList>
#include <memory>
#include "Card.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(const QString& name, int balance, QObject *parent = nullptr);
    ~Player();

    void addCard(std::unique_ptr<Card> card);
    QList<std::unique_ptr<Card>> getHand() const;
    int getHandValue() const;
    void clearHand();
    int getBalance() const;
    void adjustBalance(int amount);

signals:

public slots:

private:
    QString m_name;
    int m_balance;
    QList<std::unique_ptr<Card>> m_hand;
};

#endif // PLAYER_H
