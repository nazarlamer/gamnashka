#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamnashkaitem.h"
#include <QTimer>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const int width = 600;
    const int height = 580;

    scene = new QGraphicsScene(QRectF(0, 0, width, height));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush("#2e2f30", Qt::SolidPattern));

    GamnashkaItem *item = new GamnashkaItem();
    scene->addItem(item);
    item->setPos(0, 0);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    connect(item, &GamnashkaItem::itemWasPressed, this, &MainWindow::onItemPressed);
    items.push_back(item);

    QGraphicsTextItem *textItem = scene->addText("Press me");
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos(0, -25);
    textItem->setParentItem(item);

    timer = new QTimer{this};
    connect(timer, &QTimer::timeout, this, &MainWindow::runMovingItemLoop);
    timer->start(timerInterval);
}

void MainWindow::runMovingItemLoop()
{
    for (auto *item : items)
        updateItem(item);

    timer->start(timerInterval);
}

void MainWindow::onItemPressed()
{
    GamnashkaItem *item = new GamnashkaItem();
    scene->addItem(item);
    item->setPos(0, 0);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    connect(item, &GamnashkaItem::itemWasPressed, this, &MainWindow::onItemPressed);
    items.push_back(item);

    QGraphicsTextItem *textItem = scene->addText("Press me");
    textItem->setDefaultTextColor(Qt::white);
    textItem->setPos(0, -25);
    textItem->setParentItem(item);
}

void MainWindow::updateItem(QGraphicsItem *item)
{
    const auto itemPos = item->pos();
    const auto sceneRect = scene->sceneRect();

    switch (direction)
    {
    case MoveDirection::DownRight:
        item->setPos(QPointF{itemPos.x() + 1, itemPos.y() + 1});
        if (!sceneRect.contains(itemPos))
        {
            direction = MoveDirection::UpRight;
            item->setPos(QPointF{itemPos.x() - 1, itemPos.y() - 1});
        }
        break;

    case MoveDirection::UpRight:
        item->setPos(QPointF{itemPos.x() + 1, itemPos.y() - 1});
        if (!sceneRect.contains(itemPos))
        {
            direction = MoveDirection::UpLeft;
            item->setPos(QPointF{itemPos.x() - 1, itemPos.y() + 1});
        }
        break;

    case MoveDirection::UpLeft:
        item->setPos(QPointF{itemPos.x() - 1, itemPos.y() - 1});
        if (!sceneRect.contains(itemPos))
        {
            direction = MoveDirection::DownLeft;
            item->setPos(QPointF{itemPos.x() + 1, itemPos.y() + 1});
        }
        break;

    case MoveDirection::DownLeft:
        item->setPos(QPointF{itemPos.x() - 1, itemPos.y() + 1});
        if (!sceneRect.contains(itemPos))
        {
            direction = MoveDirection::DownRight;
            item->setPos(QPointF{itemPos.x() + 1, itemPos.y() - 1});
        }
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
