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
    "####                                                                 #                    #!###                      #",
    "####                                                                 #                    #####                      #",
    "####                                                                 #                                               #",
    "####                                                                 #################################################",
    "####                                                                 #                                                ",
    "####                                                                 #                                                ",
    "####                                                                 #                                                ",
    "####                                                                 X1                                               ",
    "####                                                                 #                                                ",
    "######################################################################                                                "};

void updateGUI(MainWindow* w, Coordinates pc){
    //range to start loading images
    int range = 10;
    //range to start unloading images
    int unload = 12;
    //getting a list of all labels
    std::vector<QLabel*> labelList;
    QObjectList l = w->children();
    for (QObject* c : l){
        if (qobject_cast<QLabel*>(c)) {
            labelList.push_back(qobject_cast<QLabel*>(c));
        }
    }
    //unloading images further than %unload tiles away
    if (!labelList.empty()){
        for (int k=0; k<labelList.size(); k++){
            if (labelList[k]->x() - pc.x > unload || labelList[k]->y() - pc.y > unload){
                delete(labelList[k]);
            }
        }
    }
    //defines what a wall '#' looks like
    const char* path = ":/assets/images/cat.png";
    Size2 tailleMur;
    tailleMur.x = 25;
    tailleMur.y = 25;

    //loading images less than %range tiles away
    for (int i= -range; i<range; i++){
        for (int j=-range; j<range; j++){
            if (i+pc.y>0 && j+pc.x>0 && j+pc.x<118 && i+pc.y<21){
                if (temp[i+pc.y][j+pc.x] == '#'){
                    Coordinates c;
                    c.y = (i+pc.y)*tailleMur.x;
                    c.x = (j+pc.x)*tailleMur.y;
                    QLabel* image = w->createImageLabelFromPath(path, tailleMur, c);
                    image->show();
                }
            }
        }
    }
}

void move(MainWindow* w, int key) {


    qDebug() << "Key pressed:" << w->pc.x;
    qDebug() << "Key pressed:" << w->pc.y;
    /*
     * W: 87
     * A: 65
     * S: 83
     * D: 68
     * Q: 81
     */


    switch (key){
    case 87:
        if (w->pc.y -= 1 >=0 && temp[w->pc.x][w->pc.y -=1] != '#'){
            w->pc.y -= 1;

        }
        break;
    case 83:
        if (w->pc.y += 1 >=0 && temp[w->pc.x][w->pc.y +=1] != '#'){
            w->pc.y += 1;

        }
        break;
    case 65:
        if (w->pc.x -= 1 >=0 && temp[w->pc.x-=1][w->pc.y] != '#'){
            w->pc.x -= 1;

        }
        break;
    case 68:
        if (w->pc.x += 1 >=0 && temp[w->pc.x+=1][w->pc.y] != '#'){
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


//    Size2 tempSize;
//    tempSize.x = 118;
//    tempSize.y = 21;
//
//    const char* path = ":/assets/images/cat.png";
//    Size2 tailleMur;
//    tailleMur.x = 25;
//    tailleMur.y = 25;
//
//    QLabel* map[118*21];
//    for (int i=0; i<tempSize.y; i++)
//        for (int j=0; j<tempSize.x; j++){
//            if (temp[i][j] == '#'){
//                Coordinates c;
//                c.y = i*tailleMur.x;
//                c.x = j*tailleMur.y;
//                QLabel* image = w->createImageLabelFromPath(path, tailleMur, c);
//                map[i*tempSize.x+j] = image;
//                image->show();
//            }
//
//        }
//
    move(w, -1);
    return;
}

void buttonPushedImageCat(QPushButton *p, MainWindow *w){
    delete p;
    w->clearTitleScreen();
    createMap(w);
    //test pour vérifier le fonctionnement du buton. spoiler: il marche.
//    const char* path2 = ":/assets/images/rat.png";
//    QDialog *dialog = new QDialog(w);
//    dialog->setWindowTitle(" ");
//
//   QLabel *label = new QLabel(dialog);
//    QPixmap pixmap(path2);
//    label->setPixmap(pixmap);
//    label->setScaledContents(true);
//
//    QVBoxLayout *layout = new QVBoxLayout(dialog);
//    layout->addWidget(label);
//    dialog->setLayout(layout);
//
//    dialog->setFixedSize(pixmap.size());
//    dialog->exec();

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

    Coordinates pc;
    pc.x = 5;
    pc.y = 0;

    w.createPushButton(":/assets/images/StartGame001.png", size, coord);

    QObject::connect(&w, &MainWindow::buttonClicked, buttonPushedImageCat);
    QObject::connect(&w, &MainWindow::keyPressed, move);

    return a.exec();
}
