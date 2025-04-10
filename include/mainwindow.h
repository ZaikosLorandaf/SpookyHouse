#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets> // warning, i know it shouldn't be included. im lazy
#include <QThread>

#include "Coordinates.h"
#include "thread.hpp"
#include "map.hpp"

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

    QThread thr;
    W_thread secondary;

    QLabel* text = new QLabel(this);

public slots:
    inline void muon(){
        qDebug() << "muon";
    };
    inline void bouton(int bouton){
        if(bouton == 1){
            emit startGame(this);
        }
        qDebug() << "bouton " << bouton;
    }; //0(haut), 1(droit), 2(bas), 3(gauche)
    inline void joystick(int direction){
        if(direction==0){
            emit keyPressed(this, 87);
        }
        if(direction==1){
            emit keyPressed(this, 68);
        }
        if(direction==2){
            emit keyPressed(this, 83);
        }
        if(direction==3){
            emit keyPressed(this, 65);
        }
        qDebug() << "joystick " << direction;
    }; //0(haut), 1(droit), 2(bas), 3(gauche). peut-etre ajouter diagonale mais pas live
    inline void potentiometre(int direction){
        qDebug() << "potentiometre " << direction;
    }; //0(antihoraire), 1(horaire)
    inline void numpad(QString car){
        qDebug() << "numpad " << car;
    };
    inline void jumpscare(){
        QLabel* l = createImageLabelFromPath(":/assets/images/Serge001.jpg", Size4 {0, 0, 2000, 1000});
        l->show();
        QThread::msleep(1000);
        l->hide();
        delete(l);
    };
    inline void accelerometre(float a){

    }

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
    void hideHint();
    void startGame(MainWindow* a);

};
#endif // MAINWINDOW_H
