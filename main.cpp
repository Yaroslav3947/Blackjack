#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <mainwindow.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();

    return a.exec();
}
