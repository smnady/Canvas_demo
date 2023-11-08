#include "mathobject.h"

MathObject::MathObject()
{

}
bool MathObject::onLine(QLine line, QPoint point) {

    int x1 = line.p1().x();
    int x2 = line.p2().x();
    int y1 = line.p1().y();
    int y2 = line.p2().y();

    if (x1 == x2) {
        return x1 == point.x() && point.y() >= std::min(y1, y2) && point.y() <= std::max(y1, y2);
    }

    int k = (y2 - y1) / (x2 - x1);
    int b = y1 - x1 * k;

    int x = point.x();
    int y = point.y();

    if (x >= std::min(x1, x2) && x <= std::max(x1, x2) && y == k * x + b)
        return true;
    else return false;
}
bool MathObject::onEllipse(QRect rect, QPoint point) {
    QPoint bl = rect.bottomLeft();
    QPoint tr = rect.topRight();
    int x1 = bl.x();
    int x2 = tr.x();
    int y1 = bl.y();
    int y2 = tr.y();

    int b = (y2 - y1) / 2;
    int a = (x2 - x1) / 2;

    int cx = x1 + a;
    int cy = y1 + b;

    if (((point.x() - cx)/a)*((point.x() - cx)/a) + ((point.y() - cy)/b)*((point.y() - cy)/b) == 1)
        return true;
    else return false;
}






