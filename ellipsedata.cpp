#include "ellipsedata.h"
#include "mathobject.h"

EllipseData::EllipseData(QRect rect, QPen pen, QBrush brush)
{
    this->rect = rect;
    this->pen = pen;
    this->brush = brush;
    changed = false;
}

QRect EllipseData::getRect() {
    return rect;
}
QBrush EllipseData::getBrush() const {
    return brush;
}
QPen EllipseData::getPen() const {
    return pen;
}
void EllipseData::draw(QPainter &painter) {
    painter.drawEllipse(rect);
}
bool EllipseData::containsPoint(const QPoint &point) {
    QPoint bl = rect.bottomLeft();
    QPoint tr = rect.topRight();
    int x1 = bl.x();
    int x2 = tr.x();
    int y1 = bl.y();
    int y2 = tr.y();

    int b = ((y2 - y1) / 2) + (pen.width() / 2);
    int a = ((x2 - x1) / 2) + (pen.width() / 2);

    int cx = x1 + a;
    int cy = y1 + b;

    double term1 = (point.x() - cx) / a;
    double term2 = (point.y() - cy) / b;
    double result = term1 * term1 + term2 * term2;

    if (result <= 1) {
        return true;
    } else {
        return false;
    }
}

void EllipseData::moveBy(const QPoint &offset) {
    rect.translate(offset);
}
void EllipseData::increase() {
    rect.setWidth((int) rect.width()*1.05);
    rect.setHeight((int) rect.height()*1.05);
}
void EllipseData::decrease() {
    rect.setWidth((int) rect.width()*0.95);
    rect.setHeight((int) rect.height()*0.95);
}
QRect EllipseData::getBoundingBox() {
    if (field.isEmpty() || changed) {
        QPoint br(rect.bottomRight().x(), rect.bottomRight().y());
        QPoint tl(rect.topLeft().x(), rect.topLeft().y());
        field = QRect(tl, br);
        changed = false;
    }
    return field;
}
bool EllipseData::isChanged() const {
    return changed;
}
void EllipseData::setChanged(bool flag) {
    changed = flag;
}
void EllipseData::setBrush(QBrush brush) {
    this->brush = brush;
}
void EllipseData::setPen(QPen pen) {
    this->pen = pen;
}
QString EllipseData::getType() const {
    return "Эллипс";
}
