#ifndef CHALLENGEENGINE_H
#define CHALLENGEENGINE_H

#include "BattleEngine.h"
#include <QObject>

class ChallengeEngine : public QObject {
    Q_OBJECT
public:
    ChallengeEngine(BattleEngine* eng, void* mn);
    ~ChallengeEngine();

public slots:
    void goToChallengeScreen();
    void leaveChallengeScreen();

private slots:
    void startChallenge();
    void startRound();
    void endRound();
    void endChallenge();
    void goToEndChallengePage();

    void leaveChooseColor();

    void setAIInterval();

private:
    BattleEngine* engine;
    void* main;
    int round;
    bool isInSession;
    int currentAISpeed;

};

#endif // CHALLENGEENGINE_H
