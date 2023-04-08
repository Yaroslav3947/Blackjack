#include "Card.h"

Card::Card(Rank rank, Suit suit, const QString &frontImageFilePath, const QString &backImageFilePath) :
    _rank(rank), _suit(suit), _frontImage(frontImageFilePath), _backImage(backImageFilePath) {
}

int Card::getValue() const {
    if (_rank >= Rank::TEN) {
        return 10;
    } else if (_rank == Rank::ACE) {
        return 11;
    } else {
        return _rank;
    }
}
