#include "mainclass.h"
#include "ui_mainclass.h"
#include <QtCore/QCoreApplication>
#include <QPropertyAnimation>

#include <QTimer>

MainClass::MainClass(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainClass)
{
    ui->setupUi(this);
    showFullScreen();
    showExpanded();
    setOrientation(ScreenOrientationLockLandscape);

    ui->screens->setCurrentIndex(9);

    connect(ui->soundYes,SIGNAL(clicked()),this,SLOT(soundDecide()));
    connect(ui->soundNo,SIGNAL(clicked()),this,SLOT(soundDecide()));

}

void MainClass::soundDecide() {
    QPushButton* btn = (QPushButton*)QObject::sender();
    if(btn == ui->soundYes)
        sound = true;
    else
        sound = false;

    battleEngine = new BattleEngine(ui,this);


    ui->battleField->setStyleSheet("background-image: url(/resource/levels/sample.png); background-color: rgba(255, 255, 255, 0);");
    ui->leftBaseArea->setStyleSheet("background-image: url(/resource/levels/sample.png); background-color: rgba(255, 255, 255, 0);");
    ui->rightBaseArea->setStyleSheet("background-image: url(/resource/levels/sample.png); background-color: rgba(255, 255, 255, 0);");

    if(sound) {
        mainMenuBGM = new BGM("/resource/sounds/redCavalry.mp3");
        marchBGM = new BGM("/resource/sounds/march.mp3");
        sacredWar = new BGM("/resource/sounds/sacredWar.mp3");
        transSound = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource("/resource/sounds/menuEnter.mp3"));
        menuSound = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource("/resource/sounds/menuSelect.mp3"));
        sound1BGM = new BGM("/resource/sounds/sound1.wav");
    }
    else {
        mainMenuBGM = NULL;
        marchBGM = NULL;
        sacredWar = NULL;
        transSound = NULL;
        menuSound = NULL;
        sound1BGM = NULL;
    }

    transitionTarget = -1;

    transitionTimer = new QTimer();
    connect(transitionTimer,SIGNAL(timeout()),this,SLOT(transToggle()));

    challenge = new ChallengeEngine(battleEngine,this);

    connect(battleEngine,SIGNAL(quitGameSIG()),this,SLOT(quitGameSession()));

    ui->background_2->setPixmap(QPixmap("/resource/factions/mil.png"));
    ui->colorBG->setPixmap(QPixmap("/resource/color/red.png"));

    ui->transition->setStyleSheet("background-image: url('/resource/transition/2.png');");

    ui->result->hide();

    connect(ui->result,SIGNAL(clicked()),battleEngine,SLOT(endCombatSession()));

    loaderAnim[0] = new QPixmap(":Interface/animated/interface/buffer/1.png");
    loaderAnim[1] = new QPixmap(":Interface/animated/interface/buffer/2.png");
    loaderAnim[2] = new QPixmap(":Interface/animated/interface/buffer/3.png");
    loaderAnim[3] = new QPixmap(":Interface/animated/interface/buffer/4.png");
    loaderAnim[4] = new QPixmap(":Interface/animated/interface/buffer/5.png");
    loaderAnim[5] = new QPixmap(":Interface/animated/interface/buffer/6.png");
    loaderDone = new QPixmap(":Interface/animated/interface/buffer/done.png");
    loadDoneText = new QPixmap(":Interface/text/bootDone.png");

    ui->moneyIcon->setIcon(QIcon("/resource/cmdIcons/sell.png"));
    ui->moneyProdIcon->setIcon(QIcon("/resource/cmdIcons/ecoC.png"));
    ui->techIcon->setIcon(QIcon("/resource/cmdIcons/repair.png"));
    ui->techProdIcon->setIcon(QIcon("/resource/cmdIcons/techC.png"));
    ui->popIcon->setIcon(QIcon("/resource/cmdIcons/barracks.png"));

    connect(ui->facePinch,SIGNAL(pressed()),this,SLOT(pinchMainCharOn()));
    connect(ui->facePinch,SIGNAL(released()),this,SLOT(pinchMainCharOff()));

    connect(ui->result,SIGNAL(clicked()),this,SLOT(goToResultScreen()));
    connect(ui->nextRESULT,SIGNAL(clicked()),this,SLOT(changeScreen()));

    //Exit Game Button Effects
    connect(ui->exitGameButton_2,SIGNAL(pressed()),this,SLOT(lightUpButton()));
    connect(ui->exitGameButton_2,SIGNAL(released()),this,SLOT(lightDownButton()));
    connect(ui->exitGameButton_2,SIGNAL(clicked()),this,SLOT(changeScreen()));

    connect(ui->helpButton,SIGNAL(pressed()),this,SLOT(lightUpButton()));
    connect(ui->helpButton,SIGNAL(released()),this,SLOT(lightDownButton()));
    connect(ui->helpButton,SIGNAL(clicked()),this,SLOT(changeScreen()));
    //Inside titleScreen
        connect(ui->splash,SIGNAL(clicked()),this,SLOT(changeScreen()));
    //Inside newGame Screen
        //Faction Types
        connect(ui->military,SIGNAL(pressed()),this,SLOT(lightUpNGSButton()));
        connect(ui->economy,SIGNAL(pressed()),this,SLOT(lightUpNGSButton()));
        connect(ui->social,SIGNAL(pressed()),this,SLOT(lightUpNGSButton()));
        connect(ui->technology,SIGNAL(pressed()),this,SLOT(lightUpNGSButton()));
        //Back Button
        connect(ui->backnewG,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backnewG,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backnewG,SIGNAL(clicked()),this,SLOT(changeScreen()));
        //Next Button
        connect(ui->nextnewG,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->nextnewG,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->nextnewG,SIGNAL(clicked()),this,SLOT(changeScreen()));
    //Inside chooseEnemy Screen
        //Enemy Difficulty
        connect(ui->easy,SIGNAL(pressed()),this,SLOT(lightUpCESButton()));
        connect(ui->medium,SIGNAL(pressed()),this,SLOT(lightUpCESButton()));
        connect(ui->hard,SIGNAL(pressed()),this,SLOT(lightUpCESButton()));
        connect(ui->extreme,SIGNAL(pressed()),this,SLOT(lightUpCESButton()));
        //Back Button
        connect(ui->backCH,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backCH,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backCH,SIGNAL(clicked()),this,SLOT(changeScreen()));
        //Next Button
        connect(ui->nextCH,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->nextCH,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->nextCH,SIGNAL(clicked()),this,SLOT(changeScreen()));
    //Inside mapScreen
        //Back Button
        connect(ui->backMAP,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backMAP,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backMAP,SIGNAL(clicked()),this,SLOT(changeScreen()));
        //Next Button
        connect(ui->nextMAP,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->nextMAP,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->nextMAP,SIGNAL(clicked()),this,SLOT(changeScreen()));
    //Inside colorScreen
        //Back Button
        connect(ui->backCOLOR,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backCOLOR,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backCOLOR,SIGNAL(clicked()),this,SLOT(changeScreen()));
        //Next Button
        connect(ui->nextCOLOR,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->nextCOLOR,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->nextCOLOR,SIGNAL(clicked()),this,SLOT(changeScreen()));
        //Red
        connect(ui->red,SIGNAL(clicked()),this,SLOT(lightUpColor()));
        //Blue
        connect(ui->blue,SIGNAL(clicked()),this,SLOT(lightUpColor()));
    //Challenge Screen
        connect(ui->backCHAL,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backCHAL,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->nextCHAL,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->nextCHAL,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backCHAL,SIGNAL(clicked()),this,SLOT(changeScreen()));
        connect(ui->nextCHAL,SIGNAL(clicked()),this,SLOT(changeScreen()));

        connect(ui->backROUND,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backROUND,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backROUND,SIGNAL(clicked()),this,SLOT(changeScreen()));

        connect(ui->nextROUND,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->nextROUND,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->nextROUND,SIGNAL(clicked()),challenge,SLOT(startRound()));
    //Game Select Screen
