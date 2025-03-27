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
    "####                                                                 #                                               #",
    "####                 #                                               #                    #!###                      #",
    "####                                                                 #                    #####                      #",
    "####                                                                 #                                               #",
    "####                                                                 #################################################",
    "####                                                                 #                                                ",
    "####                                                                 #                                                ",
    "####                                                                 #                                                ",
    "####     #                                                           X1                                               ",
    "####                                                                 #                                                ",
    "######################################################################                                                "};

void updateGUI(MainWindow* w, Coordinates pc){
    //TODO: cette fonction a VRAIMENT besoin d'optimisation.
    //range to start loading images
    int range = 10;


    //getting a list of all labels
    std::vector<QLabel*> labelList;
    QObjectList l = w->children();
    for (QObject* c : l){
        if (qobject_cast<QLabel*>(c)) {
            labelList.push_back(qobject_cast<QLabel*>(c));
        }
    }


    //unloading images further than %unload tiles away
    //TODO: i made this delete every image because i messed
    //up and the loading images part would duplicate images
    //which is bad.

    //range to start unloading images
//    int unload = 12;
    if (!labelList.empty()){
        for (int k=0; k<labelList.size(); k++){
//            if (abs(labelList[k]->x() - pc.x) > unload || abs(labelList[k]->y() - pc.y) > unload){
                delete(labelList[k]);
//            }
        }
    }
    labelList.erase(std::remove(labelList.begin(), labelList.end(), nullptr), labelList.end());

    //defines what a wall '#' looks like
    const char* path = ":/assets/images/cat.png";

    Size2 tailleMur;
    tailleMur.x = 33;
    tailleMur.y = 33;

    //loading images less than %range tiles away, centered on the player
    for (int i= -range; i<range; i++){
        for (int j=-range; j<range; j++){
            if (i+pc.y>0 && j+pc.x>0 && j+pc.x<118 && i+pc.y<21 && temp[i+pc.y][j+pc.x] == '#'){

                Coordinates c;
                c.y = (i+9)*tailleMur.y;
                c.x = (j+12)*tailleMur.x;

                QLabel* image = w->createImageLabelFromPath(path, tailleMur, c);
                image->show();

            }
        }
    }

    //display character
    Coordinates c2;
    c2.x = 12*tailleMur.x;
    c2.y = 8*tailleMur.y;
    QLabel* image = w->createImageLabelFromPath(":/assets/images/lowtiergod.jpg", tailleMur, c2);
    image->show();
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


    switch (key){
    case 87:
        if (w->pc.y - 1 >=0 && temp[w->pc.x][w->pc.y -1] != '#'){
            w->pc.y -= 1;
        }
//        w->q->move(w->q->x(),w->q->y()+10);
        break;
    case 83:
        if (w->pc.y + 1 >=0 && w->pc.y + 1 < 21 && temp[w->pc.x][w->pc.y +1] != '#'){
            w->pc.y += 1;
        }
//        w->q->move(w->q->x(),w->q->y()-10);
        break;
    case 65:
        if (w->pc.x - 1 >=0 && temp[w->pc.x-1][w->pc.y] != '#'){
            w->pc.x -= 1;
        }
        break;
    case 68:
        if (w->pc.x + 1 >=0 && w->pc.x + 1 < 121 && temp[w->pc.x+1][w->pc.y] != '#'){
            w->pc.x += 1;
        }
        break;
    case 81:
        return;
    }

    updateGUI(w, w->pc);

    return;
}

void createMap(MainWindow *w){
    move(w, -1);
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

    Coordinates coord;
    coord.x = 250;
    coord.y = 200;

    Size2 size;
    size.x = 256;
    size.y = 75;

    w.createPushButton(":/assets/images/StartGame001.png", size, coord);

    QObject::connect(&w, &MainWindow::buttonClicked, buttonPushed);
    QObject::connect(&w, &MainWindow::keyPressed, move);

    return a.exec();
}
