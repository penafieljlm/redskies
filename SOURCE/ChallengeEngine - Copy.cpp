#include "ChallengeEngine.h"
#include "mainclass.h"

ChallengeEngine::ChallengeEngine(BattleEngine *eng, void* mn) {
    engine = eng;
    round = 0;
    isInSession = false;
    main = mn;
}

void ChallengeEngine::startChallenge() {
    round = 0;

    disconnect(engine->ui->result,SIGNAL(clicked()),((MainClass*)(main)),SLOT(goToResultScreen()));
    connect(engine->ui->result,SIGNAL(clicked()),this,SLOT(endRound()));

    if(engine->playerIsRed) {
        connect(engine,SIGNAL(redDefeat()),this,SLOT(endChallenge()));
        qDebug("X");
    }
    else {
        connect(engine,SIGNAL(blueDefeat()),this,SLOT(endChallenge()));
        qDebug("Y");
    }

    startRound();
}

void ChallengeEngine::startRound() {
    round++;
    switch(engine->randomNumber(1,4)) {
        case 1:
            engine->ui->military->click();
            break;
        case 2:
            engine->ui->economy->click();
            break;
        case 3:
            engine->ui->social->click();
            break;
        case 4:
            engine->ui->technology->click();
            break;
    }
    engine->startCombatSession();
    engine->AI->setSpeed(15000/round);
}

void ChallengeEngine::endRound() {
    engine->ui->roundNo->display(round);
    ((MainClass*)(main))->screenTransition(13);
}

void ChallengeEngine::endChallenge() {
    engine->ui->roundNoEND->display(round);
    disconnect(engine->ui->result,SIGNAL(clicked()),this,SLOT(endRound()));
    connect(engine->ui->result,SIGNAL(clicked()),this,SLOT(goToEndChallengePage()));
}

void ChallengeEngine::goToEndChallengePage() {
    engine->ui->roundNoEND->display(round-1);
    disconnect(engine->ui->result,SIGNAL(clicked()),this,SLOT(goToEndChallengePage()));
    disconnect(engine,SIGNAL(redDefeat()),this,SLOT(endChallenge()));
    disconnect(engine,SIGNAL(blueDefeat()),this,SLOT(endChallenge()));

    connect(engine->ui->result,SIGNAL(clicked()),((MainClass*)(main)),SLOT(goToResultScreen()));

    ((MainClass*)(main))->screenTransition(14);
}

void ChallengeEngine::goToChallengeScreen() {
    disconnect(engine->ui->nextCOLOR,SIGNAL(clicked()),((MainClass*)(main)),SLOT(changeScreen()));
    disconnect(engine->ui->backCOLOR,SIGNAL(clicked()),((MainClass*)(main)),SLOT(changeScreen()));
    connect(engine->ui->backCOLOR,SIGNAL(clicked()),this,SLOT(leaveChooseColor()));
    connect(engine->ui->nextCOLOR,SIGNAL(clicked()),this,SLOT(startChallenge()));
}

void ChallengeEngine::leaveChallengeScreen() {
    disconnect(engine->ui->result,SIGNAL(clicked()),this,SLOT(endRound()));
    disconnect(engine->ui->result,SIGNAL(clicked()),this,SLOT(goToEndChallengePage()));
    disconnect(engine,SIGNAL(redDefeat()),this,SLOT(endChallenge()));
    disconnect(engine,SIGNAL(blueDefeat()),this,SLOT(endChallenge()));

    connect(engine->ui->result,SIGNAL(clicked()),((MainClass*)(main)),SLOT(goToResultScreen()));

    connect(engine->ui->nextCOLOR,SIGNAL(clicked()),((MainClass*)(main)),SLOT(changeScreen()));
    connect(engine->ui->backCOLOR,SIGNAL(clicked()),((MainClass*)(main)),SLOT(changeScreen()));
    disconnect(engine->ui->backCOLOR,SIGNAL(clicked()),this,SLOT(leaveChooseColor()));
    disconnect(engine->ui->nextCOLOR,SIGNAL(clicked()),this,SLOT(startChallenge()));
}

void ChallengeEngine::leaveChooseColor() {
    ((MainClass*)(main))->screenTransition(12);
    ((MainClass*)(main))->sacredWar->stop();
    ((MainClass*)(main))->sacredWar->play();
}

ChallengeEngine::~ChallengeEngine() {

}