//        connect(ui->campaignGameButton,SIGNAL(pressed()),this,SLOT(lightUpButton()));
//        connect(ui->campaignGameButton,SIGNAL(released()),this,SLOT(lightDownButton()));
//        connect(ui->campaignGameButton,SIGNAL(clicked()),this,SLOT(changeScreen()));
        connect(ui->challengeGameButton,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->challengeGameButton,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->challengeGameButton,SIGNAL(clicked()),this,SLOT(changeScreen()));
        connect(ui->customGameButton,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->customGameButton,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->customGameButton,SIGNAL(clicked()),this,SLOT(changeScreen()));

    //HELP SCREEN
        connect(ui->backHELP,SIGNAL(pressed()),this,SLOT(lightUpButton()));
        connect(ui->backHELP,SIGNAL(released()),this,SLOT(lightDownButton()));
        connect(ui->backHELP,SIGNAL(clicked()),this,SLOT(changeScreen()));


    connect(ui->backENDCHAL,SIGNAL(pressed()),this,SLOT(lightUpButton()));
    connect(ui->backENDCHAL,SIGNAL(released()),this,SLOT(lightDownButton()));
    connect(ui->backENDCHAL,SIGNAL(clicked()),this,SLOT(changeScreen()));

    ui->gameDisplay->setCurrentIndex(1);

    connect(ui->cmd1,SIGNAL(clicked()),this,SLOT(changeScreen()));
    connect(ui->cmd2,SIGNAL(clicked()),this,SLOT(changeScreen()));
    connect(ui->cmd3,SIGNAL(clicked()),this,SLOT(changeScreen()));
    connect(ui->cmd4,SIGNAL(pressed()),this,SLOT(execButtonDown()));
    connect(ui->cmd4,SIGNAL(released()),this,SLOT(execButtonUp()));

    kozakScroll = new KozakScroll(ui->redSky);

    connect(ui->quitGame,SIGNAL(clicked()),this,SLOT(startKozak()));

    connect(ui->splash,SIGNAL(clicked()),this,SLOT(startKozak()));

    ui->screens->setCurrentIndex(11);

    kaiFrame = 0;

    ui->KPanel1->hide();
    ui->KPanel1_2->hide();
    ui->KPanel1_3->hide();
    ui->KPanel1_4->hide();
    ui->KPanel1_5->hide();
    ui->KPanel1_6->hide();
    ui->KPanel1_7->hide();
    ui->KPanel1_8->hide();
    ui->KPanel1_9->hide();

    QTimer::singleShot(500,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(1000,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(1500,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(2000,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(2500,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(3000,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(3500,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(4000,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(4500,this,SLOT(kaiAnimFrame()));
    QTimer::singleShot(8000,this,SLOT(endKaiAnim()));
}

void MainClass::kaiAnimFrame() {
    switch(kaiFrame) {
        case 0:
            ui->KPanel1->show();
            break;
        case 1:
            ui->KPanel1_6->show();
            break;
        case 2:
            ui->KPanel1_8->show();
            break;
        case 3:
            ui->KPanel1_2->show();
            break;
        case 4:
            ui->KPanel1_7->show();
            break;
        case 5:
            ui->KPanel1_3->show();
            break;
        case 6:
            ui->KPanel1_4->show();
            break;
        case 7:
            ui->KPanel1_5->show();
            break;
        case 8:
            ui->KPanel1_9->show();
            break;
    }
    kaiFrame++;
}

void MainClass::startKozak() {
    //qDebug("START KOZAK");
    kozakScroll->startScroll();
}

void MainClass::endKozak() {
    //qDebug("END KOZAK");
    kozakScroll->stopScroll();
}

Ui::MainClass* MainClass::getUI() {
    return ui;
}

void MainClass::execButtonDown() {
    ui->cmd4->setIcon(*(battleEngine->exec[1]));
}

void MainClass::execButtonUp() {
    ui->cmd4->setIcon(*(battleEngine->exec[0]));
}

void MainClass::toSplash() {
    bufferAnim->stop();
    ui->loaderAnimBegin->setPixmap(*loaderDone);
    ui->loaderPrompt->setPixmap(*loadDoneText);
    QTimer::singleShot(1200,this,SLOT(toSplashCeption()));
    initializeMap();
}

void MainClass::toSplashCeption() {
    screenTransition(0);
}

void MainClass::bufferAnimBegin() {
    ui->loaderAnimBegin->setPixmap(*loaderAnim[loaderAnimIndex]);
    loaderAnimIndex++;
    loaderAnimIndex%=6;
}

MainClass::~MainClass()
{
    for(int i = 0 ; i < 6 ; i++) {
        delete loaderAnim[i];
    }

    delete loaderDone;
    delete bufferAnim;
    delete loadDoneText;
    delete kozakScroll;

    transitionTimer->stop();
    delete transitionTimer;

    //delete mapEngine;
    delete battleEngine;
    delete ui;

    delete mainMenuBGM;
    delete marchBGM;
    delete sacredWar;
    delete sound1BGM;

    if(sound) {
        transSound->stop();
        delete transSound;
    }

    if(sound) {
        menuSound->stop();
        delete menuSound;
    }
}

void MainClass::lightUpCESButton() {
    //Light up Choose Enemy Screen Buttons
    QPushButton* btn = (QPushButton*)QObject::sender();
    if(sound) {
        menuSound->stop();
        menuSound->play();
    }

    ui->diffDesc->clear();

    if (btn == ui->easy) {
        ui->easy->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/easyOn.png"));
        ui->medium->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/medium.png"));
        ui->hard->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/hard.png"));
        ui->extreme->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/superhard.png"));
        ui->diffDesc->setPixmap(QPixmap(":/Images/text/newGame/text/chooseEnemy/easyText.png"));
        battleEngine->setEnemyDiff('e');
    }
    else if (btn == ui->medium) {
        ui->easy->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/easy.png"));
        ui->medium->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/mediumOn.png"));
        ui->hard->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/hard.png"));
        ui->extreme->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/superhard.png"));
        ui->diffDesc->setPixmap(QPixmap(":/Images/text/newGame/text/chooseEnemy/mediumText.png"));
        battleEngine->setEnemyDiff('m');
    }
    else if (btn == ui->hard) {
        ui->easy->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/easy.png"));
        ui->medium->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/medium.png"));
        ui->hard->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/hardOn.png"));
        ui->extreme->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/superhard.png"));
        ui->diffDesc->setPixmap(QPixmap(":/Images/text/newGame/text/chooseEnemy/hardText.png"));
        battleEngine->setEnemyDiff('h');
    }
    else if (btn == ui->extreme) {
        ui->easy->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/easy.png"));
        ui->medium->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/medium.png"));
        ui->hard->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/hard.png"));
        ui->extreme->setIcon(QIcon(":/Images/buttons/enemy/buttons/enemy/superhardOn.png"));
        ui->diffDesc->setPixmap(QPixmap(":/Images/text/newGame/text/chooseEnemy/extremeText.png"));
        battleEngine->setEnemyDiff('s');
    }
}

void MainClass::lightUpNGSButton() {
    //Light up New Game Screen Buttons
    QPushButton* btn = (QPushButton*)QObject::sender();

    if(sound) {
        menuSound->stop();
        menuSound->play();
    }

    ui->background_2->clear();

    if (btn == ui->military) {
        ui->background_2->setPixmap(QPixmap("/resource/factions/mil.png"));
        ui->military->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/militaryOn.png"));
        ui->economy->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/economy.png"));
        ui->social->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/social.png"));
        ui->technology->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/technology.png"));
        ui->factionDescText->setText("Special Skill:\n    - Blitzkreig\n        > Increase the attack power  of your\n            troops for 30 seconds.\n        > Increase the attack speed  of your\n            troops for 30 seconds.\n        > Increase the movement speed of your\n            troops for 30 seconds.\n\nThe \"Military\" faction type specializes on the\nquality and strength of it's troops. They are\nbalanced both economically and technologically.\nThey usually employ the \"Blitzkreig\" strategy to\nquickly win skirmishes.");
        battleEngine->setPlayerType('m');
    }
    else if (btn == ui->economy) {
        ui->background_2->setPixmap(QPixmap("/resource/factions/eco.png"));
        ui->military->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/military.png"));
        ui->economy->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/economyOn.png"));
        ui->social->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/social.png"));
        ui->technology->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/technology.png"));
        ui->factionDescText->setText("Special Skill:\n    - Economic Boom\n        > Temporarily increases the output\n            of your economic centers.\n\nThe \"Economy\" faction type relies heavily\non it's economy to advance. They focus\nmore on economic development and less\non military forces.");
        battleEngine->setPlayerType('e');
    }
    else if (btn == ui->social) {
        ui->background_2->setPixmap(QPixmap("/resource/factions/soc.png"));
        ui->military->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/military.png"));
        ui->economy->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/economy.png"));
        ui->social->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/socialOn.png"));
        ui->technology->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/technology.png"));
        ui->factionDescText->setText("Special Skill:\n    - Mass Propaganda\n        > Calls upon the masses to fight\n           for your side.\n\nThe \"Social\" faction type specializes in\nMass Media and Propaganda. They rely\nmore on the sheer number of their forces\nand less on the aount of training each\nunit recieves.");
        battleEngine->setPlayerType('s');
    }
    else if (btn == ui->technology) {
        ui->background_2->setPixmap(QPixmap("/resource/factions/tec.png"));
        ui->military->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/military.png"));
        ui->economy->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/economy.png"));
        ui->social->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/social.png"));
        ui->technology->setIcon(QIcon(":/Images/buttons/newGame/buttons/newGame/technologyOn.png"));
        ui->factionDescText->setText("Special Skill:\n    - Orbital Strike\n        > Damages ALL units in the field.\n\nThe \"Technology\" faction type relies\nheavily on it's technological superiority.\nThey have the capability to perform an\nOrbital Strike anywhere on the planet.");
        battleEngine->setPlayerType('t');
    }


}

void MainClass::lightUpButton() {
    QPushButton* btn = (QPushButton*)QObject::sender();
    if(sound) {
        menuSound->stop();
        menuSound->play();
    }

    if (btn == ui->backnewG || btn == ui->backCH || btn == ui->backMAP || btn == ui->backCOLOR || btn == ui->backCHAL || btn == ui->backROUND || btn == ui->backHELP || btn ==ui->backENDCHAL) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/backButtonOn.png"));
    }
    else if (btn == ui->exitGameButton_2) {
        btn->setIcon(QIcon(":/Images/buttons/mainMenu/buttons/mainMenu/exitOn.png"));
    }
    else if (btn == ui->helpButton) {
        btn->setIcon(QIcon(":/Images/buttons/mainMenu/buttons/mainMenu/helpOn.png"));
    }
    else if (btn == ui->nextnewG || btn == ui->nextCH || btn == ui->nextMAP || btn == ui->nextCOLOR || btn == ui->nextCHAL || btn == ui->nextROUND ) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/nextButtonOn.png"));
    }
//    else if (btn == ui->campaignGameButton) {
//        icon1.addFile(QString::fromUtf8(":/Images/buttons/newGame/buttons/gameSelect/campaignOn.png"), QSize(), QIcon::Normal, QIcon::Off);
//    }
    else if (btn == ui->customGameButton) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/gameSelect/customOn.png"));
    }
    else if (btn == ui->challengeGameButton) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/gameSelect/challengeOn.png"));
    }
}

void MainClass::lightDownButton() {
    QPushButton* btn = (QPushButton *)(QObject::sender());

    if (btn == ui->backnewG || btn == ui->backCH || btn == ui->backMAP || btn == ui->backCOLOR || btn == ui->backCHAL || btn == ui->backROUND || btn == ui->backHELP || btn ==ui->backENDCHAL) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/backButton.png"));
    }
    else if (btn == ui->exitGameButton_2) {
        btn->setIcon(QIcon(":/Images/buttons/mainMenu/buttons/mainMenu/exit.png"));
    }
    else if (btn == ui->helpButton) {
        btn->setIcon(QIcon(":/Images/buttons/mainMenu/buttons/mainMenu/help.png"));
    }
    else if (btn == ui->nextnewG || btn == ui->nextCH || btn == ui->nextMAP || btn == ui->nextCOLOR || btn == ui->nextCHAL || btn == ui->nextROUND) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/nextButton.png"));
    }
//    else if (btn == ui->campaignGameButton) {
//        icon1.addFile(QString::fromUtf8(":/Images/buttons/newGame/buttons/gameSelect/campaign.png"), QSize(), QIcon::Normal, QIcon::Off);
//    }
    else if (btn == ui->customGameButton) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/gameSelect/custom.png"));
    }
    else if (btn == ui->challengeGameButton) {
        btn->setIcon(QIcon(":/Images/buttons/newGame/buttons/gameSelect/challenge.png"));
    }
}

