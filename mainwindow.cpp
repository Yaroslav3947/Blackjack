#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this),
    game = std::make_shared<Game>();
    hideAllButtonsExceptBalanceButton();
    ui->balanceLabel->setText(QString("Bank: $ %1").arg(game->getPlayer()->getBalance()));
    ui->betLabel->setText(QString("Bet: $ %1").arg(0));
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::startCardAnimation() {
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

void betFrameAnimation(Ui::MainWindow *ui) {
    const auto animationDuration = 1000;
    QPropertyAnimation* animation = new QPropertyAnimation(ui->betFrame, "pos");
    animation->setDuration(animationDuration);
    animation->setStartValue(ui->betFrame->pos());
    animation->setEndValue(QPoint(10,630));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void reverseBetFrameAnimation(Ui::MainWindow *ui) {
    const auto animationDuration = 1000;
    QPropertyAnimation* animation = new QPropertyAnimation(ui->betFrame, "pos");
    animation->setDuration(animationDuration);
    animation->setStartValue(ui->betFrame->pos());
    animation->setEndValue(QPoint(10,420));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::cardAnimation(QLabel *cardLabel, const QPoint &destination, int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(cardLabel, "pos");
    animation->setStartValue(destination);
    animation->setEndValue(cardLabel->pos());
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, [=]() {
            delete animation;
        });
}

void MainWindow::reverseCardAnimation(QLabel *cardLabel, const QPoint &destination, int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(cardLabel, "pos");
    animation->setStartValue(cardLabel->pos());
    animation->setEndValue(destination);
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, [=]() {
            delete animation;
        });
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
    const auto fileName = ":/images/cards/" +
        rankToString(card->getRank()) + "_of_" +
        suitToString(card->getSuit()) + ".png";
    QPixmap pixmap(QString::fromStdString(fileName));
    label->setPixmap(pixmap);
}

void updateSumLabel(QLabel *label, std::shared_ptr<Game> game, const std::string &participant) {
    if (participant == "Player") {
        label->setText(QString(" %1").arg(game->getPlayer()->getHandValue()));
    } else if (participant == "Dealer") {
        label->setText(QString(" %1").arg(game->getDealer()->getHandValue()));
    }
}

void setBackImageCardPixmap(QLabel* cardLabel) {
    const auto backImagePath = ":/images/cards/backImage.png";
    cardLabel->setPixmap(QPixmap(backImagePath));
}

void MainWindow::endGame(const QString &message) {
    ui->messageLabel->setText(message);
    ui->hitButton->setEnabled(false);
    ui->standButton->setEnabled(false);
    ui->balanceLabel->setText(QString("Bank: %1").arg(game->getPlayer()->getBalance()));
}

void MainWindow::updateDealerInfo() {
    auto dealerCards = game->getDealer()->getHand();
    auto numCards = dealerCards.size();

    updateSumLabel(ui->dealerSumLabel, game, "Dealer");

    ui->dealerCard2->show();
    setCardPixmap(ui->dealerCard2, dealerCards[1]);

    if (numCards >= 3) {
        updateDealerCard(ui->dealerCard3, dealerCards[2]);
    } else if (numCards >= 4) {
        updateDealerCard(ui->dealerCard4, dealerCards[3]);
    } else if (numCards >= 5) {
        updateDealerCard(ui->dealerCard5, dealerCards[4]);
    }
}

void MainWindow::displayPlayerCards() {
    auto playerCards = game->getPlayer()->getHand();
    auto playerSum = game->getPlayer()->getHandValue();

    ui->playerSumLabel->setText(QString(" %1").arg(playerSum));
    setCardPixmap(ui->playerCard1, playerCards[0]);
    setCardPixmap(ui->playerCard2, playerCards[1]);
}

void MainWindow::displayDealerCards() {
    auto dealerCards = game->getDealer()->getHand();

    setBackImageCardPixmap(ui->dealerCard2);
    setCardPixmap(ui->dealerCard1, dealerCards[0]);
}
void MainWindow::startGame() {
    game->getDeck()->pushCards();
    game->getDeck()->shuffle();
    game->dealCards();
    ui->playerInfoFrame->show();
    ui->dealerInfoFrame->show();

    displayPlayerCards();
    displayDealerCards();
}

void dealCardToPlayer(std::shared_ptr<Game> game) {
    auto cardToAdd = game->getDeck()->dealCard();
    game->getPlayer()->addCard(cardToAdd);
}

void MainWindow::handlePlayerBust() {
    if (game->getPlayer()->isBust()) {
        updateDealerInfo();
        const auto winner = game->determineWinner();
        if(winner == Game::Winner::DEALER){
            endGame("Dealer wins!");
        } else {
            endGame("Tie!");
        }
    }
}

void MainWindow::on_hitButton_clicked() {
    dealCardToPlayer(game);
    updatePlayerInfo();
    handlePlayerBust();
}

void MainWindow::on_standButton_clicked() {

    updateDealerInfo();

    const auto winner = game->determineWinner();

    if (winner == Game::Winner::PLAYER) {
        endGame("Player wins!");
    } else if (winner == Game::Winner::DEALER) {
        endGame("Dealer wins!");
    } else {
        endGame("Tie!");
    }
}

void MainWindow::hideCards() {
    QList<QLabel*> cardLabels = {ui->playerCard1, ui->playerCard2, ui->playerCard3, ui->playerCard4, ui->playerCard5,
                                 ui->dealerCard1, ui->dealerCard2, ui->dealerCard3, ui->dealerCard4, ui->dealerCard5};

    for (const auto &cardLabel : cardLabels) {
        cardLabel->hide();
    }
}

void MainWindow::updatePlayerInfo() {
    auto playerCards = game->getPlayer()->getHand();
    auto numCards = playerCards.size();

    updateSumLabel(ui->playerSumLabel, game, "Player");

    if (numCards == 3) {
        updateDealerCard(ui->playerCard3, playerCards[2]);
    } else if (numCards == 4) {
        updateDealerCard(ui->playerCard4, playerCards[3]);
    } else if (numCards == 5) {
        updateDealerCard(ui->playerCard5, playerCards[4]);
    }
}

void MainWindow::updateDealerCard(QLabel* cardLabel, const std::shared_ptr<Card> card) {
    cardLabel->show();
    cardAnimation(cardLabel, QPoint(0, 0));
    setCardPixmap(cardLabel, card);
}

void MainWindow::resetGame() {
    hideAllButtonsExceptBalanceButton();
    game->reset();
    ui->betLabel->setText("Bet: $ 0");
    ui->messageLabel->setText("");
    ui->hitButton->setEnabled(true);
    ui->standButton->setEnabled(true);
}

void MainWindow::setupForNewRound() {
    QList<QWidget*> widgets{ ui->hitButton, ui->standButton, ui->playAgainButton,
                            ui->playerSumLabel, ui->dealerSumLabel };
    for (auto widget : widgets) {
        widget->show();
    }
    ui->Button_Deal->hide();
    betFrameAnimation(ui);

}
void MainWindow::on_playAgainButton_clicked() {
    resetGame();
}

void MainWindow::startRound() {
    setupForNewRound();
    this->startGame();
    game->dealerTurn();
    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getTopCard()->getValue()));
    ui->balanceLabel->setText(QString("Bank: $ %1").arg(game->getPlayer()->getBalance() - game->getPlayer()->getBet()));
    startCardAnimation();
}

