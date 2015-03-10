#include "BattleEngine.h"
#include <QScrollBar>
#include "mainclass.h"

BattleEngine::BattleEngine(Ui::MainClass* u,void* m) {
    isInSession = false;
    playerType = 'm';
    enemyDiff = 'e';
    aiType = 'm';

    main = m;

    redLaser = NULL;
    blueLaser = NULL;
    redLaserTimer = NULL;
    blueLaserTimer = NULL;

    AI = NULL;
    latestUnit = NULL;
    ui = u;
    highlightedCmd = NULL;
    playerIsRed = true;
    //Initialize amount of money produced by an economic center at level i+1
    for(int i = 0 ; i < 6 ; i++){
        if(i <= 0)
            ecoProd[i] = 15;
        else
            ecoProd[i] = ecoProd[i-1] * 2;
    }

    //Initialize amount of technology produced by a tech center at level i+1
    for(int i = 0 ; i < 3; i++) {
        if(i <= 0)
            techProd[i] = 15;
        else
            techProd[i] = techProd[i-1] * 3;

    }

    cleaner = new QTimer();
    resourceRound = new QTimer();
    selectButtonAnimator = new QTimer();

    connect(ui->pauseButton,SIGNAL(pressed()),this,SLOT(buttonLightup()));
    connect(ui->pauseButton,SIGNAL(released()),this,SLOT(buttonLightdown()));
    connect(ui->pauseButton,SIGNAL(clicked()),this,SLOT(pauseGame()));

    connect(ui->resumeGame,SIGNAL(pressed()),this,SLOT(buttonLightup()));
    connect(ui->resumeGame,SIGNAL(released()),this,SLOT(buttonLightdown()));
    connect(ui->resumeGame,SIGNAL(clicked()),this,SLOT(resumeGame()));

    connect(ui->restartGame,SIGNAL(pressed()),this,SLOT(buttonLightup()));
    connect(ui->restartGame,SIGNAL(released()),this,SLOT(buttonLightdown()));
    connect(ui->restartGame,SIGNAL(clicked()),this,SLOT(restartGame()));

    connect(ui->quitGame,SIGNAL(pressed()),this,SLOT(buttonLightup()));
    connect(ui->quitGame,SIGNAL(released()),this,SLOT(buttonLightdown()));
    connect(ui->quitGame,SIGNAL(clicked()),this,SLOT(quitGame()));

    connect(ui->redSel1,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel2,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel3,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel4,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel5,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel6,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel7,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->redSel8,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel1,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel2,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel3,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel4,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel5,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel6,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel7,SIGNAL(clicked()),this,SLOT(engageSelectButton()));
    connect(ui->blueSel8,SIGNAL(clicked()),this,SLOT(engageSelectButton()));

    connect(ui->cmd4,SIGNAL(clicked()),this,SLOT(commandInterface()));

    connect(selectButtonAnimator,SIGNAL(timeout()),this,SLOT(animateHighlighted()));
    connect(cleaner,SIGNAL(timeout()),this,SLOT(cleanUp()));
    connect(resourceRound,SIGNAL(timeout()),this,SLOT(economyRound()));
    connect(resourceRound,SIGNAL(timeout()),this,SLOT(technologyRound()));
    highlighted = NULL;
}

void BattleEngine::engageSelectButton() {
    QPushButton* btn = (QPushButton *)(QObject::sender());
    QString displayText;
    if(highlighted != btn) {
        disengageSelectButton();
        highlighted = btn;
        animationIndex = 0;

        selectButtonAnimator->start(100);

        for(int i = 0 ; i < 8 ; i++) {
            if(redBlg[i] != NULL) {
                if(redBlg[i]->getDiplayButton() == btn) {
                    redBlg[i]->select();
                    displayText = redBlg[i]->getName();
                    displayText.append("\nHitpoints: ").append(QString::number(redBlg[i]->getHitpoints())).append("/").append(QString::number(redBlg[i]->getHpMAX())).append("\n");
                    displayText.append(redBlg[i]->getDesc());
                    ui->cmdLabel->setText(displayText);
                    break;
                }
            }
            if (blueBlg[i] != NULL) {
                if (blueBlg[i]->getDiplayButton() == btn) {
                    blueBlg[i]->select();
                    displayText = blueBlg[i]->getName();
                    displayText.append("\nHitpoints: ").append(QString::number(blueBlg[i]->getHitpoints())).append("/").append(QString::number(blueBlg[i]->getHpMAX())).append("\n");
                    displayText.append(blueBlg[i]->getDesc());
                    ui->cmdLabel->setText(displayText);
                    break;
                }
            }
        }

    }
    else
        disengageSelectButton();
}

void BattleEngine::disengageSelectButton() {
    selectButtonAnimator->stop();
    if(highlighted != NULL) {
        highlighted->setIcon(*(iconAnim->value(0)));

        for(int i = 0 ; i < 8 ; i++) {
            if(redBlg[i] != NULL) {
                if(redBlg[i]->getDiplayButton() == highlighted) {
                    redBlg[i]->deselect();
                    //redBlg[i]->displayCommands();
                    break;
                }
            }
            if (blueBlg[i] != NULL) {
                if (blueBlg[i]->getDiplayButton() == highlighted) {
                    //blueBlg[i]->displayCommands();
                    blueBlg[i]->deselect();
                    break;
                }
            }
        }
    }

    highlighted = NULL;
    disengageHighlightedCMD();
}

void BattleEngine::disengageHighlightedCMD(){
    if(highlightedCmd != NULL)
        highlightedCmd->setIcon(*(highlightedCmd->getOffImage()));
    highlightedCmd = NULL;
    if(highlighted == NULL)
        ui->cmdLabel->setText("Nothing selected.");
    else if(highlighted != NULL) {
        QString displayText = NULL;
        for(int i = 0 ; i < 8 ; i++) {
            if(redBlg[i]->getDiplayButton() == highlighted) {
                displayText = redBlg[i]->getName();
                displayText.append("\nHitpoints: ").append(QString::number(redBlg[i]->getHitpoints())).append("/").append(QString::number(redBlg[i]->getHpMAX())).append("\n");
                displayText.append(redBlg[i]->getDesc());
                ui->cmdLabel->setText(displayText);
                break;
            }
            else if(blueBlg[i]->getDiplayButton() == highlighted) {
                displayText = blueBlg[i]->getName();
                displayText.append("\nHitpoints: ").append(QString::number(blueBlg[i]->getHitpoints())).append("/").append(QString::number(blueBlg[i]->getHpMAX())).append("\n");
                displayText.append(blueBlg[i]->getDesc());
                ui->cmdLabel->setText(displayText);
                break;
            }
        }
    }
}

void BattleEngine::animateHighlighted() {
    if(highlighted != NULL) {
        switch(animationIndex) {
            case 0:
                highlighted->setIcon(*(iconAnim->value(1)));
                break;
            case 1:
                highlighted->setIcon(*(iconAnim->value(2)));
                break;
            case 2:
                highlighted->setIcon(*(iconAnim->value(3)));
                break;
            case 3:
                highlighted->setIcon(*(iconAnim->value(4)));
                break;
            case 4:
                highlighted->setIcon(*(iconAnim->value(3)));
                break;
            case 5:
                highlighted->setIcon(*(iconAnim->value(2)));
                break;
            default:
                break; //invalid case
        }
    }

    animationIndex++;

    animationIndex%=6;
}

