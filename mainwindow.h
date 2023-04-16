#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Game.h>
#include <QString.h>
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_hitButton_clicked();
    void on_standButton_clicked();
    void on_playAgainButton_clicked();
    void on_Button_Deal_clicked();
    void on_setBet100_clicked();
    void on_setBet300_clicked();
    void on_setBet200_clicked();

private:
    void hideAllButtonsExceptBalanceButton();
    void startRound();
    void hideCards();
    void start();
    void endGame(const QString &message);
    void updateDealerInfo();
    void updatePlayerInfo();
    std::shared_ptr<Game> game;
    void cardAnimation(QLabel *cardLabel, const QPoint &destination, int duration = 1000);
    void reverseCardAnimation(QLabel *cardLabel, const QPoint &destination, int duration = 1000);
    void updateDealerCard(QLabel *cardLabel, std::shared_ptr<Card> card);
    void startCardAnimation();
    void showAllButtonsAndLabels();
    Ui::MainWindow *ui;
    int currentBetAmount = 0;
};

#endif // MAINWINDOW_H