void MainWindow::hideButtonsAndLabels() {
    hideCards();
    ui->hitButton->hide();
    ui->standButton->hide();
    ui->playAgainButton->hide();
    ui->playerInfoFrame->hide();
    ui->dealerInfoFrame->hide();
}
void showDealButton(Ui::MainWindow *ui) {
    ui->Button_Deal->show();
}
void MainWindow::hideAllButtonsExceptBalanceButton() {
    hideButtonsAndLabels();
    showDealButton(ui);
    reverseBetFrameAnimation(ui);
}

void MainWindow::on_Button_Deal_clicked() {
    if(game->getPlayer()->getBet() > 0) {
        startRound();
    }
}

void MainWindow::onSetBetClicked(int betAmount) {
    int currentBetAmount = game->getPlayer()->getBet();
    if (currentBetAmount + betAmount > game->getPlayer()->getBalance()) {
        qDebug() << "You have no money";
    } else {
        currentBetAmount += betAmount;
        game->getPlayer()->setBet(currentBetAmount);
        ui->betLabel->setText(QString("Bet: $ %1").arg(currentBetAmount));
    }
}

void MainWindow::updateBetLabel(int betAmount) {
    int currentBetAmount = game->getPlayer()->getBet();
    currentBetAmount += betAmount;
    game->getPlayer()->setBet(currentBetAmount);
    ui->betLabel->setText(QString("Bet: $ %1").arg(currentBetAmount));
}

void MainWindow::on_setBet1_clicked() {
    onSetBetClicked(1);
}

void MainWindow::on_setBet5_clicked() {
    onSetBetClicked(5);
}

void MainWindow::on_setBet25_clicked() {
    onSetBetClicked(25);
}

void MainWindow::on_setBet50_clicked() {
    onSetBetClicked(50);
}

void MainWindow::on_setBet100_clicked() {
    onSetBetClicked(100);
}

void MainWindow::on_setBet500_clicked() {
    onSetBetClicked(500);
}

void MainWindow::on_setBet1000_clicked() {
    onSetBetClicked(1000);
}


