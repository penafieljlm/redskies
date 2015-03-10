#include "mainclass.h"
#include "ui_mainclass.h"
#include <QtCore/QCoreApplication>
#include "Unit.h"

Unit::Unit(bool flying, bool red, int dmg, int hp, int spd, int rng, int rld, int wid, int ht, int rfrsh, QString atk, QString def, void *eng, Ui::MainClass *u, int lv) {
    frozen = false;
    consciousness = new QTimer ();
    ui = u;
    level = lv;
    engine = eng;

    width = wid;
    height = ht;

    frameDelay = rfrsh;

    isFlying = flying;
    isRed = red;
    hitpoints = hp;
    speed = spd;
    attackRange = rng;
    damage = dmg;

    reloadLimit = rld;
    reloadGague = rld;
    isLoaded = true;
    isAttacking = false;

    walkFrameIndex = 0;
    steadyFrameIndex = 0;
    attackFrameIndex = 0;
    stance = 0;

    frameTimer = new QTimer ();
    moveTimer = new QTimer ();

    displayLabel = new QLabel(ui->battleField);
    displayLabel->setStyleSheet("background-image: url(null); background-color: rgba(255, 255, 255, 0);");

    attackType = atk;
    defenseType = def;

    if (isFlying) {
        displayLabel->setAlignment(Qt::AlignTop);
        yCoord = 0;
        defenseType = "Air";
    }
    else {
        displayLabel->setAlignment(Qt::AlignBottom);
        yCoord = ui->battleField->geometry().height() - this->height + 2;
    }

    displayLabel->setScaledContents(true);

    if(isRed)
        xCoord = 0 - this->width;
    else
        xCoord = ui->battleField->geometry().width() + this->width;

    position = (xCoord + width)/2;

    displayLabel->setGeometry(xCoord,yCoord,width,height);
    gun = NULL;
    if(((MainClass*)(((BattleEngine*)(engine))->main))->sound) {
        if(atk.contains("AI")) {
            if(def.contains("Infantry")) {
                gun  = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource("/resource/sounds/machinegun.mp3"));
            }
            else {
                if(level < 3)
                    gun  = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource("/resource/sounds/machinegun.mp3"));
            }
        }
        if(gun != NULL)
            connect(gun,SIGNAL(finished()),this,SLOT(stopSound()));
    }
}

void Unit::buildSpriteBase(QList<QPixmap *> *walk, QList<QPixmap *> *attack, QList<QPixmap *> *steady) {
    walkSprite = walk;
    attackSprite = attack;
    steadySprite = steady;
}

void Unit::wakeUnit() {

    displayLabel->show();
    currentSprite = walkSprite->value(0);
    displayLabel->setPixmap(*currentSprite);

    connect(frameTimer,SIGNAL(timeout()),this,SLOT(refreshFrame()));
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(consciousness,SIGNAL(timeout()),this,SLOT(brain()));

    frameTimer->start(frameDelay);
    moveTimer->start(500/speed);
    consciousness->start(1000);
}

void Unit::brain() {
    if(((BattleEngine*)engine)->anyAttackableEnemyUnitsInRange(this)) {
        QList <Unit*>* attackableSet = ((BattleEngine*)engine)->getAttackableEnemyUnits(this);
        Unit* target = ((BattleEngine*)engine)->getNearestEnemyUnitFromSet(this,attackableSet);
        attackableSet->clear();
        delete attackableSet;

        if(moveTimer->isActive())
            moveTimer->stop();

        if(isLoaded)
            attack(target);
        else if(stance != 2)
            stand(); //set stance to steady
    }
    else {
        if(!moveTimer->isActive()) {
            stance = 0;
            walkFrameIndex = 0;
            moveTimer->start(500/speed);
        }
    }
    reloadGague++;
    if (reloadGague >= reloadLimit)
        isLoaded = true;
}

void Unit::takeDamage(int amount) {
    hitpoints -= amount;
}

