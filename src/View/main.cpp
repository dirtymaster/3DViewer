#include <QApplication>

#include "View.h"

using namespace s21;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    View *window = View::getInstance();
    window->show();
    return a.exec();
}
