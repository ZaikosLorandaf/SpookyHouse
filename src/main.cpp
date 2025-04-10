#include "Coordinates.h"
#include "mainwindow.h"
#include "map.hpp"

#include <QApplication>

const char *temp[] = {
    "####       "
    "##########################################################################"
    "#################################",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 |    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 #    "
    "                  !                        #",
    "####                                                                 #    "
    "                #####                      #",
    "####                                                                 #    "
    "                #####                      #",
    "####                                                                 #    "
    "                                           #",
    "####                                                                 "
    "#################################################",
    "####                                                                 "
    "#################################################",
    "####                                                                 "
    "#################################################",
    "####                                                                 "
    "#################################################",
    "####                                                                "
    "X#################################################",
    "####                                                                 "
    "#################################################",
    "##########################################################################"
    "############################################"};

// je pense qu'on peut juste utiliser genre un qframe ou qqchose du genre
class DarkOverlay : public QWidget {
public:
  DarkOverlay(QWidget *parent = nullptr) : QWidget(parent) {
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    setStyleSheet("background: rgba(0, 0, 0, 111);");
  }
};

void createScene(MainWindow *w) {
  // Creer une scene et l'ajouter au vecteur scenes. Elles sont arrangees de 0
  // au nombre de piece total Elles n'ont pas de nom, juste un chiffre, donc on
  // devra genre etablir quelle numero correspond a quelle piece.
  QGraphicsScene *s = new QGraphicsScene(w->GV);
  w->scenes.push_back(s);
}

QGraphicsPixmapItem *createPixmap(const char *path, Coordinates size) {
  // Creer une QGraphicsPixmapItem pour afficher dans les scenes
  QPixmap *p = new QPixmap(path);
  QPixmap s = p->scaled(size.x, size.y);
  QGraphicsPixmapItem *q = new QGraphicsPixmapItem(s);
  delete p;
  return q;
}

// TODO: char is temporary. need to add parser compatibility LEGACY
void fillScene(MainWindow *w, int roomNumber, const char *t[],
               Coordinates imagesize) {
  // Remplir une scene d'images, labels, whatever you need.
  if (!w->scenes[roomNumber]) {
    qWarning() << "Room isn't." << roomNumber;
    return;
  }
  size_t x = strlen(t[0]);
  int y = 21;
  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      // todo: check for walls, floors, etc. and execute in separate thread
      // (ideally.)
      if (t[i][j] == '#') {
        const char *path = ":/assets/images/wall.png";
        QGraphicsPixmapItem *q = createPixmap(path, imagesize);
        w->scenes[roomNumber]->addItem(q);
        q->setPos(j * imagesize.x, i * imagesize.y);
      }
      if (t[i][j] == ' ') {
        int rand = std::rand() % 3;
        if (rand == 0) {
          const char *path = ":/assets/images/floor1.png";
          QGraphicsPixmapItem *q = createPixmap(path, imagesize);
          w->scenes[roomNumber]->addItem(q);
          q->setPos(j * imagesize.x, i * imagesize.y);
        } else if (rand == 1) {
          const char *path = ":/assets/images/floor2.png";
          QGraphicsPixmapItem *q = createPixmap(path, imagesize);
          w->scenes[roomNumber]->addItem(q);
          q->setPos(j * imagesize.x, i * imagesize.y);
        } else {
          const char *path = ":/assets/images/floor3.png";
          QGraphicsPixmapItem *q = createPixmap(path, imagesize);
          w->scenes[roomNumber]->addItem(q);
          q->setPos(j * imagesize.x, i * imagesize.y);
        }
      }
    }
  }
}

