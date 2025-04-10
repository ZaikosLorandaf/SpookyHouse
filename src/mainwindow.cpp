#include "mainwindow.h"
#include "Coordinates.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("Escape Serge");
  this->setWindowIcon(QIcon(":/assets/images/Serge001.jpg"));
  /* setup title screen */
  //    QPixmap titleLogo(":/assets/images/escapeSergeLogo001.png");
  //    QPixmap titleBG(":/assets/images/fac_pixelise_dehors_front.png");

  // this should be roughly the center of the screen
  this->pc.x = 12;
  this->pc.y = 6;

  // title screen. Size4s are roughly the center of the screen. or well, on mine. haha orwell 1984

  this->titleScreenBackground = createImageLabelFromPath(
      ":/assets/images/fac_pixelise_dehors_front.png", Size4{0, 0, 1600, 900});
  this->title = createImageLabelFromPath(
      ":/assets/images/escapeSergeLogo001.png", Size4{400, 100, 750, 100});

  this->titleScreenBackground->show();
  this->title->show();

  // fullscreen
  this->showFullScreen();

    //setup second thread
  secondary.moveToThread(&thr);
    //start second thread function when second thread start
  connect(&thr, &QThread::started, &secondary, &W_thread::doStuff);
  //stops thread when app closes
  connect(qApp, &QCoreApplication::aboutToQuit, &secondary, &W_thread::stop);

  thr.start();

  connect(&secondary, &W_thread::muon, this, &MainWindow::muon);
  connect(&secondary, &W_thread::bouton, this, &MainWindow::bouton);
  connect(&secondary, &W_thread::joystick, this, &MainWindow::joystick);
  connect(&secondary, &W_thread::jumpscare, this, &MainWindow::jumpscare);
  connect(&secondary, &W_thread::potentiometre, this, &MainWindow::potentiometre);
  connect(&secondary, &W_thread::numpad, this, &MainWindow::numpad);
  connect(&secondary, &W_thread::accelerometrex, this, &MainWindow::accelerometrex);
  connect(&secondary, &W_thread::accelerometrey, this, &MainWindow::accelerometrey);
  connect(&secondary, &W_thread::accelerometrez, this, &MainWindow::accelerometrez);
  connect(&secondary, &W_thread::keypad, this, &MainWindow::keypad);


}

MainWindow::~MainWindow() {

    delete ui;
    //close second thread
    secondary.stop();
    thr.quit();
    thr.wait();
}

QLabel *MainWindow::createImageLabelFromPath(const char *path, Size4 size4) {
  // Creates an image label with a path, an image size and coordinates.
  QLabel *q = new QLabel(this);
  q->setScaledContents(true);
  QImage *p = createImageFromPath(path);
  q->setPixmap(QPixmap::fromImage(*p));
  q->setGeometry(size4.x1, size4.y1, size4.x2, size4.y2);
  // to avoid memory leak
  delete (p);
  return q;
}

QImage *MainWindow::createImageFromPath(const char *path) {
  // Creates an image from a path. useful to create image label.
  QImage *q = new QImage(path);

  if (q->isNull()) {
    qWarning() << "Failed to load image from path: " << path;
    *q = QImage(100, 100, QImage::Format_RGB32);
  }

  return q;
}

QPushButton *MainWindow::createPushButton(const char *path, Size4 size4) {
  // Creates a push button with an image.
  QPushButton *p = new QPushButton(this);
  p->setIcon(QIcon(path));
  p->setIconSize(QSize(size4.x2, size4.y2));
  p->setFixedSize(size4.x2, size4.y2);
  p->setGeometry(size4.x1, size4.y1, size4.x2, size4.y2);
  p->setStyleSheet("QPushButton { border: none; background: transparent; }");
  p->show();

  connect(p, &QPushButton::clicked, this,
          [=]() { emit buttonClicked(p, this); });

  return p;
}

void MainWindow::clearTitleScreen() {
  delete (this->title);
  delete (this->titleScreenBackground);
  return;
}

void MainWindow::clearScreen() {}
