#include "canvas.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Canvas w;
    w.setWindowTitle("Canvas");
    w.resize(700, 600);
    w.show();
    return a.exec();
}
