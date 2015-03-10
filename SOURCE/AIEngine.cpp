#include "AIEngine.h"
#include "BattleEngine.h"

AIEngine::AIEngine(int* p, int* pC, int *m, int *t, Building **b, int sp, QList<Unit *> *enmy, QList<Unit *>* mine, int fld, bool fac, void* eng) {
    myPop = p;
    myPopCap = pC;
    myList = mine;
    money = m;
    technology = t;
    buildings = b;
    brainTimer = new QTimer();
    connect(brainTimer,SIGNAL(timeout()),this,SLOT(brain()));
    brainTimer->setInterval(sp);
    enemyList = enmy;
    fieldWidth = fld;
    selectedCmd = NULL;
    engine = eng;
    isRed = fac;
    if(isRed)
        faction = "red";
    else
        faction = "blue";
}

void AIEngine::startAI() {
    brainTimer->start();
}

void AIEngine::stopAI() {
    brainTimer->stop();
}

Command* AIEngine::getCommand(QString commandType) {
    ////qDebug(commandType.toAscii());
    Command* cmd;
    for(int i = 0 ; i < 8 ; i++)
        if((cmd = buildings[i]->getCommand(commandType)))
            if(cmd->isReady())
                return cmd;

    return NULL;
}

void AIEngine::executeCommand(Command *cmd) {
    if(!cmd)
        return;

    ////qDebug(cmd->getType().toAscii());

    Command* temp = ((BattleEngine*)engine)->highlightedCmd;
    ((BattleEngine*)engine)->highlightedCmd = cmd;
    ((BattleEngine*)engine)->commandInterface();
    ((BattleEngine*)engine)->highlightedCmd = temp;
}



bool AIEngine::spawnUnitWithLevel(QString atkType, QString defType, int level) {
    Command* cmd = NULL;
    QString command = "spawn unit ";
    command.append(defType).append(" ");
    command.append(atkType).append(" lv");
    command.append(QString::number(level)).append(" ");
    command.append(faction);
    if((cmd = getCommand(command))) {
        executeCommand(cmd);
        return true;
    }
    else
        return false;
}

bool AIEngine::unitSpawnByPriority(QString atkType, QString defType, bool lowPriority) {
    QString x = "";
    ////qDebug(x.append(atkType).append(defType).append("PRIORITY UNIT SPAWN!").toAscii());
    if(lowPriority) {
        for(int i = 1 ; i <= 3 ; i++)
            if(spawnUnitWithLevel(atkType,defType,i))
                return true;
    }
    else {
        for(int i = 3 ; i >= 1 ; i--)
            if(spawnUnitWithLevel(atkType,defType,i))
                return true;
    }
    return false;
}

void AIEngine::buildAtFrontSlot(QString type) {
    QString command = "spawn building ";
    command.append(type);
    for(int i = 7 ; i >= 0 ; i--) {
        if (!(buildings[i]->getType().compare("Empty")) && (buildings[i]->getType().compare("CommandCenter"))) {
            executeCommand(buildings[i]->getCommand(command));
            return;
        }
    }
    ////qDebug("NONE");
}

int AIEngine::lookForBuildingByLevel(QString type, int level) {
    for(int i = 0 ; i < 8 ; i++) {
        if (!(buildings[i]->getType().compare(type)) && buildings[i]->getLevel() == level)
            return i + 1;
    }
    return 0;
}

int AIEngine::lookForBuildingByPriority(QString type, bool lowPriority) {
    int b = 0;
    if(lowPriority) {
        for(int i = 1 ; i <= 6 ; i++) {
            if((b = lookForBuildingByLevel(type,i)))
                return b;
        }
    }
    else {
        for(int i = 6 ; i >= i ; i++) {
            if((b = lookForBuildingByLevel(type,i)))
                return b;
        }
    }
    return 0;
}

void AIEngine::upgradeBuilding(int slot) {
    if(!slot)
        return;

    executeCommand(buildings[slot - 1]->getCommandByName("Upgrade"));
}

bool AIEngine::blgNeedsRepair(Building* target) {
    if(target->getHitpoints() < target->getHpMAX())
        return true;
    else
        return false;
}

