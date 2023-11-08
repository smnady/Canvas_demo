#include "pointdata.h"

PointData::PointData(QPoint point, QPen pen, QBrush brush)
{
    this->point = point;
    this->pen = pen;
    this->brush = brush;
    changed = false;
}
QBrush PointData::getBrush() const {
    return brush;
}
QPoint PointData::getPoint() const {
    return point;
}
QPen PointData::getPen() const {
    return pen;
}
void PointData::draw(QPainter &painter) {
    painter.drawPoint(point);
}
bool PointData::containsPoint(const QPoint &p) {
    if (qFabs(point.x() - p.x()) < pen.width()*2 && qFabs(point.y() - p.y()) < pen.width()*2) {
        return true;
    }
    return false;
}

void PointData::moveBy(const QPoint &offset) {
    point = QPoint(point.x() + offset.x(), point.y() + offset.y());
}

QRect PointData::getBoundingBox() {
    if (field.isEmpty() || changed) {
        int x1 = point.x();
        int y1 = point.y();

        field = QRect(QPoint(x1 - 7 - pen.width(), y1 - 7 - pen.width()), QPoint(x1 + 7 + pen.width(), y1 + 7 + pen.width()));
        changed = false;
    }

    return field;
}
bool PointData::isChanged() const {
    return changed;
}
void PointData::increase() {
    pen.setWidth(pen.width()+2);
}
void PointData::decrease() {
    if (pen.width()>1) {
        pen.setWidth(pen.width()-1);
    }
}
void PointData::setChanged(bool flag) {
    changed = flag;
}
void PointData::setBrush(QBrush brush) {
    this->brush = brush;
}
void PointData::setPen(QPen pen) {
    this->pen = pen;
}

QString PointData::getType() const {
    return "Точка";
}

