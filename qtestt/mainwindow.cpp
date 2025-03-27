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

    //this should be roughly the center of the screen
    this->pc.x = 12;
    this->pc.y = 10;

    //displaying title screen
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

QLabel* MainWindow::createImageLabelFromPath(const char* path, Size2 size, Coordinates coords){
    //Creates an image label with a path, an image size and coordinates.
    QLabel* q = new QLabel(this);
    q->setScaledContents(true);
    QImage* p = createImageFromPath(path);
    q->setPixmap(QPixmap::fromImage(*p));
    q->setGeometry(coords.x, coords.y, size.x, size.y);
    //to avoid memory leak
    delete(p);
    return q;
}

QImage* MainWindow::createImageFromPath(const char* path){
    //Creates an image from a path. useful to create image label.
    QImage* q = new QImage(path);

    if (q->isNull()) {
        qWarning() << "Failed to load image from path: " << path;
        *q = QImage(100, 100, QImage::Format_RGB32);
    }

    return q;
}

QPushButton* MainWindow::createPushButton(const char* path, Size2 size, Coordinates coords){
    //Creates a push button with an image.
    QPushButton* p = new QPushButton(this);
    p->setIcon(QIcon(path));
    p->setIconSize(QSize(size.x, size.y));
    p->setFixedSize(size.x, size.y);
    p->setGeometry(coords.x, coords.y, size.x, size.y);
    p->setStyleSheet("QPushButton { border: none; background: transparent; }");
    p->show();

    connect(p, &QPushButton::clicked, this, [=]() {
        emit buttonClicked(p, this);
    });

    return p;
}

void MainWindow::clearTitleScreen(){
    if (ui->label_title){
        delete(ui->label_title);
    }
    if (ui->label_BG){
        delete(ui->label_BG);
    }
    return;
}

void MainWindow::clearScreen()
{

}
