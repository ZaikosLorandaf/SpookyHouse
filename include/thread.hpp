#ifndef W_THREAD_HPP
#define W_THREAD_HPP

#include <QDebug>
#include <QObject>
#include <QThread>
#include <iostream>
#include <string>
// using namespace std;

/*-------------------------- Librairies externes ----------------------------*/
#include "SerialPort.hpp"
#include "json.hpp"
#include <vector>

using json = nlohmann::json;

/*------------------------------ Constantes ---------------------------------*/
#define BAUD 115200       // Frequence de transmission serielle
#define MSG_MAX_SIZE 1024 // Longueur maximale d'un message

/*------------------------- Prototypes de fonctions -------------------------*/
// bool SendToSerial(SerialPort *arduino, json j_msg);
// bool RcvFromSerial(SerialPort *arduino, std::string &msg);
// list<string> listeAction;

/*---------------------------- Variables globales ---------------------------*/

class W_thread : public QObject {
  Q_OBJECT
  bool running = true;

public:
  int bup = 0;
  SerialPort *arduino; // doit etre un objet global!
  bool SendToSerial(SerialPort *arduino, json j_msg) {
    // Return 0 if error
    std::string msg = j_msg.dump();
    bool ret = arduino->writeSerialPort(msg.c_str(), msg.length());
    return ret;
  }
  bool RcvFromSerial(SerialPort *arduino, std::string &msg) {
    // Return 0 if error
    // Message output in msg
    std::string str_buffer;
    char char_buffer[MSG_MAX_SIZE];
    int buffer_size;

    msg.clear(); // clear string
    // Read serialport until '\n' character (Blocking)

    // Version fonctionnel dans VScode, mais non fonctionnel avec Visual Studio
    do {
      if (msg.size() > MSG_MAX_SIZE) {
        return false;
      }

      buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
      str_buffer.assign(char_buffer, buffer_size);
      msg.append(str_buffer);
    } while (!msg.empty() && msg.back() != '}');

    // Version fonctionnelle dans VScode et Visual Studio
    // buffer_size = arduino->readSerialPort(char_buffer, MSG_MAX_SIZE);
    // str_buffer.assign(char_buffer, buffer_size);
    // msg.append(str_buffer);

    // msg.pop_back(); //remove '/n' from string

    return true;
  }
  W_thread();
signals:
  void muon();
  void bouton(int bouton);      // 0(haut), 1(droit), 2(bas), 3(gauche)
  void joystick(int direction); // 0(haut), 1(droit), 2(bas), 3(gauche).
                                // peut-etre ajouter diagonale mais pas live
  void potentiometre(int direction); // 0(antihoraire), 1(horaire)
  void numpad(QString car);
  void done(); // quand appli ferme
  void jumpscare();
  void accelerometrex(int a);
  void accelerometrey(int a);
  void accelerometrez(int a);
  void keypad(std::string a);


public slots:
  void stop() { running = false; }
  void doStuff();
  // les affaires qu'on envoie au arduino genre DEL par exemple
};

inline W_thread::W_thread() { return; }

