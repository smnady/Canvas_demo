#include "canvaswidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QColorDialog>
#include <QImage>
#include <QFileDialog>
#include <QDir>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget{parent}
{
    pen.setColor(Qt::black);
    pen.setWidth(1);
    brush.setColor(Qt::transparent);
    backgroundColor = Qt::white;
    selectedColor = Qt::red;
    selectedPen.setColor(selectedColor);
    selectedPen.setWidth(1);
    selectedPen.setStyle(Qt::DashLine);
    selected = NULL;
    currentShape = Line;
    drawing = true;
    modification = false;
    setFocusPolicy(Qt::StrongFocus);
    countOfPoints = 3;
}
CanvasWidget::~CanvasWidget() {
    for (ObjectData* object : objects) {
        delete object;
        qDebug() << "object was deleted";
    }
    objects.clear();
    clearDeleted();
}
void CanvasWidget::increaseSize() {
    if (modification && selected != NULL) {
        selected->increase();
        selected->setChanged(true);
        update();
    }
}
void CanvasWidget::decreaseSize() {
    if (modification && selected != NULL) {
        selected->decrease();
        selected->setChanged(true);
        update();
    }
}
void CanvasWidget::undoAction() {
    if (!objects.isEmpty()) {
        ObjectData* lastObject = objects.last();
        deletedObjects.append(lastObject);
        objects.removeLast();
        update();
    }
}
void CanvasWidget::undoAction2() {
    if(!deletedObjects.isEmpty()) {
        ObjectData* lastObject = deletedObjects.last();
        objects.append(lastObject);
        deletedObjects.removeLast();
        update();
    }
}
void CanvasWidget::clearDeleted() {
    for (ObjectData* object : deletedObjects) {
        delete object;
        qDebug() << "object was deleted";
    }
    deletedObjects.clear();
}

void CanvasWidget::saveArt() {
    QString filename = QFileDialog::getSaveFileName(this, "Сохранить изображение", QDir::homePath(), "Изображения (*.png *.jpg)");
    if (!filename.isEmpty()) {
        QImage image(this->size(), QImage::Format_ARGB32);
        QPainter painter(&image);
        this->render(&painter);
        image.save(filename);
    }
}

void CanvasWidget::keyPressEvent(QKeyEvent* event) {
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_Z) {
            undoAction();
        } else if (event->key() == Qt::Key_Y) {
            undoAction2();
        } else if (event->key() == Qt::Key_S) {
            saveArt();
        }
    }
}

void CanvasWidget::selectBackgroundColor() {
    QColor color = QColorDialog::getColor(backgroundColor, this, "Выберите цвет фона");
    if (color.isValid()) {
        backgroundColor = color;
        update();
    }
}

void CanvasWidget::selectBrushColor() {
    QColor color = QColorDialog::getColor(brush.color(), this, "Выберите цвет кисти");
    if (color.isValid()) {
        pen.setColor(color);
    }
    if (modification && selected != NULL) {
        selected->setPen(pen);
        update();
    }
}
void CanvasWidget::setDrawingShape(int index) {
    switch (index) {
    case 0:
        currentShape = Line;
        break;
    case 1:
        currentShape = Curve;
        break;
    case 2:
        currentShape = Rectangle;
        break;
    case 3:
        currentShape = Ellipse;
        break;
    case 4:
        currentShape = Point;
        break;
    case 5:
        currentShape = Polygon;
        break;
    }
}
void CanvasWidget::setCountOfPoints(int count) {
    countOfPoints = count;
}
void CanvasWidget::changeObject(int index) {
    switch(index) {
    case 0:
        drawing = true;
        modification = false;
        selected = NULL;
        this->setCursor(Qt::CustomCursor);
        break;
    case 1:
        drawing = false;
        modification = true;
        this->setCursor(Qt::ClosedHandCursor);
        break;
    }
}

void CanvasWidget::setPenWidth(int width) {
    pen.setWidth(width);
    if (modification && selected != NULL) {
        selected->setPen(pen);
    }
}

