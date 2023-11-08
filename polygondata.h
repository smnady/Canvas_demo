#ifndef POLYGONDATA_H
#define POLYGONDATA_H

#include "objectdata.h"

class PolygonData : public ObjectData
{
public:
    PolygonData(QPoint point, int countOfPoints, QPen pen, QBrush brush);
    void draw(QPainter &painter) override;
    QPen getPen() const override;
    QBrush getBrush() const override;
    QString getType() const override;
    QRect getBoundingBox() override;
    bool containsPoint(const QPoint &point) override;
    void setPen(QPen pen) override;
    void setBrush(QBrush brush) override;
    void moveBy(const QPoint &offset) override;
    bool isChanged() const override;
    void setChanged(bool flag) override;
    void decrease() override;
    void increase() override;
private:
    int countOfPoints;
    QPoint startPoint;
    QRect field;
    bool changed;
    QPen pen;
    QBrush brush;
    QPainterPath path;
};

#endif // POLYGONDATA_H
