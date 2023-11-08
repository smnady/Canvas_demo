#ifndef POINTDATA_H
#define POINTDATA_H

#include "objectdata.h"

class PointData : public ObjectData {
public:
    PointData(QPoint point, QPen pen, QBrush brush);
    void draw(QPainter &painter) override;
    QPen getPen() const override;
    QBrush getBrush() const override;
    QString getType() const override;
    QPoint getPoint() const;
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
    QPoint point;
    QRect field;
    QPen pen;
    QBrush brush;
    bool changed;
};
#endif // POINTDATA_H
