#ifndef MATHOBJECT_H
#define MATHOBJECT_H

#include <QLine>
#include <QPoint>
#include <QRect>

class MathObject
{
public:
    MathObject();
    bool onLine(QLine line, QPoint point);
    bool onEllipse(QRect rect, QPoint point);
};

#endif // MATHOBJECT_H
