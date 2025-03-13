#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>

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
    QImage createImageFromPath(const char* path);
    QPushButton* createPushButton(const char* path, struct Size2 size, struct Coordinates coords);
    void clearScreen();
private:
    Ui::MainWindow *ui;
signals:
    void buttonClicked(QPushButton* b, MainWindow* a);
};
#endif // MAINWINDOW_H
