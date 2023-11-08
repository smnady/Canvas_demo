#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <QString>
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <QPainterPath>

class ObjectData
{
public:
    virtual void draw(QPainter &painter) = 0;
    virtual QPen getPen() const = 0;
    virtual QBrush getBrush() const = 0;

    virtual QString getType() const = 0;
    virtual QRect getBoundingBox() = 0;
    virtual bool containsPoint(const QPoint &point) = 0;

    virtual void setPen(QPen pen) = 0;
    virtual void setBrush(QBrush brush) = 0;
    virtual void moveBy(const QPoint &offset) = 0;
    virtual bool isChanged() const = 0;
    virtual void setChanged(bool flag) = 0;
    virtual void decrease() = 0;
    virtual void increase() = 0;

protected:
    QRect field;
    bool changed;
};

#endif // OBJECTDATA_H
