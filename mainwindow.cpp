#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this),
    game = std::make_shared<Game>();
    game->getDeck()->pushCards();
    this->startShuffle();
    game->dealerTurn();
    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getTopCard()->getValue()));
    ui->balanceLabel->setText(QString("Balance: %1").arg(game->getPlayer()->getBalance()));

}

MainWindow::~MainWindow() {
    delete ui;
}

static std::string rankToString(Card::Rank rank) {
    static const std::string rankStrings[] = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13"
    };
    return rankStrings[static_cast<int>(rank)];
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

    ui->playerSumLabel->setText(QString(" %1").arg(playerSum));

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

void MainWindow::on_hitButton_clicked() {
    auto cardToAdd = game->getDeck()->dealCard();
    game->getPlayer()->addCard(cardToAdd);

    updatePlayerInfo();

    if (game->getPlayer()->isBust()) {
        endGame("Dealer wins!");
    }
}

void MainWindow::on_standButton_clicked() {

    updateDealerInfo();

    auto winner = game->determineWinner();

    if (winner == Game::Winner::PLAYER) {
        endGame("Player wins!");
    } else if (winner == Game::Winner::DEALER) {
        endGame("Dealer wins!");
    } else {
        endGame("Tie!");
    }
}

void MainWindow::updatePlayerInfo() {
    auto playerCards = game->getPlayer()->getHand();
    auto  numCards = playerCards.size();

    ui->playerSumLabel->setText(QString(" %1").arg(game->getPlayer()->getHandValue()));

    if (numCards == 3) {
        setCardPixmap(ui->playerCard3, playerCards[2]);
    } else if (numCards == 4) {
        setCardPixmap(ui->playerCard4, playerCards[3]);
    }
}

void MainWindow::updateDealerInfo() {
    auto dealerCards = game->getDealer()->getHand();
    auto numCards = dealerCards.size();

    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getHandValue()));

    setCardPixmap(ui->dealerCard2, dealerCards[1]);

    if (numCards >= 3) {
        setCardPixmap(ui->dealerCard3, dealerCards[2]);
    } else if (numCards >= 4) {
        setCardPixmap(ui->dealerCard4, dealerCards[3]);
    }
}

void MainWindow::endGame(const QString &message) {
    updateDealerInfo();
    ui->messageLabel->setText(message);
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->balanceLabel->setText(QString("Balance: %1").arg(game->getPlayer()->getBalance()));
}



