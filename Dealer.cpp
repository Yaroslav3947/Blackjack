//#include "Dealer.h"

//Dealer::Dealer() {}

//Dealer::~Dealer() {}

//void Dealer::addCard(std::unique_ptr<Card> card) {
//    m_hand.push_back(std::move(card));
//}

//QList<std::unique_ptr<Card>> Dealer::getHand() const {
//    return m_hand;
//}

//int Dealer::getHandValue() const {
//    int value = 0;
//    int aceCount = 0;

//    for (const auto& card : m_hand) {
//        if (card->getRank() == Card::Rank::ACE) {
//            ++aceCount;
//        }
//        value += card->getBlackjackValue();
//    }

//    while (value > 21 && aceCount > 0) {
//        value -= 10;
//        --aceCount;
//    }

//    return value;
//}

//void Dealer::clearHand() {
//    m_hand.clear();
//}

//std::unique_ptr<Card> Dealer::getFirstCard() const {
//    if (m_hand.empty()) {
//        return nullptr;
//    }
//    return std::make_unique<Card>(Card::Suit::NONE, Card::Rank::NONE, ":/images/card_back.png", ":/images/card_back.png");
//}
