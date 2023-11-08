#ifndef RECTDATA_H
#define RECTDATA_H

#include <QRect>
#include <QPen>
#include <QBrush>
#include "objectdata.h"

class RectData : public ObjectData
{
public:
    RectData(QRect rect, QPen pen, QBrush brush);
    QRect getRect();
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
    QRect rect;
    QPen pen;
    QBrush brush;
    QRect field;
    bool changed;
};

#endif // RECTDATA_H
