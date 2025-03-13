#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Coordinates.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Escape Serge");
    this->setWindowIcon(QIcon(":/assets/images/Serge001.jpg"));
/* setup title screen */
    QPixmap titleLogo(":/assets/images/escapeSergeLogo001.png");
    QPixmap titleBG(":/assets/images/fac_pixelise_dehors_front.png");



    ui->label_title->setPixmap(titleLogo);
    ui->label_BG->setPixmap(titleBG);

    ui->label_title->setPixmap(titleLogo);
    ui->label_title->setScaledContents(true);
    ui->label_title->setAlignment(Qt::AlignCenter);

    ui->label_BG->setPixmap(titleBG);
    ui->label_BG->setScaledContents(true);
    ui->label_BG->setAlignment(Qt::AlignCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::createImageFromPath(const char* path){
    QImage q(path);

    if (q.isNull()) {
        qWarning() << "Failed to load image from path: " << path;
        q = QImage(100, 100, QImage::Format_RGB32);
    }

    return q;
}



QPushButton* MainWindow::createPushButton(const char* path, struct Size2 size, struct Coordinates coords){
    QPushButton* p = new QPushButton(this);
    p->setIcon(QIcon(path));
    p->setIconSize(QSize(size.x, size.y));
    p->setFixedSize(size.x, size.y);
    p->setGeometry(coords.x1, coords.y1, coords.x2, coords.y2);
    p->setStyleSheet("QPushButton { border: none; background: transparent; }");
    p->show();

    connect(p, &QPushButton::clicked, this, [=]() {
        emit buttonClicked(p, this);
    });

    return p;
}

void MainWindow::clearScreen()
{
    QLayout* layout = centralWidget()->layout();


    if (layout) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            QWidget* widget = item->widget();
            if (widget) {
                widget->deleteLater();
            }
            delete item;
        }
    }
}
