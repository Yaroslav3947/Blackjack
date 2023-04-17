#pragma once

#include <Game.h>
#include <QTimer>
#include <QMainWindow>
#include <QPropertyAnimation>

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
    void cardAnimation(QLabel *cardLabel, const QPoint &destination, int duration = 1000);
    void reverseCardAnimation(QLabel *cardLabel, const QPoint &destination, int duration = 1000);

    Ui::MainWindow *ui;
    int currentBetAmount = 0;
    std::shared_ptr<Game> game;

};

