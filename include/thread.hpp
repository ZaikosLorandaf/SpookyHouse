#ifndef W_THREAD_HPP
#define W_THREAD_HPP

#include <QObject>
#include <QThread>
#include <QDebug>

class W_thread : public QObject{
    Q_OBJECT
    bool running = true;
public:
    W_thread();
signals:
    void muon();
    void bouton(int bouton); //0(haut), 1(droit), 2(bas), 3(gauche)
    void joystick(int direction); //0(haut), 1(droit), 2(bas), 3(gauche). peut-etre ajouter diagonale mais pas live
    void potentiometre(int direction); //0(antihoraire), 1(horaire)
    void numpad(QString car);
    void done(); //quand appli ferme
    void jumpscare();
public slots:
    void stop(){
        running = false;
    }
    void doStuff();
    // les affaires qu'on envoie au arduino genre DEL par exemple
};

inline W_thread::W_thread(){
    return;
}

inline void W_thread::doStuff(){
    while(running){
//        qDebug() << "Second thread running";
        emit muon();
        emit bouton(0);
        emit joystick(0);
        emit potentiometre(0);
        QString a = "hi\0";
        emit numpad(a);

        QThread::msleep(5000); //TODO: change this to like 5 or 1 later
    }
    emit done();
    return;
}

#endif // THREAD_HPP