void fillScene2(MainWindow *w, Map &map, int roomNumber) {
  if (roomNumber > w->scenes.size() || roomNumber < 0) {
    qWarning() << "Room isn't." << roomNumber;
    return;
  }
  // Remplir une scene d'images, labels, whatever you need.
  Coordinates imagesize = {50, 50};
  int x = map.get_size().x;
  int y = map.get_size().y;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      // todo: check for walls, floors, etc. and execute in separate thread
      // (ideally.)
      auto maybe_tile = map.get_tile(i, j);
      // assert(maybe_tile);
      if (!maybe_tile) {
        std::cout << i << ' ' << j << '\n';
        exit(1);
      }
      Tile &tile = *maybe_tile;
      // TODO: add other tiles
      TileWall *wall = dynamic_cast<TileWall *>(&tile);
      TileEmpty *empty = dynamic_cast<TileEmpty *>(&tile);
      if (wall) {
        const char *path = ":/assets/images/wall.png";
        QGraphicsPixmapItem *q = createPixmap(path, imagesize);
        w->scenes[roomNumber]->addItem(q);
        q->setPos(i * imagesize.x, j * imagesize.y);
      }
      if (empty) {
        int rand = std::rand() % 3;
        if (rand == 0) {
          const char *path = ":/assets/images/floor1.png";
          QGraphicsPixmapItem *q = createPixmap(path, imagesize);
          w->scenes[roomNumber]->addItem(q);
          q->setPos(i * imagesize.x, j * imagesize.y);
        } else if (rand == 1) {
          const char *path = ":/assets/images/floor2.png";
          QGraphicsPixmapItem *q = createPixmap(path, imagesize);
          w->scenes[roomNumber]->addItem(q);
          q->setPos(i * imagesize.x, j * imagesize.y);
        } else {
          const char *path = ":/assets/images/floor3.png";
          QGraphicsPixmapItem *q = createPixmap(path, imagesize);
          w->scenes[roomNumber]->addItem(q);
          q->setPos(i * imagesize.x, j * imagesize.y);
        }
      }
    }
  }
}

void switchRoom(MainWindow *w, int roomNumber) {
  // Changement de salle -> changement de scene
  if (w->scenes.size() > roomNumber) {
    w->GV->setScene(w->scenes[roomNumber]);
  } else {
    qWarning() << "Room doesn't exist!";
  }
  return;
}

void move(MainWindow *w, int key) {
  // Deplacement (LEGACY)
  switch (key) {
  case 87:
    if (w->pc.y - 1 >= 0 && temp[int(w->pc.y - 1)][int(w->pc.x)] != '#') {
      w->pc.y -= 1;
      w->GV->move(w->GV->x(), w->GV->y() + 50);
    }

    break;
  case 83:
    if (w->pc.y + 1 >= 0 && w->pc.y + 1 < 21 &&
        temp[int(w->pc.y + 1)][int(w->pc.x)] != '#') {
      w->pc.y += 1;
      w->GV->move(w->GV->x(), w->GV->y() - 50);
    }

    break;
  case 65:
    if (w->pc.x - 1 >= 0 && temp[int(w->pc.y)][int(w->pc.x - 1)] != '#') {
      w->pc.x -= 1;
      w->GV->move(w->GV->x() + 50, w->GV->y());
    }

    break;
  case 68:
    if (w->pc.x + 1 >= 0 && w->pc.x + 1 < 121 &&
        temp[int(w->pc.y)][int(w->pc.x + 1)] != '#') {
      w->pc.x += 1;
      w->GV->move(w->GV->x() - 50, w->GV->y());
    }

    break;
  case 81:
    return;
  }

  return;
}

void move2(MainWindow *w, int key, Map &map) {
  // Deplacement
    Vec2 mapsize = map.get_size();
  if (key == 87 && w->pc.y -1 > 0) { // UP
    // TODO: add other TILE classes (door, entrance, ...)
    auto maybe_tile = map.get_tile(w->pc.x, w->pc.y - 1);

    assert(maybe_tile);
    Tile &tile = *maybe_tile;
    TileWall *wall = dynamic_cast<TileWall *>(&tile);
    TileEmpty *empty = dynamic_cast<TileEmpty *>(&tile);
    if (empty) {
      w->pc.y -= 1;
      w->GV->move(w->GV->x(), w->GV->y() + 50);
    }
    if (wall) {
      return;
    }
  }
  if (key == 83 && w->pc.y +1 < mapsize.y) { // DOWN
    // TODO: add other TILE classes (door, entrance, ...)
    auto maybe_tile = map.get_tile(w->pc.x, w->pc.y + 1);
    assert(maybe_tile);
    Tile &tile = *maybe_tile;
    TileWall *wall = dynamic_cast<TileWall *>(&tile);
    TileEmpty *empty = dynamic_cast<TileEmpty *>(&tile);
    if (empty) {
      w->pc.y += 1;
      w->GV->move(w->GV->x(), w->GV->y() - 50);
    }
    if (wall) {
      return;
    }
  }
  if (key == 65 && w->pc.x -1 > 0) { // LEFT
    // TODO: add other TILE classes (door, entrance, ...)
    auto maybe_tile = map.get_tile(w->pc.x - 1, w->pc.y);
    assert(maybe_tile);
    Tile &tile = *maybe_tile;
    TileWall *wall = dynamic_cast<TileWall *>(&tile);
    TileEmpty *empty = dynamic_cast<TileEmpty *>(&tile);
    if (empty) {
      w->pc.x -= 1;
      w->GV->move(w->GV->x() + 50, w->GV->y());
    }
    if (wall) {
      return;
    }
  }
  if (key == 68 && w->pc.x +1 < mapsize.x) { // RIGHT
    // TODO: add other TILE classes (door, entrance, ...)
    auto maybe_tile = map.get_tile(w->pc.x + 1, w->pc.y);
    assert(maybe_tile);
    Tile &tile = *maybe_tile;
    TileWall *wall = dynamic_cast<TileWall *>(&tile);
    TileEmpty *empty = dynamic_cast<TileEmpty *>(&tile);
    if (empty) {
      w->pc.x += 1;
      w->GV->move(w->GV->x() - 50, w->GV->y());
    }
    if (wall) {
      return;
    }
  }
  return;
}

