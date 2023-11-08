#include "rectdata.h"
#include "mathobject.h"
#include "linedata.h"
RectData::RectData(QRect rect, QPen pen, QBrush brush)
{
    this->rect = rect;
    this->pen = pen;
    this->brush = brush;
    changed = false;
}
QRect RectData::getRect() {
    return rect;
}
QPen RectData::getPen() const {
    return pen;
}
QBrush RectData::getBrush() const {
    return brush;
}
void RectData::draw(QPainter &painter) {
    painter.drawRect(rect);
}
void RectData::moveBy(const QPoint &offset) {
    rect.translate(offset);
}
void RectData::increase() {
    rect.setWidth((int) rect.width()*1.05);
    rect.setHeight((int) rect.height()*1.05);
}
void RectData::decrease() {
    rect.setWidth((int) rect.width()*0.95);
    rect.setHeight((int) rect.height()*0.95);
}
bool RectData::containsPoint(const QPoint &point) {
    QPoint bl = rect.bottomLeft();
    QPoint br = rect.bottomRight();
    QPoint tl = rect.topLeft();
    QPoint tr = rect.topRight();
    QLine l1(bl, br);
    QLine l2(bl, tl);
    QLine l3(br, tr);
    QLine l4(tl, tr);
    LineData line1(l1, pen, brush);
    LineData line2(l2, pen, brush);
    LineData line3(l3, pen, brush);
    LineData line4(l4, pen, brush);
    MathObject math;
    if (line1.containsPoint(point) || line2.containsPoint(point) ||
        line3.containsPoint(point) || line4.containsPoint(point)) {
        return true;
    } else return false;
}
bool RectData::isChanged() const {
    return changed;
}
void RectData::setChanged(bool flag) {
    changed = flag;
}
QString RectData::getType() const{
    return "Прямоугольник";
}
QRect RectData::getBoundingBox() {
    if (field.isEmpty() || changed) {
        QPoint br(rect.bottomRight().x() + 3, rect.bottomRight().y() + 3);
        QPoint tl(rect.topLeft().x() - 3, rect.topLeft().y() - 3);
        field = QRect(tl, br);
        changed = false;
    }
    return field;
}
void RectData::setBrush(QBrush brush) {
    this->brush = brush;
}
void RectData::setPen(QPen pen) {
    this->pen = pen;
}
