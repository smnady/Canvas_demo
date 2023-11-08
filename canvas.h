#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>
#include <QLine>
#include <QPainter>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QPen>
#include <QBrush>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainterPath>
#include "canvaswidget.h"


class Canvas : public QWidget
{
    Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);
    ~Canvas();

private:
    CanvasWidget *canvasWidget;

};
#endif // CANVAS_H