void BattleEngine::loadSpritesFor(bool faction, QString defType, QString atkType, int level) {
    qDebug(defType.append(atkType).append(QString::number(level)).toAscii());
    if(faction) {
        if(defType.contains("Air",Qt::CaseSensitive)) {
            if(atkType.contains("AA",Qt::CaseSensitive)) {
                qDebug("X");
                switch(level){
                case 1:
                    if(unitSpriteBase[0][0][0][0][0] != NULL)
                        return;
                    unitSpriteBase[0][0][0][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][0][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/walk/1.png"));
                    unitSpriteBase[0][0][0][0][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/walk/2.png"));
                    unitSpriteBase[0][0][0][0][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/walk/3.png"));
                    unitSpriteBase[0][0][0][0][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/walk/4.png"));
                    unitSpriteBase[0][0][0][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][0][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/attack/1.png"));
                    unitSpriteBase[0][0][0][0][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/attack/2.png"));
                    unitSpriteBase[0][0][0][0][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/attack/3.png"));
                    unitSpriteBase[0][0][0][0][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/attack/4.png"));
                    unitSpriteBase[0][0][0][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][0][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/steady/1.png"));
                    unitSpriteBase[0][0][0][0][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/steady/2.png"));
                    unitSpriteBase[0][0][0][0][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/steady/3.png"));
                    unitSpriteBase[0][0][0][0][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv1/steady/4.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][0][0][1][0] != NULL)
                        return;
                    unitSpriteBase[0][0][0][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][1][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/walk/1.png"));
                    unitSpriteBase[0][0][0][1][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/walk/2.png"));
                    unitSpriteBase[0][0][0][1][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/walk/3.png"));
                    unitSpriteBase[0][0][0][1][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/walk/4.png"));
                    unitSpriteBase[0][0][0][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/1.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/2.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/3.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/4.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/5.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/6.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/7.png"));
                    unitSpriteBase[0][0][0][1][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/attack/8.png"));
                    unitSpriteBase[0][0][0][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][1][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/steady/1.png"));
                    unitSpriteBase[0][0][0][1][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/steady/2.png"));
                    unitSpriteBase[0][0][0][1][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/steady/3.png"));
                    unitSpriteBase[0][0][0][1][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv2/steady/4.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][0][0][2][0] != NULL)
                        return;
                    unitSpriteBase[0][0][0][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][2][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/walk/1.png"));
                    unitSpriteBase[0][0][0][2][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/walk/2.png"));
                    unitSpriteBase[0][0][0][2][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/walk/3.png"));
                    unitSpriteBase[0][0][0][2][0]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/walk/4.png"));
                    unitSpriteBase[0][0][0][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][2][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/attack/1.png"));
                    unitSpriteBase[0][0][0][2][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/attack/2.png"));
                    unitSpriteBase[0][0][0][2][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/attack/3.png"));
                    unitSpriteBase[0][0][0][2][1]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/attack/4.png"));
                    unitSpriteBase[0][0][0][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][0][2][2]->append(new QPixmap("/resource/Red/Aircraft/AA/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AI",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][0][1][0][0] != NULL)
                        return;
                    unitSpriteBase[0][0][1][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][0][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/walk/1.png"));
                    unitSpriteBase[0][0][1][0][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/walk/2.png"));
                    unitSpriteBase[0][0][1][0][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/walk/3.png"));
                    unitSpriteBase[0][0][1][0][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/walk/4.png"));
                    unitSpriteBase[0][0][1][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][0][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][0][1][0][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][0][1][0][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/attack/3.png"));
                    unitSpriteBase[0][0][1][0][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/attack/4.png"));
                    unitSpriteBase[0][0][1][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][0][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/steady/1.png"));
                    unitSpriteBase[0][0][1][0][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/steady/2.png"));
                    unitSpriteBase[0][0][1][0][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/steady/3.png"));
                    unitSpriteBase[0][0][1][0][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv1/steady/4.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][0][1][1][0] != NULL)
                        return;
                    unitSpriteBase[0][0][1][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][1][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/walk/1.png"));
                    unitSpriteBase[0][0][1][1][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/walk/2.png"));
                    unitSpriteBase[0][0][1][1][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/walk/3.png"));
                    unitSpriteBase[0][0][1][1][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/walk/4.png"));
                    unitSpriteBase[0][0][1][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][1][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][0][1][1][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][0][1][1][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/attack/3.png"));
                    unitSpriteBase[0][0][1][1][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/attack/4.png"));
                    unitSpriteBase[0][0][1][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][1][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/steady/1.png"));
                    unitSpriteBase[0][0][1][1][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/steady/2.png"));
                    unitSpriteBase[0][0][1][1][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/steady/3.png"));
                    unitSpriteBase[0][0][1][1][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv2/steady/4.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][0][1][2][0] != NULL)
                        return;
                    unitSpriteBase[0][0][1][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][2][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/walk/1.png"));
                    unitSpriteBase[0][0][1][2][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/walk/2.png"));
                    unitSpriteBase[0][0][1][2][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/walk/3.png"));
                    unitSpriteBase[0][0][1][2][0]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/walk/4.png"));
                    unitSpriteBase[0][0][1][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][2][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/attack/1.png"));
                    unitSpriteBase[0][0][1][2][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/attack/2.png"));
                    unitSpriteBase[0][0][1][2][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/attack/3.png"));
                    unitSpriteBase[0][0][1][2][1]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/attack/4.png"));
                    unitSpriteBase[0][0][1][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][1][2][2]->append(new QPixmap("/resource/Red/Aircraft/AI/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AT",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][0][2][0][0] != NULL)
                        return;
                    unitSpriteBase[0][0][2][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][0][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/walk/1.png"));
                    unitSpriteBase[0][0][2][0][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/walk/2.png"));
                    unitSpriteBase[0][0][2][0][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/walk/3.png"));
                    unitSpriteBase[0][0][2][0][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/walk/4.png"));
                    unitSpriteBase[0][0][2][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][0][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/attack/1.png"));
                    unitSpriteBase[0][0][2][0][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/attack/2.png"));
                    unitSpriteBase[0][0][2][0][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/attack/3.png"));
                    unitSpriteBase[0][0][2][0][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/attack/4.png"));
                    unitSpriteBase[0][0][2][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][0][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/steady/1.png"));
                    unitSpriteBase[0][0][2][0][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/steady/2.png"));
                    unitSpriteBase[0][0][2][0][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/steady/3.png"));
                    unitSpriteBase[0][0][2][0][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv1/steady/4.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][0][2][1][0] != NULL)
                        return;
                    unitSpriteBase[0][0][2][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][1][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/walk/1.png"));
                    unitSpriteBase[0][0][2][1][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/walk/2.png"));
                    unitSpriteBase[0][0][2][1][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/walk/3.png"));
                    unitSpriteBase[0][0][2][1][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/walk/4.png"));
                    unitSpriteBase[0][0][2][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/1.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/2.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/3.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/4.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/5.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/6.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/7.png"));
                    unitSpriteBase[0][0][2][1][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/attack/8.png"));
                    unitSpriteBase[0][0][2][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][1][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/steady/1.png"));
                    unitSpriteBase[0][0][2][1][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/steady/2.png"));
                    unitSpriteBase[0][0][2][1][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/steady/3.png"));
                    unitSpriteBase[0][0][2][1][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv2/steady/4.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][0][2][2][0] != NULL)
                        return;
                    unitSpriteBase[0][0][2][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][2][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/walk/1.png"));
                    unitSpriteBase[0][0][2][2][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/walk/2.png"));
                    unitSpriteBase[0][0][2][2][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/walk/3.png"));
                    unitSpriteBase[0][0][2][2][0]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/walk/4.png"));
                    unitSpriteBase[0][0][2][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][2][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/attack/1.png"));
                    unitSpriteBase[0][0][2][2][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/attack/2.png"));
                    unitSpriteBase[0][0][2][2][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/attack/3.png"));
                    unitSpriteBase[0][0][2][2][1]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/attack/4.png"));
                    unitSpriteBase[0][0][2][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][0][2][2][2]->append(new QPixmap("/resource/Red/Aircraft/AT/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
        }
        else if(defType.contains("Infantry")) {
            if(atkType.contains("AI",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][1][1][0][0] != NULL)
                        return;
                    unitSpriteBase[0][1][1][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][0][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/walk/1.png"));
                    unitSpriteBase[0][1][1][0][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/walk/2.png"));
                    unitSpriteBase[0][1][1][0][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/walk/3.png"));
                    unitSpriteBase[0][1][1][0][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/walk/4.png"));
                    unitSpriteBase[0][1][1][0][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/walk/5.png"));
                    unitSpriteBase[0][1][1][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][0][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][1][1][0][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][1][1][0][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][1][1][0][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][1][1][0][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][1][1][0][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][1][1][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][0][2]->append(new QPixmap("/resource/Red/Infantry/AI/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][1][1][1][0] != NULL)
                        return;
                    unitSpriteBase[0][1][1][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][1][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/walk/1.png"));
                    unitSpriteBase[0][1][1][1][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/walk/2.png"));
                    unitSpriteBase[0][1][1][1][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/walk/3.png"));
                    unitSpriteBase[0][1][1][1][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/walk/4.png"));
                    unitSpriteBase[0][1][1][1][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/walk/5.png"));
                    unitSpriteBase[0][1][1][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][1][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][1][1][1][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][1][1][1][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][1][1][1][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][1][1][1][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][1][1][1][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][1][1][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][1][2]->append(new QPixmap("/resource/Red/Infantry/AI/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][1][1][2][0] != NULL)
                        return;
                    unitSpriteBase[0][1][1][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][2][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/walk/1.png"));
                    unitSpriteBase[0][1][1][2][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/walk/2.png"));
                    unitSpriteBase[0][1][1][2][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/walk/3.png"));
                    unitSpriteBase[0][1][1][2][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/walk/4.png"));
                    unitSpriteBase[0][1][1][2][0]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/walk/5.png"));
                    unitSpriteBase[0][1][1][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][2][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/attack/1.png"));
                    unitSpriteBase[0][1][1][2][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/attack/2.png"));
                    unitSpriteBase[0][1][1][2][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/attack/1.png"));
                    unitSpriteBase[0][1][1][2][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/attack/2.png"));
                    unitSpriteBase[0][1][1][2][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/attack/1.png"));
                    unitSpriteBase[0][1][1][2][1]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/attack/2.png"));
                    unitSpriteBase[0][1][1][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][1][2][2]->append(new QPixmap("/resource/Red/Infantry/AI/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AT",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][1][2][0][0] != NULL)
                        return;
                    unitSpriteBase[0][1][2][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][0][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/walk/1.png"));
                    unitSpriteBase[0][1][2][0][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/walk/2.png"));
                    unitSpriteBase[0][1][2][0][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/walk/3.png"));
                    unitSpriteBase[0][1][2][0][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/walk/4.png"));
                    unitSpriteBase[0][1][2][0][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/walk/5.png"));
                    unitSpriteBase[0][1][2][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][0][1]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/attack/1.png"));
                    unitSpriteBase[0][1][2][0][1]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/attack/2.png"));
                    unitSpriteBase[0][1][2][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][0][2]->append(new QPixmap("/resource/Red/Infantry/AT/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][1][2][1][0] != NULL)
                        return;
                    unitSpriteBase[0][1][2][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][1][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/walk/1.png"));
                    unitSpriteBase[0][1][2][1][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/walk/2.png"));
                    unitSpriteBase[0][1][2][1][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/walk/3.png"));
                    unitSpriteBase[0][1][2][1][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/walk/4.png"));
                    unitSpriteBase[0][1][2][1][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/walk/5.png"));
                    unitSpriteBase[0][1][2][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][1][1]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/attack/1.png"));
                    unitSpriteBase[0][1][2][1][1]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/attack/2.png"));
                    unitSpriteBase[0][1][2][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][1][2]->append(new QPixmap("/resource/Red/Infantry/AT/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][1][2][2][0] != NULL)
                        return;
                    unitSpriteBase[0][1][2][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][2][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/walk/1.png"));
                    unitSpriteBase[0][1][2][2][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/walk/2.png"));
                    unitSpriteBase[0][1][2][2][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/walk/3.png"));
                    unitSpriteBase[0][1][2][2][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/walk/4.png"));
                    unitSpriteBase[0][1][2][2][0]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/walk/5.png"));
                    unitSpriteBase[0][1][2][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][2][1]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/attack/1.png"));
                    unitSpriteBase[0][1][2][2][1]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/attack/2.png"));
                    unitSpriteBase[0][1][2][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][1][2][2][2]->append(new QPixmap("/resource/Red/Infantry/AT/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
        }
        else if(defType.contains("Vehicle",Qt::CaseSensitive)) {
            if(atkType.contains("AA",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][2][0][0][0] != NULL)
                        return;
                    unitSpriteBase[0][2][0][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][0][0]->append(new QPixmap("/resource/Red/Vehicle/AA/lv1/walk/1.png"));
                    unitSpriteBase[0][2][0][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][0][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv1/attack/1.png"));
                    unitSpriteBase[0][2][0][0][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv1/attack/2.png"));
                    unitSpriteBase[0][2][0][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][0][2]->append(new QPixmap("/resource/Red/Vehicle/AA/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][2][0][1][0] != NULL)
                        return;
                    unitSpriteBase[0][2][0][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][1][0]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/walk/1.png"));
                    unitSpriteBase[0][2][0][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][1][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/attack/1.png"));
                    unitSpriteBase[0][2][0][1][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/attack/2.png"));
                    unitSpriteBase[0][2][0][1][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/attack/3.png"));
                    unitSpriteBase[0][2][0][1][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/attack/4.png"));
                    unitSpriteBase[0][2][0][1][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/attack/5.png"));
                    unitSpriteBase[0][2][0][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][1][2]->append(new QPixmap("/resource/Red/Vehicle/AA/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][2][0][2][0] != NULL)
                        return;
                    unitSpriteBase[0][2][0][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][2][0]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/walk/1.png"));
                    unitSpriteBase[0][2][0][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/1.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/2.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/3.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/4.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/5.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/6.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/7.png"));
                    unitSpriteBase[0][2][0][2][1]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/attack/8.png"));
                    unitSpriteBase[0][2][0][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][0][2][2]->append(new QPixmap("/resource/Red/Vehicle/AA/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AI",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][2][1][0][0] != NULL)
                        return;
                    unitSpriteBase[0][2][1][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][0][0]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/walk/1.png"));
                    unitSpriteBase[0][2][1][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][0][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][2][1][0][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][2][1][0][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][2][1][0][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][2][1][0][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/attack/1.png"));
                    unitSpriteBase[0][2][1][0][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/attack/2.png"));
                    unitSpriteBase[0][2][1][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][0][2]->append(new QPixmap("/resource/Red/Vehicle/AI/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][2][1][1][0] != NULL)
                        return;
                    unitSpriteBase[0][2][1][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][1][0]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/walk/1.png"));
                    unitSpriteBase[0][2][1][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][1][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][2][1][1][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][2][1][1][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][2][1][1][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][2][1][1][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/attack/1.png"));
                    unitSpriteBase[0][2][1][1][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/attack/2.png"));
                    unitSpriteBase[0][2][1][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][1][2]->append(new QPixmap("/resource/Red/Vehicle/AI/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][2][1][2][0] != NULL)
                        return;
                    unitSpriteBase[0][2][1][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][2][0]->append(new QPixmap("/resource/Red/Vehicle/AI/lv3/walk/1.png"));
                    unitSpriteBase[0][2][1][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][2][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv3/attack/1.png"));
                    unitSpriteBase[0][2][1][2][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv3/attack/2.png"));
                    unitSpriteBase[0][2][1][2][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv3/attack/3.png"));
                    unitSpriteBase[0][2][1][2][1]->append(new QPixmap("/resource/Red/Vehicle/AI/lv3/attack/4.png"));
                    unitSpriteBase[0][2][1][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][1][2][2]->append(new QPixmap("/resource/Red/Vehicle/AI/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AT",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[0][2][2][0][0] != NULL)
                        return;
                    unitSpriteBase[0][2][2][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][0][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv1/walk/1.png"));
                    unitSpriteBase[0][2][2][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][0][1]->append(new QPixmap("/resource/Red/Vehicle/AT/lv1/attack/1.png"));
                    unitSpriteBase[0][2][2][0][1]->append(new QPixmap("/resource/Red/Vehicle/AT/lv1/attack/2.png"));
                    unitSpriteBase[0][2][2][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][0][2]->append(new QPixmap("/resource/Red/Vehicle/AT/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[0][2][2][1][0] != NULL)
                        return;
                    unitSpriteBase[0][2][2][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][1][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv2/walk/1.png"));
                    unitSpriteBase[0][2][2][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][1][1]->append(new QPixmap("/resource/Red/Vehicle/AT/lv2/attack/1.png"));
                    unitSpriteBase[0][2][2][1][1]->append(new QPixmap("/resource/Red/Vehicle/AT/lv2/attack/2.png"));
                    unitSpriteBase[0][2][2][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][1][2]->append(new QPixmap("/resource/Red/Vehicle/AT/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[0][2][2][2][0] != NULL)
                        return;
                    unitSpriteBase[0][2][2][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/1.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/2.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/3.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/4.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/5.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/6.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/7.png"));
                    unitSpriteBase[0][2][2][2][0]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/walk/8.png"));
                    unitSpriteBase[0][2][2][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][2][1]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/attack/1.png"));
                    unitSpriteBase[0][2][2][2][1]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/attack/2.png"));
                    unitSpriteBase[0][2][2][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[0][2][2][2][2]->append(new QPixmap("/resource/Red/Vehicle/AT/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
        }
    }
    else {
        if(defType.contains("Air",Qt::CaseSensitive)) {
            if(atkType.contains("AA",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][0][0][0][0] != NULL)
                        return;
                    unitSpriteBase[1][0][0][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/walk/1.png"));
                    unitSpriteBase[1][0][0][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/walk/2.png"));
                    unitSpriteBase[1][0][0][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/walk/3.png"));
                    unitSpriteBase[1][0][0][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/walk/4.png"));
                    unitSpriteBase[1][0][0][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/attack/1.png"));
                    unitSpriteBase[1][0][0][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/attack/2.png"));
                    unitSpriteBase[1][0][0][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/attack/3.png"));
                    unitSpriteBase[1][0][0][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/attack/4.png"));
                    unitSpriteBase[1][0][0][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/steady/1.png"));
                    unitSpriteBase[1][0][0][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/steady/2.png"));
                    unitSpriteBase[1][0][0][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/steady/3.png"));
                    unitSpriteBase[1][0][0][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv1/steady/4.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][0][0][1][0] != NULL)
                        return;
                    unitSpriteBase[1][0][0][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/walk/1.png"));
                    unitSpriteBase[1][0][0][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/walk/2.png"));
                    unitSpriteBase[1][0][0][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/walk/3.png"));
                    unitSpriteBase[1][0][0][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/walk/4.png"));
                    unitSpriteBase[1][0][0][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/1.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/2.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/3.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/4.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/5.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/6.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/7.png"));
                    unitSpriteBase[1][0][0][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/attack/8.png"));
                    unitSpriteBase[1][0][0][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/steady/1.png"));
                    unitSpriteBase[1][0][0][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/steady/2.png"));
                    unitSpriteBase[1][0][0][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/steady/3.png"));
                    unitSpriteBase[1][0][0][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv2/steady/4.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][0][0][2][0] != NULL)
                        return;
                    unitSpriteBase[1][0][0][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/walk/1.png"));
                    unitSpriteBase[1][0][0][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/walk/2.png"));
                    unitSpriteBase[1][0][0][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/walk/3.png"));
                    unitSpriteBase[1][0][0][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/walk/4.png"));
                    unitSpriteBase[1][0][0][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/attack/1.png"));
                    unitSpriteBase[1][0][0][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/attack/2.png"));
                    unitSpriteBase[1][0][0][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/attack/3.png"));
                    unitSpriteBase[1][0][0][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/attack/4.png"));
                    unitSpriteBase[1][0][0][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][0][2][2]->append(new QPixmap("/resource/Blue/Aircraft/AA/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AI",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][0][1][0][0] != NULL)
                        return;
                    unitSpriteBase[1][0][1][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/walk/1.png"));
                    unitSpriteBase[1][0][1][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/walk/2.png"));
                    unitSpriteBase[1][0][1][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/walk/3.png"));
                    unitSpriteBase[1][0][1][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/walk/4.png"));
                    unitSpriteBase[1][0][1][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][0][1][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][0][1][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/attack/3.png"));
                    unitSpriteBase[1][0][1][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/attack/4.png"));
                    unitSpriteBase[1][0][1][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/steady/1.png"));
                    unitSpriteBase[1][0][1][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/steady/2.png"));
                    unitSpriteBase[1][0][1][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/steady/3.png"));
                    unitSpriteBase[1][0][1][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv1/steady/4.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][0][1][1][0] != NULL)
                        return;
                    unitSpriteBase[1][0][1][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/walk/1.png"));
                    unitSpriteBase[1][0][1][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/walk/2.png"));
                    unitSpriteBase[1][0][1][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/walk/3.png"));
                    unitSpriteBase[1][0][1][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/walk/4.png"));
                    unitSpriteBase[1][0][1][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][0][1][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][0][1][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/attack/3.png"));
                    unitSpriteBase[1][0][1][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/attack/4.png"));
                    unitSpriteBase[1][0][1][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/steady/1.png"));
                    unitSpriteBase[1][0][1][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/steady/2.png"));
                    unitSpriteBase[1][0][1][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/steady/3.png"));
                    unitSpriteBase[1][0][1][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv2/steady/4.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][0][1][2][0] != NULL)
                        return;
                    unitSpriteBase[1][0][1][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/walk/1.png"));
                    unitSpriteBase[1][0][1][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/walk/2.png"));
                    unitSpriteBase[1][0][1][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/walk/3.png"));
                    unitSpriteBase[1][0][1][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/walk/4.png"));
                    unitSpriteBase[1][0][1][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/attack/1.png"));
                    unitSpriteBase[1][0][1][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/attack/2.png"));
                    unitSpriteBase[1][0][1][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/attack/3.png"));
                    unitSpriteBase[1][0][1][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/attack/4.png"));
                    unitSpriteBase[1][0][1][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][1][2][2]->append(new QPixmap("/resource/Blue/Aircraft/AI/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AT",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][0][2][0][0] != NULL)
                        return;
                    unitSpriteBase[1][0][2][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/walk/1.png"));
                    unitSpriteBase[1][0][2][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/walk/2.png"));
                    unitSpriteBase[1][0][2][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/walk/3.png"));
                    unitSpriteBase[1][0][2][0][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/walk/4.png"));
                    unitSpriteBase[1][0][2][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/attack/1.png"));
                    unitSpriteBase[1][0][2][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/attack/2.png"));
                    unitSpriteBase[1][0][2][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/attack/3.png"));
                    unitSpriteBase[1][0][2][0][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/attack/4.png"));
                    unitSpriteBase[1][0][2][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/steady/1.png"));
                    unitSpriteBase[1][0][2][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/steady/2.png"));
                    unitSpriteBase[1][0][2][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/steady/3.png"));
                    unitSpriteBase[1][0][2][0][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv1/steady/4.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][0][2][1][0] != NULL)
                        return;
                    unitSpriteBase[1][0][2][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/walk/1.png"));
                    unitSpriteBase[1][0][2][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/walk/2.png"));
                    unitSpriteBase[1][0][2][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/walk/3.png"));
                    unitSpriteBase[1][0][2][1][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/walk/4.png"));
                    unitSpriteBase[1][0][2][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/1.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/2.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/3.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/4.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/5.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/6.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/7.png"));
                    unitSpriteBase[1][0][2][1][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/attack/8.png"));
                    unitSpriteBase[1][0][2][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/steady/1.png"));
                    unitSpriteBase[1][0][2][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/steady/2.png"));
                    unitSpriteBase[1][0][2][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/steady/3.png"));
                    unitSpriteBase[1][0][2][1][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv2/steady/4.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][0][2][2][0] != NULL)
                        return;
                    unitSpriteBase[1][0][2][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/walk/1.png"));
                    unitSpriteBase[1][0][2][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/walk/2.png"));
                    unitSpriteBase[1][0][2][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/walk/3.png"));
                    unitSpriteBase[1][0][2][2][0]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/walk/4.png"));
                    unitSpriteBase[1][0][2][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/attack/1.png"));
                    unitSpriteBase[1][0][2][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/attack/2.png"));
                    unitSpriteBase[1][0][2][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/attack/3.png"));
                    unitSpriteBase[1][0][2][2][1]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/attack/4.png"));
                    unitSpriteBase[1][0][2][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][0][2][2][2]->append(new QPixmap("/resource/Blue/Aircraft/AT/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
        }
        else if(defType.contains("Infantry",Qt::CaseSensitive)) {
            if(atkType.contains("AI",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][1][1][0][0] != NULL)
                        return;
                    unitSpriteBase[1][1][1][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][0][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/walk/1.png"));
                    unitSpriteBase[1][1][1][0][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/walk/2.png"));
                    unitSpriteBase[1][1][1][0][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/walk/3.png"));
                    unitSpriteBase[1][1][1][0][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/walk/4.png"));
                    unitSpriteBase[1][1][1][0][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/walk/5.png"));
                    unitSpriteBase[1][1][1][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][0][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][1][1][0][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][1][1][0][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][1][1][0][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][1][1][0][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][1][1][0][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][1][1][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][0][2]->append(new QPixmap("/resource/Blue/Infantry/AI/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][1][1][1][0] != NULL)
                        return;
                    unitSpriteBase[1][1][1][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][1][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/walk/1.png"));
                    unitSpriteBase[1][1][1][1][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/walk/2.png"));
                    unitSpriteBase[1][1][1][1][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/walk/3.png"));
                    unitSpriteBase[1][1][1][1][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/walk/4.png"));
                    unitSpriteBase[1][1][1][1][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/walk/5.png"));
                    unitSpriteBase[1][1][1][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][1][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][1][1][1][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][1][1][1][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][1][1][1][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][1][1][1][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][1][1][1][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][1][1][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][1][2]->append(new QPixmap("/resource/Blue/Infantry/AI/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][1][1][2][0] != NULL)
                        return;
                    unitSpriteBase[1][1][1][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][2][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/walk/1.png"));
                    unitSpriteBase[1][1][1][2][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/walk/2.png"));
                    unitSpriteBase[1][1][1][2][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/walk/3.png"));
                    unitSpriteBase[1][1][1][2][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/walk/4.png"));
                    unitSpriteBase[1][1][1][2][0]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/walk/5.png"));
                    unitSpriteBase[1][1][1][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][2][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/attack/1.png"));
                    unitSpriteBase[1][1][1][2][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/attack/2.png"));
                    unitSpriteBase[1][1][1][2][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/attack/1.png"));
                    unitSpriteBase[1][1][1][2][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/attack/2.png"));
                    unitSpriteBase[1][1][1][2][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/attack/1.png"));
                    unitSpriteBase[1][1][1][2][1]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/attack/2.png"));
                    unitSpriteBase[1][1][1][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][1][2][2]->append(new QPixmap("/resource/Blue/Infantry/AI/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AT",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][1][2][0][0] != NULL)
                        return;
                    unitSpriteBase[1][1][2][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][0][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/walk/1.png"));
                    unitSpriteBase[1][1][2][0][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/walk/2.png"));
                    unitSpriteBase[1][1][2][0][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/walk/3.png"));
                    unitSpriteBase[1][1][2][0][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/walk/4.png"));
                    unitSpriteBase[1][1][2][0][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/walk/5.png"));
                    unitSpriteBase[1][1][2][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][0][1]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/attack/1.png"));
                    unitSpriteBase[1][1][2][0][1]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/attack/2.png"));
                    unitSpriteBase[1][1][2][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][0][2]->append(new QPixmap("/resource/Blue/Infantry/AT/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][1][2][1][0] != NULL)
                        return;
                    unitSpriteBase[1][1][2][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][1][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/walk/1.png"));
                    unitSpriteBase[1][1][2][1][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/walk/2.png"));
                    unitSpriteBase[1][1][2][1][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/walk/3.png"));
                    unitSpriteBase[1][1][2][1][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/walk/4.png"));
                    unitSpriteBase[1][1][2][1][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/walk/5.png"));
                    unitSpriteBase[1][1][2][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][1][1]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/attack/1.png"));
                    unitSpriteBase[1][1][2][1][1]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/attack/2.png"));
                    unitSpriteBase[1][1][2][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][1][2]->append(new QPixmap("/resource/Blue/Infantry/AT/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][1][2][2][0] != NULL)
                        return;
                    unitSpriteBase[1][1][2][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][2][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/walk/1.png"));
                    unitSpriteBase[1][1][2][2][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/walk/2.png"));
                    unitSpriteBase[1][1][2][2][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/walk/3.png"));
                    unitSpriteBase[1][1][2][2][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/walk/4.png"));
                    unitSpriteBase[1][1][2][2][0]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/walk/5.png"));
                    unitSpriteBase[1][1][2][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][2][1]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/attack/1.png"));
                    unitSpriteBase[1][1][2][2][1]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/attack/2.png"));
                    unitSpriteBase[1][1][2][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][1][2][2][2]->append(new QPixmap("/resource/Blue/Infantry/AT/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
        }
        else if(defType.contains("Vehicle",Qt::CaseSensitive)) {
            if(atkType.contains("AA",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][2][0][0][0] != NULL)
                        return;
                    unitSpriteBase[1][2][0][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][0][0]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv1/walk/1.png"));
                    unitSpriteBase[1][2][0][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv1/attack/1.png"));
                    unitSpriteBase[1][2][0][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv1/attack/2.png"));
                    unitSpriteBase[1][2][0][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][0][2]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][2][0][1][0] != NULL)
                        return;
                    unitSpriteBase[1][2][0][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][1][0]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/walk/1.png"));
                    unitSpriteBase[1][2][0][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/attack/1.png"));
                    unitSpriteBase[1][2][0][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/attack/2.png"));
                    unitSpriteBase[1][2][0][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/attack/3.png"));
                    unitSpriteBase[1][2][0][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/attack/4.png"));
                    unitSpriteBase[1][2][0][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/attack/5.png"));
                    unitSpriteBase[1][2][0][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][1][2]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][2][0][2][0] != NULL)
                        return;
                    unitSpriteBase[1][2][0][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/walk/1.png"));
                    unitSpriteBase[1][2][0][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/1.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/2.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/3.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/4.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/5.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/6.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/7.png"));
                    unitSpriteBase[1][2][0][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/attack/8.png"));
                    unitSpriteBase[1][2][0][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][0][2][2]->append(new QPixmap("/resource/Blue/Vehicle/AA/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AI",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][2][1][0][0] != NULL)
                        return;
                    unitSpriteBase[1][2][1][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][0][0]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/walk/1.png"));
                    unitSpriteBase[1][2][1][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][2][1][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][2][1][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][2][1][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][2][1][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/attack/1.png"));
                    unitSpriteBase[1][2][1][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/attack/2.png"));
                    unitSpriteBase[1][2][1][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][0][2]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][2][1][1][0] != NULL)
                        return;
                    unitSpriteBase[1][2][1][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][1][0]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/walk/1.png"));
                    unitSpriteBase[1][2][1][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][2][1][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][2][1][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][2][1][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][2][1][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/attack/1.png"));
                    unitSpriteBase[1][2][1][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/attack/2.png"));
                    unitSpriteBase[1][2][1][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][1][2]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][2][1][2][0] != NULL)
                        return;
                    unitSpriteBase[1][2][1][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv3/walk/1.png"));
                    unitSpriteBase[1][2][1][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv3/attack/1.png"));
                    unitSpriteBase[1][2][1][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv3/attack/2.png"));
                    unitSpriteBase[1][2][1][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv3/attack/3.png"));
                    unitSpriteBase[1][2][1][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv3/attack/4.png"));
                    unitSpriteBase[1][2][1][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][1][2][2]->append(new QPixmap("/resource/Blue/Vehicle/AI/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
            else if(atkType.contains("AT",Qt::CaseSensitive)) {
                switch(level){
                case 1:
                    if(unitSpriteBase[1][2][2][0][0] != NULL)
                        return;
                    unitSpriteBase[1][2][2][0][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][0][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv1/walk/1.png"));
                    unitSpriteBase[1][2][2][0][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv1/attack/1.png"));
                    unitSpriteBase[1][2][2][0][1]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv1/attack/2.png"));
                    unitSpriteBase[1][2][2][0][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][0][2]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv1/steady/1.png"));
                    break;
                case 2:
                    if(unitSpriteBase[1][2][2][1][0] != NULL)
                        return;
                    unitSpriteBase[1][2][2][1][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][1][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv2/walk/1.png"));
                    unitSpriteBase[1][2][2][1][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv2/attack/1.png"));
                    unitSpriteBase[1][2][2][1][1]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv2/attack/2.png"));
                    unitSpriteBase[1][2][2][1][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][1][2]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv2/steady/1.png"));
                    break;
                case 3:
                    if(unitSpriteBase[1][2][2][2][0] != NULL)
                        return;
                    unitSpriteBase[1][2][2][2][0] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/1.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/2.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/3.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/4.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/5.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/6.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/7.png"));
                    unitSpriteBase[1][2][2][2][0]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/walk/8.png"));
                    unitSpriteBase[1][2][2][2][1] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/attack/1.png"));
                    unitSpriteBase[1][2][2][2][1]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/attack/2.png"));
                    unitSpriteBase[1][2][2][2][2] = new QList <QPixmap*> ();
                    unitSpriteBase[1][2][2][2][2]->append(new QPixmap("/resource/Blue/Vehicle/AT/lv3/steady/1.png"));
                    break;
                default:
                    break;
                }
            }
        }

    }
}

void BattleEngine::buildSpriteBase() {
    laserSound = new QSound("/resource/sounds/laser.wav");
    laserSound->setLoops(-1);

    alertSound = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource("/resource/sounds/alert.mp3"));
    ambientSound = new BGM("/resource/sounds/ambience.mp3");

    iconAnim = new QList <QIcon*> ();
    iconAnim->append(new QIcon(":Interface/animated/interface/select/0.png"));
    iconAnim->append(new QIcon(":Interface/animated/interface/select/1.png"));
    iconAnim->append(new QIcon(":Interface/animated/interface/select/2.png"));
    iconAnim->append(new QIcon(":Interface/animated/interface/select/3.png"));
    iconAnim->append(new QIcon(":Interface/animated/interface/select/4.png"));

    switchBase[0][0] = new QIcon(":Images/generic/buttons/flip/redOff.png");
    switchBase[0][1] = new QIcon(":Images/generic/buttons/flip/redOn.png");
    switchBase[1][0] = new QIcon(":Images/generic/buttons/flip/batOff.png");
    switchBase[1][1] = new QIcon(":Images/generic/buttons/flip/batOn.png");
    switchBase[2][0] = new QIcon(":Images/generic/buttons/flip/blueOff.png");
    switchBase[2][1] = new QIcon(":Images/generic/buttons/flip/blueOn.png");

    cmdIconBase[0][0] = new QIcon("/resource/cmdIcons/airfield.png");
    cmdIconBase[1][0] = new QIcon("/resource/cmdIcons/on/airfield.png");
    cmdIconBase[0][1] = new QIcon("/resource/cmdIcons/barracks.png");
    cmdIconBase[1][1] = new QIcon("/resource/cmdIcons/on/barracks.png");
    cmdIconBase[0][2] = new QIcon("/resource/cmdIcons/warfactory.png");
    cmdIconBase[1][2] = new QIcon("/resource/cmdIcons/on/warfactory.png");
    cmdIconBase[0][3] = new QIcon("/resource/cmdIcons/ecoC.png");
    cmdIconBase[1][3] = new QIcon("/resource/cmdIcons/on/ecoC.png");
    cmdIconBase[0][4] = new QIcon("/resource/cmdIcons/techC.png");
    cmdIconBase[1][4] = new QIcon("/resource/cmdIcons/on/techC.png");
    cmdIconBase[0][5] = new QIcon("/resource/cmdIcons/superweapon.png");
    cmdIconBase[1][5] = new QIcon("/resource/cmdIcons/on/superweapon.png");
    cmdIconBase[0][6] = new QIcon("/resource/cmdIcons/upgrade.png");
    cmdIconBase[1][6] = new QIcon("/resource/cmdIcons/on/upgrade.png");
    cmdIconBase[0][7] = new QIcon("/resource/cmdIcons/sell.png");
    cmdIconBase[1][7] = new QIcon("/resource/cmdIcons/on/sell.png");
    cmdIconBase[0][8] = new QIcon("/resource/cmdIcons/repair.png");
    cmdIconBase[1][8] = new QIcon("/resource/cmdIcons/on/repair.png");
    cmdIconBase[0][9] = new QIcon("/resource/cmdIcons/artillery.png");
    cmdIconBase[1][9] = new QIcon("/resource/cmdIcons/on/artillery.png");
    cmdIconBase[0][10] = new QIcon("/resource/cmdIcons/blitz.png");
    cmdIconBase[1][10] = new QIcon("/resource/cmdIcons/on/blitz.png");
    cmdIconBase[0][11] = new QIcon("/resource/cmdIcons/ecoBoom.png");
    cmdIconBase[1][11] = new QIcon("/resource/cmdIcons/on/ecoBoom.png");
    cmdIconBase[0][12] = new QIcon("/resource/cmdIcons/revolt.png");
    cmdIconBase[1][12] = new QIcon("/resource/cmdIcons/on/revolt.png");
    cmdIconBase[0][13] = new QIcon("/resource/cmdIcons/laser.png");
    cmdIconBase[1][13] = new QIcon("/resource/cmdIcons/on/laser.png");
    cmdIconBase[0][14] = new QIcon("/resource/cmdIcons/nuke.png");
    cmdIconBase[1][14] = new QIcon("/resource/cmdIcons/on/nuke.png");

    unitIconBase[0][0] = new QIcon("/resource/unitIcons/airAA1.png");
    unitIconBase[1][0] = new QIcon("/resource/unitIcons/on/airAA1.png");
    unitIconBase[0][1] = new QIcon("/resource/unitIcons/airAA2.png");
    unitIconBase[1][1] = new QIcon("/resource/unitIcons/on/airAA2.png");
    unitIconBase[0][2] = new QIcon("/resource/unitIcons/airAA3.png");
    unitIconBase[1][2] = new QIcon("/resource/unitIcons/on/airAA3.png");
    unitIconBase[0][3] = new QIcon("/resource/unitIcons/airAI1.png");
    unitIconBase[1][3] = new QIcon("/resource/unitIcons/on/airAI1.png");
    unitIconBase[0][4] = new QIcon("/resource/unitIcons/airAI2.png");
    unitIconBase[1][4] = new QIcon("/resource/unitIcons/on/airAI2.png");
    unitIconBase[0][5] = new QIcon("/resource/unitIcons/airAI3.png");
    unitIconBase[1][5] = new QIcon("/resource/unitIcons/on/airAI3.png");
    unitIconBase[0][6] = new QIcon("/resource/unitIcons/airAT1.png");
    unitIconBase[1][6] = new QIcon("/resource/unitIcons/on/airAT1.png");
    unitIconBase[0][7] = new QIcon("/resource/unitIcons/airAT2.png");
    unitIconBase[1][7] = new QIcon("/resource/unitIcons/on/airAT2.png");
    unitIconBase[0][8] = new QIcon("/resource/unitIcons/airAT3.png");
    unitIconBase[1][8] = new QIcon("/resource/unitIcons/on/airAT3.png");
    unitIconBase[0][9] = new QIcon("/resource/unitIcons/infAI1.png");
    unitIconBase[1][9] = new QIcon("/resource/unitIcons/on/infAI1.png");
    unitIconBase[0][10] = new QIcon("/resource/unitIcons/infAI2.png");
    unitIconBase[1][10] = new QIcon("/resource/unitIcons/on/infAI2.png");
    unitIconBase[0][11] = new QIcon("/resource/unitIcons/infAI3.png");
    unitIconBase[1][11] = new QIcon("/resource/unitIcons/on/infAI3.png");
    unitIconBase[0][12] = new QIcon("/resource/unitIcons/infAT1.png");
    unitIconBase[1][12] = new QIcon("/resource/unitIcons/on/infAT1.png");
    unitIconBase[0][13] = new QIcon("/resource/unitIcons/infAT2.png");
    unitIconBase[1][13] = new QIcon("/resource/unitIcons/on/infAT2.png");
    unitIconBase[0][14] = new QIcon("/resource/unitIcons/infAT3.png");
    unitIconBase[1][14] = new QIcon("/resource/unitIcons/on/infAT3.png");
    unitIconBase[0][15] = new QIcon("/resource/unitIcons/vehAA1.png");
    unitIconBase[1][15] = new QIcon("/resource/unitIcons/on/vehAA1.png");
    unitIconBase[0][16] = new QIcon("/resource/unitIcons/vehAA2.png");
    unitIconBase[1][16] = new QIcon("/resource/unitIcons/on/vehAA2.png");
    unitIconBase[0][17] = new QIcon("/resource/unitIcons/vehAA3.png");
    unitIconBase[1][17] = new QIcon("/resource/unitIcons/on/vehAA3.png");
    unitIconBase[0][18] = new QIcon("/resource/unitIcons/vehAI1.png");
    unitIconBase[1][18] = new QIcon("/resource/unitIcons/on/vehAI1.png");
    unitIconBase[0][19] = new QIcon("/resource/unitIcons/vehAI2.png");
    unitIconBase[1][19] = new QIcon("/resource/unitIcons/on/vehAI2.png");
    unitIconBase[0][20] = new QIcon("/resource/unitIcons/vehAI3.png");
    unitIconBase[1][20] = new QIcon("/resource/unitIcons/on/vehAI3.png");
    unitIconBase[0][21] = new QIcon("/resource/unitIcons/vehAT1.png");
    unitIconBase[1][21] = new QIcon("/resource/unitIcons/on/vehAT1.png");
    unitIconBase[0][22] = new QIcon("/resource/unitIcons/vehAT2.png");
    unitIconBase[1][22] = new QIcon("/resource/unitIcons/on/vehAT2.png");
    unitIconBase[0][23] = new QIcon("/resource/unitIcons/vehAT3.png");
    unitIconBase[1][23] = new QIcon("/resource/unitIcons/on/vehAT3.png");

    effects[0][0] = new QList <QPixmap*> ();
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/1.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/2.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/3.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/4.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/5.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/6.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/7.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/8.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/9.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/10.png"));
    effects[0][0]->append(new QPixmap("/resource/effects/gnd1/11.png"));

    effects[0][1] = new QList <QPixmap*> ();
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/1.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/2.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/3.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/4.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/5.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/6.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/7.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/8.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/9.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/10.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/11.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/12.png"));
    effects[0][1]->append(new QPixmap("/resource/effects/gnd2/13.png"));

    effects[0][2] = new QList <QPixmap*> ();
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/1.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/2.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/3.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/4.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/5.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/6.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/7.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/8.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/9.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/10.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/11.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/12.png"));
    effects[0][2]->append(new QPixmap("/resource/effects/gnd3/13.png"));

    effects[1][0] = new QList <QPixmap*> ();
    effects[1][0]->append(new QPixmap("/resource/effects/air1/1.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/2.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/3.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/4.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/5.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/6.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/7.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/8.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/9.png"));
    effects[1][0]->append(new QPixmap("/resource/effects/air1/10.png"));

    effects[1][1] = new QList <QPixmap*> ();
    effects[1][1]->append(new QPixmap("/resource/effects/air2/1.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/2.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/3.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/4.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/5.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/6.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/7.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/8.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/9.png"));
    effects[1][1]->append(new QPixmap("/resource/effects/air2/10.png"));

    effects[1][2] = new QList <QPixmap*> ();
    effects[1][2]->append(new QPixmap("/resource/effects/air3/1.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/2.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/3.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/4.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/5.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/6.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/7.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/8.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/9.png"));
    effects[1][2]->append(new QPixmap("/resource/effects/air3/10.png"));

    exec[0] = new QIcon(":Images/generic/buttons/exec/off.png");
    exec[1] = new QIcon(":Images/generic/buttons/exec/on.png");

    for(int a = 0 ; a < 2 ; a++) {
        for(int b = 0 ; b < 3 ; b++) {
            for(int c = 0 ; c < 3 ; c++) {
                for(int d = 0 ; d < 3 ; d++) {
                    for(int e = 0 ; e < 3 ; e++) {
                        unitSpriteBase[a][b][c][d][e] = NULL;
                    }
                }
            }
        }
    }

    for(int a = 0 ; a < 2 ; a++) {
        for(int b = 0 ; b < 6 ; b++) {
            for(int c = 0 ; c < 6 ; c++)
                for(int d = 0 ; d < 2 ; d++) {
                    blgSpriteBase[a][b][c][d] = NULL;
                }
        }
    }

    for(int i = 0 ; i < 3 ; i++) {
        QString defT = "";
        switch(i) {
            case 0: defT = "Air";
                break;
            case 1: defT = "Infantry";
                 break;
            case 2: defT = "Vehicle";
                break;
        }
        for(int j = 0 ; j < 3 ; j++) {
            QString atkT = "";
            switch(j) {
                case 0: atkT = "AA";
                    break;
                case 1: atkT = "AI";
                     break;
                case 2: atkT = "AT";
                    break;
            }
            for(int k = 1 ; k <= 3 ; k++) {
                loadSpritesFor(true,defT,atkT,k);
                loadSpritesFor(false,defT,atkT,k);
            }
        }
    }

}

void BattleEngine::run() {
    buildSpriteBase();
}

bool BattleEngine::unitCanAttackUnit(Unit* base, Unit* target) {
    if (!QString::compare(base->getAttackType(),"AA")) {
        if (!QString::compare(target->getDefenseType(),"Air")) {
            return true;
        }
    }
    else if (QString::compare(base->getAttackType(),"AA")) {
        if (QString::compare(target->getDefenseType(),"Air")) {
            return true;
        }
    }
    else
        return false;

    return false;
}

QList <Unit*>* BattleEngine::getAttackableEnemyUnits(Unit *base) {
    QList <Unit*>* temp = new QList <Unit*> ();
    if(base->getFaction() && blueUnits != NULL) {
        for(int i = 0 ; i < blueUnits->size() ; i++) {
            if((blueUnits->value(i)->getPosition() - base->getPosition()) < base->getAttackRange()
                &&
               (blueUnits->value(i)->getPosition() - base->getPosition()) > 0
                &&
                unitCanAttackUnit(base,blueUnits->value(i)))
                temp->append(blueUnits->value(i));
        }
    }
    else if(!(base->getFaction()) && redUnits != NULL) {
        for(int i = 0 ; i < redUnits->size() ; i++) {
            if((base->getPosition() - redUnits->value(i)->getPosition()) < base->getAttackRange()
                &&
               (base->getPosition() - redUnits->value(i)->getPosition()) > 0
                &&
                unitCanAttackUnit(base,redUnits->value(i)))
                temp->append(redUnits->value(i));
        }
    }
    return temp;
}

Unit* BattleEngine::getNearestEnemyUnitFromSet(Unit* base, QList<Unit*>* set){
    Unit* nearestEnemyUnit = set->value(0);

    if(base->getFaction()) {
        for(int i = 0 ; i < set->size() ; i++) {
            if(set->value(i)->getPosition() - base->getPosition() <
                nearestEnemyUnit->getPosition() - base->getPosition()) {
                nearestEnemyUnit = set->value(i);
            }
        }
        return nearestEnemyUnit;
    }
    else if(!base->getFaction()) {
        for(int i = 0 ; i < set->size() ; i++) {
            if(base->getPosition() - set->value(i)->getPosition() <
                base->getPosition() - nearestEnemyUnit->getPosition()){
                nearestEnemyUnit = set->value(i);
            }
        }
        return nearestEnemyUnit;
    }
    else
        return NULL;

    return NULL;
}

bool BattleEngine::anyAttackableEnemyUnitsInRange(Unit *base) {
    if(!(getAttackableEnemyUnits(base)->size()))
        return false;
    else
        return true;

    return false;
}

bool BattleEngine::searchForUnit(Unit *target, bool red) {
    if(!red){
        for(int i = 0 ; i < redUnits->size() ; i++) {
            if(target == redUnits->value(i))
                return true;
        }
    }
    else{
        for(int i = 0 ; i < blueUnits->size() ; i++) {
            if(target == blueUnits->value(i))
                return true;
        }
    }
    return false;
}

void BattleEngine::spawnUnit(QString defType, QString atkType, int level, bool isRed) {

    if(!isInSession)
        return;

    //if(!spriteForTypeExists(isRed,defType,atkType,level))
    //    loadSpritesFor(isRed,defType,atkType,level);

    Unit* newUnit = NULL;
    int color = 1;
    int def = 0;
    int atk = 0;

    if(isRed) {
        color = 0;
        redPop++;
        if(playerIsRed)
            unitsProduced++;
    }
    else {
        bluePop++;
        if(!playerIsRed)
            unitsProduced++;
    }

    if(playerIsRed)
        ui->population->setText(QString::number(redPop).append("/").append(QString::number(redPopCap)));
    else
        ui->population->setText(QString::number(bluePop).append("/").append(QString::number(bluePopCap)));


    if(!(atkType.compare("AA")))
        atk = 0;
    else if(!(atkType.compare("AI")))
        atk = 1;
    else if(!(atkType.compare("AT")))
        atk = 2;

    if(!(defType.compare("Air"))) {
        def = 0;
        if(!(atkType.compare("AA"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(true,isRed,50,300,110,200,240,169,68,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(true,isRed,80,600,110,200,240,236,118,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(true,isRed,140,1200,110,200,240,235,89,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else if(!(atkType.compare("AI"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(true,isRed,10,300,100,140,120,184,65,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(true,isRed,20,600,100,140,120,189,91,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(true,isRed,40,1200,100,140,120,163,93,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else if(!(atkType.compare("AT"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(true,isRed,30,600,75,235,200,157,105,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(true,isRed,50,1200,75,235,200,242,126,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(true,isRed,90,2400,75,235,200,224,178,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else
            ; //invalid attack type
    }
    else if(!(defType.compare("Infantry"))) {
        def = 1;
        if(!(atkType.compare("AI"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(false,isRed,12,50,35,160,90,31,31,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(false,isRed,24,100,35,160,90,31,31,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(false,isRed,48,200,35,160,90,31,31,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else if(!(atkType.compare("AT"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(false,isRed,60,100,27,180,900,31,31,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(false,isRed,120,200,27,180,900,31,31,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(false,isRed,240,400,27,180,900,31,31,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else
            ; //invalid attack type
    }
    else if(!(defType.compare("Vehicle"))) {
        def = 2;
        if(!(atkType.compare("AA"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(false,isRed,40,400,55,190,240,90,61,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(false,isRed,80,800,55,190,240,140,95,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(false,isRed,160,1600,55,190,240,162,121,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else if(!(atkType.compare("AI"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(false,isRed,30,200,65,200,120,37,37,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(false,isRed,50,400,65,200,120,110,50,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(false,isRed,90,800,65,200,120,209,77,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else if(!(atkType.compare("AT"))) {
            switch(level) {
                case 1:
                    newUnit = new Unit(false,isRed,160,500,45,240,1100,125,53,100,atkType,defType,this,ui,level);
                    break;
                case 2:
                    newUnit = new Unit(false,isRed,320,1000,45,240,1100,209,79,100,atkType,defType,this,ui,level);
                    break;
                case 3:
                    newUnit = new Unit(false,isRed,640,2000,45,240,1100,238,141,100,atkType,defType,this,ui,level);
                    break;
                default:
                    break; //invalid level
            }
        }
        else
            ; //invalid attack type
    }
    else
        ; //invalid defType


    if(isRed && newUnit != NULL)
        redUnits->append(newUnit);
    else if(newUnit != NULL)
        blueUnits->append(newUnit);
    else
        //qDebug("NULL POINTER EXCEPTION")
        ;

    if(newUnit != NULL) {
        newUnit->buildSpriteBase(unitSpriteBase[color][def][atk][level - 1][0],unitSpriteBase[color][def][atk][level - 1][1],unitSpriteBase[color][def][atk][level - 1][2]);
        newUnit->wakeUnit();
    }

    latestUnit = newUnit;
}

void BattleEngine::spawnBuilding(QString type, int slot, int isRed) {

    if(!(thereExistsThisTypeOfBlg(isRed,type,1)))
        loadSpritesForBlg(isRed,type,1);

    if((isRed && playerIsRed) || (!isRed && !playerIsRed))
        disengageSelectButton();

    if(isRed && redBlg[slot-1] != NULL) {
        cleaner->stop();
        if(!type.compare("Empty"))
            createCombatEffect(redBlg[slot-1]->getDisplayLabel()->x() + redBlg[slot-1]->getDisplayLabel()->width() / 2,true,ui->leftBaseArea);

        delete redBlg[slot-1];
        redBlg[slot-1] = NULL;
        cleaner->start(1);
    }
    else if(!isRed && blueBlg[slot-1] != NULL) {
        cleaner->stop();
        if(!type.compare("Empty"))
            createCombatEffect(blueBlg[slot-1]->getDisplayLabel()->x() + blueBlg[slot-1]->getDisplayLabel()->width() / 2,true,ui->rightBaseArea);

        delete blueBlg[slot-1];
        blueBlg[slot-1] = NULL;
        cleaner->start(1);
    }

    int color = 1;

    if(isRed)
        color = 0;

    if(type.compare("Empty") && type.compare("CommandCenter")) {
        if(isRed && playerIsRed)
            blgProduced++;
        else if(!isRed && !playerIsRed)
            blgProduced++;
    }

    QString slotIndicator = determineSlotNo(slot);

    QString temp;
    if(!(type.compare("CommandCenter"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(blgSpriteBase[color][0][0][1],blgSpriteBase[color][0][0][0],"Faction Capitol (LV1)","Vital structure for all factions.",isRed,slot,this,ui,type,1000);
            temp = "upgrade red ";
            temp.append(slotIndicator);
            redBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Capitol to next level",temp,900,300);
            redBlg[slot-1]->addCmd(cmdIconBase[1][9],cmdIconBase[0][9],"Artillery Strike (LV1)","Barrages the enemy front with an artillery strike.","power artillery",1000,200);
            redBlg[slot-1]->getCommand("power artillery")->setCountdownMAX(3000);
            if(playerIsRed) {
                switch(playerType) {
                    case 'm':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][10],cmdIconBase[0][10],"Blitzkreig (LV1)","Increases all your existing units' attack by 20%.","power blitz",500,150);
                        redBlg[slot-1]->getCommand("power blitz")->setCountdownMAX(10000);
                        break;
                    case 'e':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][11],cmdIconBase[0][11],"Economic Boom (LV1)","Increases economic production by 20%.","power ecoBoom",500,150);
                        redBlg[slot-1]->getCommand("power ecoBoom")->setCountdownMAX(10000);
                        break;
                    case 's':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][12],cmdIconBase[0][12],"Mass Propaganda (LV1)","Creates a mass of LV1 infantry units for your side.","power revolt",500,150);
                        redBlg[slot-1]->getCommand("power revolt")->setCountdownMAX(10000);
                        break;
                    case 't':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][13],cmdIconBase[0][13],"Orbital Strike (LV1)","Deals 300 damage to all units in the battlefield.","power laser",1300,900);
                        redBlg[slot-1]->getCommand("power laser")->setCountdownMAX(10000);
                        break;
                    default:
                        break;
                }
            }
            else {
                switch(aiType) {
                    case 'm':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][10],cmdIconBase[0][10],"Blitzkreig (LV1)","Increases all your existing units' attack by 20%.","power blitz",500,150);
                        redBlg[slot-1]->getCommand("power blitz")->setCountdownMAX(10000);
                        break;
                    case 'e':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][11],cmdIconBase[0][11],"Economic Boom (LV1)","Increases economic production by 20%.","power ecoBoom",500,150);
                        redBlg[slot-1]->getCommand("power ecoBoom")->setCountdownMAX(10000);
                        break;
                    case 's':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][12],cmdIconBase[0][12],"Mass Propaganda (LV1)","Creates a mass of LV1 infantry units for your side.","power revolt",500,150);
                        redBlg[slot-1]->getCommand("power revolt")->setCountdownMAX(10000);
                        break;
                    case 't':
                        redBlg[slot-1]->addCmd(cmdIconBase[1][13],cmdIconBase[0][13],"Orbital Strike (LV1)","Deals 300 damage to all units in the battlefield.","power laser",1300,900);
                        redBlg[slot-1]->getCommand("power laser")->setCountdownMAX(10000);
                        break;
                    default:
                        break;
                }
            }
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(blgSpriteBase[color][0][0][1],blgSpriteBase[color][0][0][0],"Faction Capitol (LV1)","Vital structure for all factions.",isRed,slot,this,ui,type,1000);
            temp = "upgrade blue ";
            temp.append(slotIndicator);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Capitol to next level",temp,900,300);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][9],cmdIconBase[0][9],"Artillery Strike (LV1)","Barrages the enemy front with an artillery strike.","power artillery",1000,200);
            blueBlg[slot-1]->getCommand("power artillery")->setCountdownMAX(3000);
            if(!playerIsRed) {
                switch(playerType) {
                    case 'm':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][10],cmdIconBase[0][10],"Blitzkreig (LV1)","Increases all your existing units' attack by 20%.","power blitz",500,150);
                        blueBlg[slot-1]->getCommand("power blitz")->setCountdownMAX(10000);
                        break;
                    case 'e':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][11],cmdIconBase[0][11],"Economic Boom (LV1)","Increases economic production by 20%.","power ecoBoom",500,150);
                        blueBlg[slot-1]->getCommand("power ecoBoom")->setCountdownMAX(10000);
                        break;
                    case 's':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][12],cmdIconBase[0][12],"Mass Propaganda (LV1)","Creates a mass of LV1 infantry units for your side.","power revolt",500,150);
                        blueBlg[slot-1]->getCommand("power revolt")->setCountdownMAX(10000);
                        break;
                    case 't':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][13],cmdIconBase[0][13],"Orbital Strike (LV1)","Deals 300 damage to all units in the battlefield.","power laser",1300,500);
                        blueBlg[slot-1]->getCommand("power laser")->setCountdownMAX(10000);
                        break;
                    default:
                        break;
                }
            }
            else {
                switch(aiType) {
                    case 'm':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][10],cmdIconBase[0][10],"Blitzkreig (LV1)","Increases all your existing units' attack by 20%.","power blitz",500,150);
                        blueBlg[slot-1]->getCommand("power blitz")->setCountdownMAX(10000);
                        break;
                    case 'e':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][11],cmdIconBase[0][11],"Economic Boom (LV1)","Increases economic production by 20%.","power ecoBoom",500,150);
                        blueBlg[slot-1]->getCommand("power ecoBoom")->setCountdownMAX(10000);
                        break;
                    case 's':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][12],cmdIconBase[0][12],"Mass Propaganda (LV1)","Creates a mass of LV1 infantry units for your side.","power revolt",500,150);
                        blueBlg[slot-1]->getCommand("power revolt")->setCountdownMAX(10000);
                        break;
                    case 't':
                        blueBlg[slot-1]->addCmd(cmdIconBase[1][13],cmdIconBase[0][13],"Orbital Strike (LV1)","Deals 300 damage to all units in the battlefield.","power laser",1300,500);
                        blueBlg[slot-1]->getCommand("power laser")->setCountdownMAX(10000);
                        break;
                    default:
                        break;
                }
            }
        }
    }
    else if(!(type.compare("Barracks"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(blgSpriteBase[color][1][0][1],blgSpriteBase[color][1][0][0],"Training Camp (LV1)","Produces LV1 infantry units.",isRed,slot,this,ui,type,500);
            redBlg[slot-1]->addCmd(unitIconBase[1][9],unitIconBase[0][9],"Rifleman (LV1)","Standard infantry unit for the most basic of armies.","spawn unit inf AI lv1 red");
            redBlg[slot-1]->addCmd(unitIconBase[1][12],unitIconBase[0][12],"RPG Trooper (LV1)","Standard anti-tank infantry unit for the most basic\nof armies.","spawn unit inf AT lv1 red");
            redBlg[slot-1]->getCommand("spawn unit inf AI lv1 red")->setCostReq(50);
            redBlg[slot-1]->getCommand("spawn unit inf AT lv1 red")->setCostReq(100);
            redBlg[slot-1]->getCommand("spawn unit inf AI lv1 red")->setCountdownMAX(400);
            redBlg[slot-1]->getCommand("spawn unit inf AT lv1 red")->setCountdownMAX(800);
            temp = "upgrade red ";
            temp = "upgrade red ";
            temp.append(slotIndicator);
            redBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Barracks (LV1) to an Army Barracks (LV2).\nUnlocks higher level units.",temp,600,200);
            redBlg[slot-1]->setSellPrice(300);
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(blgSpriteBase[color][1][0][1],blgSpriteBase[color][1][0][0],"Training Camp (LV1)","Produces LV1 infantry units.",isRed,slot,this,ui,type,500);
            blueBlg[slot-1]->addCmd(unitIconBase[1][9],unitIconBase[0][9],"Rifleman (LV1)","Standard infantry unit for the most basic of armies.","spawn unit inf AI lv1 blue");
            blueBlg[slot-1]->addCmd(unitIconBase[1][12],unitIconBase[0][12],"RPG Trooper (LV1)","Standard anti-tank infantry unit for the most basic\nof armies.","spawn unit inf AT lv1 blue");
            blueBlg[slot-1]->getCommand("spawn unit inf AI lv1 blue")->setCostReq(50);
            blueBlg[slot-1]->getCommand("spawn unit inf AT lv1 blue")->setCostReq(100);
            blueBlg[slot-1]->getCommand("spawn unit inf AI lv1 blue")->setCountdownMAX(400);
            blueBlg[slot-1]->getCommand("spawn unit inf AT lv1 blue")->setCountdownMAX(800);
            temp = "upgrade blue ";
            temp.append(slotIndicator);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Barracks (LV1) to an Army Barracks (LV2).\nUnlocks higher level units.",temp,600,200);
            blueBlg[slot-1]->setSellPrice(300);
        }
    }
    else if(!(type.compare("Warfactory"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(blgSpriteBase[color][2][0][1],blgSpriteBase[color][2][0][0],"Vehicle Workshop (LV1)","Produces LV1 vehicle units.",isRed,slot,this,ui,type,1500);
            redBlg[slot-1]->addCmd(unitIconBase[1][21],unitIconBase[0][21],"M4 Sherman Tank (LV1)","An antiquated battle tank\nutilized by under-developed factions.","spawn unit veh AT lv1 red");
            redBlg[slot-1]->addCmd(unitIconBase[1][15],unitIconBase[0][15],"SdKfz 251 AA Half-Track (LV1)","An antiquated anti-air vehicle\nutilized by under-developed factions.","spawn unit veh AA lv1 red");
            redBlg[slot-1]->addCmd(unitIconBase[1][18],unitIconBase[0][18],"Jeep (LV1)","An antiquated anti-infantry vehicle\nutilized by under-developed factions.","spawn unit veh AI lv1 red");
            redBlg[slot-1]->getCommand("spawn unit veh AA lv1 red")->setCostReq(400);
            redBlg[slot-1]->getCommand("spawn unit veh AI lv1 red")->setCostReq(200);
            redBlg[slot-1]->getCommand("spawn unit veh AT lv1 red")->setCostReq(500);
            redBlg[slot-1]->getCommand("spawn unit veh AA lv1 red")->setCountdownMAX(900);
            redBlg[slot-1]->getCommand("spawn unit veh AI lv1 red")->setCountdownMAX(1000);
            redBlg[slot-1]->getCommand("spawn unit veh AT lv1 red")->setCountdownMAX(1100);
            temp = "upgrade red ";
            temp.append(slotIndicator);
            redBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Vehicle Workshop (LV1) to a\nModern Warfactory (LV2). Unlocks higher level units.",temp,1800,600);
            redBlg[slot-1]->setSellPrice(900);
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(blgSpriteBase[color][2][0][1],blgSpriteBase[color][2][0][0],"Vehicle Workshop (LV1)","Produces LV1 vehicle units.",isRed,slot,this,ui,type,1500);
            blueBlg[slot-1]->addCmd(unitIconBase[1][21],unitIconBase[0][21],"M4 Sherman Tank (LV1)","An antiquated battle tank\nutilized by under-developed factions.","spawn unit veh AT lv1 blue");
            blueBlg[slot-1]->addCmd(unitIconBase[1][15],unitIconBase[0][15],"SdKfz 251 AA Half-Track (LV1)","An antiquated anti-air vehicle\nutilized by under-developed factions.","spawn unit veh AA lv1 blue");
            blueBlg[slot-1]->addCmd(unitIconBase[1][18],unitIconBase[0][18],"Jeep (LV1)","An antiquated anti-infantry vehicle\nutilized by under-developed factions.","spawn unit veh AI lv1 blue");
            blueBlg[slot-1]->getCommand("spawn unit veh AA lv1 blue")->setCostReq(400);
            blueBlg[slot-1]->getCommand("spawn unit veh AI lv1 blue")->setCostReq(200);
            blueBlg[slot-1]->getCommand("spawn unit veh AT lv1 blue")->setCostReq(500);
            blueBlg[slot-1]->getCommand("spawn unit veh AA lv1 blue")->setCountdownMAX(900);
            blueBlg[slot-1]->getCommand("spawn unit veh AI lv1 blue")->setCountdownMAX(1000);
            blueBlg[slot-1]->getCommand("spawn unit veh AT lv1 blue")->setCountdownMAX(1100);
            temp = "upgrade blue ";
            temp.append(slotIndicator);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Vehicle Workshop (LV1) to a\nModern Warfactory (LV2). Unlocks higher level units.",temp,1800,600);
            blueBlg[slot-1]->setSellPrice(900);
        }
    }
    else if(!(type.compare("Airfield"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(blgSpriteBase[color][3][0][1],blgSpriteBase[color][3][0][0],"Airstrip (LV1)","Produces LV1 air units.",isRed,slot,this,ui,type,1000);
            redBlg[slot-1]->addCmd(unitIconBase[1][6],unitIconBase[0][6],"A-24 Banshee (LV1)","An antiquated bomber aircraft\nutilized by under-developed factions.","spawn unit air AT lv1 red");
            redBlg[slot-1]->addCmd(unitIconBase[1][0],unitIconBase[0][0],"Bell XP-77 (LV1)","An antiquated lightweight fighter aircraft\nutilized by under-developed factions.","spawn unit air AA lv1 red");
            redBlg[slot-1]->addCmd(unitIconBase[1][3],unitIconBase[0][3],"DH-4B Biplane (LV1)","An antiquated anti-infantry aircraft\nutilized by under-developed factions.","spawn unit air AI lv1 red");
            redBlg[slot-1]->getCommand("spawn unit air AA lv1 red")->setCostReq(300);
            redBlg[slot-1]->getCommand("spawn unit air AI lv1 red")->setCostReq(300);
            redBlg[slot-1]->getCommand("spawn unit air AT lv1 red")->setCostReq(600);
            redBlg[slot-1]->getCommand("spawn unit air AA lv1 red")->setCountdownMAX(800);
            redBlg[slot-1]->getCommand("spawn unit air AI lv1 red")->setCountdownMAX(900);
            redBlg[slot-1]->getCommand("spawn unit air AT lv1 red")->setCountdownMAX(1000);
            temp = "upgrade red ";
            temp.append(slotIndicator);
            redBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Airstrip (LV1) to an Airfield (LV2).\nUnlocks higher level units.",temp,1400,500);
            redBlg[slot-1]->setSellPrice(700);
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(blgSpriteBase[color][3][0][1],blgSpriteBase[color][3][0][0],"Airstrip (LV1)","Produces LV1 air units.",isRed,slot,this,ui,type,1000);
            blueBlg[slot-1]->addCmd(unitIconBase[1][6],unitIconBase[0][6],"A-24 Banshee (LV1)","An antiquated bomber aircraft\nutilized by under-developed factions.","spawn unit air AT lv1 blue");
            blueBlg[slot-1]->addCmd(unitIconBase[1][0],unitIconBase[0][0],"Bell XP-77 (LV1)","An antiquated lightweight fighter aircraft\nutilized by under-developed factions..","spawn unit air AA lv1 blue");
            blueBlg[slot-1]->addCmd(unitIconBase[1][3],unitIconBase[0][3],"DH-4B Biplane (LV1)","An antiquated anti-infantry aircraft\nutilized by under-developed factions.","spawn unit air AI lv1 blue");
            blueBlg[slot-1]->getCommand("spawn unit air AA lv1 blue")->setCostReq(300);
            blueBlg[slot-1]->getCommand("spawn unit air AI lv1 blue")->setCostReq(300);
            blueBlg[slot-1]->getCommand("spawn unit air AT lv1 blue")->setCostReq(600);
            blueBlg[slot-1]->getCommand("spawn unit air AA lv1 blue")->setCountdownMAX(800);
            blueBlg[slot-1]->getCommand("spawn unit air AI lv1 blue")->setCountdownMAX(900);
            blueBlg[slot-1]->getCommand("spawn unit air AT lv1 blue")->setCountdownMAX(1000);
            temp = "upgrade blue ";
            temp.append(slotIndicator);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Airstrip (LV1) to an Airfield (LV2).\nUnlocks higher level units.",temp,1400,500);
            blueBlg[slot-1]->setSellPrice(700);
        }
    }
    else if(!(type.compare("EconomicC"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(blgSpriteBase[color][4][0][1],blgSpriteBase[color][4][0][0],"Agricultural Industry (LV1)","Low-income economic center.\nGenerates funds every resource round.",isRed,slot,this,ui,type,300);
            temp = "upgrade red ";
            temp.append(slotIndicator);
            redBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Agricultural Industry (LV1) to a Small\nManufactory (LV2).",temp,400,150);
            redBlg[slot-1]->setSellPrice(150);
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(blgSpriteBase[color][4][0][1],blgSpriteBase[color][4][0][0],"Agricultural Industry (LV1)","Low-income economic center.\nGenerates funds every resource round.",isRed,slot,this,ui,type,300);
            temp = "upgrade blue ";
            temp.append(slotIndicator);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades Agricultural Industry (LV1) to a Small\nManufactory (LV2).",temp,400,150);
            blueBlg[slot-1]->setSellPrice(150);
        }
    }
    else if(!(type.compare("TechnologyC"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(blgSpriteBase[color][5][0][1],blgSpriteBase[color][5][0][0],"University (LV1)","Basic research institution.\nGenerates technology every resource round.",isRed,slot,this,ui,type,800);
            temp = "upgrade red ";
            temp.append(slotIndicator);
            redBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades University (LV1) to a Research Facility (LV2).",temp,1500,500);
            redBlg[slot-1]->setSellPrice(150);
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(blgSpriteBase[color][5][0][1],blgSpriteBase[color][5][0][0],"University (LV1)","Basic research institution.\nGenerates technology every resource round.",isRed,slot,this,ui,type,800);
            temp = "upgrade blue ";
            temp.append(slotIndicator);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][6],cmdIconBase[0][6],"Upgrade","Upgrades University (LV1) to a Research Facility (LV2).",temp,1500,500);
            blueBlg[slot-1]->setSellPrice(150);
        }
    }
    else if(!(type.compare("Empty"))) {
        if(isRed && redBlg[slot-1] == NULL) {
            redBlg[slot-1] = new Building(NULL,NULL,"Empty Space","You can construct buildings here.",isRed,slot,this,ui,type);
            redBlg[slot-1]->addCmd(cmdIconBase[1][1],cmdIconBase[0][1],"Training Camp (LV1)","Produces LV1 infantry units.","spawn building barracks",300,100);
            redBlg[slot-1]->addCmd(cmdIconBase[1][2],cmdIconBase[0][2],"Vehicle Workshop (LV1)","Produces LV1 vehicle units.","spawn building warfactory",1800,600);
            redBlg[slot-1]->addCmd(cmdIconBase[1][0],cmdIconBase[0][0],"Airstrip (LV1)","Produces LV1 air units.","spawn building airfield",1400,500);
            redBlg[slot-1]->addCmd(cmdIconBase[1][3],cmdIconBase[0][3],"Agricultural Industry (LV1)","Low-income economic center.\nGenerates funds every resource round.","spawn building economic_center",300,100);
            redBlg[slot-1]->addCmd(cmdIconBase[1][4],cmdIconBase[0][4],"University (LV1)","Basic research institution.\nGenerates technology every resource round.","spawn building technology_center",300,100);
        }
        else if (!isRed && blueBlg[slot-1] == NULL) {
            blueBlg[slot-1] = new Building(NULL,NULL,"Empty Space","You can construct buildings here.",isRed,slot,this,ui,type);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][1],cmdIconBase[0][1],"Training Camp (LV1)","Produces LV1 infantry units.","spawn building barracks",300,100);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][2],cmdIconBase[0][2],"Vehicle Workshop (LV1)","Produces LV1 vehicle units.","spawn building warfactory",1800,600);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][0],cmdIconBase[0][0],"Airstrip (LV1)","Produces LV1 air units.","spawn building airfield",1400,500);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][3],cmdIconBase[0][3],"Agricultural Industry (LV1)","Low-income economic center.\nGenerates funds every resource round.","spawn building economic_center",300,100);
            blueBlg[slot-1]->addCmd(cmdIconBase[1][4],cmdIconBase[0][4],"University (LV1)","Basic research institution.\nGenerates technology every resource round.","spawn building technology_center",300,100);
        }
    }

    if(!type.compare("Empty"))
        return;

    if(isRed) {
        redBlg[slot-1]->addCmd(cmdIconBase[1][8],cmdIconBase[0][8],"Repair","Repair this building.","repair",0,0);
    }
    else {
        blueBlg[slot-1]->addCmd(cmdIconBase[1][8],cmdIconBase[0][8],"Repair","Repair this building.","repair",0,0);
    }

    if(!type.compare("CommandCenter"))
        return;

    if(isRed) {
        temp = "sell red ";
        temp.append(slotIndicator);
        redBlg[slot-1]->addCmd(cmdIconBase[1][7],cmdIconBase[0][7],"Sell","Sell this building.",temp,0,0);
    }
    else {
        temp = "sell blue ";
        temp.append(slotIndicator);
        blueBlg[slot-1]->addCmd(cmdIconBase[1][7],cmdIconBase[0][7],"Sell","Sell this building.",temp,0,0);
    }

}

void BattleEngine::deselectAllRedBuildings() {
    //Red Buildings
    for(int i = 0 ; i < 8 ; i++) {
        if(redBlg[i] != NULL)
            redBlg[i]->deselect();
    }
}

void BattleEngine::deselectAllBlueBuildings() {
    //Blue Buildings
    for(int i = 0 ; i < 8 ; i++) {
        if(blueBlg[i] != NULL)
            blueBlg[i]->deselect();
    }
}

void BattleEngine::economyRound() {
    int totalRedMoney = 0;
    int totalBlueMoney = 0;
    for(int i = 0 ; i < 8 ; i++) {
        if(redBlg[i] != NULL) {
            if(!redBlg[i]->getType().compare("EconomicC"))
                totalRedMoney += ecoProd[redBlg[i]->getLevel() - 1];
            else if(!redBlg[i]->getType().compare("CommandCenter"))
                totalRedMoney += 50 * redBlg[i]->getLevel();
            else
                ; //do nothing
        }

        if(blueBlg[i] != NULL) {
            if(!blueBlg[i]->getType().compare("EconomicC"))
                totalBlueMoney += ecoProd[blueBlg[i]->getLevel() - 1];
            else if(!blueBlg[i]->getType().compare("CommandCenter"))
                totalBlueMoney += 50 * blueBlg[i]->getLevel();
            else
                ; //do nothing
        }
    }

    if(redEcoBoom)
        totalRedMoney += totalRedMoney * ((((float)redBlg[7]->getLevel()) / 5.0));

    if(blueEcoBoom)
        totalBlueMoney += totalBlueMoney * ((((float)blueBlg[7]->getLevel()) / 5.0));

    redMoney += totalRedMoney;
    blueMoney += totalBlueMoney;

    if(playerIsRed)
        ui->money->setText(QString::number(redMoney));
    else
        ui->money->setText(QString::number(blueMoney));
}

void BattleEngine::technologyRound() {
    for(int i = 0 ; i < 8 ; i++) {
        if(redBlg[i] != NULL) {
            if(!redBlg[i]->getType().compare("TechnologyC"))
                redTech += techProd[redBlg[i]->getLevel() - 1];
            else if(!redBlg[i]->getType().compare("CommandCenter"))
                redTech += 15 * redBlg[i]->getLevel();
            else
                ; //do nothing
        }

        if(blueBlg[i] != NULL) {
            if(!blueBlg[i]->getType().compare("TechnologyC"))
                blueTech += techProd[blueBlg[i]->getLevel() - 1];
            else if(!blueBlg[i]->getType().compare("CommandCenter"))
                blueTech += 15 * blueBlg[i]->getLevel();
            else
                ; //do nothing
        }
    }

    if(playerIsRed)
        ui->techPoints->setText(QString::number(redTech));
    else
        ui->techPoints->setText(QString::number(blueTech));
}

void BattleEngine::reprintBlgData() {
    //qDebug("reprintData");
    Building* sender = ((Building*)(QObject::sender()));
    if(highlighted == sender->getDiplayButton()) {
        QString displayText = "";
        displayText = sender->getName();
        displayText.append("\nHitpoints: ").append(QString::number(sender->getHitpoints())).append("/").append(QString::number(sender->getHpMAX())).append("\n");
        displayText.append(sender->getDesc());
        ui->cmdLabel->setText(displayText);
    }
}

void BattleEngine::damageFrontMostBuilding(bool red, int amt) {
    for(int i = 0 ; i < 8 ; i++) {
        if(red) {
            if(redBlg[i] == NULL) {

            }
            else if(redBlg[i]->getType().compare("Empty")) {
                redBlg[i]->setHitpoints(redBlg[i]->getHitpoints() - amt);
//                if(highlightedCmd == NULL && highlighted == redBlg[i]->getDiplayButton()) {
//                    QString displayText = redBlg[i]->getName();
//                    displayText.append("\nHitpoints: ").append(QString::number(redBlg[i]->getHitpoints())).append("/").append(QString::number(redBlg[i]->getHpMAX())).append("\n");
//                    displayText.append(redBlg[i]->getDesc());
//                    ui->cmdLabel->setText(displayText);
//                }

                return;
            }
            else {

            }
            if(playerIsRed) {
                if(alertSound->state() == Phonon::PlayingState)
                    alertSound->stop();

                alertSound->play();
            }
        }
        else {
            if(blueBlg[i] == NULL) {

            }
            else if(blueBlg[i]->getType().compare("Empty")) {
                blueBlg[i]->setHitpoints(blueBlg[i]->getHitpoints() - amt);
//                if(highlightedCmd == NULL && highlighted == blueBlg[i]->getDiplayButton()) {
//                    QString displayText = blueBlg[i]->getName();
//                    displayText.append("\nHitpoints: ").append(QString::number(blueBlg[i]->getHitpoints())).append("/").append(QString::number(blueBlg[i]->getHpMAX())).append("\n");
//                    displayText.append(blueBlg[i]->getDesc());
//                    ui->cmdLabel->setText(displayText);
//                }

                return;
            }
            else {

            }
            if(!playerIsRed) {
                if(alertSound->state() == Phonon::PlayingState)
                    alertSound->stop();

                alertSound->play();
            }
        }
    }
}

void BattleEngine::cleanUp() {
    if(!cleanSession && isInSession) {
        cleanSession = true;
        bool blueFlag = true;
        bool redFlag = true;
        bool effectFlag = true;
        Unit* deleteThis = NULL;
        Effect* deleteEffect = NULL;
        QString atkType;
        QString defType;
        int level;

        if(highlightedCmd != NULL) {
            QString cmdDesc = highlightedCmd->getName();
            if(cmdDesc.compare("Sell") && cmdDesc.compare("Repair"))
                cmdDesc.append("\nPrice: ").append(QString::number(highlightedCmd->getCostReq())).append(" Tech: ").append(QString::number(highlightedCmd->getTechReq())).append(" Cooldown: ").append(QString::number(highlightedCmd->getCountdown())).append("\n");
            else
                cmdDesc.append("\n\n");

            cmdDesc.append(highlightedCmd->getDesc());
            ui->cmdLabel->setText(cmdDesc);
        }

        while(redFlag) {
            redFlag = false;
            for(int i = 0 ; i < redUnits->size() && !redFlag ; i++){
                if((redUnits->value(i)->getHP() <= 0 || redUnits->value(i)->xCoord > ui->battleField->width()) && !redFlag) {
                    if(redUnits->value(i)->xCoord > ui->battleField->width()) {
                        damageFrontMostBuilding(false,redUnits->value(i)->getHP() + redUnits->value(i)->damage);
                    }
                    //qDebug("flagRed");
                    deleteThis = redUnits->value(i);
                    deleteThis->freeze();

                    atkType = deleteThis->getAttackType();
                    defType = deleteThis->defenseType;
                    level = deleteThis->level;

                    redUnits->removeAt(i);
                    if(deleteThis != NULL) {
                        delete deleteThis;
                    }
                    deleteThis = NULL;
                    redPop--;

                    if(playerIsRed) {
                        ui->population->setText(QString::number(redPop).append("/").append(QString::number(redPopCap)));
                        deaths++;
                    }
                    else
                        kills++;
                    //if(!thereExistsThisTypeOfUnit(true,defType,atkType,level))
                    //    destroySpritesFor(true,defType,atkType,level);

                    redFlag = true;

                    unfreezeAllUnits();

                    break;
                }
            }
        }

        while(blueFlag) {
            blueFlag = false;
            for(int i = 0 ; i < blueUnits->size() && !blueFlag; i++){
                if((blueUnits->value(i)->getHP() <= 0 || blueUnits->value(i)->xCoord + blueUnits->value(i)->width < 0) && !blueFlag) {
                    if(blueUnits->value(i)->xCoord + blueUnits->value(i)->width < 0)
                        damageFrontMostBuilding(true,blueUnits->value(i)->getHP() + blueUnits->value(i)->damage);
                    //qDebug("flagBlue");
                    deleteThis = blueUnits->value(i);
                    deleteThis->freeze();

                    atkType = deleteThis->getAttackType();
                    defType = deleteThis->defenseType;
                    level = deleteThis->level;

                    blueUnits->removeAt(i);
                    if(deleteThis != NULL) {
                        delete deleteThis;
                    }
                    deleteThis = NULL;
                    bluePop--;
                    if(!playerIsRed) {
                        ui->population->setText(QString::number(bluePop).append("/").append(QString::number(bluePopCap)));
                        deaths++;
                    }
                    else
                        kills++;
                    //if(!thereExistsThisTypeOfUnit(false,defType,atkType,level))
                    //    destroySpritesFor(false,defType,atkType,level);

                    blueFlag = true;

                    unfreezeAllUnits();

                    break;
                }
            }
        }

        //unfreezeAllUnits();

        while(effectFlag) {
            effectFlag = false;
            for(int i = 0 ; i < effectList->size() && !effectFlag; i++){
                if(effectList->value(i)->isFinished() && !effectFlag) {
                    deleteEffect = effectList->value(i);
                    effectList->removeAt(i);

                    if(deleteEffect != NULL) {
                        delete deleteEffect;
                    }
                    deleteEffect = NULL;
                    effectFlag = true;
                    //qDebug("effectFlag");
                    break;
                }
            }
        }

        QString tempType;
        int tempLv;
        for(int i = 0 ; i < 8 ; i++) {
            if(redBlg[i] != NULL) {
                if(redBlg[i]->getHitpoints() <= 0 && redBlg[i]->getType().compare("Empty")) {
                    if(playerIsRed)
                        blgLost++;
                    else
                        blgDestroyed++;

                    if(redBlg[i]->getType().contains("CommandCenter"))
                        redLose();

                    tempType = redBlg[i]->getType();
                    tempLv = redBlg[i]->getLevel();
                    spawnBuilding("Empty",i+1,true);
                    if(!thereExistsThisTypeOfBlg(true,tempType,tempLv))
                        destroySpritesForBlg(true,tempType,tempLv);
                }
            }
        }

        for(int i = 0 ; i < 8 ; i++) {
            if(blueBlg[i] != NULL) {
                if(blueBlg[i]->getHitpoints() <= 0 && blueBlg[i]->getType().compare("Empty")) {
                    if(!playerIsRed)
                        blgLost++;
                    else
                        blgDestroyed++;

                    if(blueBlg[i]->getType().contains("CommandCenter"))
                        blueLose();

                    tempType = blueBlg[i]->getType();
                    tempLv = blueBlg[i]->getLevel();
                    spawnBuilding("Empty",i+1,false);
                    if(!thereExistsThisTypeOfBlg(false,tempType,tempLv))
                        destroySpritesForBlg(false,tempType,tempLv);
                }
            }
        }

        int currentEcoProd = 0;
        int currentTechProd = 0;

        if(playerIsRed)
            for(int i = 0 ; i < 8 ; i++) {
                if(redBlg[i] != NULL) {
                    if(!redBlg[i]->getType().compare("EconomicC")){
                        currentEcoProd += ecoProd[redBlg[i]->getLevel() - 1];
                    }
                    else if(!redBlg[i]->getType().compare("TechnologyC"))
                        currentTechProd += techProd[redBlg[i]->getLevel() - 1];
                    else if(!redBlg[i]->getType().compare("CommandCenter")) {
                        currentEcoProd += 50 * redBlg[i]->getLevel();
                        currentTechProd += 15 * redBlg[i]->getLevel();
                    }
                    else
                        ; //do nothing
                }
            }
        else
            for(int i = 0 ; i < 8 ; i++) {
                if(blueBlg[i] != NULL) {
                    if(!blueBlg[i]->getType().compare("EconomicC")) {
                        currentEcoProd += ecoProd[blueBlg[i]->getLevel() - 1];
                    }
                    else if(!blueBlg[i]->getType().compare("TechnologyC"))
                        currentTechProd += techProd[blueBlg[i]->getLevel() - 1];
                    else if(!blueBlg[i]->getType().compare("CommandCenter")) {
                        currentEcoProd += 50 * blueBlg[i]->getLevel();
                        currentTechProd += 15 * blueBlg[i]->getLevel();
                    }
                    else
                        ; //do nothing
                }
            }

        if(playerIsRed && redEcoBoom) {
            currentEcoProd += currentEcoProd * ((((float)redBlg[7]->getLevel()) / 5.0));
        }
        else if(!playerIsRed && blueEcoBoom) {
            currentEcoProd += currentEcoProd * ((((float)blueBlg[7]->getLevel()) / 5.0));
        }

        ui->techProduction->setText(QString::number(currentTechProd));
        ui->moneyProduction->setText(QString::number(currentEcoProd));

        if(ui->battleFieldScroll->horizontalScrollBar()->value() <= ui->battleFieldScroll->horizontalScrollBar()->minimum()) {
            ui->battleFieldScroll->horizontalScrollBar()->setValue(ui->battleFieldScroll->horizontalScrollBar()->value() + 1);
            ui->leftBaseScroll->horizontalScrollBar()->setValue(ui->leftBaseScroll->horizontalScrollBar()->maximum() - 1);
            ui->cmd1->click();
        }
        else if(ui->battleFieldScroll->horizontalScrollBar()->value() >= ui->battleFieldScroll->horizontalScrollBar()->maximum()) {
            ui->battleFieldScroll->horizontalScrollBar()->setValue(ui->battleFieldScroll->horizontalScrollBar()->value() - 1);
            ui->rightBaseScroll->horizontalScrollBar()->setValue(ui->rightBaseScroll->horizontalScrollBar()->minimum() + 1);
            ui->cmd3->click();
        }
        else if(ui->leftBaseScroll->horizontalScrollBar()->value() >= ui->leftBaseScroll->horizontalScrollBar()->maximum()) {
            ui->leftBaseScroll->horizontalScrollBar()->setValue(ui->leftBaseScroll->horizontalScrollBar()->value() - 1);
            ui->battleFieldScroll->horizontalScrollBar()->setValue(ui->battleFieldScroll->horizontalScrollBar()->minimum() + 1);
            ui->cmd2->click();
        }
        else if(ui->rightBaseScroll->horizontalScrollBar()->value() <= ui->rightBaseScroll->horizontalScrollBar()->minimum()) {
            ui->rightBaseScroll->horizontalScrollBar()->setValue(ui->leftBaseScroll->horizontalScrollBar()->value() + 1);
            ui->battleFieldScroll->horizontalScrollBar()->setValue(ui->battleFieldScroll->horizontalScrollBar()->maximum() - 1);
            ui->cmd2->click();
        }

        cleanSession = false;
    }

    if(!isInSession) {
        qDebug("EXEME!");
        disengageSelectButton();
        destroyAllUnits();
        deleteAllEffects();

        selectButtonAnimator->stop();
        resourceRound->stop();
        AI->stopAI();

        redCrosshair = 0;
        blueCrosshair = 0;

        endRedLaser();
        endBlueLaser();

        redLaserIsInEffect = false;
        blueLaserIsInEffect = false;

        delete AI;
        AI = NULL;

        disengageHighlightedCMD();
        highlightedCmd = NULL;

        redEcoBoom = false;
        blueEcoBoom = false;

        cleanSession = false;

        latestUnit = NULL;

//        QString atkTp = "";
//        QString defTp = "";
//        for(int i = 0 ; i < 3 ; i++) {
//            switch(i) {
//                case 0:
//                    defTp = "Air";
//                    break;
//                case 1:
//                    defTp = "Infantry";
//                    break;
//                case 2:
//                    defTp = "Vehicle";
//                    break;
//            }
//            for(int j = 0 ; j < 3 ; j++) {
//                switch(j) {
//                    case 0:
//                        atkTp = "AA";
//                        break;
//                    case 1:
//                        atkTp = "AI";
//                        break;
//                    case 2:
//                        atkTp = "AT";
//                        break;
//                }
//                for(int k = 1 ; k <= 3 ; k++) {
//                    destroySpritesFor(true,defTp,atkTp,k);
//                    destroySpritesFor(false,defTp,atkTp,k);
//                }
//            }
//        }

        for(int i = 1 ; i <= 3 ; i++) {
            destroySpritesForBlg(true,"CommandCenter",i);
            destroySpritesForBlg(true,"Barracks",i);
            destroySpritesForBlg(true,"Warfactory",i);
            destroySpritesForBlg(true,"TechnologyC",i);
            destroySpritesForBlg(true,"EconomicC",i);
            destroySpritesForBlg(true,"EconomicC",i+3);
            destroySpritesForBlg(true,"Airfield",i);
            destroySpritesForBlg(false,"CommandCenter",i);
            destroySpritesForBlg(false,"Barracks",i);
            destroySpritesForBlg(false,"Warfactory",i);
            destroySpritesForBlg(false,"TechnologyC",i);
            destroySpritesForBlg(false,"EconomicC",i);
            destroySpritesForBlg(false,"EconomicC",i+3);
            destroySpritesForBlg(false,"Airfield",i);
        }

        delete redUnits;
        delete blueUnits;
        delete effectList;

        redUnits = NULL;
        blueUnits = NULL;
        effectList = NULL;
        cleaner->stop();
    }
}

QPoint* BattleEngine::vectorXY(int magnitude, int angle, int baseX, int baseY){
    return new QPoint(baseX + (magnitude * cos((double)angle * 0.0174532925)), baseY - (magnitude * sin((double)angle * 0.0174532925)));
}

void BattleEngine::spawnInfLv1() {
    //spawnUnit("Air","AI",1,true);
    //spawnUnit("Infantry","AT",3,false);
}

void BattleEngine::commandInterface(){
    Command* btn = highlightedCmd;

    if(highlightedCmd == NULL)
        return;

    if(((Building*)(btn->getParentBuilding()))->getFaction()) {
        if(btn->getCostReq() > redMoney) {
            return;
        }
    }
    else {
        if(btn->getCostReq() > blueMoney){
            return;
        }
    }

    if(((Building*)(btn->getParentBuilding()))->getFaction()) {
        if(btn->getTechReq() > redTech) {
            return;
        }
    }
    else {
        if(btn->getTechReq() > blueTech) {
            return;
        }
    }

    if(!(btn->isReady())) {
        return;
    }
    else {
        btn->executeCountdown();
        if(btn->getType().contains("spawn unit") && btn->getType().contains("red")) {
            if(redPop >= redPopCap)
                return;
            else {
                if(playerIsRed)
                    ui->population->setText(QString::number(redPop).append("/").append(QString::number(redPopCap)));
            }
        }
        else if(btn->getType().contains("spawn unit") && btn->getType().contains("blue")) {
            if(bluePop >= bluePopCap)
                return;
            else {
                if(!playerIsRed)
                    ui->population->setText(QString::number(bluePop).append("/").append(QString::number(bluePopCap)));
            }
        }
    }

    if(((Building*)(btn->getParentBuilding()))->getFaction()) {
        redMoney -= btn->getCostReq();
        redTech -= btn->getTechReq();
    }
    else {
        blueMoney -= btn->getCostReq();
        blueTech -= btn->getTechReq();
    }

    if(playerIsRed) {
        ui->money->setText(QString::number(redMoney));
        ui->techPoints->setText(QString::number(redTech));
    }
    else {
        ui->money->setText(QString::number(blueMoney));
        ui->techPoints->setText(QString::number(blueTech));
    }


    if(btn->getType().contains("spawn")){
        if(btn->getType().contains("unit")) {
            if(btn->getType().contains("air")) {
                if(btn->getType().contains("AA")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AA",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AA",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AA",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AA",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AA",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AA",3,false);
                    }
                    else
                        ; //invalid unit type
                }
                else if(btn->getType().contains("AI")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AI",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AI",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AI",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AI",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AI",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AI",3,false);
                    }
                    else
                        ; //invalid unit type
                }
                else if(btn->getType().contains("AT")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AT",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AT",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AT",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AT",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Air","AT",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Air","AT",3,false);
                    }
                    else
                        ; //invalid unit type

                }
                else
                    ; //invalid unit type
            }
            else if(btn->getType().contains("inf")) {
                if(btn->getType().contains("AI")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Infantry","AI",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Infantry","AI",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Infantry","AI",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Infantry","AI",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Infantry","AI",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Infantry","AI",3,false);
                    }
                    else
                        ; //invalid unit type
                }
                else if(btn->getType().contains("AT")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Infantry","AT",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Infantry","AT",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Infantry","AT",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Infantry","AT",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Infantry","AT",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Infantry","AT",3,false);
                    }
                    else
                        ; //invalid unit type

                }
                else
                    ; //invalid unit type

            }
            else if(btn->getType().contains("veh")) {
                if(btn->getType().contains("AA")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AA",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AA",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AA",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AA",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AA",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AA",3,false);
                    }
                    else
                        ; //invalid unit type
                }
                else if(btn->getType().contains("AI")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AI",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AI",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AI",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AI",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AI",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AI",3,false);
                    }
                    else
                        ; //invalid unit type
                }
                else if(btn->getType().contains("AT")) {
                    if(btn->getType().contains("lv1")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AT",1,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AT",1,false);
                    }
                    else if(btn->getType().contains("lv2")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AT",2,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AT",2,false);
                    }
                    else if(btn->getType().contains("lv3")) {
                        if(btn->getType().contains("red"))
                            spawnUnit("Vehicle","AT",3,true);
                        else if(btn->getType().contains("blue"))
                            spawnUnit("Vehicle","AT",3,false);
                    }
                    else
                        ; //invalid unit type

                }
                else
                    ; //invalid unit type
            }
            else
                ; //invalid unit type
        }
        else if(btn->getType().contains("building")) {
            ((Building*)(btn->getParentBuilding()))->hideCommands();

            for(int i = 0 ; i < 8 ; i++) {
                if(((Building*)(btn->getParentBuilding())) == redBlg[i] && !(redBlg[i]->getType().compare("Empty"))) {

                    if(btn->getType().contains("command_center"))
                        spawnBuilding("CommandCenter",i+1,true);
                    else if(btn->getType().contains("barracks"))
                        spawnBuilding("Barracks",i+1,true);
                    else if(btn->getType().contains("warfactory"))
                        spawnBuilding("Warfactory",i+1,true);
                    else if(btn->getType().contains("airfield"))
                        spawnBuilding("Airfield",i+1,true);
                    else if(btn->getType().contains("economic_center"))
                        spawnBuilding("EconomicC",i+1,true);
                    else if(btn->getType().contains("technology_center"))
                        spawnBuilding("TechnologyC",i+1,true);
                    else
                        ; //invalid building type

                    //delete deleteThis;

                    break;

                }
                else if(((Building*)(btn->getParentBuilding())) == blueBlg[i] && !(blueBlg[i]->getType().compare("Empty"))) {

                    if(btn->getType().contains("command_center"))
                        spawnBuilding("CommandCenter",i+1,false);
                    else if(btn->getType().contains("barracks"))
                        spawnBuilding("Barracks",i+1,false);
                    else if(btn->getType().contains("warfactory"))
                        spawnBuilding("Warfactory",i+1,false);
                    else if(btn->getType().contains("airfield"))
                        spawnBuilding("Airfield",i+1,false);
                    else if(btn->getType().contains("economic_center"))
                        spawnBuilding("EconomicC",i+1,false);
                    else if(btn->getType().contains("technology_center"))
                        spawnBuilding("TechnologyC",i+1,false);
                    else
                        ; //invalid building type

                    break;
                }
            }
        }
    }
    else if(btn->getType().contains("upgrade")) {
        Building* upgradeTarget = NULL;
        if(btn->getType().contains("red")) {
            if(btn->getType().contains("slot1")) {
                upgradeTarget = redBlg[0];
            }
            else if(btn->getType().contains("slot2")) {
                upgradeTarget = redBlg[1];
            }
            else if(btn->getType().contains("slot3")) {
                upgradeTarget = redBlg[2];
            }
            else if(btn->getType().contains("slot4")) {
                upgradeTarget = redBlg[3];
            }
            else if(btn->getType().contains("slot5")) {
                upgradeTarget = redBlg[4];
            }
            else if(btn->getType().contains("slot6")) {
                upgradeTarget = redBlg[5];
            }
            else if(btn->getType().contains("slot7")) {
                upgradeTarget = redBlg[6];
            }
            else if(btn->getType().contains("slot8")) {
                upgradeTarget = redBlg[7];
            }
            else
                ; //invalid slot

            if(upgradeTarget != NULL)
                upgradeTarget->promote();
        }
        else if(btn->getType().contains("blue")) {
            if(btn->getType().contains("slot1")) {
                upgradeTarget = blueBlg[0];
            }
            else if(btn->getType().contains("slot2")) {
                upgradeTarget = blueBlg[1];
            }
            else if(btn->getType().contains("slot3")) {
                upgradeTarget = blueBlg[2];
            }
            else if(btn->getType().contains("slot4")) {
                upgradeTarget = blueBlg[3];
            }
            else if(btn->getType().contains("slot5")) {
                upgradeTarget = blueBlg[4];
            }
            else if(btn->getType().contains("slot6")) {
                upgradeTarget = blueBlg[5];
            }
            else if(btn->getType().contains("slot7")) {
                upgradeTarget = blueBlg[6];
            }
            else if(btn->getType().contains("slot8")) {
                upgradeTarget = blueBlg[7];
            }
            else
                ; //invalid slot

            if(upgradeTarget != NULL)
                upgradeTarget->promote();
        }
        else
            ; //invalid building
    }
    else if(btn->getType().contains("sell")) {
        QString tempType = ((Building*)(btn->getParentBuilding()))->getType();
        int tempLv = ((Building*)(btn->getParentBuilding()))->getLevel();
        bool tempFact = ((Building*)(btn->getParentBuilding()))->getFaction();

        if(btn->getType().contains("red")) {
            if(btn->getType().contains("slot1")) {
                redMoney += redBlg[0]->getSellPrice();
                spawnBuilding("Empty",1,true);
            }
            else if(btn->getType().contains("slot2")) {
                redMoney += redBlg[1]->getSellPrice();
                spawnBuilding("Empty",2,true);
            }
            else if(btn->getType().contains("slot3")) {
                redMoney += redBlg[2]->getSellPrice();
                spawnBuilding("Empty",3,true);
            }
            else if(btn->getType().contains("slot4")) {
                redMoney += redBlg[3]->getSellPrice();
                spawnBuilding("Empty",4,true);
            }
            else if(btn->getType().contains("slot5")) {
                redMoney += redBlg[4]->getSellPrice();
                spawnBuilding("Empty",5,true);
            }
            else if(btn->getType().contains("slot6")) {
                redMoney += redBlg[5]->getSellPrice();
                spawnBuilding("Empty",6,true);
            }
            else if(btn->getType().contains("slot7")) {
                redMoney += redBlg[6]->getSellPrice();
                spawnBuilding("Empty",7,true);
            }
            else if(btn->getType().contains("slot8")) {
                redMoney += redBlg[7]->getSellPrice();
                spawnBuilding("Empty",8,true);
            }

            if(playerIsRed) {
                ui->money->setText(QString::number(redMoney));
            }
        }
        else if(btn->getType().contains("blue")) {
            if(btn->getType().contains("slot1")) {
                blueMoney += blueBlg[0]->getSellPrice();
                spawnBuilding("Empty",1,false);
            }
            else if(btn->getType().contains("slot2")) {
                blueMoney += blueBlg[1]->getSellPrice();
                spawnBuilding("Empty",2,false);
            }
            else if(btn->getType().contains("slot3")) {
                blueMoney += blueBlg[2]->getSellPrice();
                spawnBuilding("Empty",3,false);
            }
            else if(btn->getType().contains("slot4")) {
                blueMoney += blueBlg[3]->getSellPrice();
                spawnBuilding("Empty",4,false);
            }
            else if(btn->getType().contains("slot5")) {
                blueMoney += blueBlg[4]->getSellPrice();
                spawnBuilding("Empty",5,false);
            }
            else if(btn->getType().contains("slot6")) {
                blueMoney += blueBlg[5]->getSellPrice();
                spawnBuilding("Empty",6,false);
            }
            else if(btn->getType().contains("slot7")) {
                blueMoney += blueBlg[6]->getSellPrice();
                spawnBuilding("Empty",7,false);
            }
            else if(btn->getType().contains("slot8")) {
                blueMoney += blueBlg[7]->getSellPrice();
                spawnBuilding("Empty",8,false);
            }

            if(!playerIsRed) {
                ui->money->setText(QString::number(blueMoney));
            }

        }
        if(!thereExistsThisTypeOfBlg(tempFact,tempType,tempLv))
            destroySpritesForBlg(tempFact,tempType,tempLv);
    }
    else if(btn->getType().contains("repair")) {
        if(((Building*)(btn->getParentBuilding()))->getRed()) {
            redMoney -= ((Building*)(btn->getParentBuilding()))->getHpMAX() - ((Building*)(btn->getParentBuilding()))->getHitpoints();
            if(playerIsRed) {
                ui->money->setText(QString::number(redMoney));
            }
        }
        else {
            blueMoney -= ((Building*)(btn->getParentBuilding()))->getHpMAX() - ((Building*)(btn->getParentBuilding()))->getHitpoints();
            if(!playerIsRed) {
                ui->money->setText(QString::number(blueMoney));
            }
        }
        ((Building*)(btn->getParentBuilding()))->setHitpoints(((Building*)(btn->getParentBuilding()))->getHpMAX());
    }
    else if(btn->getType().contains("power")) {
        bool ownIsRed = ((Building*)(btn->getParentBuilding()))->getFaction();
        if(btn->getType().contains("artillery")) {
            artilleryStrike(ownIsRed);
        }
        else if(btn->getType().contains("blitz")) {
            if(ownIsRed) {
                for(int i = 0 ; i < redUnits->size() ; i++) {
                    redUnits->value(i)->increaseAttack(((int)(redUnits->value(i)->damage * ((((float)redBlg[7]->getLevel()) / 5.0)))));
                    qDebug(QString::number(((int)(redUnits->value(i)->damage * ((((float)redBlg[7]->getLevel()) / 5.0))))).toAscii());
                    redUnits->value(i)->speed *= 2;
                    redUnits->value(i)->reloadLimit /= 2;
                }
            }
            else {
                for(int i = 0 ; i < blueUnits->size() ; i++) {
                    blueUnits->value(i)->increaseAttack(((int)(blueUnits->value(i)->damage * ((((float)blueBlg[7]->getLevel()) / 5.0)))));
                    qDebug(QString::number(((int)(blueUnits->value(i)->damage * ((((float)blueBlg[7]->getLevel()) / 5.0))))).toAscii());
                    blueUnits->value(i)->speed *= 2;
                    blueUnits->value(i)->reloadLimit /= 2;
                }
            }
        }
        else if(btn->getType().contains("ecoBoom")) {
            if(ownIsRed) {
                redEcoBoom = true;
                QTimer::singleShot(25000,this,SLOT(stopEcoBoomRed()));
            }
            else {
                blueEcoBoom = true;
                QTimer::singleShot(25000,this,SLOT(stopEcoBoomBlue()));
            }
        }
        else if(btn->getType().contains("revolt")) {
            if(ownIsRed) {
                QTimer::singleShot(1000,this,SLOT(revoltRed()));
                QTimer::singleShot(2000,this,SLOT(revoltRed()));
                QTimer::singleShot(3000,this,SLOT(revoltRed()));
                QTimer::singleShot(4000,this,SLOT(revoltRed()));
                QTimer::singleShot(5000,this,SLOT(revoltRed()));
                QTimer::singleShot(6000,this,SLOT(revoltRed()));
                QTimer::singleShot(7000,this,SLOT(revoltRed()));
                QTimer::singleShot(8000,this,SLOT(revoltRed()));
            }
            else {
                QTimer::singleShot(1000,this,SLOT(revoltBlue()));
                QTimer::singleShot(2000,this,SLOT(revoltBlue()));
                QTimer::singleShot(3000,this,SLOT(revoltBlue()));
                QTimer::singleShot(4000,this,SLOT(revoltBlue()));
                QTimer::singleShot(5000,this,SLOT(revoltBlue()));
                QTimer::singleShot(6000,this,SLOT(revoltBlue()));
                QTimer::singleShot(7000,this,SLOT(revoltBlue()));
                QTimer::singleShot(8000,this,SLOT(revoltBlue()));
            }
        }
        else if(btn->getType().contains("laser")) {
            if(((Building*)(btn->getParentBuilding()))->getFaction()) {
                laser(true);
            }
            else {
                laser(false);
            }

        }
        else if(btn->getType().contains("nuke")) {

        }
    }
}

void BattleEngine::load1() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Setting Default Values\n"));

    kills = 0;
    deaths = 0;
    unitsProduced = 0;
    blgDestroyed = 0;
    blgLost = 0;
    blgProduced = 0;
    QTimer::singleShot(200,this,SLOT(load2()));
}

void BattleEngine::load2() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Assessing Battlefield Topography\n"));

    ui->battleFieldScroll->horizontalScrollBar()->setValue((ui->battleFieldScroll->horizontalScrollBar()->minimum() + ui->battleFieldScroll->horizontalScrollBar()->maximum())/2);
    ui->leftBaseScroll->horizontalScrollBar()->setValue((ui->leftBaseScroll->horizontalScrollBar()->minimum() + ui->leftBaseScroll->horizontalScrollBar()->maximum())/2);
    ui->rightBaseScroll->horizontalScrollBar()->setValue((ui->rightBaseScroll->horizontalScrollBar()->minimum() + ui->rightBaseScroll->horizontalScrollBar()->maximum())/2);

    ui->result->hide();

    isInSession = true;
    QTimer::singleShot(200,this,SLOT(load3()));
}

void BattleEngine::load3() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Allocating Resources\n"));

    redMoney = 1000000;
    redTech = 1000000;
    blueMoney = 1000000;
    blueTech = 1000000;

    redLaserTimer = NULL;
    blueLaserTimer = NULL;

    redEcoBoom = false;
    blueEcoBoom = false;

    redLaserIsInEffect = false;
    blueLaserIsInEffect = false;
    QTimer::singleShot(200,this,SLOT(load4()));
}

void BattleEngine::load4() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Initializing Command Interface\n"));

    ui->cmd1->setEnabled(true);
    ui->cmd2->setEnabled(true);
    ui->cmd3->setEnabled(true);
    ui->cmd4->setEnabled(true);
    ui->pauseButton->setEnabled(true);
    ui->money->setEnabled(true);
    ui->moneyProduction->setEnabled(true);
    ui->techPoints->setEnabled(true);
    ui->techProduction->setEnabled(true);
    ui->population->setEnabled(true);
    ui->cmdLabel->setEnabled(true);

    ui->moneyIcon->setEnabled(true);
    ui->moneyProdIcon->setEnabled(true);
    ui->techIcon->setEnabled(true);
    ui->techProdIcon->setEnabled(true);
    ui->popIcon->setEnabled(true);
    QTimer::singleShot(200,this,SLOT(load5()));
}

void BattleEngine::load5() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Analyzing Enemy Forces\n"));

    switch(randomNumber(1,4)) {
        case 1:
            aiType = 'm';
            break;
        case 2:
            aiType = 'e';
            break;
        case 3:
            aiType = 's';
            break;
        case 4:
            aiType = 't';
            break;
        default:
            break;
    }

    highlighted = NULL;

    highlightedCmd = NULL;

    cleanSession = false;
    QTimer::singleShot(200,this,SLOT(load6()));
}

void BattleEngine::load6() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Initializing Unit Tracking Interface\n"));

    redUnits = new QList <Unit*> ();
    blueUnits = new QList <Unit*> ();

    for(int i = 0 ; i < 8 ; i++) {
        redBlg[i] = NULL;
        blueBlg[i] = NULL;
    }

    effectList = new QList <Effect*> ();
    QTimer::singleShot(200,this,SLOT(load7()));
}

void BattleEngine::load7() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Searching For Suitable Build Site\n"));

    resourceRound->start(8000);
    spawnBuilding("Empty",1,true);
    spawnBuilding("Empty",1,false);
    spawnBuilding("Empty",2,true);
    spawnBuilding("Empty",2,false);
    spawnBuilding("Empty",3,true);
    spawnBuilding("Empty",3,false);
    spawnBuilding("Empty",4,true);
    spawnBuilding("Empty",4,false);
    spawnBuilding("Empty",5,true);
    spawnBuilding("Empty",5,false);
    spawnBuilding("Empty",6,true);
    spawnBuilding("Empty",6,false);
    spawnBuilding("Empty",7,true);
    spawnBuilding("Empty",7,false);
    spawnBuilding("CommandCenter",8,true);
    spawnBuilding("CommandCenter",8,false);
    QTimer::singleShot(200,this,SLOT(load8()));
}

void BattleEngine::load8() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Retrieving Battefield Visuals\n"));

    redPop = 0;
    redPopCap = 12;

    bluePop = 0;
    bluePopCap = 12;

    if(playerIsRed)
        ui->population->setText(QString::number(redPop).append("/").append(QString::number(redPopCap)));
    else
        ui->population->setText(QString::number(bluePop).append("/").append(QString::number(bluePopCap)));

    QTimer::singleShot(200,this,SLOT(load9()));
}

void BattleEngine::load9() {
    ui->loaderOutput->setText(ui->loaderOutput->text().append("Starting A.I. Engine\n"));

    cleaner->start(1);
    initializeAI();
    AI->startAI();
    emit startSession();
    QTimer::singleShot(200,this,SLOT(load10()));
}

void BattleEngine::load10() {
    ((MainClass*)(main))->screenTransition(4);

    ui->resumeGame->click();
}

void BattleEngine::startCombatSession() {
    QTimer::singleShot(200,this,SLOT(load1()));
}

void BattleEngine::commandSelect() {
    Command* btn = (Command*)QObject::sender();

    if(highlightedCmd != btn) {
        if(highlightedCmd != NULL)
            highlightedCmd->setIcon(*(highlightedCmd->getOffImage()));

        btn->setIcon(*(btn->getOnImage()));
        highlightedCmd = btn;
        QString cmdDesc = btn->getName();

        if(cmdDesc.compare("Sell") &&  cmdDesc.compare("Repair"))
            cmdDesc.append("\nPrice: ").append(QString::number(btn->getCostReq())).append(" Tech: ").append(QString::number(btn->getTechReq())).append(" Cooldown: ").append(QString::number(btn->getCountdown())).append("\n");
        else
            cmdDesc.append("\n\n");

        cmdDesc.append(btn->getDesc());
        ui->cmdLabel->setText(cmdDesc);
    }
    else {
        commandInterface();
    }
}

void BattleEngine::connectToInterface(Command *c) {
    connect(c,SIGNAL(clicked()),this,SLOT(commandSelect()));
}

void BattleEngine::createCombatEffect(int xCoord, bool isGnd, QWidget* widget) {
    if(effectList->size() > 5)
        return;
    int randNo = (rand() % 3);
    int x = xCoord;
    int y = 25;
    Effect* e = NULL;
    if(isGnd) {
        QList <QPixmap*>* sprite = effects[0][randNo];
        switch(randNo) {
            case 0:
                x-=60;
                break;
            case 1:
                x-=66;
                break;
            case 2:
                x-=61;
                break;
            default: //invalid case
                break;
        }

        e = new Effect(QRect(x,widget->geometry().height() - 167 + 2,177,167),sprite,120,false,widget,this);
        e->alignToGround();
    }
    else {
        QList <QPixmap*>* sprite = effects[1][randNo];
        switch(randNo) {
            case 0:
                x-=67;
                y-=55;
                break;
            case 1:
                x-=72;
                y-=52;
                break;
            case 2:
                x-=80;
                y-=56;
                break;
            default: //invalid case
                break;
        }
        e = new Effect(QRect(x,y,177,167),sprite,120,false,widget,this);
        e->alignToAir();
    }
    e->playAnimation();
    effectList->append(e);
}

void BattleEngine::endCombatSession() {
    ambientSound->stop();
    isInSession = false;
    deleteAllBuildings();
    emit endSession();
}

void BattleEngine::setPlayerSide(bool red) {
    playerIsRed = red;
}

void BattleEngine::setPlayerType(char type) {
    playerType = type;
}

void BattleEngine::setAIType(char type) {
    aiType = type;
}

void BattleEngine::setEnemyDiff(char diff) {
    enemyDiff = diff;
}

QString BattleEngine::determineSlotNo(int slotNo) {
    QString temp = "slot";
    if(slotNo < 0 || slotNo > 8)
        return "";
    else
        return temp.append(QString::number(slotNo)).append(" ");
}

QString BattleEngine::determineFaction(bool isRed) {
    if(isRed)
        return "red ";
    else
        return "blue ";
}

void BattleEngine::initializeAI() {
    int aiSpeed;
    switch(enemyDiff) {
        case 'e':
            aiSpeed = 8000;
            break;
        case 'm':
            aiSpeed = 4000;
            break;
        case 'h':
            aiSpeed = 2000;
            break;
        case 's':
            aiSpeed = 500;
            break;
    }

    if(AI != NULL)
        delete AI;

    if(playerIsRed) {
        AI = new AIEngine(&bluePop,&bluePopCap,&blueMoney,&blueTech,blueBlg,aiSpeed,redUnits,blueUnits,ui->battleField->width(),false,(void*)this);
    }
    else {
        AI = new AIEngine(&redPop,&redPopCap,&redMoney,&redTech,redBlg,aiSpeed,blueUnits,redUnits,ui->battleField->width(),true,(void*)this);
    }
}

void BattleEngine::finalizeAI() {

}

int BattleEngine::randomNumber(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

BattleEngine::~BattleEngine() {
    if(redLaserTimer != NULL) {
        redLaserTimer->stop();
        delete redLaserTimer;
    }
    if(blueLaserTimer != NULL) {
        blueLaserTimer->stop();
        delete blueLaserTimer;
    }
    if(redLaser != NULL) {
        delete redLaser;
    }
    if(blueLaser != NULL) {
        delete blueLaser;
    }
    if(AI != NULL) {
        delete AI;
    }
    for(int i = 0 ; i < 3 ; i++) {
        for(int j = 0 ; j < 2 ; j++) {
            delete switchBase[i][j];
        }
    }
    delete exec[0];
    delete exec[1];

    laserSound->stop();
    delete laserSound;

    ambientSound->stop();
    delete ambientSound;

    for(int i = 0 ; i < iconAnim->size() ; i++) {
        delete iconAnim->value(i);
    }
    iconAnim->clear();
    delete iconAnim;

    for(int i = 0 ; i < 2 ; i++) {
        for(int j = 0 ; j < 3 ; j++) {
            if(effects[i][j] != NULL) {
                for(int k = 0 ; k < effects[i][j]->size() ; k++) {
                    delete effects[i][j]->value(k);
                }
                effects[i][j]->clear();
                delete effects[i][j];
            }
        }
    }

    for(int i = 0 ; i < 2 ; i++) {
        for(int j = 0 ; j < 15 ; j++) {
            delete cmdIconBase[i][j];
        }
    }

    selectButtonAnimator->stop();
    delete selectButtonAnimator;

    cleaner->stop();
    delete cleaner;

    resourceRound->stop();
    delete resourceRound;

    for(int a = 0 ; a < 2 ; a++) {
        for(int b = 0 ; b < 3 ; b++) {
            for(int c = 0 ; c < 3 ; c++) {
                for(int d = 0 ; d < 3 ; d++) {
                    for(int e = 0 ; e < 3 ; e++) {
                        if(unitSpriteBase[a][b][c][d][e] != NULL) {
                            for(int i = 0 ; i < unitSpriteBase[a][b][c][d][e]->size() ; i++) {
                                delete unitSpriteBase[a][b][c][d][e]->value(i);
                            }
                            unitSpriteBase[a][b][c][d][e]->clear();
                            delete unitSpriteBase[a][b][c][d][e];
                        }
                    }
                }
            }
        }
    }

    for(int a = 0 ; a < 2 ; a++) {
        for(int b = 0 ; b < 6 ; b++) {
            for(int c = 0 ; c < 6 ; c++) {
                for(int d = 0 ; d < 2 ; d++) {
                    if(blgSpriteBase[a][b][c][d] != NULL) {
                        delete blgSpriteBase[a][b][c][d];
                    }
                }
            }
        }
    }

    alertSound->stop();
    delete alertSound;
}

void BattleEngine::destroySpritesFor(bool faction, QString defType, QString atkType, int level) {
    qDebug("Sprite CLEAR!");

    int fac = -1;
    int def = -1;
    int atk = -1;

    if(faction)
        fac = 0;
    else
        fac = 1;

    if(!defType.compare("Air"))
        def = 0;
    else if(!defType.compare("Infantry"))
        def = 1;
    else if(!defType.compare("Vehicle"))
        def = 2;

    if(!atkType.compare("AA"))
        atk = 0;
    else if(!atkType.compare("AI"))
        atk = 1;
    else if(!atkType.compare("AT"))
        atk = 2;

    for(int i = 0 ; i < 3 ; i++) {
        if(unitSpriteBase[fac][def][atk][level-1][i] == NULL)
            return;
        for(int j = 0 ; j < unitSpriteBase[fac][def][atk][level-1][i]->size() ; j++) {
            delete unitSpriteBase[fac][def][atk][level-1][i]->value(j);
        }
        unitSpriteBase[fac][def][atk][level-1][i]->clear();
        delete unitSpriteBase[fac][def][atk][level-1][i];
        unitSpriteBase[fac][def][atk][level-1][i] = NULL;
    }
}

bool BattleEngine::spriteForTypeExists(bool faction, QString defType, QString atkType, int level) {
    int fac = -1;
    int def = -1;
    int atk = -1;

    if(faction)
        fac = 0;
    else
        fac = 1;

    if(!defType.compare("Air"))
        def = 0;
    else if(!defType.compare("Infantry"))
        def = 1;
    else if(!defType.compare("Vehicle"))
        def = 2;

    if(!atkType.compare("AA"))
        atk = 0;
    else if(!atkType.compare("AI"))
        atk = 1;
    else if(!atkType.compare("AT"))
        atk = 2;

    if(unitSpriteBase[fac][def][atk][level-1][0] == NULL)
        return false;
    else
        return true;
}

bool BattleEngine::thereExistsThisTypeOfUnit(bool faction, QString defType, QString atkType, int level) {

    if(faction) {
        for(int i = 0 ; i < redUnits->size() ; i++) {
            if(!redUnits->value(i)->getDefenseType().compare(defType) && !redUnits->value(i)->attackType.compare(atkType) && redUnits->value(i)->level == level)
                return true;
        }
    }
    else {
        for(int i = 0 ; i < blueUnits->size() ; i++) {
            if(!blueUnits->value(i)->getDefenseType().compare(defType) && !blueUnits->value(i)->attackType.compare(atkType) && blueUnits->value(i)->level == level)
                return true;
        }
    }

    //qDebug("NONE!");
    return false;
}

bool BattleEngine::xIsWithinInterval(int intX, int intW, int targetX) {
    if(targetX >= intX && targetX <= intX + intW) {
        qDebug(QString::number(intX).append("intX").toAscii());
        qDebug(QString::number(intW).append("intW").toAscii());
        qDebug(QString::number(targetX).append("targetX").toAscii());
        return true;
    }
    else
        return false;
}

QList <Unit*>* BattleEngine::getUnitsWithinInterval(int x, int width, bool isRed, bool isAir) {
    QList <Unit*>* list = new QList <Unit*> ();
    if(isRed) {
        for(int i = 0 ; i < redUnits->size() ; i++) {
            if((xIsWithinInterval(x,width,redUnits->value(i)->xCoord))
                ||
              (xIsWithinInterval(x,width,redUnits->value(i)->xCoord + redUnits->value(i)->width))) {
                if(isAir && !redUnits->value(i)->defenseType.compare("Air"))
                    list->append(redUnits->value(i));
                else if(!isAir && redUnits->value(i)->defenseType.compare("Air"))
                    list->append(redUnits->value(i));
            }
        }
    }
    else {
        for(int i = 0 ; i < blueUnits->size() ; i++) {
            if((xIsWithinInterval(x,width,blueUnits->value(i)->xCoord))
                ||
              (xIsWithinInterval(x,width,blueUnits->value(i)->xCoord + blueUnits->value(i)->width))){
                if(isAir && !blueUnits->value(i)->defenseType.compare("Air"))
                    list->append(blueUnits->value(i));
                else if(!isAir && blueUnits->value(i)->defenseType.compare("Air"))
                    list->append(blueUnits->value(i));
            }
        }
    }
    if(list->empty() && isRed)
        //qDebug("NEIN FOUND!")
        ;

    return list;
}

void BattleEngine::damageAllUnitsInSet(QList<Unit*>* targetSet, int amt) {
    if(targetSet->isEmpty()) {
        //qDebug("TARGET SET IS EMPTY!");
        return;
    }
    for(int i = 0 ; i < targetSet->size() ; i++) {
        targetSet->value(i)->takeDamage(amt);
    }
}

void BattleEngine::createExplosion(int xCoord, int width, int damage, bool isRed, bool isAir) {
    QList <Unit*>* targetSet;
    createCombatEffect(xCoord + (width / 2),!isAir,ui->battleField);
    targetSet = getUnitsWithinInterval(xCoord,width,!isRed,isAir);
    damageAllUnitsInSet(targetSet,damage);
    targetSet->clear();
    delete targetSet;
}

Unit* BattleEngine::getFrontmostEnemyUnit(bool perspective, bool isAir) {
    int nearest;
    Unit* frontmost = NULL;
    if(perspective) {
        nearest = ui->battleField->width() + 500;
        for(int i = 0 ; i < blueUnits->size() ; i++) {
            if(blueUnits->value(i)->xCoord < nearest) {
                if(!isAir && blueUnits->value(i)->defenseType.compare("Air")) {
                    nearest = blueUnits->value(i)->xCoord;
                    frontmost = blueUnits->value(i);
                }
                else if (isAir && !blueUnits->value(i)->defenseType.compare("Air")){
                    nearest = blueUnits->value(i)->xCoord;
                    frontmost = blueUnits->value(i);
                }
            }
        }
    }
    else {
        nearest = 0 - 500;
        for(int i = 0 ; i < redUnits->size() ; i++) {
            if(redUnits->value(i)->xCoord > nearest) {
                if(!isAir && redUnits->value(i)->defenseType.compare("Air")) {
                    nearest = redUnits->value(i)->xCoord;
                    frontmost = redUnits->value(i);
                }
                else if(isAir && !redUnits->value(i)->defenseType.compare("Air")) {
                    nearest = redUnits->value(i)->xCoord;
                    frontmost = redUnits->value(i);
                }
            }
        }
    }
    return frontmost;
}

void BattleEngine::fireRedShell() {
    createExplosion(redCrosshair,100,300,true,false);
    redCrosshair += 100;
}

void BattleEngine::fireBlueShell() {
    createExplosion(blueCrosshair,100,300,false,false);
    blueCrosshair -= 100;
}

void BattleEngine::artilleryStrike(bool firerIsRed) {
    Unit* frontline = NULL;
    if(firerIsRed) {
        redCrosshair = 0;
        frontline = getFrontmostEnemyUnit(true,false);
        if(frontline)
            redCrosshair = frontline->xCoord;
        fireRedShell();
        QTimer::singleShot(200,this,SLOT(fireRedShell()));
        QTimer::singleShot(400,this,SLOT(fireRedShell()));
        QTimer::singleShot(800,this,SLOT(fireRedShell()));
        QTimer::singleShot(1000,this,SLOT(fireRedShell()));
    }
    else {
        blueCrosshair = ui->battleField->width();
        frontline = getFrontmostEnemyUnit(false,false);
        if(frontline)
            blueCrosshair = frontline->xCoord;
        fireBlueShell();
        QTimer::singleShot(200,this,SLOT(fireBlueShell()));
        QTimer::singleShot(400,this,SLOT(fireBlueShell()));
        QTimer::singleShot(800,this,SLOT(fireBlueShell()));
        QTimer::singleShot(1000,this,SLOT(fireBlueShell()));
    }
}



void BattleEngine::pauseGame() {

    cleaner->stop();
    freezeAllEffects();
    freezeAllUnits();
    freezeAllCommands();
    selectButtonAnimator->stop();
    resourceRound->stop();
    AI->stopAI();
    ui->gameDisplay->setCurrentIndex(3);
    ui->cmd1->hide();
    ui->cmd2->hide();
    ui->cmd3->hide();
    ui->cmd4->hide();
    ui->pauseButton->hide();
    ui->money->hide();
    ui->moneyProduction->hide();
    ui->techPoints->hide();
    ui->techProduction->hide();
    ui->population->hide();
    ui->cmdLabel->hide();

    ui->moneyIcon->hide();
    ui->moneyProdIcon->hide();
    ui->techIcon->hide();
    ui->techProdIcon->hide();
    ui->popIcon->hide();

    ambientSound->stop();

    isInSession = false;

}

void BattleEngine::resumeGame() {

    isInSession = true;

    cleaner->start(1);
    unfreezeAllEffects();
    unfreezeAllUnits();
    unfreezeAllCommands();
    selectButtonAnimator->start(100);
    resourceRound->start(8000);
    AI->startAI();
    ui->cmd2->click();
    ui->cmd1->show();
    ui->cmd2->show();
    ui->cmd3->show();
    ui->cmd4->show();
    ui->pauseButton->show();
    ui->money->show();
    ui->moneyProduction->show();
    ui->techPoints->show();
    ui->techProduction->show();
    ui->population->show();
    ui->cmdLabel->show();

    ui->moneyIcon->show();
    ui->moneyProdIcon->show();
    ui->techIcon->show();
    ui->techProdIcon->show();
    ui->popIcon->show();

    ambientSound->play();

}

void BattleEngine::freezeAllEffects() {
    for(int i = 0 ; i < effectList->size() ; i++) {
        effectList->value(i)->freeze();
    }
}

void BattleEngine::unfreezeAllEffects() {
    for(int i = 0 ; i < effectList->size() ; i++) {
        effectList->value(i)->unfreeze();
    }
}

void BattleEngine::freezeAllUnits() {
    for(int i = 0 ; i < redUnits->size() ; i++) {
        redUnits->value(i)->freeze();
    }
    for(int i = 0 ; i < blueUnits->size() ; i++) {
        blueUnits->value(i)->freeze();
    }
}

void BattleEngine::unfreezeAllUnits() {
    for(int i = 0 ; i < redUnits->size() ; i++) {
        redUnits->value(i)->unfreeze();
    }
    for(int i = 0 ; i < blueUnits->size() ; i++) {
        blueUnits->value(i)->unfreeze();
    }
}


void BattleEngine::buttonLightup() {
    QPushButton* btn = (QPushButton *)(QObject::sender());

    if(btn == ui->pauseButton)
        ui->pauseButton->setIcon(QIcon(":Images/generic/buttons/pauseButtonOn.png"));
    else if(btn == ui->resumeGame)
        ui->resumeGame->setIcon(QIcon(":GameScreen/buttons/gameScreen/exitOn.png"));
    else if(btn == ui->restartGame)
        ui->restartGame->setIcon(QIcon(":GameScreen/buttons/gameScreen/resetOn.png"));
    else if(btn == ui->quitGame)
        ui->quitGame->setIcon(QIcon(":GameScreen/buttons/gameScreen/quitOn.png"));
}

void BattleEngine::buttonLightdown() {
    QPushButton* btn = (QPushButton *)(QObject::sender());

    if(btn == ui->pauseButton)
        ui->pauseButton->setIcon(QIcon(":Images/generic/buttons/pauseButton.png"));
    else if(btn == ui->resumeGame)
        ui->resumeGame->setIcon(QIcon(":GameScreen/buttons/gameScreen/exit.png"));
    else if(btn == ui->restartGame)
        ui->restartGame->setIcon(QIcon(":GameScreen/buttons/gameScreen/reset.png"));
    else if(btn == ui->quitGame)
        ui->quitGame->setIcon(QIcon(":GameScreen/buttons/gameScreen/quit.png"));
}

bool BattleEngine::thereExistsThisTypeOfBlg(bool isRed, QString type, int level) {
    if(isRed) {
        for(int i = 0 ; i < 8 ; i++) {
            if(redBlg[i] != NULL) {
                if(!(redBlg[i]->getType().compare(type)) && redBlg[i]->getLevel() == level){
                    //qDebug("true");
                    return true;
                }
            }
        }
    }
    else {
        for(int i = 0 ; i < 8 ; i++) {
            if(blueBlg[i] != NULL) {
                if(!(blueBlg[i]->getType().compare(type)) && blueBlg[i]->getLevel() == level){
                    //qDebug("true");
                    return true;
                }
            }
        }
    }
    //qDebug("false");
    return false;
}

void BattleEngine::destroySpritesForBlg(bool isRed, QString type, int level) {
    qDebug("DESTOY!");
    int faction = -1;
    int blg = -1;
    if(isRed) {
        faction = 0;
    }
    else {
        faction = 1;
    }

    if(!(type.compare("CommandCenter"))) {
        blg = 0;
    }
    else if(!(type.compare("Barracks"))) {
        blg = 1;
    }
    else if(!(type.compare("Warfactory"))) {
        blg = 2;
    }
    else if(!(type.compare("Airfield"))) {
        blg = 3;
    }
    else if(!(type.compare("EconomicC"))) {
        blg = 4;
    }
    else if(!(type.compare("TechnologyC"))) {
        blg = 5;
    }

    if(blgSpriteBase[faction][blg][level - 1][0] == NULL || blgSpriteBase[faction][blg][level - 1][1] == NULL)
        return;

    delete blgSpriteBase[faction][blg][level - 1][0];
    delete blgSpriteBase[faction][blg][level - 1][1];

    blgSpriteBase[faction][blg][level - 1][0] = NULL;
    blgSpriteBase[faction][blg][level - 1][1] = NULL;
}

void BattleEngine::loadSpritesForBlg(bool isRed, QString type, int level) {
    //qDebug("SPRITE LOAD");
    QString pathOff = "/resource/";
    QString pathOn = "/resource/";
    int faction = -1;
    int blg = -1;
    if(isRed) {
        pathOff.append("Red/Building/");
        pathOn.append("Red/Building/");
        faction = 0;
    }
    else {
        pathOff.append("Blue/Building/");
        pathOn.append("Blue/Building/");
        faction = 1;
    }

    if(!(type.compare("CommandCenter"))) {
        pathOff.append("Capitol/");
        pathOn.append("Capitol/");
        blg = 0;
    }
    else if(!(type.compare("Barracks"))) {
        pathOff.append(type).append("/");
        pathOn.append(type).append("/");
        blg = 1;
    }
    else if(!(type.compare("Warfactory"))) {
        pathOff.append(type).append("/");
        pathOn.append(type).append("/");
        blg = 2;
    }
    else if(!(type.compare("Airfield"))) {
        pathOff.append(type).append("/");
        pathOn.append(type).append("/");
        blg = 3;
    }
    else if(!(type.compare("EconomicC"))) {
        pathOff.append("EconomicCenter/");
        pathOn.append("EconomicCenter/");
        blg = 4;
    }
    else if(!(type.compare("TechnologyC"))) {
        pathOff.append("TechCenter/");
        pathOn.append("TechCenter/");
        blg = 5;
    }
    else if(!(type.compare("Empty")))
        return;

    pathOff.append("lv").append(QString::number(level)).append(".png");
    pathOn.append("lv").append(QString::number(level)).append("ON").append(".png");

    //qDebug(pathOff.toAscii());
    //qDebug(pathOn.toAscii());

    blgSpriteBase[faction][blg][level - 1][0] = new QPixmap(pathOff);
    blgSpriteBase[faction][blg][level - 1][1] = new QPixmap(pathOn);


}

void BattleEngine::freezeAllCommands() {
    for(int i = 0 ; i < 8 ; i++) {
        redBlg[i]->freezeCommands();
        blueBlg[i]->freezeCommands();
    }
}

void BattleEngine::unfreezeAllCommands() {
    for(int i = 0 ; i < 8 ; i++) {
        redBlg[i]->unfreezeCommands();
        blueBlg[i]->unfreezeCommands();
    }
}

void BattleEngine::stopEcoBoomRed() {
    redEcoBoom = false;
}

void BattleEngine::stopEcoBoomBlue() {
    blueEcoBoom = false;
}

void BattleEngine::revoltRed() {
    if(randomNumber(1,100) <= 65)
        spawnUnit("Infantry","AI",redBlg[7]->getLevel(),true);
    else
        spawnUnit("Infantry","AT",redBlg[7]->getLevel(),true);
}

void BattleEngine::revoltBlue() {
    if(randomNumber(1,100) <= 65)
        spawnUnit("Infantry","AI",blueBlg[7]->getLevel(),false);
    else
        spawnUnit("Infantry","AT",blueBlg[7]->getLevel(),false);
}

void BattleEngine::laser(bool firerIsRed) {
    if(redLaserIsInEffect || blueLaserIsInEffect)
        ;
    else
        laserSound->play();

    if(firerIsRed && !redLaserIsInEffect) {
        redLaser = new QLabel(ui->battleField);
        redLaser->setPixmap(QPixmap("/resource/effects/redLaser.png"));
        redLaser->setGeometry(-384,0,384,420);
        redLaserTimer = new QTimer();
        connect(redLaserTimer,SIGNAL(timeout()),this,SLOT(redLaserFire()));
        redLaserIsInEffect = true;
        redLaser->setStyleSheet("background-image: url(null); background-color: rgba(255, 255, 255, 0);");
        redLaser->show();
        redLaserTimer->start(1);
        qDebug("FIRE LASER!");
    }
    else if (!firerIsRed && !blueLaserIsInEffect) {
        blueLaser = new QLabel(ui->battleField);
        blueLaser->setPixmap(QPixmap("/resource/effects/blueLaser.png"));
        blueLaser->setGeometry(ui->battleField->width(),0,384,420);
        blueLaserTimer = new QTimer();
        connect(blueLaserTimer,SIGNAL(timeout()),this,SLOT(blueLaserFire()));
        blueLaserIsInEffect = true;
        blueLaser->setStyleSheet("background-image: url(null); background-color: rgba(255, 255, 255, 0);");
        blueLaser->show();
        blueLaserTimer->start(1);
    }
}

void BattleEngine::redLaserFire() {
    redLaser->move(redLaser->x()+1,0);
    QList <Unit*>* set = NULL;
    set = getUnitsWithinInterval(redLaser->x()+160,60,true,false);
    damageAllUnitsInSet(set,redBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = getUnitsWithinInterval(redLaser->x()+160,60,true,true);
    damageAllUnitsInSet(set,redBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = getUnitsWithinInterval(redLaser->x()+160,60,false,false);
    damageAllUnitsInSet(set,redBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = getUnitsWithinInterval(redLaser->x()+160,60,false,true);
    damageAllUnitsInSet(set,redBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = NULL;
    if(redLaser->x() > ui->battleField->width())
        endRedLaser();
}

void BattleEngine::blueLaserFire() {
    blueLaser->move(blueLaser->x()-1,0);
    QList <Unit*>* set = NULL;
    set = getUnitsWithinInterval(blueLaser->x()+160,60,true,false);
    damageAllUnitsInSet(set,blueBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = getUnitsWithinInterval(blueLaser->x()+160,60,true,true);
    damageAllUnitsInSet(set,blueBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = getUnitsWithinInterval(blueLaser->x()+160,60,false,false);
    damageAllUnitsInSet(set,blueBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = getUnitsWithinInterval(blueLaser->x()+160,60,false,true);
    damageAllUnitsInSet(set,blueBlg[7]->getLevel() * 10);
    set->clear();
    delete set;
    set = NULL;if(blueLaser->x() < -384)
        endBlueLaser();
}

void BattleEngine::endRedLaser() {
    if(redLaserTimer) {
        redLaserTimer->stop();
        disconnect(redLaserTimer,SIGNAL(timeout()),this,SLOT(redLaserFire()));
        delete redLaserTimer;
        redLaserTimer = NULL;
        delete redLaser;
        redLaser = NULL;
        redLaserIsInEffect = false;
    }
    if(redLaserIsInEffect || blueLaserIsInEffect)
        ;
    else
        laserSound->stop();
}

void BattleEngine::endBlueLaser() {
    if(blueLaserTimer) {
        blueLaserTimer->stop();
        disconnect(blueLaserTimer,SIGNAL(timeout()),this,SLOT(blueLaserFire()));
        delete blueLaserTimer;
        blueLaserTimer = NULL;
        delete blueLaser;
        blueLaser = NULL;
        blueLaserIsInEffect = false;
    }
    if(redLaserIsInEffect || blueLaserIsInEffect)
        ;
    else
        laserSound->stop();
}

void BattleEngine::destroyAllUnits() {
    for(int i = 0 ; i < redUnits->size() ; i++) {
        redUnits->value(i)->freeze();
        delete redUnits->value(i);
    }
    for(int i = 0 ; i < blueUnits->size() ; i++) {
        blueUnits->value(i)->freeze();
        delete blueUnits->value(i);
    }
    redUnits->clear();
    blueUnits->clear();
}

void BattleEngine::deleteAllBuildings() {
    for(int i = 1 ; i <= 8 ; i++) {
        spawnBuilding("Empty",i,true);
        spawnBuilding("Empty",i,false);
    }
}

void BattleEngine::deleteAllEffects() {
    for(int i = 0 ; i < effectList->size() ; i++) {
        delete effectList->value(i);
    }
    effectList->clear();
}

void BattleEngine::quitGame() {
    endCombatSession();
    emit quitGameSIG();
}

void BattleEngine::restartGame() {
    ((MainClass*)(main))->screenTransition(16);
    ui->screens->setCurrentIndex(16);
    endCombatSession();
    ui->loaderOutput->setText("Rebooting...\n");
    QTimer::singleShot(9000,this,SLOT(startCombatSession()));
}

void BattleEngine::winlose() {
    cleaner->stop();
    freezeAllEffects();
    freezeAllUnits();
    freezeAllCommands();
    selectButtonAnimator->stop();
    resourceRound->stop();
    AI->stopAI();
    ui->cmd1->setEnabled(false);
    ui->cmd2->setEnabled(false);
    ui->cmd3->setEnabled(false);
    ui->cmd4->setEnabled(false);
    ui->pauseButton->setEnabled(false);
    ui->money->setEnabled(false);
    ui->moneyProduction->setEnabled(false);
    ui->techPoints->setEnabled(false);
    ui->techProduction->setEnabled(false);
    ui->population->setEnabled(false);
    ui->cmdLabel->setEnabled(false);

    ui->moneyIcon->setEnabled(false);
    ui->moneyProdIcon->setEnabled(false);
    ui->techIcon->setEnabled(false);
    ui->techProdIcon->setEnabled(false);
    ui->popIcon->setEnabled(false);

    ui->unitKilled->display(kills);
    ui->unitLost->display(deaths);
    ui->unitProduced->display(unitsProduced);
    ui->blgKilled->display(blgDestroyed);
    ui->blgLost->display(blgLost);
    ui->blgProduced->display(blgProduced);
}

void BattleEngine::redLose() {
    winlose();
    if(playerIsRed)
        ui->result->setIcon(QIcon("/resource/winLose/defeat.png"));
    else
        ui->result->setIcon(QIcon("/resource/winLose/victory.png"));

    ui->result->show();
    emit redDefeat();
}

void BattleEngine::blueLose() {
    winlose();
    if(playerIsRed)
        ui->result->setIcon(QIcon("/resource/winLose/victory.png"));
    else
        ui->result->setIcon(QIcon("/resource/winLose/defeat.png"));

    ui->result->show();
    emit blueDefeat();
}

void BattleEngine::cleanUpSFX() {
    Phonon::MediaObject* snd = (Phonon::MediaObject*)(QObject::sender());
    qDebug("BOOM!");
    snd->stop();
    delete snd;
}
