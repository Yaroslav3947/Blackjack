#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this),
    game = std::make_shared<Game>();
    game->getDeck()->pushCards();
    this->startShuffle();
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

void setCardPixmap(QLabel *label, std::shared_ptr<Card> card) {
    QPixmap pixmap("C:/Users/Yaroslav/Desktop/images/cards/" +
                   QString::fromStdString(rankToString(card->getRank())) +
                   "_of_" +
                   QString::fromStdString(suitToString(card->getSuit())) +
                   ".png");
    label->setPixmap(pixmap);
}

void MainWindow::startShuffle()
{
    game->getDeck()->shuffle();
    game->dealCards();

    auto playerCards = game->getPlayer()->getHand();
    auto dealerCards = game->getDealer()->getHand();

    auto playerSum = game->getPlayer()->getHandValue();
    auto dealerSum = game->getDealer()->getHandValue();

    ui->playerSumLabel->setText(QString(" %1").arg(playerSum));
    ui->dealerSumLabel->setText(QString(" %1").arg(dealerSum));

    if (playerCards.size() > 0) {
        setCardPixmap(ui->playerCard1, playerCards[0]);
    }

    if (playerCards.size() > 1) {
        setCardPixmap(ui->playerCard2, playerCards[1]);
    }

    if (dealerCards.size() > 0) {
        setCardPixmap(ui->dealerCard1, dealerCards[0]);
    }

}



void MainWindow::on_hitButton_clicked()
{
    auto cardToAdd = game->getDeck()->dealCard();
    game->getPlayer()->addCard(cardToAdd);

    ui->playerSumLabel->setText(QString(" %1").arg(game->getPlayer()->getHandValue()));

    auto playerCards = game->getPlayer()->getHand();
        int numCards = playerCards.size();
        if (numCards == 3) {
            setCardPixmap(ui->playerCard3, playerCards[2]);
        } else if (numCards == 4) {
           setCardPixmap(ui->playerCard4, playerCards[3]);
        }

        if (game->getPlayer()->isBust()) {
                ui->hitButton->setEnabled(false);
                ui->standButton->setEnabled(false);
                setCardPixmap(ui->dealerCard2, playerCards[1]);

//               player that they have lost
            }

}

