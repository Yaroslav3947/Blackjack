#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <vector>
#include <random>
#include <algorithm>

class Deck
{
public:
    Deck() = default;
    void shuffle();
    Card drawCard();
    int cardsLeft() const;
    ~Deck() = default;

private:
    std::vector<Card> m_cards;
    int m_nextCardIndex;
};

#endif // DECK_H
