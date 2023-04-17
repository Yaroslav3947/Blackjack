#pragma once

#include <I_Participant.h>

class Player : public I_Participant {
    Q_OBJECT
public:
    constexpr static int defaultBalance = 1000;
    Player(const QString &name, const int &balance = defaultBalance);
    int getBet() const;
    bool isBust() const;
    void setBet(int bet);
    bool isBankrupt() const;
    void clearHand() override;
    void changeBet(int amount);
    int getBalance() const override;
    int getHandValue() const override;
    void adjustBalance(const int &amount) override;
    void addCard(std::shared_ptr<Card> card) override;
    QList<std::shared_ptr<Card>> getHand() const override;
    ~Player() = default;
private:
    int _bet = 0;
};