void createMap(MainWindow *w) {
  // setup la plupart des utilitaires (Graphics view GV, la composante
  // principale de l'affichage des map Les scenes, qui sont les tableaux (les
  // differentes salles)

  QGraphicsView *GV = w->GV;
  GV->setGeometry(-50, -200, 6000, 2000);

  //  fillScene(w, 0, temp, Coordinates{50, 50});


  switchRoom(w, 0);
  GV->show();

  // character

  QLabel *a = w->createImageLabelFromPath(":/assets/images/Oscilloscope.webp",
                                          Size4{600, 575, 50, 50});
  a->show();

  // darkness

  DarkOverlay *overlay = new DarkOverlay(w);
  overlay->resize(1700, 1500);
  overlay->show();
  return;
}

void numberLockChange(MainWindow *w, int number) {
  const char a = char(number);
  w->text->setText(QString(a));
}

void displayLock4(MainWindow *w) {
  // image of the lock4
  QLabel *label = w->createImageLabelFromPath(":/assets/images/Lock4.jpg",
                                              Size4{100, 100, 100, 100});
  label->show();
  // number of the lock4

  w->text->setText("00");
  w->text->setGeometry(200, 200, 200, 200);
  QObject::connect(w, &MainWindow::hideHint, w, [w, label]() {
    w->text->hide();
    label->hide();
  });
}

void displayLockCirculaire(MainWindow *w) {
  // image of the circular lock
  QLabel *label = w->createImageLabelFromPath(":/assets/images/LockCirculaire.jpg",
                                              Size4{100, 100, 100, 100});
  label->show();
  // number of the circular lock

  w->text->setText("00");
  w->text->setGeometry(200, 200, 200, 200);
  QObject::connect(w, &MainWindow::hideHint, w, [w, label]() {
    w->text->hide();
    label->hide();
  });
}

void displayNumpad(MainWindow *w) {
  // image of the numpad
  QLabel *label = w->createImageLabelFromPath(":/assets/images/numpad.webp",
                                              Size4{100, 100, 100, 100});
  label->show();

  w->text->setGeometry(200, 200, 200, 200);
  QObject::connect(w, &MainWindow::hideHint, w, [w, label]() {
    w->text->hide();
    label->hide();
  });
}

void displayHint(MainWindow *w, QString s) {
  w->text->setText("00");
  QObject::connect(w, &MainWindow::hideHint, [w]() { w->text->hide(); });
}

void buttonPushed(QPushButton *p, MainWindow *w) {
  // Lorsque le bouton Start Game est actionne
  delete p;
  w->clearTitleScreen();
  createMap(w);
}

void muon() { return; }

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  Size4 size4;
  size4.x1 = 635;
  size4.y1 = 400;
  size4.x2 = 256;
  size4.y2 = 75;

  QPushButton* b = w.createPushButton(":/assets/images/StartGame001.png", size4);

  createScene(&w);

  Map niveau1("assets/map/Etage1.txt");


  QObject::connect(&w, &MainWindow::buttonClicked, [&niveau1](QPushButton* p, MainWindow* w){
      buttonPushed(p, w);
      fillScene2(w, niveau1, 0);
      w->GV->setScene(w->scenes[0]);
      w->GV->setGeometry(-50, -200, 6000, 2000);

      w->GV->show();
  });
  QObject::connect(&w, &MainWindow::keyPressed, [&niveau1](MainWindow* w, int key){
      move2(w, key, niveau1);
  });

  QObject::connect(&w, &MainWindow::startGame, [&b, &niveau1](MainWindow* w){
      if(b){
          buttonPushed(b, w);
          fillScene2(w, niveau1, 0);
          w->GV->setScene(w->scenes[0]);
          w->GV->setGeometry(-50, -200, 6000, 2000);

          w->GV->show();
      }

  });


  return a.exec();
}
