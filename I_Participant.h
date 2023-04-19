#pragma once

#include <QList>
#include "Card.h"
#include "qobject.h"

class I_Participant: public QObject {
public:
    I_Participant(const QString &name, const int &balance);
    virtual void clearHand();
    virtual int getBalance() const;
    virtual QString getName() const;
    virtual int getHandValue() const;
    virtual void adjustBalance(const int &amount);
    virtual void addCard(std::shared_ptr<Card> card);
    virtual QList<std::shared_ptr<Card>> getHand() const;
    virtual ~I_Participant() = default;
protected:
    QString _name;
    int _balance;
    QList<std::shared_ptr<Card>> _hand;

};
