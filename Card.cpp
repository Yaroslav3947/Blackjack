#include "Card.h"

Card::Card(Rank rank, Suit suit, const QString &frontImagePath, const QPixmap &backImagePath):
    _rank(rank), _suit(suit), _backImage(backImagePath), _frontImage(frontImagePath) {
}

bool Card::isAce() const {
    return _rank == Rank::ACE;
}

static QString suitToString(Card::Suit suit) {
    switch (suit) {
        case Card::Suit::CLUBS: return "clubs";
        case Card::Suit::DIAMONDS: return "diamonds";
        case Card::Suit::HEARTS: return "hearts";
        case Card::Suit::SPADES: return "spades";
        default: return "";
    }
}

QString rankToString(Card::Rank rank) {
    std::vector<QString> rankStrings = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
    };
    return rankStrings[static_cast<int>(rank) - 1];
}

int Card::getValue() const {
    switch (_rank) {
    case ACE:
        return 1;
    case TWO:
            return 2;
        case THREE:
            return 3;
        case FOUR:
            return 4;
        case FIVE:
            return 5;
        case SIX:
            return 6;
        case SEVEN:
            return 7;
        case EIGHT:
            return 8;
        case NINE:
            return 9;
        default:
            return 10;
    }
}

Card::Rank Card::getRank() const {
    return _rank;
}

Card::Suit Card::getSuit() const {
    return _suit;
}

QString Card::getFrontImagePath(const Card::Suit &suit, const Card::Rank &rank)  {
    return ":/images/cards2/" +
            rankToString(rank) +
            "_of_" +
            suitToString(suit) +
            ".png";
}

QPixmap Card::getBackImagePath() const {
    return QPixmap(":/images/cards2/backImage.png");
}

QPixmap Card::getBackImage() const {
    return _backImage;
}

QPixmap Card::getFrontImage() const {
    return _frontImage;
}