void MainClass::lightUpColor() {
    QPushButton* btn = (QPushButton *)(QObject::sender());

    ui->colorBG->clear();

    if(btn == ui->red){
        ui->colorBG->setPixmap(QPixmap("/resource/color/red.png"));
        battleEngine->setPlayerSide(true);
    }
    else if(btn == ui->blue){
        ui->colorBG->setPixmap(QPixmap("/resource/color/blue.png"));
        battleEngine->setPlayerSide(false);
    }

}

void MainClass::changeScreen() {
    QPushButton* btn = (QPushButton *)(QObject::sender());
    int index = 0;

    //qDebug(btn->objectName().toAscii());

    if(sound) {
        mainMenuBGM->stop();

        if(btn != ui->nextnewG && btn != ui->backCH)
            sacredWar->stop();

        marchBGM->stop();

        sound1BGM->stop();
    }

    if (btn == ui->backnewG || btn == ui->nextRESULT || btn == ui->backHELP || btn == ui->splash || btn == ui->backENDCHAL) {
        index = 1;
        if(sound)
            mainMenuBGM->play();
        startKozak();
    }
    else if (btn == ui->nextnewG) {
        index = 3;
    }
    else if (btn == ui->customGameButton) {
        index = 2;
        if(sound)
            sacredWar->play();
        endKozak();
    }
    else if (btn == ui->backCH) {
        index = 2;
    }
    else if (btn == ui->cmd1)
        index = 0;
    else if (btn == ui->cmd2)
        index = 1;
    else if (btn == ui->cmd3)
        index = 2;
    else if (btn == ui->backMAP)
        ; //index = 3;
    else if (/*btn == ui->nextMAP ||*/ btn == ui->nextCHAL || btn == ui->nextCH) {
        index = 7;
        if(sound)
            sound1BGM->play();
    }
    else if (btn == ui->nextCOLOR) {
        index = 16;
        ui->loaderOutput->clear();
    }
    else if (btn == ui->backCOLOR) {
        index = 3; //index = 6;
        if(sound)
            sacredWar->play();
    }
    else if (btn == ui->challengeGameButton) {
        if(sound)
            sacredWar->play();
        index = 12;
        endKozak();
        challenge->goToChallengeScreen();
    }
    else if (btn == ui->backCHAL || btn == ui->backROUND) {
        if(sound)
            mainMenuBGM->play();
        index = 1;
        challenge->leaveChallengeScreen();
        startKozak();
    }
    else if (btn == ui->helpButton) {
        if(sound)
            sound1BGM->play();
        index = 15;
        endKozak();
    }

    //qDebug(QString::number(index).toAscii());

    if(btn != ui->cmd1 && btn != ui->cmd2 && btn != ui->cmd3)
        screenTransition(index);
    else {
        ui->gameDisplay->setCurrentIndex(index);
        switch(index) {
            case 0:
                ui->cmd1->setIcon((*battleEngine->switchBase[0][1]));
                ui->cmd2->setIcon((*battleEngine->switchBase[1][0]));
                ui->cmd3->setIcon((*battleEngine->switchBase[2][0]));
                break;
            case 1:
                ui->cmd1->setIcon((*battleEngine->switchBase[0][0]));
                ui->cmd2->setIcon((*battleEngine->switchBase[1][1]));
                ui->cmd3->setIcon((*battleEngine->switchBase[2][0]));
                break;
            case 2:
                ui->cmd1->setIcon((*battleEngine->switchBase[0][0]));
                ui->cmd2->setIcon((*battleEngine->switchBase[1][0]));
                ui->cmd3->setIcon((*battleEngine->switchBase[2][1]));
                break;
        }
    }

    if(btn == ui->nextCOLOR)
        battleEngine->startCombatSession();

    if(btn == ui->splash) {
        ui->splash->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->splash->close();
        ui->loaderAnimBegin->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->loaderAnimBegin->close();
        ui->KPanel1->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1->close();
        ui->KPanel1_2->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_2->close();
        ui->KPanel1_3->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_3->close();
        ui->KPanel1_4->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_4->close();
        ui->KPanel1_5->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_5->close();
        ui->KPanel1_6->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_6->close();
        ui->KPanel1_7->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_7->close();
        ui->KPanel1_8->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_8->close();
        ui->KPanel1_9->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->KPanel1_9->close();
        ui->loaderSCBG->setAttribute(Qt::WA_DeleteOnClose,true);
        ui->loaderSCBG->close();
    }
}

