#include "canvas.h"
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QColorDialog>
#include <QPixmap>
#include <QIcon>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    vbox->addLayout(hbox, Qt::AlignTop | Qt::AlignLeft);

    QComboBox *shapeSettings = new QComboBox;
    shapeSettings->addItem("Прямая линия");
    shapeSettings->addItem("Кривая");
    shapeSettings->addItem("Прямоугольник");
    shapeSettings->addItem("Эллипс");
    shapeSettings->addItem("Точка");
    shapeSettings->addItem("Многоугольник");

    hbox->addWidget(shapeSettings);

    QSpinBox *penWidthSpinBox = new QSpinBox;
    penWidthSpinBox->setRange(1, 100);

    hbox->addWidget(penWidthSpinBox);

    QSpinBox *forPolygon = new QSpinBox;
    forPolygon->setRange(3, 100);

    QComboBox *penSettings = new QComboBox;
    penSettings->addItems({ "Сплошная", "Штриховая",
                            "Точки", "Ш-Т-Ш",
                            "Ш-Т-Т-Ш"});

    hbox->addWidget(penSettings);

    QPushButton *backColorButton = new QPushButton("Цвет фона");

    hbox->addWidget(backColorButton);

    QPushButton *brushColorButton = new QPushButton("Цвет кисти");

    hbox->addWidget(brushColorButton);

    QComboBox *moveCursor = new QComboBox;
    moveCursor->addItems({"Режим рисования", "Режим изменения"});

    hbox->addWidget(moveCursor);

    QPixmap minusPix("://minus.png");
    QPixmap plusPix("://plus.png");

    QPushButton *plusButton = new QPushButton(QIcon(plusPix), "");
    plusButton->setToolTip("увеличить размер");
    QPushButton *minusButton = new QPushButton(QIcon(minusPix), "");
    minusButton->setToolTip("уменьшить размер");

    hbox->addWidget(plusButton);
    hbox->addWidget(minusButton);
    hbox->addWidget(forPolygon);

    QPixmap undoPix("://undo.png");
    QPushButton *undoButton = new QPushButton(QIcon(undoPix), "");
    undoButton->setToolTip("Отменить действие");

    hbox->addWidget(undoButton);

    QPixmap undoPix2("://undo_2.png");
    QPushButton *undoButton2 = new QPushButton(QIcon(undoPix2), "");
    undoButton2->setToolTip("Отменить отмену действия");

    hbox->addWidget(undoButton2);

    QPixmap savePix("://save.png");
    QPushButton *saveButton = new QPushButton(QIcon(savePix), "");
    saveButton->setToolTip("Сохранить рисунок");

    hbox->addWidget(saveButton);

    canvasWidget = new CanvasWidget(this);
    vbox->addWidget(canvasWidget);

    connect(shapeSettings, QOverload<int>::of(&QComboBox::currentIndexChanged), canvasWidget, &CanvasWidget::setDrawingShape);
    connect(penWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), canvasWidget, &CanvasWidget::setPenWidth);
    connect(penSettings, QOverload<int>::of(&QComboBox::currentIndexChanged), canvasWidget, &CanvasWidget::setPenStyle);
    connect(backColorButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::selectBackgroundColor);
    connect(brushColorButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::selectBrushColor);
    connect(moveCursor, QOverload<int>::of(&QComboBox::currentIndexChanged), canvasWidget, &CanvasWidget::changeObject);
    connect(undoButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::undoAction);
    connect(undoButton2, &QPushButton::clicked, canvasWidget, &CanvasWidget::undoAction2);
    connect(saveButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::saveArt);
    connect(plusButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::increaseSize);
    connect(minusButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::decreaseSize);
    connect(forPolygon, QOverload<int>::of(&QSpinBox::valueChanged), canvasWidget, &CanvasWidget::setCountOfPoints);
}

Canvas::~Canvas()
{
}


