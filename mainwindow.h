#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class QGraphicsItem;
class QGraphicsScene;
class QTimer;

namespace Ui {
class MainWindow;
}

enum class MoveDirection
{
    DownRight,
    UpRight,
    UpLeft,
    DownLeft
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void runMovingItemLoop();
    void onItemPressed();

private:
    void updateItem(QGraphicsItem *item);

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene{nullptr};
    QVector<QGraphicsItem *> items;
    QTimer *timer{nullptr};
    int timerInterval{5};
    MoveDirection direction{MoveDirection::DownRight};
};

#endif // MAINWINDOW_H
