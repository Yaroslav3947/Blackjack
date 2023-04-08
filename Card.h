#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QPixmap>

class Card {
public:
    enum Suit {
        HEARTS,
        DIAMONDS,
        CLUBS,
        SPADES
    };
    enum Rank {
        ACE = 1,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING
    };

    Card(Rank rank, Suit suit, const QString &frontImageFilePath, const QString &backImageFilePath);
    ~Card() = default;
    bool isAce() const{return this->_rank == Rank::ACE;};
    int getValue() const;
    Rank getRank() const {return this->_rank;};
    Suit getSuit() const {return this->_suit;};
    QPixmap getFrontImage() const {return this->_frontImage;};
    QPixmap getBackImage() const {return this->_backImage;};

private:
    Rank _rank;
    Suit _suit;
    QPixmap _frontImage;
    QPixmap _backImage;
};

#endif // CARD_H
