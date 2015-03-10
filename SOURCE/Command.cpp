#include "Command.h"
#include "BattleEngine.h"

Command::Command(QIcon *on, QIcon *off, QString nm, QString desc, QString tp, void *batEng, void *parent) {
    ready = true;
    countdownTimer = new QTimer();
    connect(countdownTimer,SIGNAL(timeout()),this,SLOT(decCountdown()));
    countdown = 0;
    countdownMAX = 300;
    tech = 0;
    cost = 0;
    onImage = on;
    offImage = off;
    name = nm;
    description = desc;
    type = tp;
    engine = batEng;
    setIcon(*off);
    setGeometry(0,0,25,25);
    setVisible(false);
    interfaceConnect();
    parentBuilding = parent;
    setStyleSheet("background-image: url(null); border-color: rgba(255, 255, 255, 0);\nbackground-color: rgba(255, 255, 255, 0);");
    setIconSize(QSize(50,50));
    setFocusPolicy(Qt::NoFocus);
}

void Command::executeCountdown() {
    ready = false;
    countdown = countdownMAX;
    countdownTimer->start(1);
}

bool Command::isReady() {
    return ready;
}

void Command::decCountdown() {
    if(countdown <= 0) {
        countdown = 0;
        countdownTimer->stop();
        ready = true;
    }
    else
        countdown--;
}

int Command::getCountdown() {
    return countdown;
}

void Command::setCountdownMAX(int amt) {
    countdownMAX = amt;
}

void Command::setTechReq(int amt) {
    tech = amt;
}

int Command::getTechReq() {
    return tech;
}

void Command::setCostReq(int amt) {
    cost = amt;
}

int Command::getCostReq() {
    return cost;
}

void Command::emitExecute() {
    emit execute();
}

void* Command::getParentBuilding() {
    return parentBuilding;
}

void Command::moveToEndPoint() {
    move(*endPoint);
}

void Command::setPoints(QPoint* start, QPoint* end) {
    startPoint = start;
    endPoint = end;
}

QString Command::getType() {
    return type;
}

void Command::interfaceConnect(){
    ((BattleEngine*)engine)->connectToInterface(this);
}

QString Command::getDesc() {
    return description;
}

QString Command::getName() {
    return name;
}

QIcon* Command::getOnImage() {
    return onImage;
}

QIcon* Command::getOffImage() {
    return offImage;
}

void Command::freeze() {
    countdownTimer->stop();
}

void Command::unfreeze() {
    countdownTimer->start(1);
}

Command::~Command() {
    delete countdownTimer;
}
