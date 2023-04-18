#pragma once

#include <vector>
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

    Card(Rank rank,
         Suit suit,
         const QString &frontImagePath,
         const QPixmap &backImagePath);
    ~Card() = default;
    bool isAce() const;
    int getValue() const;
    Rank getRank() const;
    Suit getSuit() const;
    QPixmap getBackImage() const;
    QPixmap getFrontImage() const;
    QPixmap getBackImagePath() const;
    QString getFrontImagePath(const Card::Suit &suit, const Card::Rank &rank, const QString &path = ":/images/cards/");
private:
    Rank _rank;
    Suit _suit;
    QPixmap _backImage;
    QPixmap _frontImage;
};

