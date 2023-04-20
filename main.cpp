#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

#include <mainwindow.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.setFixedSize(1014,696);
    mainWindow.show();

    return a.exec();
}
