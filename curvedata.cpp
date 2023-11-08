#include "curvedata.h"
#include <QRectF>

CurveData::CurveData(QPainterPath path, QPen pen, QBrush brush)
{
    this->path = path;
    this->pen = pen;
    this->brush = brush;
    changed = false;
}
QPainterPath CurveData::getPath() {
    return path;
}
QBrush CurveData::getBrush() const {
    return brush;
}
QPen CurveData::getPen() const {
    return pen;
}
void CurveData::draw(QPainter &painter) {
    painter.drawPath(path);
}
void CurveData::increase() {
    QPainterPath scaledPath;
    QPointF startPoint = path.elementAt(0);
    scaledPath.moveTo(startPoint);
    for (int i = 0; i < path.elementCount(); ++i) {
        QPainterPath::Element element = path.elementAt(i);
        QPointF point((element.x - startPoint.x()) * 1.05 + startPoint.x(),
                            (element.y - startPoint.y()) * 1.05 + startPoint.y());
        scaledPath.lineTo(point);
    }
    path = scaledPath;
}
void CurveData::decrease() {
    QPainterPath scaledPath;
    QPointF startPoint = path.elementAt(0);
    scaledPath.moveTo(startPoint);
    for (int i = 0; i < path.elementCount(); ++i) {
        QPainterPath::Element element = path.elementAt(i);
        QPointF point((element.x - startPoint.x()) * 0.95 + startPoint.x(),
                      (element.y - startPoint.y()) * 0.95 + startPoint.y());
        scaledPath.lineTo(point);
    }
    path = scaledPath;
}
bool CurveData::containsPoint(const QPoint &point) {
    return path.contains(point);
}
void CurveData::moveBy(const QPoint &offset) {
    path.translate(offset);
}
QRect CurveData::getBoundingBox() {
    if (field.isEmpty() || changed) {
        QRectF rectF = path.boundingRect();
        int x1 = rectF.topLeft().x() - 3;
        int x2 = rectF.bottomRight().x() + 3;
        int y1 = rectF.topLeft().y() - 3;
        int y2 = rectF.bottomRight().y() + 3;
        field = QRect(QPoint(x1, y1), QPoint(x2, y2));
        changed = false;
    }
    return field;
}
bool CurveData::isChanged() const {
    return changed;
}
void CurveData::setChanged(bool flag) {
     changed = flag;
}
void CurveData::setBrush(QBrush brush) {
    this->brush = brush;
}
void CurveData::setPen(QPen pen) {
    this->pen = pen;
}
QString CurveData::getType() const {
    return "Кривая";
}
