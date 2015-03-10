#include "Effect.h"
#include "BattleEngine.h"
#include "mainclass.h"

Effect::Effect(QRect geom, QList <QPixmap*>* frames, int speed, bool loop, QWidget* labelParent, void* eng) {
    loops = loop;
    animationFrames = frames;
    displayLabel = new QLabel();
    displayLabel->setScaledContents(true);
    displayLabel->setParent(labelParent);
    displayLabel->setGeometry(geom);
    displayLabel->setStyleSheet("background-image: url(null); background-color: rgba(255, 255, 255, 0);");
    animationTimer = new QTimer();
    animationSpeed = speed;
    currentFrame = 0 ;
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(refreshFrame()));
    finished = false;
    engine = eng;
    if(((MainClass*)(((BattleEngine*)(engine))->main))->sound) {
        sfx  = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource("/resource/sounds/explosion.mp3"));
        connect(sfx,SIGNAL(finished()),((BattleEngine*)(eng)),SLOT(cleanUpSFX()));
    }
}

void Effect::alignToAir() {
    displayLabel->setAlignment(Qt::AlignTop);
}

void Effect::alignToGround() {
    displayLabel->setAlignment(Qt::AlignBottom);
}

void Effect::playAnimation() {
    displayLabel->setPixmap(*(animationFrames->value(0)));
    displayLabel->show();
    animationTimer->start(animationSpeed);
    if(((BattleEngine*)(engine))->isInSession && ((MainClass*)(((BattleEngine*)(engine))->main))->sound)
        sfx->play();
}

void Effect::refreshFrame() {
    displayLabel->setPixmap(*(animationFrames->value(currentFrame)));
    displayLabel->repaint();
    currentFrame++;
    if(!loops) {
        if(currentFrame >= animationFrames->size()) {
            stopAnimation();
            finished = true;
            return;
        }
    }
    currentFrame%=animationFrames->size();
}

bool Effect::isFinished() {
    return finished;
}

void Effect::stopAnimation() {
    animationTimer->stop();
    currentFrame = 0;
    displayLabel->setVisible(false);
}

void Effect::freeze() {
    animationTimer->stop();
}

void Effect::unfreeze() {
    animationTimer->start(animationSpeed);
}

Effect::~Effect() {
    displayLabel->clear();
    delete displayLabel;
    delete animationTimer;
}
