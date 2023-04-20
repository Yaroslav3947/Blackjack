#pragma once

#include <QTimer>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QPropertyAnimation>

#include "Game.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_setBet1_clicked();
    void on_setBet5_clicked();
    void on_setBet25_clicked();
    void on_setBet50_clicked();
    void on_setBet100_clicked();
    void on_setBet500_clicked();
    void on_hitButton_clicked();
    void on_setBet1000_clicked();
    void on_standButton_clicked();
    void on_Button_Deal_clicked();
    void on_playAgainButton_clicked();

    void on_choose1StyleButton_clicked();

    void on_choose2StyleButton_clicked();

    void toggleMusic();

private:
    void handlePlayerBust();
    void displayPlayerCards();
    void displayDealerCards();

    void startGame();
    void resetGame();
    void startRound();
    void setupForNewRound();
    void endGame(const QString &message);

    void hideAllButtonsExceptBalanceButton();
    void hideCards();

    void updateDealerInfo();
    void updatePlayerInfo();
    void updateCard(QLabel *cardLabel, const std::shared_ptr<Card> card);

    void updateBetLabel(int betAmount);
    void onSetBetClicked(int betAmount);
    void hideButtonsAndLabels();

    void startCardAnimation();
    void cardAnimation(QLabel *cardLabel, const QPoint &startValue, const QPoint &endValue);

    void setFrontImageCard(QLabel *label, const std::shared_ptr<Card> &card);
    void setBackImageCard(QLabel *cardLabel, const std::shared_ptr<Card> &card);

    void setToggleMusic();
    void setCardSound();
    void setbackgroundSound();
    void setButtonClickSound();


    void playButtonClickSound();
    void playCardSound();


    std::unique_ptr<QMediaPlayer> backgroundSound;
    std::unique_ptr<QMediaPlayer> buttonClickSound;
    std::unique_ptr<QMediaPlayer> cardSound;
    Ui::MainWindow *ui;
    int currentBetAmount = 0;
    bool soundOn;
    std::unique_ptr<QPushButton> musicButton;
    std::shared_ptr<Game> game;
};

