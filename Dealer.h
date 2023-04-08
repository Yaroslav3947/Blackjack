#ifndef DEALER_H
#define DEALER_H

#include "Participant.h"

class Dealer : public Participant {
public:
    Dealer();
    virtual ~Dealer();

    void addCard(std::shared_ptr<Card> card) override;
    QList<std::shared_ptr<Card>> getHand() const override;
    int getHandValue() const override;
    void clearHand() override;
    std::unique_ptr<Card> getFirstCard() const;
};

#endif // DEALER_H
