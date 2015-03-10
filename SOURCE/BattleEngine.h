#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include <QQueue>
#include <QTimer>
#include <QString>
#include "Unit.h"
#include "Building.h"
#include <QPoint>
#include <qmath.h>
#include "Command.h"
#include <QThread>
#include "Effect.h"
#include "AIEngine.h"
#include <QObjectCleanupHandler>
#include <phonon/MediaObject>
#include "BGM.h"
#include <QSound>

class BattleEngine : public QThread{

    private: Q_OBJECT

    public:
        explicit BattleEngine(Ui::MainClass* u, void* m);
        ~BattleEngine();

        void connectToInterface(Command* c);

        //Clean Up Purposes
        void loadSpritesFor(bool faction, QString defType, QString atkType, int level);
        void destroySpritesFor(bool faction, QString defType,QString atkType, int level);
        bool spriteForTypeExists(bool faction, QString defType, QString atkType, int level);
        bool thereExistsThisTypeOfUnit(bool faction, QString defType, QString atkType, int level);
        bool thereExistsThisTypeOfBlg(bool isRed, QString type, int level);
        void loadSpritesForBlg(bool isRed, QString type, int level);
        void destroySpritesForBlg(bool isRed, QString type, int level);
    public slots:
        void cleanUpSFX();
    public:
        void run();

        //Support Powers
        QList <Unit*>* getUnitsWithinInterval(int x, int width, bool isRed, bool isAir);
        void createExplosion(int xCoord, int width, int damage, bool isRed, bool isAir);
        bool xIsWithinInterval(int intX, int intW, int targetX);
        void damageAllUnitsInSet(QList <Unit*>* targetSet, int amt);
        void artilleryStrike(bool firerIsRed);
            int redCrosshair;
            int blueCrosshair;
            public slots:
            void fireRedShell();
            void fireBlueShell();
            void laser(bool firerIsRed);
            void endRedLaser();
            void endBlueLaser();
            void redLaserFire();
            void blueLaserFire();
            public:
            QTimer* redLaserTimer;
            QTimer* blueLaserTimer;
            QLabel* redLaser;
            QLabel* blueLaser;
            bool redLaserIsInEffect;
            bool blueLaserIsInEffect;
            QSound* laserSound;

        //Graphics Utilities
        void createCombatEffect(int xCoord, bool isGnd, QWidget* widget);
        QPoint* vectorXY(int magnitude, int angle, int baseX, int baseY);

        //Utilities
        QString determineSlotNo (int slotNo);
        QString determineFaction (bool isRed);
        int randomNumber (int low, int high);
        bool searchForUnit(Unit* target, bool red);
        Unit* getFrontmostEnemyUnit(bool perspective, bool isAir);
        void destroyAllUnits();
        void deleteAllBuildings();
        void deleteAllEffects();

        //Game Settings
        void setPlayerType(char type);
        void setAIType(char type);
        void setEnemyDiff(char diff);
        void setPlayerSide(bool red);
        void initializeAI();
        void finalizeAI();

        //Unit Utilities
        bool anyAttackableEnemyUnitsInRange(Unit* base);
        QList <Unit*>* getAttackableEnemyUnits(Unit* base);
        Unit* getNearestEnemyUnitFromSet(Unit* base, QList <Unit*>* set);

        //Game Loader
    public slots:
        void load1();
        void load2();
        void load3();
        void load4();
        void load5();
        void load6();
        void load7();
        void load8();
        void load9();
        void load10();

    private:
        bool unitCanAttackUnit(Unit* base, Unit* target);
        void placeBuildingAtSlot();

    private slots:
        void economyRound();
        void technologyRound();
        void cleanUp(); //removes dead units from battle field
        void animateHighlighted();

    public slots:
        void reprintBlgData();
        void spawnInfLv1();
        void engageSelectButton();
        void disengageSelectButton();
        void disengageHighlightedCMD();

        void spawnUnit(QString defType, QString atkType, int level, bool isRed);
        void spawnBuilding(QString type, int slot, int isRed);
        void deselectAllRedBuildings();
        void deselectAllBlueBuildings();
        void startCombatSession();
        void endCombatSession();
        void buildSpriteBase();

        void commandInterface();

        void commandSelect();

        void damageFrontMostBuilding(bool red, int amt);

        void stopEcoBoomRed();
        void stopEcoBoomBlue();

        void revoltRed();
        void revoltBlue();

