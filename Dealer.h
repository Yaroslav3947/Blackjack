#ifndef DEALER_H
#define DEALER_H

#include "I_Participant.h"

class Dealer : public I_Participant {
public:
    Dealer();

//    virtual ~Dealer();

    void addCard(std::shared_ptr<Card> card) override;
    QList<std::shared_ptr<Card>> getHand() const override {return this->_hand;};
    int getHandValue() const override;
    void clearHand() override;
    std::unique_ptr<Card> getTopCard() const;
private:
    QList<std::shared_ptr<Card>> _hand;
};

#endif // DEALER_H