void Unit::move() { //Displaces the unit
    stance = 0;
    if(isRed)
        xCoord++;
    else
        xCoord--;
    displayLabel->move(xCoord,yCoord);
    position = (xCoord + width)/2;
}

void Unit::stopSound() {
    Phonon::MediaObject* snd = (Phonon::MediaObject*)(QObject::sender());
    snd->stop();
}

void Unit::attack(Unit* target) {
    //qDebug(QString::number((int)this).append(" - STOP").toAscii());

    if(gun!=NULL && ((MainClass*)(((BattleEngine*)(engine))->main))->sound) {
        if(gun->state() != Phonon::PlayingState)
            gun->play();
    }

    consciousness->stop();
    reloadGague = 0;
    isLoaded = false;

    attackFrameIndex = 0;

    crosshair = target;
    stance = 1;

}

void Unit::stand() {
    steadyFrameIndex = 0;
    stance = 2;
}

void Unit::refreshFrame() { //Sets the sprite appropriate for the current stance
    switch(stance) {
        case 0:
            currentSprite = walkSprite->value(walkFrameIndex);
            walkFrameIndex++;
            walkFrameIndex %= walkSprite->size();
            break;
        case 1:
            currentSprite = attackSprite->value(attackFrameIndex);
            attackFrameIndex++;
            attackFrameIndex %= attackSprite->size();

            if(!(((BattleEngine*)engine)->searchForUnit(crosshair,isRed)))
                return;

            if(attackFrameIndex >= attackSprite->size() - 1) {
                if(!getAttackType().compare("AA")) {
                    ((BattleEngine*)engine)->createCombatEffect((crosshair->xCoord + crosshair->displayLabel->width()/2),false,ui->battleField);
                }
                else if(!getAttackType().compare("AT")) {
                    ((BattleEngine*)engine)->createCombatEffect((crosshair->xCoord + crosshair->displayLabel->width()/2),true,ui->battleField);
                }
                crosshair->takeDamage(damage);
                crosshair = NULL;
                //qDebug(QString::number((int)this).append(" - START").toAscii());
                consciousness->start(5);
            }
            break;
        case 2:
            currentSprite = steadySprite->value(steadyFrameIndex);
            steadyFrameIndex++;
            steadyFrameIndex %= steadySprite->size();
            break;
        default:
            //do nothing;
            break;
    }
    displayLabel->setPixmap(*currentSprite);
}

void Unit::setFrameRate(int arg) { //Sets the frame rate
    frameDelay = arg;
    frameTimer->setInterval(frameDelay);
}

void Unit::setSpeed(int arg) { //Sets speed in which unit will travel
    speed = arg;
    moveTimer->setInterval(arg);
}

QString Unit::getAttackType() {
    return attackType;
}

QString Unit::getDefenseType() {
    return defenseType;
}

bool Unit::getFaction() {
    return isRed;
}

int Unit::getPosition() {
    return position;
}

int Unit::getAttackRange() {
    return attackRange;
}

int Unit::getHP(){
    return hitpoints;
}

void Unit::freeze() {
    if(consciousness->isActive())
        consciousness->stop();

    if(moveTimer->isActive())
        moveTimer->stop();

    if(frameTimer->isActive())
        frameTimer->stop();
}

void Unit::unfreeze() {
    if(!consciousness->isActive())
        consciousness->start(5);

    if(!moveTimer->isActive())
        moveTimer->start(500/speed);

    if(!frameTimer->isActive())
        frameTimer->start(frameDelay);
}

void Unit::increaseAttack(int amt) {
    damage += amt;
}

Unit::~Unit()
{
    ((BattleEngine*)engine)->createCombatEffect(xCoord + (width/2),!isFlying,ui->battleField);
    displayLabel->clear();
    delete displayLabel;
    delete frameTimer;
    delete moveTimer;
    delete consciousness;
    if(gun!=NULL) {
        gun->stop();
        delete gun;
    }
}

