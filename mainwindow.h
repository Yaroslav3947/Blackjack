#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Game.h>
#include <qstring.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startShuffle();
    void updateDealerInfo();
    void updatePlayerInfo();
    void on_hitButton_clicked();
    void endGame(const QString &message);
    void on_standButton_clicked();

private:
    std::shared_ptr<Game> game;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
