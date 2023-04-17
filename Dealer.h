#pragma once

#include "I_Participant.h"

class Dealer : public I_Participant {
public:
    Dealer();
    void clearHand() override;
    int getHandValue() const override;
    std::unique_ptr<Card> getTopCard() const;
    void addCard(std::shared_ptr<Card> card) override;
    QList<std::shared_ptr<Card>> getHand() const override;
};

