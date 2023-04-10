#ifndef I_PARTICIPANT_H
#define I_PARTICIPANT_H

#include "Card.h"

#include <QList>
#include <QString>
#include <memory>

class I_Participant {
public:
    I_Participant(const QString &name, int balance);

    virtual void clearHand() = 0;
    virtual int getHandValue() const = 0;
    virtual void addCard(std::shared_ptr<Card> card) = 0;
    virtual QList<std::shared_ptr<Card>> getHand() const = 0;

    void adjustBalance(int amount);
    int getBalance() const {return _balance;};
    QString getName() const {return this->_name;};

    virtual ~I_Participant() = default;

private:
    QString _name;
    int _balance;
};

#endif // I_PARTICIPANT_H
