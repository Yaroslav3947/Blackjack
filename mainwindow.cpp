#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    game = std::make_shared<Game>();
    hideAllButtonsExceptBalanceButton();
    setLabelsByDefault();
    setbackgroundSound();
    setButtonClickSound();
    setCardSound();
    setToggleMusic();
}

void MainWindow::setLabelsByDefault() {
    ui->balanceLabel->setText(QString("Bank: $ %1").arg(game->getPlayer()->getBalance()));
    ui->style1Label->setStyleSheet("border: 2px solid #1b1f3b;");
    ui->betLabel->setText(QString("Bet: $ %1").arg(0));
}


void MainWindow::setCardSound() {
    cardSound = std::make_unique<QMediaPlayer>();
    cardSound->setMedia(QUrl("qrc:/sounds/sounds/throw_card_on_table.mp3"));
    cardSound->setVolume(35);
}

void MainWindow::setToggleMusic() {
    musicButton = std::make_unique<QPushButton>(this);
    musicButton->setGeometry(870, 650, 50, 50);
    connect(musicButton.get(), &QPushButton::clicked, this, &MainWindow::toggleMusic);
    toggleMusic();
    musicButton->setStyleSheet("QPushButton { border-radius: 10px; }");
}
void MainWindow::playCardSound() {
    if (cardSound->state() == QMediaPlayer::PlayingState) {
        cardSound->setPosition(0);
    } else if (cardSound->state() == QMediaPlayer::StoppedState) {
        setCardSound();
    }
    cardSound->play();
}

void MainWindow::onBackgroundMusicStateChanged(QMediaPlayer::State state) {
    if (state == QMediaPlayer::StoppedState) {
        backgroundSound->setPosition(0);
        backgroundSound->play();
    }
}
void MainWindow::setbackgroundSound() {
    backgroundSound = std::make_unique<QMediaPlayer>();
    backgroundSound->setMedia(QUrl("qrc:/sounds/sounds/backgroundMusic.wav"));
    backgroundSound->setVolume(23);
    backgroundSound->play();

    connect(backgroundSound.get(), &QMediaPlayer::stateChanged, this, &MainWindow::onBackgroundMusicStateChanged);
}

