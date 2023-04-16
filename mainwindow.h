#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Game.h>
#include <qstring.h>
#include "ui_mainwindow.h"
#include <qpropertyanimation.h>
#include <qtimer.h>
//#include <QtMultimedia/QMediaPlayer>

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

private:
    void hideCards();
    void start();
    void endGame(const QString &message);
    void updateDealerInfo();
    void updatePlayerInfo();
    std::shared_ptr<Game> game;
    void cardAnimation(QLabel* cardLabel, const QPoint& destination, int duration = 1000);
    void reverseCardAnimation(QLabel* cardLabel, const QPoint& destination, int duration = 1000);
    void updateDealerCard(QLabel* cardLabel, std::shared_ptr<Card> card);
    void startCardAnimation();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