        //Pause mechanism
        void pauseGame();
        void resumeGame();
        void quitGame();
        void restartGame();
        void freezeAllUnits();
        void unfreezeAllUnits();
        void freezeAllEffects();
        void unfreezeAllEffects();
        void buttonLightup();
        void buttonLightdown();
        void freezeAllCommands();
        void unfreezeAllCommands();

        void redLose();
        void blueLose();
        void winlose();


    public:
        Phonon::MediaObject* alertSound;
        BGM* ambientSound;

        bool isInSession;
        AIEngine* AI;
        Command* highlightedCmd;
        QIcon* switchBase[3][2]; //[switchno][state]
        QIcon* exec[2];
        QList <QIcon*>* iconAnim;
        QList <QPixmap*>* effects[2][3]; //[air/ground][variation]

        QIcon* cmdIconBase[2][15]; //[off/on][type]
        // 0 - airfield
        // 1 - barracks
        // 2 - warfactory
        // 3 - ecoC
        // 4 - techC
        // 5 - superweapon
        // 6 - upgrade
        // 7 - sell
        // 8 - repair
        // 9 - artillery
        //10 - blitz
        //11 - ecoBoom
        //12 - revolt
        //13 - laser
        //14 - nuke

        QIcon* unitIconBase[2][24]; //[off/on][type]
        //00 - AIR AA LV1
        //01 - AIR AA LV2
        //02 - AIR AA LV3
        //03 - AIR AI LV1
        //04 - AIR AI LV2
        //05 - AIR AI LV3
        //06 - AIR AT LV1
        //07 - AIR AT LV2
        //08 - AIR AT LV3
        //09 - INF AI LV1
        //10 - INF AI LV2
        //11 - INF AI LV3
        //12 - INF AT LV1
        //13 - INF AT LV2
        //14 - INF AT LV3
        //15 - VEH AA LV1
        //16 - VEH AA LV2
        //17 - VEH AA LV3
        //18 - VEH AI LV1
        //19 - VEH AI LV2
        //20 - VEH AI LV3
        //21 - VEH AT LV1
        //22 - VEH AT LV2
        //23 - VEH AT LV3

       //Session speifications
        char playerType;
        char aiType;

        bool redEcoBoom;
        bool blueEcoBoom;

        //        m = military
        //        e = economy
        //        s = social
        //        t = technology
        char enemyDiff;
        //        e = easy
        //        m = medium
        //        h = hard
        //        s = ultrahard

        QPushButton* highlighted;
        int animationIndex;
        bool cleanSession; //true if a clean session if being done
        QList <Unit*>* redUnits;
        QList <Unit*>* blueUnits;
        QList <Effect*>* effectList;

        QTimer* selectButtonAnimator;
        QTimer* cleaner; //timer for checking on dead units in the battlefield
        QTimer* resourceRound; //timer for resource rounds

        int ecoProd[6];
        int techProd[3];

        bool playerIsRed;

        //Red Player Stats
        int redMoney;
        int redTech;

        int redPop;
        int redPopCap;

        Building* redBlg[8];

        //Blue Player Stats
        int blueMoney;
        int blueTech;

        int bluePop;
        int bluePopCap;

        Building* blueBlg[8];

        Ui::MainClass *ui;
        Unit* latestUnit;

        QPixmap* blgSpriteBase[2][6][6][2];
        //red = 0, blue = 1
        //cc = 0, brks = 1, wrfctry = 2, airfld = 3, ecoC = 4, techC = 5
        //lv1 = 0, lv2 = 1, lv3 = 2, lv4 = 3, lv5 = 4, lv6 = 5
        //off = 0, on = 1

        QList <QPixmap*>* unitSpriteBase[2][3][3][3][3];
        //unitSpriteBase[blue/red][air/inf/veh][aa/ai/at][lv1/lv2/lv3][wlk/atk/std]
        //red = 0, blue = 1
        //air = 0, inf = 1, veh = 2
        //aa = 0, ai = 1, at = 2
        //lv1 = 0, lv2 = 1, lv3 = 2
        //wlk = 0, atk = 1, std = 2


        //Player statistics
        int kills;
        int deaths;
        int unitsProduced;
        int blgDestroyed;
        int blgLost;
        int blgProduced;

        void* main;

    signals:
        void endSession();
        void startSession();

        void quitGameSIG();

        void redDefeat();
        void blueDefeat();

        void gameLoaded();
};

#endif // BATTLEENGINE_H
