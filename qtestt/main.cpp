#include "mainwindow.h"
#include "Coordinates.h"

#include <QApplication>

void buttonPushedImageCat(QPushButton *p, MainWindow *w){
    delete p;
    const char* path2 = ":/assets/images/cat.png";
    QDialog *dialog = new QDialog(w);
    dialog->setWindowTitle(" ");

    QLabel *label = new QLabel(dialog);
    QPixmap pixmap(path2);
    label->setPixmap(pixmap);
    label->setScaledContents(true);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(label);
    dialog->setLayout(layout);

    dialog->setFixedSize(pixmap.size());
    dialog->exec();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    struct Coordinates coord;
    coord.x1 = 250;
    coord.x2 = 50;
    coord.y1 = 200;
    coord.y2 = 50;
    struct Size2 size;
    size.x = 256;
    size.y = 75;

    w.createPushButton(":/assets/images/StartGame001.png", size, coord);

    QObject::connect(&w, &MainWindow::buttonClicked, buttonPushedImageCat);

    //infinite loop here

    return a.exec();
}
