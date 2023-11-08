#include "polygondata.h"
#include <QPainterPath>
#include <QSize>

PolygonData::PolygonData(QPoint point, int countOfPoints, QPen pen, QBrush brush)
{
    startPoint = point;
    this->countOfPoints = countOfPoints;
    this->pen = pen;
    this->brush = brush;
    field = QRect(startPoint, QSize(80, 80));
    changed = false;
}
void PolygonData::setPen(QPen pen) {
    this->pen = pen;
}
void PolygonData::setBrush(QBrush brush) {
    this->brush = brush;
}
QBrush PolygonData::getBrush() const {
    return brush;
}
QPen PolygonData::getPen() const {
    return pen;
}
void PolygonData::draw(QPainter &painter) {
    if (changed || path.isEmpty()) {
        path = QPainterPath(startPoint);
        QPointF center = startPoint;
        qreal radius = std::min(field.width(), field.height()) / 2;
        qreal angle = 2 * M_PI / countOfPoints;

        for (int i = 0; i < countOfPoints; ++i) {
            qreal x = center.x() + radius * std::cos(i * angle);
            qreal y = center.y() + radius * std::sin(i * angle);
            QPointF point(x, y);
            if (i == 0) {
                path.moveTo(point);
            } else {
                path.lineTo(point);
            }
        }
        path.closeSubpath();
    }
    painter.drawPath(path);
}
bool PolygonData::containsPoint(const QPoint &point) {
    return path.contains(point);
}

void PolygonData::moveBy(const QPoint &offset) {
    startPoint = QPoint(startPoint.x() + offset.x(), startPoint.y() + offset.y());
    field.translate(offset);
}

QRect PolygonData::getBoundingBox() {
    return QRect(QPoint(field.topLeft().x() - field.width()/2, field.topLeft().y() - field.height()/2),
                 QPoint(field.bottomRight().x() - field.width()/2, field.bottomRight().y() - field.height()/2));
}
bool PolygonData::isChanged() const {
    return changed;
}
void PolygonData::increase() {
    field = QRect(startPoint, QSize(field.width() + 5, field.height() + 5));
}
void PolygonData::decrease() {
    field = QRect(startPoint, QSize(field.width() - 5, field.height() - 5));
}
void PolygonData::setChanged(bool flag) {
    changed = flag;
}
QString PolygonData::getType() const {
    return "Многоугольник";
}