void MainWindow::setButtonClickSound() {
    buttonClickSound = std::make_unique<QMediaPlayer>();
    buttonClickSound->setMedia(QUrl("qrc:/sounds/sounds/Short_and_fast_buttonclick.mp3"));
    buttonClickSound->setVolume(30);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateBankLabel() {
    ui->balanceLabel->setText(QString("Bank: $ %1").arg(game->getPlayer()->getBalance() - game->getPlayer()->getBet()));
}
void MainWindow::playButtonClickSound() {
    if (buttonClickSound->state() == QMediaPlayer::PlayingState) {
        buttonClickSound->setPosition(0);
    } else if (buttonClickSound->state() == QMediaPlayer::StoppedState) {
        setButtonClickSound();
    }
    buttonClickSound->play();
}
void MainWindow::startCardAnimation() {
    const auto DIFFERENCE_IN_DELAYS = 500;
    const auto DELAY1 = 500;
    const auto DELAY2 = DELAY1 + DIFFERENCE_IN_DELAYS;
    const auto DELAY3 = DELAY2 + DIFFERENCE_IN_DELAYS;
    cardAnimation(ui->playerCard1, ui->playerCard1->pos(), QPoint(0, 0));
            ui->playerCard1->show();
            QTimer::singleShot(DELAY1, this, [this]() {
                ui->dealerCard1->show();
                cardAnimation(ui->dealerCard1, ui->dealerCard1->pos(), QPoint(0, 0));
            });
            QTimer::singleShot(DELAY2 , this, [this]() {
                ui->playerCard2->show();
                cardAnimation(ui->playerCard2, ui->playerCard2->pos(), QPoint(0, 0));
            });
            QTimer::singleShot(DELAY3, this, [this]() {
                ui->dealerCard2->show();
                cardAnimation(ui->dealerCard2, ui->dealerCard2->pos(), QPoint(0, 0));
            });
}

void animateStyleFrame(Ui::MainWindow* ui, bool reverse = false) {
    const auto animationDuration = 1000;
    QPropertyAnimation* animation = new QPropertyAnimation(ui->Styleframe, "pos");
    animation->setDuration(animationDuration);
    animation->setStartValue(ui->Styleframe->pos());
    if (reverse) {
        animation->setEndValue(QPoint(50, 20));
    } else {
        animation->setEndValue(QPoint(-200, 20));
    }
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void animateBetFrame(Ui::MainWindow* ui, bool reverse = false) {
    const auto animationDuration = 1000;
    QPropertyAnimation* animation = new QPropertyAnimation(ui->betFrame, "pos");
    animation->setDuration(animationDuration);
    animation->setStartValue(ui->betFrame->pos());
    if (reverse) {
        animation->setEndValue(QPoint(10, 420));
    } else {
        animation->setEndValue(QPoint(10, 650));
    }
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::cardAnimation(QLabel *cardLabel, const QPoint &endValue, const QPoint &startValue) {
    playCardSound();
    const int duration = 1000;
    QPropertyAnimation* animation = new QPropertyAnimation(cardLabel, "pos");
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::OutCirc);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void MainWindow::setFrontImageCard(QLabel *label, const std::shared_ptr<Card> &card) {
    if(!game->getChangePath()) {
        label->setPixmap(card->getFrontImage());
    } else {
        const auto cardsPath = ":/images/cards2/";
        label->setPixmap((card->getFrontImagePath(card->getSuit(), card->getRank(), cardsPath)));
    }
}

void updateSumLabel(QLabel *label, std::shared_ptr<Game> game, const std::string &participant) {
    if (participant == "Player") {
        label->setText(QString(" %1").arg(game->getPlayer()->getHandValue()));
    } else if (participant == "Dealer") {
        label->setText(QString(" %1").arg(game->getDealer()->getHandValue()));
    }
}

void MainWindow::setBackImageCard(QLabel *cardLabel, const std::shared_ptr<Card> &card) {
    cardLabel->setPixmap(QPixmap(card->getBackImage()));

    if(!game->getChangePath()) {
        cardLabel->setPixmap(QPixmap(card->getBackImage()));
    } else {
        const auto backImagePath = ":/images/cards2/backImage.png";
        cardLabel->setPixmap(QPixmap(backImagePath));
    }
}

void MainWindow::endGame(const QString &message) {
    ui->hitButton->setDisabled(true);
    ui->standButton->setDisabled(true);
    if (message == "Player wins!") {
        ui->playerMessageLabel->setText("Player Wins!");
        ui->dealerMessageLabel->setText("Dealer Bust!");
    } else if (message == "Dealer wins!") {
        ui->playerMessageLabel->setText("Player Bust!");
        ui->dealerMessageLabel->setText("Dealer Wins!");
    } else if (message == "Tie!") {
        ui->playerMessageLabel->setText("Tie!");
        ui->dealerMessageLabel->setText("Tie!");
    }
    ui->balanceLabel->setText(QString("Bank $: %1").arg(game->getPlayer()->getBalance()));
}

void MainWindow::updateCard(QLabel *cardLabel, const std::shared_ptr<Card> card) {
    cardLabel->show();
    cardAnimation(cardLabel, cardLabel->pos(), QPoint(0, 0));
    setFrontImageCard(cardLabel, card);
}

void MainWindow::updateDealerInfo() {
    auto dealerCards = game->getDealer()->getHand();
    auto numCards = dealerCards.size();

    setFrontImageCard(ui->dealerCard2, dealerCards[1]);
    ui->dealerCard2->show();

    updateSumLabel(ui->dealerSumLabel, game, "Dealer");

    QList<QLabel *> dealerCardsLabels = {ui->dealerCard1, ui->dealerCard2, ui->dealerCard3, ui->dealerCard4,
                                         ui->dealerCard5, ui->dealerCard6, ui->dealerCard7};
    for(auto i = 3; i <= numCards; i++) {
        updateCard(dealerCardsLabels[i-1], dealerCards[i-1]);
    }
}

void MainWindow::updatePlayerInfo() {
    auto playerCards = game->getPlayer()->getHand();
    auto numCards = playerCards.size();

    const auto CARD_INDEX_OFFSET = 3;
    const auto MAX_NUM_CARDS = 7;
    const auto MIN_NUM_CARDS = 3;
    const auto LAST_CARD_INDEX = numCards - 1;

    updateSumLabel(ui->playerSumLabel, game, "Player");
    QList<QLabel*> playerCardsLabels = {ui->playerCard3, ui->playerCard4, ui->playerCard5, ui->playerCard6, ui->playerCard7};
    if (numCards >= MIN_NUM_CARDS && numCards <= MAX_NUM_CARDS) {
        updateCard(playerCardsLabels[numCards - CARD_INDEX_OFFSET], playerCards[LAST_CARD_INDEX]);
    }
}

void MainWindow::displayPlayerCards() {
    auto playerCards = game->getPlayer()->getHand();
    auto playerSum = game->getPlayer()->getHandValue();

    ui->playerSumLabel->setText(QString(" %1").arg(playerSum));
    setFrontImageCard(ui->playerCard1, playerCards[0]);
    setFrontImageCard(ui->playerCard2, playerCards[1]);
}

void MainWindow::displayDealerCards() {
    auto dealerCards = game->getDealer()->getHand();

    setBackImageCard(ui->dealerCard2, dealerCards[0]);
    setFrontImageCard(ui->dealerCard1, dealerCards[0]);
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
    const auto POINTS_TO_WIN = 21;
    if(game->getPlayer()->getHandValue() == POINTS_TO_WIN) {
        updateDealerInfo();
        endGame("Player wins!");
    } else if (game->getPlayer()->isBust()) {
        updateDealerInfo();
        const auto winner = game->determineWinner();
        if(winner == Game::Winner::DEALER){
            endGame("Dealer wins!");
        } else {
            endGame("Tie!");
        }
    }
}

void lockButton(QAbstractButton *button, const int &duration) {
    button->setEnabled(false);
    QTimer::singleShot(duration, button, [=]() {
        button->setEnabled(true);
    });
}

void MainWindow::on_hitButton_clicked() {
    dealCardToPlayer(game);
    updatePlayerInfo();
    handlePlayerBust();
}

void MainWindow::on_standButton_clicked() {
    playButtonClickSound();
    game->dealerTurn();
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
    QList<QLabel*> cardLabels = {ui->playerCard1, ui->playerCard2, ui->playerCard3, ui->playerCard4, ui->playerCard5, ui->playerCard6, ui->playerCard7,
                                 ui->dealerCard1, ui->dealerCard2, ui->dealerCard3, ui->dealerCard4, ui->dealerCard5, ui->dealerCard6, ui->dealerCard7};
    for (const auto &cardLabel : cardLabels) {
        cardLabel->hide();
    }
}
void MainWindow::proccedGameOver() {
    hideCards();
    std::vector<QWidget*> uiElementsToHide = {
        ui->playerMessageLabel,
        ui->dealerMessageLabel,
        ui->betFrame,
        ui->dealerInfoFrame,
        ui->playerInfoFrame,
        ui->Styleframe,
        ui->hitButton,
        ui->standButton,
        ui->playAgainButton
    };
    for (QWidget *uiElement : uiElementsToHide) {
        uiElement->hide();
    }
    ui->gameOverLabel->show();
    ui->exitButton->move(470,300);
    ui->exitButton->resize(180,60);
}

void MainWindow::resetGame() {
    if(game->getPlayer()->getBalance() > 0) {
        hideAllButtonsExceptBalanceButton();
        game->reset();
        ui->betLabel->setText("Bet: $ 0");
        ui->dealerMessageLabel->setText("");
        ui->playerMessageLabel->setText("");
        ui->hitButton->setEnabled(true);
        ui->standButton->setEnabled(true);
    } else {
        proccedGameOver();
    }
}

void MainWindow::setupForNewRound() {
    QList<QWidget*> widgets{ ui->hitButton, ui->standButton, ui->playAgainButton,
                            ui->playerSumLabel, ui->dealerSumLabel};
    for (const auto &widget : widgets) {
        widget->show();
    }
    ui->Button_Deal->hide();
    animateBetFrame(ui);
    animateStyleFrame(ui);
}
void MainWindow::on_playAgainButton_clicked() {
    playButtonClickSound();
    resetGame();
}

void lockButtons(Ui::MainWindow *ui) {
    const auto LOCK_DURATION_MS = 3000;
    lockButton(ui->playAgainButton, LOCK_DURATION_MS);
    lockButton(ui->hitButton, LOCK_DURATION_MS);
    lockButton(ui->standButton, LOCK_DURATION_MS);
}
void MainWindow::startRound() {
    setupForNewRound();
    this->startGame();
    ui->dealerSumLabel->setText(QString(" %1").arg(game->getDealer()->getTopCard()->getValue()));
    updateBankLabel();
    lockButtons(ui);
    startCardAnimation();
}

void MainWindow::hideButtonsAndLabels() {
    hideCards();
    ui->hitButton->hide();
    ui->standButton->hide();
    ui->playAgainButton->hide();
    ui->playerInfoFrame->hide();
    ui->dealerInfoFrame->hide();
    ui->gameOverLabel->hide();
    ui->Button_Deal->hide();
}

void showDealButton(Ui::MainWindow *ui) {
    ui->Button_Deal->show();
}

void MainWindow::hideAllButtonsExceptBalanceButton() {
    hideButtonsAndLabels();
    animateBetFrame(ui, true);
    animateStyleFrame(ui, true);
}

void MainWindow::on_Button_Deal_clicked() {
    playButtonClickSound();
    if(game->getPlayer()->getBet() > 0) {
        startRound();
    }
}

void MainWindow::onSetBetClicked(int betAmount) {
    playButtonClickSound();
    showDealButton(ui);
    auto currentBetAmount = game->getPlayer()->getBet();
    if (currentBetAmount + betAmount > game->getPlayer()->getBalance()) {
        showErrorMessageLabel(betAmount);
    } else {
        currentBetAmount += betAmount;
        game->getPlayer()->setBet(currentBetAmount);
        ui->betLabel->setText(QString("Bet: $ %1").arg(currentBetAmount));
        updateBankLabel();
    }
}
void MainWindow::animateMessageLabel(QLabel *errorMessageLabel) {
    QPropertyAnimation* animation = new QPropertyAnimation(errorMessageLabel, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        errorMessageLabel->hide();
        delete animation;
        delete errorMessageLabel;
    });

    errorMessageLabel->show();
    animation->start();
}

void MainWindow::showErrorMessageLabel(int betAmount) {
    QLabel *errorMessageLabel = new QLabel(ui->betFrame);
    errorMessageLabel->setText("You don't have enough money to bet $" + QString::number(betAmount));
    errorMessageLabel->setAlignment(Qt::AlignCenter);
    errorMessageLabel->setStyleSheet("background-color: transparent; color: white; font-size: 10px; padding: 10px;");

    const auto errorMessageWidth = 280;
    const auto errorMessageHeight = 50;
    const auto errorMessageX = 90;
    const auto errorMessageY = 230;
    errorMessageLabel->setGeometry(errorMessageX, errorMessageY, errorMessageWidth, errorMessageHeight);

    animateMessageLabel(errorMessageLabel);
}

void MainWindow::updateBetLabel(int betAmount) {
    auto currentBetAmount = game->getPlayer()->getBet();
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

void MainWindow::on_choose1StyleButton_clicked() {
    playButtonClickSound();
    game->setChangePath(false);
    ui->style1Label->setStyleSheet("border: 2px solid #1b1f3b;");
    ui->style2Label->setStyleSheet("");
}

void MainWindow::on_choose2StyleButton_clicked() {
    playButtonClickSound();
    game->setChangePath(true);
    ui->style2Label->setStyleSheet("border: 2px solid #1b1f3b;");
    ui->style1Label->setStyleSheet("");
}

void MainWindow::toggleMusic() {
    soundOn = !soundOn;
    if (soundOn) {
        backgroundSound->play();
        musicButton->setIcon(QIcon(":/images/icons/musicOn.png"));
    } else {
        backgroundSound->pause();
        musicButton->setIcon(QIcon(":/images/icons/musicOff.png"));
    }
}

void MainWindow::on_exitButton_clicked() {
    qApp->exit();
}

