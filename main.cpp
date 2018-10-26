#include <QApplication> // Provides an event loop for GUI application
#include "factory.h" // Own the initial class form pattern MVC

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Factory fact; // Create factory class which contains instance of MVC pattern
    fact.init();

    return a.exec();
}
