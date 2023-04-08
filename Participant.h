#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "Card.h"

#include <QList>
#include <QString>
#include <memory>

class Participant {
public:
    Participant(const QString &name, int balance);
    virtual ~Participant();

    QString getName() const {return this->m_name;};
    virtual void addCard(std::shared_ptr<Card> card) = 0;
    virtual QList<std::shared_ptr<Card>> getHand() const = 0;
    virtual int getHandValue() const = 0;
    virtual void clearHand() = 0;
    int getBalance() const {return m_balance;};
    void adjustBalance(int amount);

private:
    QString m_name;
    int m_balance;
};

#endif // PARTICIPANT_H
