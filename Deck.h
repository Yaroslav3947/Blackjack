#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>
#include <random>
#include <algorithm>

class Deck {
public:
    Deck() = default;
    void shuffle();
    std::shared_ptr<Card> dealCard();
    int cardsLeft() const;
    ~Deck() = default;

private:
    std::vector<Card> _cards;
    int _nextCardIndex;
};

#endif // DECK_H
