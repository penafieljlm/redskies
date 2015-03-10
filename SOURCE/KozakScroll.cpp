#include "KozakScroll.h"

KozakScroll::KozakScroll(QWidget *applyTo) {
    target = applyTo;
    spawnTimer = new QTimer();
    connect(spawnTimer,SIGNAL(timeout()),this,SLOT(createKozak()));
    walkList = new QList <QPixmap*> ();
    walkList->append(new QPixmap("\\resource\\Red\\Aircraft\\AT\\lv3\\walk\\1.png"));
    walkList->append(new QPixmap("\\resource\\Red\\Aircraft\\AT\\lv3\\walk\\2.png"));
    walkList->append(new QPixmap("\\resource\\Red\\Aircraft\\AT\\lv3\\walk\\3.png"));
    walkList->append(new QPixmap("\\resource\\Red\\Aircraft\\AT\\lv3\\walk\\4.png"));
    kozakList = new QList <KozakElement*> ();
}

void KozakScroll::startScroll() {
    spawnTimer->start(6000);
}

void KozakScroll::stopScroll() {
    spawnTimer->stop();
    for(int i = 0 ; i < kozakList->size() ; i++) {
        kozakList->value(i)->endScroll();
    }
    kozakList->clear();
}

void KozakScroll::createKozak() {
    KozakElement* newKozak = new KozakElement(target,walkList);
    kozakList->append(newKozak);
    connect(newKozak,SIGNAL(end()),this,SLOT(cleanKozak()));
    newKozak->startScroll();
}

void KozakScroll::cleanKozak() {
    KozakElement* sender = ((KozakElement*)(QObject::sender()));
    for(int i = 0 ; i < kozakList->size() ; i++) {
        if(kozakList->value(i) == sender) {
            delete kozakList->value(i);
            kozakList->removeAt(i);
            break;
        }
    }
}

KozakScroll::~KozakScroll() {
    stopScroll();
    for(int i = 0 ; i < walkList->size() ; i++) {
        delete walkList->value(i);
    }
    walkList->clear();
    delete walkList;
    kozakList->clear();
    delete kozakList;
}
