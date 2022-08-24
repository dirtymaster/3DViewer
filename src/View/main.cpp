#include "View.h"

#include <QApplication>

using namespace s21;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    View *window = View::getInstance();
    window->show();
    return a.exec();
}
