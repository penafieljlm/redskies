#ifndef AIENGINE_H
#define AIENGINE_H

#include <QObject>
#include "Building.h"
#include <QTimer>
#include <QList>

class AIEngine : public QObject
{
    Q_OBJECT
public:
    explicit AIEngine(int* p, int* pC, int* m, int* t, Building* b[8], int sp, QList <Unit*>* enmy, QList <Unit*>* mine, int fld, bool fac, void* eng);
    void setSpeed(int msec);
    ~AIEngine();

private:
    void safe();
        void safeUnitSpawn();
        void safeBuildSpawn();
    void normal();
        bool assessBestCounter(Unit* target);
    void threat();
    void emergency();

    bool blgNeedsRepair(Building* target);
    bool repairBlg();

    Command* getCommand (QString commandType);
    void executeCommand(Command* cmd);
    bool spawnUnitWithLevel(QString atkType, QString defType, int level);
    bool unitSpawnByPriority (QString atkType, QString defType, bool lowPriority);

    bool build();
    void buildAtFrontSlot(QString type);
    int lookForBuildingByLevel(QString type, int level);
    int lookForBuildingByPriority(QString type, bool lowPriority);
    void upgradeBuilding(int slot);
    int getBuildingCount(QString type);

    bool buildingNeedsUpgrade(int slot);

    int distanceFromEnemyFront();

    Unit* getFrontMostUnit();

private slots:
    void brain();

public slots:
    void startAI();
    void stopAI();

private:
    Command* selectedCmd;
    int* money;
    int* technology;
    Building** buildings;
    QTimer* brainTimer;
    QList <Unit*>* enemyList;
    QList <Unit*>* myList;
    QString faction;
    int fieldWidth;
    bool isRed;
    void* engine;
    int* myPopCap;
    int* myPop;

};

#endif // AIENGINE_H
