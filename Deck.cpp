#include "Deck.h"

static std::string suitToString(Card::Suit suit) {
    switch (suit) {
        case Card::Suit::CLUBS: return "C";
        case Card::Suit::DIAMONDS: return "D";
        case Card::Suit::HEARTS: return "H";
        case Card::Suit::SPADES: return "S";
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
        case Card::Rank::JACK: return "J";
        case Card::Rank::QUEEN: return "Q";
        case Card::Rank::KING: return "K";
        default: return "";
    }
}

void Deck::pushCards() {
    for (int s = Card::Suit::HEARTS; s <= Card::Suit::SPADES; s++) {
        for (int r = Card::Rank::ACE; r <= Card::Rank::KING; r++) {
            Card::Suit suit = static_cast<Card::Suit>(s);
            Card::Rank rank = static_cast<Card::Rank>(r);

            QString frontImageFilePath = QDir::currentPath() + "/images/cards/" +
                                          QString::fromStdString(suitToString(suit)) +
                                          QString::fromStdString(rankToString(rank)) +
                                          ".png";

            QString backImageFilePath;

            _cards.push_back({rank, suit, frontImageFilePath, backImageFilePath});
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
    _nextCardIndex++;
    return card;
}

int Deck::cardsLeft() const {
    return _cards.size() - _nextCardIndex;
}
