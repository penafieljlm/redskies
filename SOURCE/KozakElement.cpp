#include "KozakElement.h"

KozakElement::KozakElement(QWidget *parent, QList<QPixmap *> *walkList) {
    setParent(parent);
    animList = walkList;
    animTimer = new QTimer();
    parentWidget = parent;
    connect(animTimer,SIGNAL(timeout()),this,SLOT(scroll()));
    frameCounter = 0;
    setStyleSheet("background-image: url(null); background-color: rgba(255, 255, 255, 0);");
    scale = randomNum(80,224);
    frameTimer = new QTimer();
    connect(frameTimer,SIGNAL(timeout()),this,SLOT(animate()));
}

void KozakElement::startScroll() {
    setGeometry(-224,randomNum(-100,parentWidget->height()),224,178);
    setVisible(true);
    int time = ((224/(float)scale) * 10.0);

    animTimer->start(time);
    frameTimer->start(100);
    emit start();
}

void KozakElement::animate() {
    setPixmap((*(animList->value(frameCounter))).scaledToWidth(scale));
    frameCounter++;
    frameCounter%=animList->size();
}

void KozakElement::scroll() {
    move(this->x()+1,this->y());

    if(this->x() > parentWidget->width())
        endScroll();
}

void KozakElement::endScroll() {
    animTimer->stop();
    frameTimer->stop();
    emit end();
}

int KozakElement::randomNum(int low, int hi) {
    return qrand() % ((hi + 1) - low) + low;
}

KozakElement::~KozakElement() {
    //qDebug("DELETE!");
    this->clear();
    delete animTimer;
    delete frameTimer;
}


