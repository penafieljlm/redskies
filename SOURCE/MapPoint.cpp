#include "MapPoint.h"

MapPoint::MapPoint(int x, int y, QList<QIcon *> *butOnListImg, QLabel *nmLabel, QLabel *dscLabel, QLabel *prLabel, QWidget* parentWidget, QString image) {
    xCoord = x;
    yCoord = y;
    imagePath = image;
    iconAnim = butOnListImg;
    timer = new QTimer ();
    frameCounter = 0;
    nameLabel = nmLabel;
    descLabel = dscLabel;
    prevLabel = prLabel;
    if(!butOnListImg->isEmpty())
        setIcon(*(butOnListImg->value(0)));
    connect(this,SIGNAL(clicked()),this,SLOT(animate()));
    connect(timer,SIGNAL(timeout()),this,SLOT(animateFrame()));
    setParent(parentWidget);
    setGeometry(x-15,y-15,30,30);
    setIconSize(QSize(30,30));
    setStyleSheet("background-image: url(null); border-color: rgba(255, 255, 255, 0);\nbackground-color: rgba(255, 255, 255, 0);");
    setFocusPolicy(Qt::NoFocus);
}

MapPoint::~MapPoint() {
    delete timer;
}

int MapPoint::getX() {
    return xCoord;
}

int MapPoint::getY() {
    return yCoord;
}

void MapPoint::setX(int amt) {
    xCoord = amt;
}

void MapPoint::setY(int amt) {
    yCoord = amt;
}

void MapPoint::animateFrame() {

    switch(frameCounter) {
        case 0:
            setIcon(*(iconAnim->value(1)));
            break;
        case 1:
            setIcon(*(iconAnim->value(2)));
            break;
        case 2:
            setIcon(*(iconAnim->value(3)));
            break;
        case 3:
            setIcon(*(iconAnim->value(4)));
            break;
        case 4:
            setIcon(*(iconAnim->value(3)));
            break;
        case 5:
            setIcon(*(iconAnim->value(2)));
            break;
        default:
            break; //invalid case
    }

    frameCounter++;

    frameCounter%=6;
}

void MapPoint::animate() {
    emit selected();
    frameCounter = 0;
    nameLabel->setText(name);
    descLabel->setText(description);
    prevLabel->setPixmap(QPixmap(imagePath));
    prevLabel->setStyleSheet("background-color: rgba(0, 0, 0, 0); font: 4pt 'Calibri'; color: rgb(255, 170, 0);");
    timer->start(100);
    disconnect(this,SIGNAL(clicked()),this,SLOT(animate()));
    connect(this,SIGNAL(clicked()),this,SLOT(stopAnimate()));
}

void MapPoint::stopAnimate() {
    emit deselected();
    nameLabel->setText("");
    descLabel->setText("");
    timer->stop();
    prevLabel->setPixmap(QPixmap("null"));
    prevLabel->setStyleSheet("background-color: rgba(0, 0, 0, 200); font: 4pt 'Calibri'; color: rgb(255, 170, 0);");
    setIcon(*(iconAnim->value(0)));
    disconnect(this,SIGNAL(clicked()),this,SLOT(stopAnimate()));
    connect(this,SIGNAL(clicked()),this,SLOT(animate()));
}

QString MapPoint::getName() {
    return name;
}

QString MapPoint::getDesc() {
    return description;
}

void MapPoint::setName(QString nm) {
    name = nm;
}

void MapPoint::setDesc(QString desc) {
    description = desc;
}
