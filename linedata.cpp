#include "linedata.h"

LineData::LineData(QLine line, QPen pen, QBrush brush)
{
    this->line = line;
    this->pen = pen;
    this->brush = brush;
    changed = false;
}
QBrush LineData::getBrush() const {
    return brush;
}
QLine LineData::getLine() {
    return line;
}
QPen LineData::getPen() const {
    return pen;
}
void LineData::draw(QPainter &painter) {
    painter.drawLine(line);
}
bool LineData::containsPoint(const QPoint &point) {
    int x1 = line.p1().x();
    int x2 = line.p2().x();
    int y1 = line.p1().y();
    int y2 = line.p2().y();

    if (!(point.x() >= std::min(x1, x2) - 6 && point.x() <= std::max(x1, x2) + 6))
        return false;

    int A = y2 - y1;
    int B = -(x2 - x1);
    int C = y1 *(x2 - x1) - x1 * A;

    double znam = qFabs(A*point.x() + B*point.y() + C);
    double del = qSqrt(A*A + B*B);

    double des = (znam / del);

    return pen.width() >= 3 ? des <= pen.width()*2 : des <= pen.width()*6;
}

void LineData::moveBy(const QPoint &offset) {
    line.translate(offset);
}

QRect LineData::getBoundingBox() {
    if (field.isEmpty() || changed) {
        int x1 = line.p1().x();
        int x2 = line.p2().x();
        int y1 = line.p1().y();
        int y2 = line.p2().y();

        int topLeftX = std::min(x1, x2);
        int topLeftY = std::min(y1, y2);
        int bottomRightX = std::max(x1, x2);
        int bottomRightY = std::max(y1, y2);

        field = QRect(QPoint(topLeftX - 10, topLeftY - 10), QPoint(bottomRightX + 10, bottomRightY + 10));
        changed = false;
    }

    return field;
}
bool LineData::isChanged() const {
    return changed;
}
void LineData::increase() {
    QPoint newP2 = (line.p2() - line.p1()) * 1.05;
    line.setP2(line.p1() + newP2);
}
void LineData::decrease() {
    QPoint newP2 = (line.p2() - line.p1()) * 0.95;
    line.setP2(line.p1() + newP2);
}
void LineData::setChanged(bool flag) {
    changed = flag;
}
void LineData::setBrush(QBrush brush) {
    this->brush = brush;
}
void LineData::setPen(QPen pen) {
    this->pen = pen;
}

QString LineData::getType() const {
    return "Прямая";
}
