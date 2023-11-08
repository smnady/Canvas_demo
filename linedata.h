#ifndef LINEDATA_H
#define LINEDATA_H

#include <QLine>
#include "objectdata.h"

class LineData : public ObjectData
{
public:
    LineData(QLine line, QPen pen, QBrush brush);
    QLine getLine();
    void draw(QPainter &painter) override;
    QPen getPen() const override;
    QBrush getBrush() const override;
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
    QLine line;
    QPen pen;
    QBrush brush;
    QRect field;
    bool changed;
};

#endif // LINEDATA_H