BattleEngine* MainClass::getBattleEngine() {
    return battleEngine;
}

void MainClass::showExpanded() {

#ifdef  Q_OS_SYMBIAN
    showFullScreen();
#elif   defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    showMaximized();
#else
    show();
#endif
}

void MainClass::initializeMap() {
    //mapEngine = new MapEngine(ui->mapWidget,battleEngine->iconAnim,ui->mapPageHeader,ui->mapPrevDesc,ui->mapPrevImage);
    //mapEngine->buildMap("CustomGame");
}

void MainClass::pinchMainCharOff() {
    ui->menuCharacter->clear();
    ui->menuCharacter->setPixmap(QPixmap(":/Images/backgrounds/mainMenu/char1.png"));
}

void MainClass::pinchMainCharOn() {
    ui->menuCharacter->clear();
    ui->menuCharacter->setPixmap(QPixmap(":/Images/backgrounds/mainMenu/char2.png"));
}

void MainClass::screenTransition(int destinationIndex) {
    ui->menuCharacter->clear();
    ui->sidebar->clear();
    ui->background_2->clear();
    ui->newGsidebar->clear();
    ui->chooseEnemyBG->clear();
    ui->chooseEnemySB->clear();
    ui->background_3->clear();
    ui->colorBG->clear();
    ui->challengeBG->clear();
    ui->challengeHeader->clear();
    ui->challengeEndBG->clear();
    ui->challengeEndBG_2->clear();
    ui->challengeHeader_3->clear();
    ui->label_12->clear();
    ui->label_10->clear();
    ui->label_37->clear();
    ui->label_38->clear();
    ui->label_39->clear();
    ui->label_21->clear();
    ui->label_8->clear();
    ui->resBG->clear();
    ui->redSkyBG->clear();
    ui->chooseEnemySB->clear();
    //ui->easy->setIcon();
    switch(destinationIndex) {
        case 1:
            ui->menuCharacter->setPixmap(QPixmap(":/Images/backgrounds/mainMenu/char1.png"));
            ui->sidebar->setPixmap(QPixmap(":/Images/backgrounds/mainMenu/bgMain.png"));
            ui->redSkyBG->setPixmap(QPixmap(":/Images/backgrounds/mainMenu/menuBG.png"));
            break;
        case 2:
            ui->military->click();
            ui->newGsidebar->setPixmap(QPixmap(":/Images/backgrounds/newGame/newGSideBar.png"));
            break;
        case 3:
            ui->easy->click();
            ui->chooseEnemyBG->setPixmap(QPixmap(":/Images/generic/bgLayer.png"));
            ui->chooseEnemySB->setPixmap(QPixmap(":/Images/backgrounds/enemy/chooseEnemySB.png"));
            break;
        case 4:
            ui->background_3->setPixmap(QPixmap(":/Images/generic/interfaceBG.png"));
            break;
        case 7:
            ui->red->click();
            break;
        case 8:
            ui->resBG->setPixmap(QPixmap(":/Images/generic/bgLayer.png"));
        case 12:
            ui->challengeBG->setPixmap(QPixmap(":/Images/backgrounds/newGame/newGBG.png"));
            ui->challengeHeader->setPixmap(QPixmap(":/Images/generic/challengeHeader.png"));
            break;
        case 13:
            ui->challengeEndBG->setPixmap(QPixmap(":/Images/generic/bgLayer.png"));
            break;
        case 14:
            ui->challengeEndBG_2->setPixmap(QPixmap(":/Images/generic/bgLayer.png"));
            ui->challengeHeader_3->setPixmap(QPixmap(":/Images/generic/endChallenge.png"));
            break;
        case 15:
            ui->label_12->setPixmap(QPixmap("/resource/inst/instHead.png"));
            ui->label_10->setPixmap(QPixmap("/resource/inst/inst1.png"));
            ui->label_37->setPixmap(QPixmap("/resource/inst/inst4.png"));
            ui->label_38->setPixmap(QPixmap("/resource/inst/inst2.png"));
            ui->label_39->setPixmap(QPixmap("/resource/inst/inst3.png"));
            ui->label_8->setPixmap(QPixmap(":/Images/generic/bgLayer.png"));
            break;
        case 16:
            ui->label_21->setPixmap(QPixmap(":/Images/generic/bgLayer.png"));
            break;
    }
    if(sound) {
        transSound->stop();
        transSound->play();
    }
    transitionState = false;
    transitionTimer->start(75);
    ui->screens->setCurrentIndex(10);
    transitionTarget = destinationIndex;
    QTimer::singleShot(500,this,SLOT(goTransition()));
}

void MainClass::goTransition() {
    ui->screens->setCurrentIndex(transitionTarget);
    transitionTimer->stop();
    transitionTarget = -1;
}

void MainClass::transToggle() {
    ui->transLabel->clear();

    if(transitionState)
        ui->transLabel->setPixmap(QPixmap("/resource/transition/1.png"));
    else
        ui->transLabel->setPixmap(QPixmap("/resource/transition/2.png"));

    transitionState = !transitionState;
}

void MainClass::quitGameSession() {
    challenge->leaveChallengeScreen();
    if(sound)
        mainMenuBGM->play();
    screenTransition(1);
}

void MainClass::goToResultScreen() {
    screenTransition(8);
}

void MainClass::goToLoader() {
    screenTransition(5);
}

void MainClass::endKaiAnim() {
    goToLoader();

    bufferAnim = new QTimer();
    connect(bufferAnim,SIGNAL(timeout()),this,SLOT(bufferAnimBegin()));
    loaderAnimIndex = 0;
    bufferAnim->start(100);
    if(sound)
        marchBGM->play();

    QTimer::singleShot(4000,battleEngine,SLOT(buildSpriteBase()));
    QTimer::singleShot(8000,this,SLOT(toSplash()));
}

void MainClass::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

