#pragma once

#include <random>
#include <vector>
#include <QString>

#include "Card.h"

class Deck {
public:
    Deck() = default;
    void pushCards();
    void shuffle();
    std::shared_ptr<Card> dealCard();
    std::vector<Card> getCards() const {return _cards;};
    std::shared_ptr<Card> getCard() const {return _card;};
    ~Deck() = default;
private:
    std::shared_ptr<Card> _card;
    std::vector<Card> _cards;
    int _nextCardIndex;
};

