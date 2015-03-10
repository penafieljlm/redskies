#ifndef MAINCLASS_H
#define MAINCLASS_H

#include "Unit.h"
#include "BattleEngine.h"
#include "MapEngine.h"
#include <QPushButton>
#include "KozakScroll.h"
#include "ChallengeEngine.h"
#include <QtGui/QMainWindow>
#include <QProcess>


namespace Ui {              //Ui is a namespace,
    class MainClass;        //class name only
}

class MainClass : public QMainWindow
{
    Q_OBJECT

    enum ScreenOrientation {
            ScreenOrientationLockPortrait,
            ScreenOrientationLockLandscape,
            ScreenOrientationAuto
        };


public:
    explicit MainClass(QWidget *parent = 0);
    ~MainClass();
    void showExpanded();
    BattleEngine* getBattleEngine();
    Ui::MainClass* getUI();
    void screenTransition(int destinationIndex);
    void setOrientation(ScreenOrientation orientation);
    bool sound;

public slots:
    void goTransition();

private:
    Ui::MainClass *ui;      //to declare an instance of MainClass* , use ::

    BattleEngine* battleEngine;
    //MapEngine* mapEngine;

    int loaderAnimIndex;
    QPixmap* loaderAnim[6];
    QPixmap* loaderDone;
    QTimer* bufferAnim;
    QPixmap* loadDoneText;
    KozakScroll* kozakScroll;

    bool transitionState;
    QTimer* transitionTimer;
    int transitionTarget;

    ChallengeEngine* challenge;

    int kaiFrame;

public:
    BGM* mainMenuBGM;
    BGM* marchBGM;
    BGM* sacredWar;
    BGM* sound1BGM;
    Phonon::MediaObject* transSound;
    Phonon::MediaObject* menuSound;

private slots:
    void changeScreen();
    void lightDownButton();
    void lightUpButton();
    void lightUpNGSButton();
    void lightUpCESButton();
    void execButtonDown();
    void execButtonUp();

    void bufferAnimBegin();

    void toSplash();
    void toSplashCeption();

    void lightUpColor();

    void initializeMap();

    void pinchMainCharOn();
    void pinchMainCharOff();

    void startKozak();
    void endKozak();

    void transToggle();

    void quitGameSession();

    void goToResultScreen();

    void goToLoader();

    void endKaiAnim();

    void kaiAnimFrame();

    void soundDecide();

};

#endif // MAINCLASS_H
