#include "Deck.h"

void Deck::pushCards() {
    this->_cards.clear();
    for (int s = Card::Suit::HEARTS; s <= Card::Suit::SPADES; s++) {
        for (int r = Card::Rank::ACE; r <= Card::Rank::KING; r++) {
            Card::Suit suit = static_cast<Card::Suit>(s);
            Card::Rank rank = static_cast<Card::Rank>(r);

            QString frontImagePath = getCard()->getFrontImagePath(suit, rank);
            QPixmap backImagePath = getCard()->getBackImagePath();
            _cards.push_back({rank, suit, frontImagePath, backImagePath});
        }
    }
}
void Deck::shuffle() {
    for (int i = _cards.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(_cards[i], _cards[j]);
    }
    _nextCardIndex = 0;
}
//void Deck::shuffle() {
//    std::random_device rd;
//    std::mt19937 g(rd());
//    std::shuffle(_cards.begin(), _cards.end(), g);
//    _nextCardIndex = 0;
//}

std::shared_ptr<Card> Deck::dealCard() {
    if (_nextCardIndex >= static_cast<int>(_cards.size())) {
        throw std::out_of_range("No more cards in the deck!");
    }
    auto card = std::make_shared<Card>(_cards[_nextCardIndex]);
    _cards.erase(_cards.begin() + _nextCardIndex);
    return card;
}

