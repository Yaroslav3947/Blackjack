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

    Rank getRank() const {return this->rank_;};
    Suit getSuit() const {return this->suit_;};
    QPixmap getFrontImage() const {return this->frontImage_;};
    QPixmap getBackImage() const {return this->backImage_;};

private:
    Rank rank_;
    Suit suit_;
    QPixmap frontImage_;
    QPixmap backImage_;
};

#endif // CARD_H
