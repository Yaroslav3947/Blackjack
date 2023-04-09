#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this),
    game = std::make_shared<Game>();
    game->getDeck()->pushCards();
    game->getDeck()->shuffle();
}

MainWindow::~MainWindow() {
    delete ui;
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

static std::string suitToString(Card::Suit suit) {
    switch (suit) {
        case Card::Suit::CLUBS: return "clubs";
        case Card::Suit::DIAMONDS: return "diamonds";
        case Card::Suit::HEARTS: return "hearts";
        case Card::Suit::SPADES: return "spades";
        default: return "";
    }
}

void MainWindow::on_shuffleButton_clicked()
{
    game->getDeck()->shuffle();
    game->dealCards();

    auto playerCards = game->getPlayer()->getHand();
    auto dealerCards = game->getDealer()->getHand();

    if (playerCards.size() > 0) {
        QPixmap playerCard1("C:/Users/Yaroslav/Desktop/images/cards/" +
                            QString::fromStdString(rankToString(playerCards[0]->getRank())) +
                            "_of_" +
                            QString::fromStdString(suitToString(playerCards[0]->getSuit())) +
                            ".png");
        ui->playerCard1->setPixmap(playerCard1);

    }

    if (playerCards.size() > 1) {
        QPixmap playerCard2("C:/Users/Yaroslav/Desktop/images/cards/" +
                            QString::fromStdString(rankToString(playerCards[1]->getRank())) +
                            "_of_" +
                            QString::fromStdString(suitToString(playerCards[1]->getSuit())) +
                            ".png");
        ui->playerCard2->setPixmap(playerCard2);
    }

    // Set the dealer's cards labels
    if (dealerCards.size() > 0) {
        QPixmap dealerCard1("C:/Users/Yaroslav/Desktop/images/cards/" +
                            QString::fromStdString(rankToString(dealerCards[0]->getRank())) +
                            "_of_" +
                            QString::fromStdString(suitToString(dealerCards[0]->getSuit())) +
                            ".png");
        ui->dealerCard1->setPixmap(dealerCard1);
    }

    if (dealerCards.size() > 1) {
        QPixmap dealerCard2("C:/Users/Yaroslav/Desktop/images/cards/" +
                            QString::fromStdString(rankToString(dealerCards[1]->getRank())) +
                            "_of_" +
                            QString::fromStdString(suitToString(dealerCards[1]->getSuit())) +
                            ".png");
        ui->dealerCard2->setPixmap(dealerCard2);
    }
}


