#ifndef CURVEDATA_H
#define CURVEDATA_H

#include "objectdata.h"
#include <QPainterPath>

class CurveData : public ObjectData
{
public:
    CurveData(QPainterPath path, QPen pen, QBrush brush);
    QPainterPath getPath();
    QPen getPen() const override;
    QBrush getBrush() const override;
    void draw(QPainter &painter) override;
    bool containsPoint(const QPoint &point) override;
    QString getType() const override;
    QRect getBoundingBox() override;
    void setBrush(QBrush brush) override;
    void setPen(QPen pen) override;
    void moveBy(const QPoint &offset) override;
    bool isChanged() const override;
    void setChanged(bool flag) override;
    void increase() override;
    void decrease() override;
private:
    QPainterPath path;
    QPen pen;
    QBrush brush;
    QRect field;
    bool changed;
};

#endif // CURVEDATA_H