bool AIEngine::repairBlg() {
    for(int i = 8 ; i > 0 ; i--) {
        if(blgNeedsRepair(buildings[i-1])) {
            if(buildings[i-1]->getCommand("repair")) {
                executeCommand(buildings[i-1]->getCommand("repair"));
                return true;
            }
        }
    }
    return false;
}

int AIEngine::getBuildingCount(QString type) {
    int ctr = 0;
    for(int i = 0 ; i < 8 ; i++) {
        if(!(buildings[i]->getType().compare(type))) {
            ctr++;
        }
    }
    return ctr;
}

bool AIEngine::build() {
    ////qDebug("BuildingSpawn!");
    int per = ((BattleEngine*)engine)->randomNumber(1,100);
    ////qDebug(QString::number(per).toAscii());
    ////qDebug(QString::number(*money).append(" - MONEY").toAscii());
    if(*money <= 500 || getBuildingCount("TechnologyC") < 1 || getBuildingCount("EconomicC") < 2) {
        if(per <= 40 && getBuildingCount("EconomicC") < 2) {
            buildAtFrontSlot("economic_center");
            return true;
        }
        else if(per <= 65 && getBuildingCount("TechnologyC") < 1){
            buildAtFrontSlot("technology_center");
            return true;
        }
        else {
            if(getBuildingCount("EconomicC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("EconomicC",true));
            }
            if(getBuildingCount("TechnologyC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            return true;
        }
    }
    else if(*money <= 1000 || getBuildingCount("Barracks") < 1) {
        if(getBuildingCount("Barracks") < 1) {
            buildAtFrontSlot("barracks");
            return true;
        }
        else {
            if(getBuildingCount("EconomicC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("EconomicC",true));
            }
            if(getBuildingCount("TechnologyC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            if(getBuildingCount("CommandCenter") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            return true;
        }
    }
    else if(*money <= 1500 || getBuildingCount("Barracks") < 2) {
        if(per <= 25 && getBuildingCount("Barracks") < 2) {
            buildAtFrontSlot("barracks");
            return true;
        }
        else if(per <= 75 && lookForBuildingByLevel("Barracks",1)) {
            upgradeBuilding(lookForBuildingByLevel("Barracks",1));
            return true;
        }
        else {
            if(getBuildingCount("EconomicC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("EconomicC",true));
            }
            if(getBuildingCount("TechnologyC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            return true;
        }
    }
    else if(*money <= 2000 || getBuildingCount("Warfactory") < 1) {
        if(getBuildingCount("Warfactory") < 1) {
            buildAtFrontSlot("warfactory");
            return true;
        }
        else {
            if(getBuildingCount("EconomicC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("EconomicC",true));
            }
            if(getBuildingCount("TechnologyC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            return true;
        }
    }
    else if(*money <= 2500 || getBuildingCount("Airfield") < 1) {
        if(per <= 25 && getBuildingCount("Airfield") < 1) {
            buildAtFrontSlot("airfield");
            return true;
        }
        else if(per <= 50 && lookForBuildingByLevel("Warfactory",1)) {
            upgradeBuilding(lookForBuildingByLevel("Warfactory",1));
            return true;
        }
        else if(per <= 75 && lookForBuildingByLevel("Airfield",1)) {
            upgradeBuilding(lookForBuildingByLevel("Airfield",1));
            return true;
        }
        else {
            if(getBuildingCount("EconomicC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("EconomicC",true));
            }
            if(getBuildingCount("TechnologyC") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            if(getBuildingCount("CommandCenter") > 1) {
                upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
            }
            return true;
        }
    }
    else if(*money > 3000) {
        bool tries[6];
        for(int i = 0 ; i < 6 ; i++)
            tries[i] = true;

        do {
            if(per <= 20 && lookForBuildingByPriority("Barracks",true) && tries[0]) {
                if(buildingNeedsUpgrade(lookForBuildingByPriority("Barracks",true)))
                    upgradeBuilding(lookForBuildingByPriority("Barracks",true));
                tries[0] = false;
            }
            else if(per <= 35 && lookForBuildingByPriority("Warfactory",true) && tries[1]) {
                if(buildingNeedsUpgrade(lookForBuildingByPriority("Warfactory",true)))
                    upgradeBuilding(lookForBuildingByPriority("Warfactory",true));
                tries[1] = false;
            }
            else if(per <= 55 && lookForBuildingByPriority("Airfield",true) && tries[2]) {
                if(buildingNeedsUpgrade(lookForBuildingByPriority("Airfield",true)))
                    upgradeBuilding(lookForBuildingByPriority("Airfield",true));
                tries[2] = false;
            }
            else if(per <= 75 && lookForBuildingByPriority("EconomicC",true) && tries[3]) {
                if(buildingNeedsUpgrade(lookForBuildingByPriority("EconomicC",true)))
                    upgradeBuilding(lookForBuildingByPriority("EconomicC",true));
                tries[3] = false;
            }
            else if (lookForBuildingByPriority("TechnologyC",true) && tries[4]){
                if(buildingNeedsUpgrade(lookForBuildingByPriority("TechnologyC",true)))
                    upgradeBuilding(lookForBuildingByPriority("TechnologyC",true));
                tries[4] = false;
            }
            else if (lookForBuildingByPriority("CommandCenter",true) && tries[4]){
                if(buildingNeedsUpgrade(lookForBuildingByPriority("CommandCenter",true)))
                    upgradeBuilding(lookForBuildingByPriority("CommandCenter",true));
                tries[5] = false;
            }
        } while (tries[0] && tries[1] && tries[2] && tries[3] && tries[4] && tries[5]);
        return true;
    }
    return false;
}

bool AIEngine::buildingNeedsUpgrade(int slot) {
    if(buildings[slot-1]->getLevel() > 2 && !(buildings[slot-1]->getType().contains("EconomicC")))
        return false;
    else if (buildings[slot-1]->getLevel() > 5 && (buildings[slot-1]->getType().contains("EconomicC")))
        return false;

    return true;
}

void AIEngine::safe() {
    int per = ((BattleEngine*)engine)->randomNumber(1,100);

    if(repairBlg())
        return;

    if(per <= 80 && build())
        ;
    else
        safeUnitSpawn();
}

void AIEngine::safeUnitSpawn() {
    ////qDebug("UnitSpawn!");
    int per = ((BattleEngine*)engine)->randomNumber(1,100);
    ////qDebug(QString::number(per).append(" PER ").append(QString::number(*money)).append(" MON ").toAscii());
    if(*money <= 500) {
            unitSpawnByPriority("AI","inf",true);
    }
    else if (*money <= 1000) {
        if(per <= 75)
            unitSpawnByPriority("AI","inf",true);
        else
            unitSpawnByPriority("AI","veh",true);
    }
    else if (*money <= 1500) {
        if(per <= 50)
            unitSpawnByPriority("AI","inf",true);
        else if(per <= 75)
            unitSpawnByPriority("AI","veh",true);
        else if(per <= 85)
            unitSpawnByPriority("AI","air",true);
        else
            unitSpawnByPriority("AT","veh",true);
    }
    else if (*money <= 2000) {
        if(per <= 25)
            unitSpawnByPriority("AI","inf",false);
        else if(per <= 45)
            unitSpawnByPriority("AI","veh",false);
        else if(per <= 60)
            unitSpawnByPriority("AI","air",false);
        else if(per <= 75)
            unitSpawnByPriority("AT","veh",false);
        else if(per <= 85)
            unitSpawnByPriority("AT","air",true);
        else
            unitSpawnByPriority("AA","veh",true);
    }
    else if (*money <= 2500) {
        if(per <= 20)
            unitSpawnByPriority("AI","inf",false);
        else if(per <= 40)
            unitSpawnByPriority("AI","veh",false);
        else if(per <= 55)
            unitSpawnByPriority("AI","air",false);
        else if(per <= 75)
            unitSpawnByPriority("AT","veh",false);
        else if(per <= 85)
            unitSpawnByPriority("AT","air",true);
        else if(per <= 90)
            unitSpawnByPriority("AA","veh",true);
        else
            unitSpawnByPriority("AA","air",true);
    }
    else if (*money <= 3000) {
        if(per <= 20)
            unitSpawnByPriority("AI","inf",false);
        else if(per <= 40)
            unitSpawnByPriority("AI","veh",false);
        else if(per <= 55)
            unitSpawnByPriority("AI","air",false);
        else if(per <= 75)
            unitSpawnByPriority("AT","veh",false);
        else if(per <= 85)
            unitSpawnByPriority("AT","air",true);
        else if(per <= 90)
            unitSpawnByPriority("AA","veh",true);
        else
            unitSpawnByPriority("AA","air",true);
    }
    else if (*money > 3000) {
        if(per <= 20)
            unitSpawnByPriority("AI","inf",false);
        else if(per <= 40)
            unitSpawnByPriority("AI","veh",false);
        else if(per <= 55)
            unitSpawnByPriority("AI","air",false);
        else if(per <= 75)
            unitSpawnByPriority("AT","veh",false);
        else if(per <= 85)
            unitSpawnByPriority("AT","air",false);
        else if(per <= 90)
            unitSpawnByPriority("AA","veh",false);
        else
            unitSpawnByPriority("AA","air",false);

    }
}

bool AIEngine::assessBestCounter(Unit *target) {
    if(target == NULL) {
        ////qDebug("You gave me NULL!");
        return false;
    }
    if(!(target->getDefenseType().compare("Air"))) {
        if((unitSpawnByPriority("aa","veh",false)))
            return true;
        else if((unitSpawnByPriority("aa","air",false)))
            return true;
        else
            return false;
    }
    else if(!(target->getDefenseType().compare("Infantry"))) {
        if(!(target->getAttackType().compare("AI"))) {
            if((unitSpawnByPriority("AI","veh",false)))
                return true;
            else if((unitSpawnByPriority("AI","inf",false)))
                return true;
            else if((unitSpawnByPriority("AI","air",false)))
                return true;
            else if((unitSpawnByPriority("AT","veh",false)))
                return true;
            else if((unitSpawnByPriority("AT","air",false)))
                return true;
            else if((unitSpawnByPriority("AT","inf",false)))
                return true;
            else
                return false;
        }
        else if(!(target->getAttackType().compare("AT"))) {
            if((unitSpawnByPriority("AI","veh",false)))
                return true;
            else if((unitSpawnByPriority("AI","inf",false)))
                return true;
            else if((unitSpawnByPriority("AI","air",false)))
                return true;
            else if((unitSpawnByPriority("AT","veh",false)))
                return true;
            else if((unitSpawnByPriority("AT","inf",false)))
                return true;
            else if((unitSpawnByPriority("AT","air",false)))
                return true;
            else
                return false;
        }
    }
    else if(!(target->getDefenseType().compare("Vehicle"))) {
        if(!(target->getAttackType().compare("AA"))) {
            if((unitSpawnByPriority("AT","veh",false)))
                return true;
            else if((unitSpawnByPriority("at","inf",false)))
                return true;
            else if((unitSpawnByPriority("AI","veh",false)))
                return true;
            else if((unitSpawnByPriority("AI","inf",false)))
                return true;
            else if((unitSpawnByPriority("AT","air",false)))
                return true;
            else if((unitSpawnByPriority("AI","air",false)))
                return true;
            else
                return false;
        }
        else if(!(target->getAttackType().compare("AI"))) {
            if((unitSpawnByPriority("AT","veh",false)))
                return true;
            else if((unitSpawnByPriority("AT","air",false)))
                return true;
            else if((unitSpawnByPriority("AI","veh",false)))
                return true;
            else if((unitSpawnByPriority("AI","air",false)))
                return true;
            else if((unitSpawnByPriority("AT","inf",false)))
                return true;
            else if((unitSpawnByPriority("AI","inf",false)))
                return true;
            else
                return false;
        }
        else if(!(target->getAttackType().compare("AT"))) {
            ////qDebug("ENEMY VEH AT");
            if((unitSpawnByPriority("AT","inf",false))) {
                ////qDebug("I made AT inf");
                return true;
            }
            else if((unitSpawnByPriority("AT","veh",false)))
                return true;
            else if((unitSpawnByPriority("AT","air",false)))
                return true;
            else if((unitSpawnByPriority("AI","inf",false)))
                return true;
            else if((unitSpawnByPriority("AI","veh",false)))
                return true;
            else if((unitSpawnByPriority("AI","air",false)))
                return true;
            else
                return false;
        }
    }
    return false;
}

void AIEngine::normal() {
    if(repairBlg())
        return;

    int per = ((BattleEngine*)engine)->randomNumber(1,100);

    if(per <= 50 && !assessBestCounter(getFrontMostUnit())) {
        build();
    }
    else if(per <= 75 && build())
        ;
    else if(per <= 95)
        safeUnitSpawn();

}

void AIEngine::threat() {
    if(!repairBlg())
        assessBestCounter(getFrontMostUnit());
    executeCommand(getCommand("power artillery"));
    executeCommand(getCommand("power blitz"));
    executeCommand(getCommand("power laser"));
    executeCommand(getCommand("power revolt"));
}

void AIEngine::emergency() {
    int per = ((BattleEngine*)engine)->randomNumber(1,100);

    assessBestCounter(getFrontMostUnit());

    if(per <= 70)
        if(((BattleEngine*)engine)->getFrontmostEnemyUnit(isRed,false))
            executeCommand(getCommand("power artillery"));
}

int AIEngine::distanceFromEnemyFront() {
    int acc;
    if(enemyList->isEmpty())
        return -1;
    if(!isRed) {
        acc = 0 - 1;
        for(int i = 0 ; i < enemyList->size() ; i++) {
            if(enemyList->value(i)->xCoord > acc && acc < ((BattleEngine*)engine)->ui->battleField->width())
                acc = enemyList->value(i)->xCoord;
        }
    }
    else {
        acc = ((BattleEngine*)engine)->ui->battleField->width() + 1;
        for(int i = 0 ; i < enemyList->size() ; i++) {
            if(enemyList->value(i)->xCoord < acc && acc > 0)
                acc = enemyList->value(i)->xCoord + enemyList->value(i)->width;
        }
    }

    if(!isRed)
        return ((BattleEngine*)engine)->ui->battleField->width() - acc;
    else
        return acc;
}

void AIEngine::brain() {

    ////qDebug("AIRound!");

    if(*myPop >= *myPopCap) {
        QString temp = "upgrade ";
        temp.append(faction).append(" slot8");
        executeCommand(getCommand(temp));
    }


    if(distanceFromEnemyFront() < 0 || enemyList->isEmpty()) {
        ////qDebug("SAFE");
        safe();
    }
    else if(distanceFromEnemyFront() <= ((BattleEngine*)engine)->ui->battleField->width() / 4) {
        ////qDebug("EMERGENCY");
        emergency();
    }
    else if(distanceFromEnemyFront() <= ((BattleEngine*)engine)->ui->battleField->width() / 2) {
        ////qDebug("THREAT");
        threat();
    }
    else if(distanceFromEnemyFront() >= ((BattleEngine*)engine)->ui->battleField->width() / 2) {
        ////qDebug("NORMAL");
        normal();
    }

    executeCommand(getCommand("power ecoBoom"));
}

Unit* AIEngine::getFrontMostUnit() {
    ////qDebug("get front most unit!");
    if(enemyList->isEmpty()) {
        ////qDebug("enemy list is empty!");
        return NULL;
    }

    Unit* frontMost = NULL;
    int acc;

    if(!isRed) {
        ////qDebug("i am blue!");
        acc = 0 - 1;
        for(int i = 0 ; i < enemyList->size() ; i++) {
            if(enemyList->value(i)->xCoord > acc && acc < ((BattleEngine*)engine)->ui->battleField->width()) {
                ////qDebug("found something");
                acc = enemyList->value(i)->xCoord;
                frontMost = enemyList->value(i);
            }
        }
    }
    else {
        ////qDebug("i am red!");
        acc = ((BattleEngine*)engine)->ui->battleField->width() + 1;
        for(int i = 0 ; i < enemyList->size() ; i++) {
            if(enemyList->value(i)->xCoord < acc && acc > 0) {
                ////qDebug("found something");
                acc = enemyList->value(i)->xCoord;
                frontMost = enemyList->value(i);
            }
        }
    }

    ////qDebug(QString::number((int)frontMost).toAscii());
    return frontMost;
}

AIEngine::~AIEngine() {
    brainTimer->stop();
    delete brainTimer;
}

void AIEngine::setSpeed(int msec) {
    brainTimer->setInterval(msec);
}
