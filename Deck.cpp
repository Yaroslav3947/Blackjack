#include "Deck.h"

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(_cards.begin(), _cards.end(), g);
    _nextCardIndex = 0;
}

std::shared_ptr<Card> Deck::dealCard() {
    if (_nextCardIndex >= static_cast<int>(_cards.size())) {
        throw std::out_of_range("No more cards in the deck!");
    }
    auto card = std::make_shared<Card>(_cards[_nextCardIndex]);
    _nextCardIndex++;
    return card;
}

int Deck::cardsLeft() const {
    return _cards.size() - _nextCardIndex;
}
