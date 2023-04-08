#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create main window
    QMainWindow mainWindow;

    // Create central widget
    QWidget centralWidget(&mainWindow);

    // Create a button
    QPushButton button("Hello World!", &centralWidget);
    button.move(10, 10);
    button.show();

    // Create a label
    QLabel label("Welcome to my Qt Application", &centralWidget);
    label.move(10, 50);
    label.show();

    // Set central widget
    mainWindow.setCentralWidget(&centralWidget);

    // Show main window
    mainWindow.show();

    // Run application
    return a.exec();
}