void CanvasWidget::setPenStyle(int index) {
    switch (index) {
    case 0:
        pen.setStyle(Qt::SolidLine);
        break;
    case 1:
        pen.setStyle(Qt::DashLine);
        break;
    case 2:
        pen.setStyle(Qt::DotLine);
        break;
    case 3:
        pen.setStyle(Qt::DashDotLine);
        break;
    case 4:
        pen.setStyle(Qt::DashDotDotLine);
        break;
    }
    if (modification && selected != NULL) {
        selected->setPen(pen);
        update();
    }
}

void CanvasWidget::paintEvent(QPaintEvent *event) {

    qDebug() << "Paint Event";

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(event->rect(), backgroundColor);

    if (drawing) {
        painter.setPen(pen);
        painter.setBrush(brush);

        switch (currentShape) {
        case Line:
            painter.drawLine(startPoint, endPoint);
            break;
        case Curve:
            painter.drawPath(currentCurvePath);
            break;
        case Rectangle:
            painter.drawRect(QRect(startPoint, endPoint));
            break;
        case Ellipse:
            painter.drawEllipse(QRect(startPoint, endPoint));
            break;
        case Point:
            painter.drawPoint(startPoint);
            break;
        }
    }
    for (ObjectData* object : objects) {
        if (object) {
            painter.setPen(object->getPen());
            painter.setBrush(object->getBrush());
            object->draw(painter);
        }
    }
    if (selected != NULL && modification) {
        painter.setPen(selectedPen);
        painter.drawRect(selected->getBoundingBox());
        painter.drawText(selected->getBoundingBox().topLeft() + QPoint(10, -10), selected->getType());
    }
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    if (!modification) {
        startPoint = event->pos();
        qDebug() << "Mouse Press Event - startPoint: " << startPoint;
        if(currentShape==Curve) {
            currentCurvePath = QPainterPath(startPoint);
        } else {
            endPoint = startPoint;
          }
    }
    else if (modification) {
          moveStartPoint = event->pos();
          for (ObjectData* obj : objects) {
            if (obj->containsPoint(moveStartPoint)) {
                selected = obj;
                qDebug() << "object was selected";
                update();
                break;
            }
          }
    }
}
void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    if (!modification) {
        endPoint = event->pos();
        drawing = true;
        switch (currentShape) {
        case Line:
        case Rectangle:
        case Ellipse:
            qDebug() << "Mouse Move Event - endPoint: " << endPoint;
            break;
        case Curve:
            currentCurvePath.lineTo(endPoint);
            break;
        }
    }
    if (modification && selected != NULL) {
        moveEndPoint = event->pos();
        if (selected->containsPoint(moveStartPoint)) {
            selected->moveBy(QPoint(moveEndPoint.x() - moveStartPoint.x(), moveEndPoint.y() - moveStartPoint.y()));
            moveStartPoint = moveEndPoint;
            selected->setChanged(true);
        }
    }
    update();
}
void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    if(drawing && !modification) {
        if (currentShape != Curve) {
            endPoint = event->pos();
        }
        if (currentShape == Line) {
            objects.append(new LineData(QLine(startPoint, endPoint), pen, brush));
        }
        else if (currentShape == Curve) {
            objects.append(new CurveData(currentCurvePath, pen, brush));
            currentCurvePath.clear();
        }
        else if (currentShape == Rectangle) {
            objects.append(new RectData(QRect(startPoint, endPoint), pen, brush));
        }
        else if (currentShape == Ellipse) {
            objects.append(new EllipseData(QRect(startPoint, endPoint), pen, brush));
        }
        else if (currentShape == Point) {
            objects.append(new PointData(startPoint, pen, brush));
        }
        else if (currentShape == Polygon) {
            objects.append(new PolygonData(startPoint, countOfPoints, pen, brush));
        }
        drawing = false;
        if (!deletedObjects.isEmpty()) clearDeleted();
        update();
    }
    else if(modification && selected != NULL && !moveEndPoint.isNull()) {
        if (selected->containsPoint(moveStartPoint)) {
            selected->moveBy(QPoint(moveEndPoint.x() - moveStartPoint.x(), moveEndPoint.y() - moveStartPoint.y()));
            selected->setChanged(true);
            moveEndPoint = QPoint(0, 0);
            update();
        }
    }
}