inline void W_thread::doStuff() {
  std::string raw_msg;

  // Initialisation du port de communication
  std::string com;
  std::cout << "Entrer le port de communication du Arduino: ";
  // cin >> com;
  com = "com5";
  // com = "com5";
  std::cout << std::endl << "Using " << com << std::endl;
  arduino = new SerialPort(com.c_str(), BAUD);

  if (!arduino->isConnected()) {
    std::cerr << "Impossible de se connecter au port " << std::string(com)
              << ". Fermeture du programme!" << std::endl;
    // exit(1);
  }

  // Structure de donnees JSON pour envoie et reception
  int led_state = 1;
  json j_msg_send, j_msg_rcv;
  while (running) {

    // Envoie message Arduino
    j_msg_send["accelNeeded"] = 7;
    if (!SendToSerial(arduino, j_msg_send)) {
      // std::cerr << "Erreur lors de l'envoie du message. " << std::endl;
    } else {
      // cout << j_msg_send << endl;
    }
    // Reception message Arduino
    j_msg_rcv.clear(); // effacer le message precedent
    if (!RcvFromSerial(arduino, raw_msg)) {
      // std::cerr << "Erreur lors de la reception du message. " << std::endl;
    } else {
      // std::cout << raw_msg << std::endl;
    }

    // Impression du message de l'Arduino si valide + mis dans une liste
    if (raw_msg.size() > 0) {
      // BEGIN, FIND DOUBLE OUTPUT
      // CREATE ARRAY OF DUP
      std::vector<std::string> *duplicate = new std::vector<std::string>();

      // CREATE COUNTER
      int bracketsCounter = 0;
      int lastStartIndex = 0;

      // WHILE COUNTER STRICT POSITIVE
      for (int i = 0; i < raw_msg.size(); i++) {

        // INC COUNTER ON {
        if (raw_msg[i] == '{')
          bracketsCounter++;

        // DEC COUNTER ON }
        if (raw_msg[i] == '}')
          bracketsCounter--;

        // COUNTER == 0
        if (bracketsCounter == 0 && i != 0) {
          std::string current =
              raw_msg.substr(lastStartIndex, i - lastStartIndex + 1);
          duplicate->push_back(current);
          lastStartIndex = i + 1;
        }
      }
      // MSG END
      // IF SMTH REMAINS, REDO
      // END FIND DOUBLE OUTPUT
      // COUT ALL ARRAY ENTRIES ON ONE LINE EACH
      // BEGIN NEW PRINT

      for (std::string const &msg : *duplicate) {
        // cout << "raw_msg: " << msg << endl;  // debug
        // cout << "raw_msg: " << ((duplicate->size() > 1) ? "MORE THAN ONE" :
        // "")  << msg << endl;  // debug
        json jsonmsg;
        jsonmsg = json::parse(msg);
         //std::cout << jsonmsg << std::endl;
        //qDebug()<< jsonmsg;
        if (!jsonmsg["bUp"].is_null()) {
          int bUpVal = jsonmsg["bUp"];
          if (bUpVal == 1 && bup == 0) {
              bup = 1;
              emit bouton(1);
            // button up
          } else {
            // stop button up
          }
        }
        if (!jsonmsg["bDo"].is_null()) {
          int bDownVal = jsonmsg["bDo"];
          if (bDownVal == 1) {
              emit bouton(4);

            // button down
          } else {
            // stop button down
          }
        }
        if (!jsonmsg["bLe"].is_null()) {
          int bLeftVal = jsonmsg["bLe"];
          if (bLeftVal == 1) {
            // button left
              emit bouton(2);
          } else {
            // stop button left
          }
        }
        if (!jsonmsg["bRi"].is_null()) {
          int bRightVal = jsonmsg["bRi"];
          if (bRightVal == 1) {
            // button right
              emit bouton(3);
          } else {
            // stop button right
          }
        }
        if (!jsonmsg["joy"].is_null()) {
          int JoyVal = jsonmsg["joy"];
          if (JoyVal == 1) {
            emit joystick(0);
            // move up
          } else if (JoyVal == 2) {
            emit joystick(2);

            // move down
          } else if (JoyVal == 3) {
            emit joystick(1);

            // move right
          } else if (JoyVal == 4) {
            emit joystick(3);

            // move left
          } else {
            // stop mooving
          }
        }
        if (!jsonmsg["pot"].is_null()) {
          int potval = jsonmsg["pot"];
          // change potentiometer value
        }
        if (!jsonmsg["accX"].is_null()) {
          int accelXval = jsonmsg["accX"];
            if(accelXval == 1 || accelXval == 10){
                emit accelerometrex(accelXval);

            }          // change accelerometer X value
        }
        if (!jsonmsg["accY"].is_null()) {
          int accelYval = jsonmsg["accY"];

            if(accelYval == 1 || accelYval == 10){
                emit accelerometrey(accelYval);

            }
          // change accelerometer Y value
        }
        if (!jsonmsg["accZ"].is_null()) {
          int accelZval = jsonmsg["accZ"];
            if(accelZval == 1 || accelZval == 10){
              emit accelerometrez(accelZval);

            }

          // change accelerometer Z value
        }
        if (!jsonmsg["scream"].is_null()) {
          bool screamer = jsonmsg["scream"];
          if (screamer) {
              emit jumpscare();
          }
        }
        if (!jsonmsg["kpd"].is_null()) {
          std::string keypadval = jsonmsg["kpd"];
            // change keypad value
              emit keypad(keypadval);

        }
      }
      // END NEW PRINT

      // Transfert du message en json
    }

    // if (listeAction.size()<0)
    // {
    //     string action = "";
    //     action = listeAction.pop_front();
    //     /*  */
    // }

    // Changement de l'etat led

    // Sleep(20); // Why??

    //        qDebug() << "Second thread running";
    // emit muon();
    // emit bouton(0);
    // emit joystick(0);
    // emit potentiometre(0);
    // QString a = "hi\0";
    // emit numpad(a);

    QThread::msleep(5); // TODO: change this to like 5 or 1 later
  }
  emit done();
  return;
}

#endif // THREAD_HPP
