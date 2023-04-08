#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWindow;


    QWidget centralWidget(&mainWindow);

    QPushButton button("Hello World!", &centralWidget);
    button.move(10, 10);
    button.show();

    QLabel label("Welcome to my Qt Application", &centralWidget);
    label.move(10, 50);
    label.show();

    mainWindow.setCentralWidget(&centralWidget);

    mainWindow.show();

    return a.exec();
}
