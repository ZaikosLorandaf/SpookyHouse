#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets> // warning, i know it shouldn't be included. im lazy

#include "Coordinates.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage* createImageFromPath(const char* path);
    QPushButton* createPushButton(const char* path, Size4 size4);
    void clearScreen();
    void clearTitleScreen();
    QLabel* createImageLabelFromPath(const char* path, Size4 size4);

    QLabel* titleScreenBackground;
    QLabel* title;

    Coordinates pc;
    QGraphicsView* GV = new QGraphicsView(this);

    //index represents the room number.
    std::vector<QGraphicsScene*> scenes;


private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Escape) {
            close();
        } else {
            emit keyPressed(this, event->key());
//            qDebug() << "Key pressed:" << event->text();
        }
    }

signals:
    void buttonClicked(QPushButton* b, MainWindow* a);
    void keyPressed(MainWindow *a, int key);

};
#endif // MAINWINDOW_H
