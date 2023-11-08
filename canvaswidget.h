#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPoint>
#include <QLine>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QPainterPath>
#include "linedata.h"
#include "rectdata.h"
#include "curvedata.h"
#include "ellipsedata.h"
#include "mathobject.h"
#include "objectdata.h"
#include "pointdata.h"
#include "polygondata.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();
    void setPenColor(const QColor &color);
    void setPenStyle(int index);
    void setPenWidth(int width);
    void setBrushStyle(int index);
    void setBackgroundColor(const QColor &color);
    void clearCanvas();
    void selectBackgroundColor();
    void selectBrushColor();
    void setDrawingShape(int index);
    void changeObject(int index);
    void undoAction();
    void undoAction2();
    void clearDeleted();
    void saveArt();
    void setCountOfPoints(int count);

    void keyPressEvent(QKeyEvent* event) override;
    void increaseSize();
    void decreaseSize();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    bool drawing;
    bool modification;
    QPen pen;
    QBrush brush;
    QColor backgroundColor;
    QPoint startPoint;
    QPoint endPoint;
    QPoint anotherPoint;
    QPainterPath currentCurvePath;
    //QVector<RectData> rects;
    //QVector<CurveData> curves;
    //QVector<EllipseData> ellipses;
    //QVector<LineData> lines;
    QVector<ObjectData*> objects;
    QVector<ObjectData*> deletedObjects;
    ObjectData* selected;
    QColor selectedColor;
    QPen selectedPen;
    QPoint moveStartPoint;
    QPoint moveEndPoint;
    int countOfPoints;
    enum DrawingShape {
        Line,
        Curve,
        Rectangle,
        Ellipse,
        Point,
        Polygon
    } currentShape;

signals:

};

#endif // CANVASWIDGET_H
