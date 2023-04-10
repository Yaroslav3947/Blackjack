#include "Deck.h"

static std::string suitToString(Card::Suit suit) {
    switch (suit) {
        case Card::Suit::CLUBS: return "clubs";
        case Card::Suit::DIAMONDS: return "diamonds";
        case Card::Suit::HEARTS: return "hearts";
        case Card::Suit::SPADES: return "spades";
        default: return "";
    }
}

static std::string rankToString(Card::Rank rank) {
    switch (rank) {
        case Card::Rank::ACE: return "1";
        case Card::Rank::TWO: return "2";
        case Card::Rank::THREE: return "3";
        case Card::Rank::FOUR: return "4";
        case Card::Rank::FIVE: return "5";
        case Card::Rank::SIX: return "6";
        case Card::Rank::SEVEN: return "7";
        case Card::Rank::EIGHT: return "8";
        case Card::Rank::NINE: return "9";
        case Card::Rank::TEN: return "10";
        case Card::Rank::JACK: return "11";
        case Card::Rank::QUEEN: return "12";
        case Card::Rank::KING: return "13";
        default: return "";
    }
}

void Deck::pushCards() {
    for (int s = Card::Suit::HEARTS; s <= Card::Suit::SPADES; s++) {
        for (int r = Card::Rank::ACE; r <= Card::Rank::KING; r++) {
            Card::Suit suit = static_cast<Card::Suit>(s);
            Card::Rank rank = static_cast<Card::Rank>(r);

            QString frontImageFilePath = "C:/Users/Yaroslav/Desktop/images/cards/" +
                                          QString::fromStdString(rankToString(rank)) +
                                          "_of_" +
                                          QString::fromStdString(suitToString(suit)) +
                                          ".png";
            _cards.push_back({rank, suit, frontImageFilePath});
        }
    }
}

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
    _cards.erase(_cards.begin() + _nextCardIndex);
    return card;
}


int Deck::cardsLeft() const {
    return _cards.size() - _nextCardIndex;
}
