#ifndef DECK_H
#define DECK_H

#include "Card.h"

#include <qdir.h>

#include <vector>
#include <random>
#include <algorithm>
#include <QString>

class Deck {
public:
    Deck() = default;
    void pushCards();
    void shuffle();
    std::shared_ptr<Card> dealCard();
    int cardsLeft() const;
    std::vector<Card> getCards() const {return _cards;};
    ~Deck() = default;

private:
    Card *card;
    std::vector<Card> _cards;
    int _nextCardIndex;
};

#endif // DECK_H
