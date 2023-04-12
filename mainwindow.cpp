#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this),
    game = std::make_shared<Game>();
    this->startShuffle();
    game->dealerTurn();
    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getTopCard()->getValue()));
    ui->balanceLabel->setText(QString("Balance: %1").arg(game->getPlayer()->getBalance()));
    hideCards();

    cardAnimation(ui->playerCard1, QPoint(0, 0));
        ui->playerCard1->show();
        QTimer::singleShot(500, this, [this]() {
            ui->dealerCard1->show();
            cardAnimation(ui->dealerCard1, QPoint(0, 0));
        });
        QTimer::singleShot(1000, this, [this]() {
            ui->playerCard2->show();
            cardAnimation(ui->playerCard2, QPoint(0, 0));
        });
        QTimer::singleShot(1500, this, [this]() {
            ui->dealerCard2->show();
            cardAnimation(ui->dealerCard2, QPoint(0, 0));
        });
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::cardAnimation(QLabel *cardLabel, const QPoint &destination, int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(cardLabel, "pos");
    animation->setStartValue(destination);
    animation->setEndValue(cardLabel->pos());
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();
}


static std::string rankToString(const Card::Rank &rank) {
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


static std::string suitToString(const Card::Suit &suit) {
    switch (suit) {
        case Card::Suit::CLUBS: return "clubs";
        case Card::Suit::DIAMONDS: return "diamonds";
        case Card::Suit::HEARTS: return "hearts";
        case Card::Suit::SPADES: return "spades";
        default: return "";
    }
}

void setCardPixmap(QLabel *label, const std::shared_ptr<Card> &card) {
    const auto fileName = "C:/Users/Yaroslav/Desktop/images/cards/" +
        rankToString(card->getRank()) + "_of_" +
        suitToString(card->getSuit()) + ".png";
    QPixmap pixmap(QString::fromStdString(fileName));
    label->setPixmap(pixmap);
}


void MainWindow::startShuffle()
{
    game->getDeck()->pushCards();
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
    ////TODO: rm if
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

void MainWindow::hideCards() {
    ui->playerCard1->hide();
    ui->playerCard2->hide();
    ui->playerCard3->hide();
    ui->playerCard4->hide();
    ui->dealerCard1->hide();
    ui->dealerCard2->hide();
    ui->dealerCard3->hide();
    ui->dealerCard4->hide();
}

void MainWindow::updatePlayerInfo() {
    auto playerCards = game->getPlayer()->getHand();
    auto  numCards = playerCards.size();

    ui->playerSumLabel->setText(QString(" %1").arg(game->getPlayer()->getHandValue()));

    if (numCards == 3) {
        ui->playerCard3->show();
        cardAnimation(ui->playerCard3, QPoint(0, 0));
        setCardPixmap(ui->playerCard3, playerCards[2]);
    } else if (numCards == 4) {
        ui->playerCard4->show();
        cardAnimation(ui->playerCard4, QPoint(0, 0));
        setCardPixmap(ui->playerCard4, playerCards[3]);
    }
}

void MainWindow::updateDealerInfo() {
    auto dealerCards = game->getDealer()->getHand();
    auto numCards = dealerCards.size();

    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getHandValue()));

    ui->dealerCard2->show();
    setCardPixmap(ui->dealerCard2, dealerCards[1]);

    if (numCards == 3) {
        ui->dealerCard3->show();
        cardAnimation(ui->dealerCard3, QPoint(0, 0)); //TODO: fix bug
        setCardPixmap(ui->dealerCard3, dealerCards[2]);

    } else if (numCards == 4) {
        ui->dealerCard4->show();
        cardAnimation(ui->dealerCard4, QPoint(0, 0));
        setCardPixmap(ui->dealerCard4, dealerCards[3]);
    }
}

void MainWindow::endGame(const QString &message) {
    ui->messageLabel->setText(message);
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->balanceLabel->setText(QString("Balance: %1").arg(game->getPlayer()->getBalance()));
}

void MainWindow::on_playAgainButton_clicked() {
    const auto backImagePath = "C:/Users/Yaroslav/Desktop/images/cards/backImage.png";
    game->reset();
    hideCards();
    qDebug() << "Size: " << game->getPlayer()->getHand().size();
    startShuffle();
    ui->hitButton->setEnabled(true);
    ui->standButton->setEnabled(true);
    game->dealerTurn();
    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getTopCard()->getValue()));
    ui->playerSumLabel->setText(QString(" %1").arg(game->getPlayer()->getHandValue()));
    ui->balanceLabel->setText(QString("Balance: %1").arg(game->getPlayer()->getBalance()));
    ui->messageLabel->setText("");
    ui->dealerCard2->setPixmap(QPixmap(backImagePath));
    ui->dealerCard3->setPixmap(QPixmap(backImagePath));
    ui->dealerCard4->setPixmap(QPixmap(backImagePath));
    ui->playerCard3->setPixmap(QPixmap(backImagePath));
    ui->playerCard4->setPixmap(QPixmap(backImagePath));


        QTimer::singleShot(250, this, [this]() {
            ui->playerCard1->show();
            cardAnimation(ui->playerCard1, QPoint(0, 0));
        });

        QTimer::singleShot(500, this, [this]() {
            ui->dealerCard1->show();
            cardAnimation(ui->dealerCard1, QPoint(0, 0));
        });
        QTimer::singleShot(1000, this, [this]() {
            ui->playerCard2->show();
            cardAnimation(ui->playerCard2, QPoint(0, 0));
        });
        QTimer::singleShot(1500, this, [this]() {
            ui->dealerCard2->show();
            cardAnimation(ui->dealerCard2, QPoint(0, 0));
        });
}

