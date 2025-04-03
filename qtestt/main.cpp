#include "mainwindow.h"
#include "Coordinates.h"

#include <QApplication>
#include <conio.h>

const char* temp[] = {
    "####       ###########################################################################################################",
    "####                                                                 #                                               #",
    "####                                                                 #                                               #",
    "####                                                                 |                                               #",
    "####                                                                 #                                               #",
    "####                                                                 #                                               #",
    "####                                                                 #                                               #",
    "####                                                                 #                                               #",
    "####                                                                 #                                               #",
    "####                                                                 #                                               #",
    "####                                                                 #                      !                        #",
    "####                                                                 #                    #####                      #",
    "####                                                                 #                    #####                      #",
    "####                                                                 #                                               #",
    "####                                                                 #################################################",
    "####                                                                 #################################################",
    "####                                                                 #################################################",
    "####                                                                 #################################################",
    "####                                                                X#################################################",
    "####                                                                 #################################################",
    "######################################################################################################################"};

//je pense qu'on peut juste utiliser genre un qframe ou qqchose du genre
class DarkOverlay : public QWidget {
public:
    DarkOverlay(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
        setStyleSheet("background: rgba(0, 0, 0, 200);");
    }
};

void createScene(MainWindow* w){
    //Creer une scene et l'ajouter au vecteur scenes. Elles sont arrangees de 0 au nombre de piece total
    //Elles n'ont pas de nom, juste un chiffre, donc on devra genre etablir quelle numero correspond a
    //quelle piece.
    QGraphicsScene* s = new QGraphicsScene(w->GV);
    w->scenes.push_back(s);
}

QGraphicsPixmapItem* createPixmap(const char* path, Coordinates size){
    //Creer une QGraphicsPixmapItem pour afficher dans les scenes
    QPixmap* p = new QPixmap(path);
    QPixmap s = p->scaled(size.x, size.y);
    QGraphicsPixmapItem* q = new QGraphicsPixmapItem(s);
    delete p;
    return q;
}

//TODO: char is temporary. need to add parser compatibility
void fillScene(MainWindow* w, int roomNumber, const char* t[], Coordinates imagesize){
    //Remplir une scene d'images, labels, whatever you need.
    if (!w->scenes[roomNumber]){
        qWarning() << "Room isn't." << roomNumber;
        return;
    }
    size_t x = strlen(t[0]);
    int y = 21;
    for (int i=0; i<y; i++){
        for(int j=0; j<x; j++){
            //todo: check for walls, floors, etc. and execute in separate thread (ideally.)
            if (t[i][j] == '#'){
                const char* path = ":/assets/images/wall.png";
                QGraphicsPixmapItem* q = createPixmap(path, imagesize);
                w->scenes[roomNumber]->addItem(q);
                q->setPos(j*imagesize.x,i*imagesize.y);
            }
            if (t[i][j] == ' '){
                int rand = std::rand() % 3;
                if (rand == 0){
                    const char* path = ":/assets/images/floor1.png";
                    QGraphicsPixmapItem* q = createPixmap(path, imagesize);
                    w->scenes[roomNumber]->addItem(q);
                    q->setPos(j*imagesize.x,i*imagesize.y);
                }else if (rand == 1){
                    const char* path = ":/assets/images/floor2.png";
                    QGraphicsPixmapItem* q = createPixmap(path, imagesize);
                    w->scenes[roomNumber]->addItem(q);
                    q->setPos(j*imagesize.x,i*imagesize.y);
                }else {
                    const char* path = ":/assets/images/floor3.png";
                    QGraphicsPixmapItem* q = createPixmap(path, imagesize);
                    w->scenes[roomNumber]->addItem(q);
                    q->setPos(j*imagesize.x,i*imagesize.y);
                }
            }
        }
    }
}

void switchRoom(MainWindow* w, int roomNumber){
    //Changement de salle -> changement de scene
    if (w->scenes.size()>roomNumber){
        w->GV->setScene(w->scenes[roomNumber]);
    }
    else{
        qWarning() << "Room doesn't exist!";
    }
    return;
}



void move(MainWindow* w, int key) {
//Lorsqu'on recoit un user input. Peut-etre meme pas un mouvement mais une interaction.

//Tests.
//    qDebug() << "posx" << w->pc.x;
//    qDebug() << "posy" << w->pc.y;
//    qDebug() << key;
    /*
     * W: 87
     * A: 65
     * S: 83
     * D: 68
     * Q: 81
     */
//qDebug() << (w->pc.x + 1 >=0) << (w->pc.x + 1 < 121) << (temp[w->pc.x+1][w->pc.y] != '#');

//qDebug() << w->pc.x << "  " << w->pc.y;
//qDebug() <<( w->pc.y - 1 >= 0) << (temp[int(w->pc.x)][int(w->pc.y -1)] != '#');
//qDebug() << temp[int(w->pc.y -1)][int(w->pc.x)];
    switch (key){
    case 87:
        if (w->pc.y - 1 >=0 && temp[int(w->pc.y -1)][int(w->pc.x)] != '#'){
            w->pc.y -= 1;
            w->GV->move(w->GV->x(), w->GV->y()+50);
        }

        break;
    case 83:
        if (w->pc.y + 1 >=0 && w->pc.y + 1 < 21 && temp[int(w->pc.y +1)][int(w->pc.x)] != '#'){
            w->pc.y += 1;
            w->GV->move(w->GV->x(), w->GV->y()-50);
        }

        break;
    case 65:
        if (w->pc.x - 1 >=0 && temp[int(w->pc.y)][int(w->pc.x-1)] != '#'){
            w->pc.x -= 1;
            w->GV->move(w->GV->x()+50, w->GV->y());
        }

        break;
    case 68:
        if (w->pc.x + 1 >=0 && w->pc.x + 1 < 121 && temp[int(w->pc.y)][int(w->pc.x+1)] != '#'){
            w->pc.x += 1;
            w->GV->move(w->GV->x()-50, w->GV->y());
        }

        break;
    case 81:
        return;
    }

//    updateGUI(w, w->pc);

    return;
}

void createMap(MainWindow *w){
    //setup la plupart des utilitaires (Graphics view GV, la composante principale de l'affichage des map
    //Les scenes, qui sont les tableaux (les differentes salles)

    QGraphicsView* GV = w->GV;
    GV->setGeometry(-50, -200, 6000, 2000);
    createScene(w);
    fillScene(w, 0, temp, Coordinates {50, 50});
    switchRoom(w, 0);
    GV->show();

    //character

    QLabel* a = w->createImageLabelFromPath(":assets/images/rat.png", Size4 {600, 575, 50, 50});
    a->show();

    //darkness

    DarkOverlay *overlay = new DarkOverlay(w);
    overlay->resize(1700, 1500);
    overlay->show();
    return;
}

void buttonPushed(QPushButton *p, MainWindow *w){
    //Lorsque le bouton Start Game est actionne
    delete p;
    w->clearTitleScreen();
    createMap(w);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Size4 size4;
    size4.x1 = 635;
    size4.y1 = 400;
    size4.x2 = 256;
    size4.y2 = 75;

    w.createPushButton(":/assets/images/StartGame001.png", size4);

    QObject::connect(&w, &MainWindow::buttonClicked, buttonPushed);
    QObject::connect(&w, &MainWindow::keyPressed, move);

    return a.exec();
}
