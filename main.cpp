#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <mainwindow.h>

#include <Dealer.h>
#include <Deck.h>
#include <Game.h>
#include <Player.h>
#include <I_Participant.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWindow;

    Game* game = new Game();
    game->start();

    mainWindow.show();

    return a.exec();
}
