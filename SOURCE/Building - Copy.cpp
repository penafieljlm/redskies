#include "mainclass.h"
#include "ui_mainclass.h"
#include <QtCore/QCoreApplication>
#include "Building.h"
#include "QPropertyAnimation"

Building::Building(QPixmap* imgOn, QPixmap* imgOff, QString nm, QString setDesc, bool red, int slot, void *eng, Ui::MainClass* u, QString tp, int hp) {
    sellPrice = 0;
    hitpoints = hp;
    hpMax = hp;
    type = tp;
    isRed = red;
    description = setDesc;
    engine = eng;
    ui = u;
    name = nm;
    level = 1;

    if(isRed) {
        switch(slot) {
            case 1:
                displayLabel = ui->redSlot1;
                displayButton = ui->redSel1;
                break;
            case 2:
                displayLabel = ui->redSlot2;
                displayButton = ui->redSel2;
                break;
            case 3:
                displayLabel = ui->redSlot3;
                displayButton = ui->redSel3;
                break;
            case 4:
                displayLabel = ui->redSlot4;
                displayButton = ui->redSel4;
                break;
            case 5:
                displayLabel = ui->redSlot5;
                displayButton = ui->redSel5;
                break;
            case 6:
                displayLabel = ui->redSlot6;
                displayButton = ui->redSel6;
                break;
            case 7:
                displayLabel = ui->redSlot7;
                displayButton = ui->redSel7;
                break;
            case 8:
                displayLabel = ui->redSlot8;
                displayButton = ui->redSel8;
                break;
            default:
                break;
        }
    }
    else {
        switch(slot) {
            case 1:
                displayLabel = ui->blueSlot1;
                displayButton = ui->blueSel1;
                break;
            case 2:
                displayLabel = ui->blueSlot2;
                displayButton = ui->blueSel2;
                break;
            case 3:
                displayLabel = ui->blueSlot3;
                displayButton = ui->blueSel3;
                break;
            case 4:
                displayLabel = ui->blueSlot4;
                displayButton = ui->blueSel4;
                break;
            case 5:
                displayLabel = ui->blueSlot5;
                displayButton = ui->blueSel5;
                break;
            case 6:
                displayLabel = ui->blueSlot6;
                displayButton = ui->blueSel6;
                break;
            case 7:
                displayLabel = ui->blueSlot7;
                displayButton = ui->blueSel7;
                break;
            case 8:
                displayLabel = ui->blueSlot8;
                displayButton = ui->blueSel8;
                break;
            default:
                break;
        }

    }

    //displayButton->setGeometry();

    imageOn = imgOn;
    imageOff = imgOff;
    if(imageOff != NULL)
        displayLabel->setPixmap(*imageOff);

    displayLabel->update();

    displayButton->setStyleSheet("background-image: url(null); border-color: rgba(255, 255, 255, 0);\nbackground-color: rgba(255, 255, 255, 0);");
    displayButton->setFocusPolicy(Qt::NoFocus);

    cmdList = new QList <Command*> ();

    connect(this,SIGNAL(hpModify()),((BattleEngine*)engine),SLOT(reprintBlgData()));
}

bool Building::getRed() {
    return isRed;
}

int Building::getHpMAX() {
    return hpMax;
}

void Building::setHpMAX(int amt) {
    hpMax = amt;
    hitpoints = hpMax;
}

QLabel* Building::getDisplayLabel() {
    return displayLabel;
}


int Building::getHitpoints() {
    return hitpoints;
}

void Building::setHitpoints(int val) {
    hitpoints = val;

    if(hitpoints > hpMax)
        hitpoints = hpMax;

    emit hpModify();
}

void Building::addCmd(QIcon *imgOn, QIcon *imgOff, QString nm, QString desc, QString type, int price, int tech) {
    Command* newCmd = new Command(imgOn,imgOff,nm,desc,type,engine,this);
    newCmd->setCostReq(price);
    newCmd->setTechReq(tech);
    if(isRed)
        newCmd->setParent(ui->leftBaseArea);
    else
        newCmd->setParent(ui->rightBaseArea);

    cmdList->append(newCmd);
}

void Building::select() {
    ((BattleEngine*)engine)->deselectAllRedBuildings();
    ((BattleEngine*)engine)->deselectAllBlueBuildings();
    isSelected = true;
    if(imageOn != NULL)
        displayLabel->setPixmap(*imageOn);

    if(((BattleEngine*)engine)->playerIsRed && isRed)
        displayCommands();
    else if(!((BattleEngine*)engine)->playerIsRed && !isRed)
        displayCommands();
}

void Building::deselect() {
    isSelected = false;
    if(imageOff != NULL)
        displayLabel->setPixmap(*imageOff);

    hideCommands();    
}

int Building::getLevel() {
    return level;
}

QString Building::getName() {
    return name;
}

QString Building::getDesc() {
    return description;
}

void Building::displayCommands() {
    QPoint* location = NULL;
    QPoint* startPt = NULL;
    int v = 0;
    if(cmdList->size() > 0)
        for(int i = 0 ; i < 360 ; i += 360 / cmdList->size()) {
            location = ((BattleEngine*)engine)->vectorXY(80,i + 90,displayButton->x() + 45,displayButton->y() + 45);
            if(cmdList->value(v) != NULL) {
                cmdList->value(v)->setGeometry(displayButton->x()+45-25, displayButton->y()+45-25, 50, 50);
                cmdList->value(v)->show();
                startPt = new QPoint(displayButton->x()+45-25, displayButton->y()+45-25);
                location->setX(location->x() - 25);
                location->setY(location->y() - 25);
                cmdList->value(v)->setPoints(startPt,location);
                cmdList->value(v)->moveToEndPoint();
            }
            delete location;
            v++;
        }
    delete startPt;
}

void Building::setSellPrice(int amt) {
    sellPrice = amt;
}

int Building::getSellPrice() {
    return sellPrice;
}

void Building::hideCommands() {
    for(int i = 0 ; i < cmdList->size() ; i ++) {
        cmdList->value(i)->setVisible(false);
        cmdList->value(i)->setGeometry(QRect(displayButton->x() + 45, displayButton->y() + 45, 90, 90));
    }
}

bool Building::getFaction() {
    return isRed;
}

void Building::clearCommands() {
    ((BattleEngine*)engine)->cleaner->stop();
    hideCommands();

    for(int i = 0 ; i < cmdList->size() ; i ++) {
        if(((BattleEngine*)engine)->highlightedCmd == cmdList->value(i))
            ((BattleEngine*)engine)->disengageHighlightedCMD();
        delete cmdList->value(i);
    }
    cmdList->clear();
    ((BattleEngine*)engine)->cleaner->start(1);
}

void Building::promote() {
    BattleEngine* e = ((BattleEngine*)(engine));
    QString desc;
    int faction = 1;
    if(isRed)
        faction = 0;

    int blgType = 0;

    //clear commands list
    //reconstruct commands list
    level++;
    clearCommands();

    QString spawnAcc = "";
    QString spawnUnit = "spawn unit ";
    QString stringColor = ((BattleEngine*)engine)->determineFaction(isRed);
    int prc = 0;
    int techReq = 0;

    int i;
    for(i = 0 ; i < 8 ; i++) {
        if(((BattleEngine*)engine)->redBlg[i] == this)
            break;
        else if(((BattleEngine*)engine)->blueBlg[i] == this)
            break;
    }
    i+=1;
    QString slotIndicator = ((BattleEngine*)engine)->determineSlotNo(i);

    QString temp = "upgrade ";
    temp.append(stringColor);

    temp.append(slotIndicator);

    if(!(type.compare("Barracks"))) {
        blgType = 1;
        if(level > 3)
            level = 3;
        switch(level) {
            case 2:
                setHpMAX(1000);
                techReq = 300;
                name = "Army Barracks (LV2)";
                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("inf AI ").append("lv2 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][10],((BattleEngine*)engine)->unitIconBase[0][10],"Marine (LV2)","Highly trained soldiers.\nEquipped with modern equipment.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(100);
                this->getCommand(spawnAcc)->setCountdownMAX(400);

                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("inf AT ").append("lv2 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][13],((BattleEngine*)engine)->unitIconBase[0][13],"Javelin Trooper (LV2)","Highly trained anti-tank trooper.\nEquipped with a javelin missile launcher.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(200);
                this->getCommand(spawnAcc)->setCountdownMAX(800);

                description = "Produces LV2 infantry units.";
                desc = "Upgrades Army Barracks (LV2) to a Mobius Facility (LV3).\nUnlocks higher level units.";
                prc = 900;
                setSellPrice(450);
                break;
            case 3:
                setHpMAX(2000);
                name = "Mobius Facility (LV3)";
                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("inf AI ").append("lv3 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][11],((BattleEngine*)engine)->unitIconBase[0][11],"Shock Trooper (LV3)","Heavy anti-personnel trooper.\nEquipped with a heavy laser.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(200);
                this->getCommand(spawnAcc)->setCountdownMAX(400);

                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("inf AT ").append("lv3 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][14],((BattleEngine*)engine)->unitIconBase[0][14],"Mobius Trooper (LV3)","Heavy anti-tank trooper.\nEquipped with a heavy rail-gun.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(400);
                this->getCommand(spawnAcc)->setCountdownMAX(800);

                description = "Produces LV3 infantry units.";
                setSellPrice(900);
                break;
            default:
                //invalid
                break;
        }

    }
    else if(!(type.compare("Warfactory"))) {
        blgType = 2;
        if(level > 3)
            level = 3;
            switch(level) {
                case 2:
                    setHpMAX(3000);
                    techReq = 600;
                    name = "Modern Warfactory (LV2)";
                    spawnAcc.clear();
                    spawnAcc.append(spawnUnit).append("veh AT ").append("lv2 ").append(stringColor);
                    addCmd(((BattleEngine*)engine)->unitIconBase[1][22],((BattleEngine*)engine)->unitIconBase[0][22],"M1 Abrams (LV2)","A modern main battle tank\nutilized by modern factions.",spawnAcc);

                    this->getCommand(spawnAcc)->setCostReq(1000);
                    this->getCommand(spawnAcc)->setCountdownMAX(1100);

                    spawnAcc.clear();
                    spawnAcc.append(spawnUnit).append("veh AA ").append("lv2 ").append(stringColor);
                    addCmd(((BattleEngine*)engine)->unitIconBase[1][16],((BattleEngine*)engine)->unitIconBase[0][16],"Mobile GTAM (LV2)","A modern anti-air vehicle\nutilized by modern factions.",spawnAcc);

                    this->getCommand(spawnAcc)->setCostReq(800);
                    this->getCommand(spawnAcc)->setCountdownMAX(900);

                    spawnAcc.clear();
                    spawnAcc.append(spawnUnit).append("veh AI ").append("lv2 ").append(stringColor);
                    addCmd(((BattleEngine*)engine)->unitIconBase[1][19],((BattleEngine*)engine)->unitIconBase[0][19],"Type 89 IFV (LV2)","A modern anti-infantry vehicle\nutilized by modern factions.",spawnAcc);

                    this->getCommand(spawnAcc)->setCostReq(400);
                    this->getCommand(spawnAcc)->setCountdownMAX(1000);

                    description = "Produces LV2 vehicle units.";
                    desc = "Upgrades Modern Warfactory (LV2) to a Mech\nInstallation (LV3). Unlocks higher level units.";
                    prc = 1800;
                    setSellPrice(1800);
                    break;
                case 3:
                    setHpMAX(6000);
                    name = "Mech Installation (LV3)";
                    spawnAcc.clear();
                    spawnAcc.append(spawnUnit).append("veh AT ").append("lv3 ").append(stringColor);
                    addCmd(((BattleEngine*)engine)->unitIconBase[1][23],((BattleEngine*)engine)->unitIconBase[0][23],"W3 Xavier (LV3)","A bipedal assault walker. Capable\nof destroying entire columns of tanks.",spawnAcc);

                    this->getCommand(spawnAcc)->setCostReq(2000);
                    this->getCommand(spawnAcc)->setCountdownMAX(1100);

                    spawnAcc.clear();
                    spawnAcc.append(spawnUnit).append("veh AA ").append("lv3 ").append(stringColor);
                    addCmd(((BattleEngine*)engine)->unitIconBase[1][17],((BattleEngine*)engine)->unitIconBase[0][17],"Mobile PBC (LV3)","A mobile particle-beam cannon.\nPrimarily used against air units.",spawnAcc);

                    this->getCommand(spawnAcc)->setCostReq(1600);
                    this->getCommand(spawnAcc)->setCountdownMAX(900);

                    spawnAcc.clear();
                    spawnAcc.append(spawnUnit).append("veh AI ").append("lv3 ").append(stringColor);
                    addCmd(((BattleEngine*)engine)->unitIconBase[1][20],((BattleEngine*)engine)->unitIconBase[0][20],"Plasma Tank (LV3)","Highly advanced anti-personnel\nvehicle.",spawnAcc);

                    this->getCommand(spawnAcc)->setCostReq(800);
                    this->getCommand(spawnAcc)->setCountdownMAX(1000);

                    description = "Produces LV3 vehicle units.";
                    setSellPrice(2700);
                    break;
                default:
                    //invalid
                    break;
            }
    }
    else if(!(type.compare("Airfield"))) {
        blgType = 3;
        if(level > 3)
            level = 3;
        switch(level) {
            case 2:
                setHpMAX(2000);
                techReq = 500;
                name = "Airfield (LV2)";
                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("air AT ").append("lv2 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][7],((BattleEngine*)engine)->unitIconBase[0][7],"AH-1G Cobra (LV2)","Modern anti-tank helicopter.\nHeavily equipped anti-tank weapons.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(1200);
                this->getCommand(spawnAcc)->setCountdownMAX(1000);

                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("air AA ").append("lv2 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][1],((BattleEngine*)engine)->unitIconBase[0][1],"AH-64 Apache (LV2)","Modern combat helicopter.\nHeavily equipped with anti-air weapons.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(600);
                this->getCommand(spawnAcc)->setCountdownMAX(800);

                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("air AI ").append("lv2 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][4],((BattleEngine*)engine)->unitIconBase[0][4],"UH-1A Huey (LV2)","Modern transport helicopter.\nEquipped with anti-personnel weapons.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(600);
                this->getCommand(spawnAcc)->setCountdownMAX(900);

                description = "Produces LV2 air units.";
                desc = "Upgrades Airfield (LV2) to a Stratos Port (LV3).\nUnlocks higher level units.";
                prc = 1400;
                setSellPrice(1400);
                break;
            case 3:
                setHpMAX(4000);
                name = "Stratos Port (LV3)";
                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("air AT ").append("lv3 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][8],((BattleEngine*)engine)->unitIconBase[0][8],"GU-A2 Kozak (LV3)","VTOL capital-class aircraft.\nHeavily equipped with anti-tank weapons.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(2400);
                this->getCommand(spawnAcc)->setCountdownMAX(1000);

                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("air AA ").append("lv3 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][2],((BattleEngine*)engine)->unitIconBase[0][2],"CAA-11 Xin (LV3)","VTOL frigate-class aircraft.\nHeavily equipped with anti-air weapons.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(1200);
                this->getCommand(spawnAcc)->setCountdownMAX(800);

                spawnAcc.clear();
                spawnAcc.append(spawnUnit).append("air AI ").append("lv3 ").append(stringColor);
                addCmd(((BattleEngine*)engine)->unitIconBase[1][5],((BattleEngine*)engine)->unitIconBase[0][5],"GU-A9 Viper (LV3)","VTOL assault-class aircraft.\nEquipped with anti-personnel lasers.",spawnAcc);

                this->getCommand(spawnAcc)->setCostReq(1200);
                this->getCommand(spawnAcc)->setCountdownMAX(900);

                description = "Produces LV3 air units.";
                setSellPrice(2100);
                break;
            default:
                //invalid
                break;
        }
    }
    else if(!(type.compare("EconomicC"))) {
        blgType = 4;
        if(level > 6)
            level = 6;
        switch(level) {
            case 2:
                setHpMAX(600);
                techReq = 150;
                name = "Small Manufactory (LV2)";
                description = "Low-income economic center.\nGenerates funds every resource round.";
                desc = "Upgrades Small Manufactory (LV2) to a Large\nManufactory (LV3).";
                prc = 500;
                setSellPrice(350);
                break;
            case 3:
                setHpMAX(1000);
                techReq = 200;
                name = "Large Manufactory (LV3)";
                description = "Medium-income economic center.\nGenerates funds every resource round.";
                desc = "Upgrades Large Manufactory (LV3) to a Oil\nIndustry (LV4).";
                prc = 600;
                setSellPrice(600);
                break;
            case 4:
                setHpMAX(1500);
                techReq = 300;
                name = "Oil Industry (LV4)";
                description = "Medium-income economic center.\nGenerates funds every resource round.";
                desc = "Upgrades Oil Industry (LV4) to a Corporation (LV5).";
                prc = 900;
                setSellPrice(900);
                break;
            case 5:
                setHpMAX(2000);
                techReq = 400;
                name = "Corporation (LV5)";
                description = "High-income economic center.\nGenerates funds every resource round.";
                desc = "Upgrades Corporation (LV5) to a Conglomerate (LV6).";
                prc = 1200;
                setSellPrice(1350);
                break;
            case 6:
                setHpMAX(2500);
                name = "Conglomerate (LV6)";
                description = "High-income economic center.\nGenerates funds every resource round.";
                break;
                setSellPrice(1950);
            default:
                //invalid
                break;
        }
    }
    else if(!(type.compare("TechnologyC"))) {
        blgType = 5;
        if(level > 3)
            level = 3;
        switch(level) {
            case 2:
                setHpMAX(1000);
                techReq = 900;
                name = "Research Facility (LV2)";
                description = "Advanced research institution.\nGenerates technology every resource round.";
                desc = "Upgrades Research Facility (LV2) to a Mobius Research\nCenter (LV3).";
                prc = 2700;
                setSellPrice(1600);
                break;
            case 3:
                setHpMAX(3200);
                name = "Mobius Research Center (LV3)";
                description = "HiTech research institution.\nGenerates technology every resource round.";
                setSellPrice(2250);
                break;
            default:
                //invalid
                break;
        }
    }
    else if(!(type.compare("CommandCenter"))) {
        blgType = 0;
        if(level > 3)
            level = 3;

        switch(level) {
            case 2:
                setHpMAX(3000);
                prc = 2000;
                techReq = 600;
                name = "Faction Capitol (LV2)";
                description = "Vital structure for all factions.";
                desc = "Upgrades Capitol to next level";

                if(isRed) {
                    ((BattleEngine*)engine)->redPopCap = 25;
                    if(((BattleEngine*)engine)->playerIsRed) {
                        ((BattleEngine*)engine)->ui->population->setText(QString::number(((BattleEngine*)engine)->redPop).append("/").append(QString::number(((BattleEngine*)engine)->redPopCap)));
                    }
                }
                else {
                    ((BattleEngine*)engine)->bluePopCap = 25;
                    if(!(((BattleEngine*)engine)->playerIsRed)) {
                        ((BattleEngine*)engine)->ui->population->setText(QString::number(((BattleEngine*)engine)->bluePop).append("/").append(QString::number(((BattleEngine*)engine)->bluePopCap)));
                    }
                }

                if(isRed) {
                    if(((BattleEngine*)engine)->playerIsRed) {
                        switch(((BattleEngine*)engine)->playerType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV2)","Increases all your existing units' attack by 40%.","power blitz",1000,300);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV2)","Increases economic production by 40%.","power ecoBoom",1000,300);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV2)","Creates a mass of LV1 infantry units for your side.","power revolt",1000,300);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV2)","Deals 300 damage to all units in the battlefield.","power laser",1300,900);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                    else {
                        switch(((BattleEngine*)engine)->aiType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV2)","Increases all your existing units' attack by 40%.","power blitz",1000,300);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV2)","Increases economic production by 40%.","power ecoBoom",1000,300);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV2)","Creates a mass of LV1 infantry units for your side.","power revolt",1000,300);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV2)","Deals 300 damage to all units in the battlefield.","power laser",1300,900);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                }
                else {
                    if(!(((BattleEngine*)engine)->playerIsRed)) {
                        switch(((BattleEngine*)engine)->playerType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV2)","Increases all your existing units' attack by 40%.","power blitz",1000,300);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV2)","Increases economic production by 40%.","power ecoBoom",1000,300);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV2)","Creates a mass of LV1 infantry units for your side.","power revolt",1000,300);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV2)","Deals 300 damage to all units in the battlefield.","power laser",1300,500);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                    else {
                        switch(((BattleEngine*)engine)->aiType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV2)","Increases all your existing units' attack by 40%.","power blitz",1000,300);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV2)","Increases economic production by 40%.","power ecoBoom",1000,300);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV2)","Creates a mass of LV1 infantry units for your side.","power revolt",1000,300);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV2)","Deals 300 damage to all units in the battlefield.","power laser",1300,500);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                }
                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][9],((BattleEngine*)engine)->cmdIconBase[0][9],"Artillery Strike (LV2)","Barrages the enemy front with an artillery strike.","power artillery",1000,200);
                this->getCommand("power artillery")->setCountdownMAX(1500);
                break;
            case 3:
                setHpMAX(9000);
                name = "Faction Capitol (LV3)";
                description = "Vital structure for all factions.";

                if(isRed) {
                    ((BattleEngine*)engine)->redPopCap = 50;
                    if(((BattleEngine*)engine)->playerIsRed) {
                        ((BattleEngine*)engine)->ui->population->setText(QString::number(((BattleEngine*)engine)->redPop).append("/").append(QString::number(((BattleEngine*)engine)->redPopCap)));
                    }
                }
                else {
                    ((BattleEngine*)engine)->bluePopCap = 50;
                    if(!(((BattleEngine*)engine)->playerIsRed)) {
                        ((BattleEngine*)engine)->ui->population->setText(QString::number(((BattleEngine*)engine)->bluePop).append("/").append(QString::number(((BattleEngine*)engine)->bluePopCap)));
                    }
                }

                if(isRed) {
                    if(((BattleEngine*)engine)->playerIsRed) {
                        switch(((BattleEngine*)engine)->playerType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV3)","Increases all your existing units' attack by 60%.","power blitz",2000,800);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV3)","Increases economic production by 60%.","power ecoBoom",2000,800);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV3)","Creates a mass of LV1 infantry units for your side.","power revolt",2000,800);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV3)","Deals 300 damage to all units in the battlefield.","power laser",2800,1000);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                    else {
                        switch(((BattleEngine*)engine)->aiType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV3)","Increases all your existing units' attack by 60%.","power blitz",2000,800);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV3)","Increases economic production by 60%.","power ecoBoom",2000,800);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV3)","Creates a mass of LV1 infantry units for your side.","power revolt",2000,800);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV3)","Deals 300 damage to all units in the battlefield.","power laser",2800,1000);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                }
                else {
                    if(!(((BattleEngine*)engine)->playerIsRed)) {
                        switch(((BattleEngine*)engine)->playerType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV3)","Increases all your existing units' attack by 60%.","power blitz",2000,800);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV3)","Increases economic production by 60%.","power ecoBoom",2000,800);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV3)","Creates a mass of LV1 infantry units for your side.","power revolt",2000,800);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV3)","Deals 300 damage to all units in the battlefield.","power laser",2800,1000);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                    else {
                        switch(((BattleEngine*)engine)->aiType) {
                            case 'm':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][10],((BattleEngine*)engine)->cmdIconBase[0][10],"Blitzkreig (LV3)","Increases all your existing units' attack by 60%.","power blitz",2000,800);
                                this->getCommand("power blitz")->setCountdownMAX(10000);
                                break;
                            case 'e':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][11],((BattleEngine*)engine)->cmdIconBase[0][11],"Economic Boom (LV3)","Increases economic production by 60%.","power ecoBoom",2000,800);
                                this->getCommand("power ecoBoom")->setCountdownMAX(10000);
                                break;
                            case 's':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][12],((BattleEngine*)engine)->cmdIconBase[0][12],"Mass Propaganda (LV3)","Creates a mass of LV1 infantry units for your side.","power revolt",2000,800);
                                this->getCommand("power revolt")->setCountdownMAX(10000);
                                break;
                            case 't':
                                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][13],((BattleEngine*)engine)->cmdIconBase[0][13],"Orbital Strike (LV3)","Deals 300 damage to all units in the battlefield.","power laser",2800,1000);
                                this->getCommand("power laser")->setCountdownMAX(10000);
                                break;
                            default:
                                break;
                        }
                    }
                }

                this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][9],((BattleEngine*)engine)->cmdIconBase[0][9],"Artillery Strike (LV3)","Barrages the enemy front with an artillery strike.","power artillery",1000,200);
                this->getCommand("power artillery")->setCountdownMAX(750);
                break;
            default:
                //invalid
                break;
        }
    }

    ((BattleEngine*)engine)->loadSpritesForBlg(isRed,type,level);

    if(!(((BattleEngine*)engine)->thereExistsThisTypeOfBlg(isRed,type,level - 1)))
        ((BattleEngine*)engine)->destroySpritesForBlg(isRed,type,level - 1);

    imageOn = e->blgSpriteBase[faction][blgType][level - 1][1];
    imageOff = e->blgSpriteBase[faction][blgType][level - 1][0];

    if(level < 3 && type.compare("EconomicC"))
        this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][6],((BattleEngine*)engine)->cmdIconBase[0][6],"Upgrade",desc,temp,prc,techReq);
    else if(level < 6 && !type.compare("EconomicC"))
        this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][6],((BattleEngine*)engine)->cmdIconBase[0][6],"Upgrade",desc,temp,prc,techReq);
    else
        ; // do nothing

    if(isRed) {
        this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][8],((BattleEngine*)engine)->cmdIconBase[0][8],"Repair","Repair this building.","repair",0,0);
    }
    else {
        this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][8],((BattleEngine*)engine)->cmdIconBase[0][8],"Repair","Repair this building.","repair",0,0);
    }

    if(isRed && type.compare("CommandCenter")) {
        temp = "sell red ";
        temp.append(slotIndicator);
        this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][7],((BattleEngine*)engine)->cmdIconBase[0][7],"Sell","Sell this building.",temp,0,0);
    }
    else if(type.compare("CommandCenter")) {
        temp = "sell blue ";
        temp.append(slotIndicator);
        this->addCmd(((BattleEngine*)engine)->cmdIconBase[1][7],((BattleEngine*)engine)->cmdIconBase[0][7],"Sell","Sell this building.",temp,0,0);
    }

    ((BattleEngine*)engine)->highlightedCmd = NULL;

    if(((BattleEngine*)engine)->playerIsRed && isRed)
        ((BattleEngine*)engine)->disengageSelectButton();
    else if(!((BattleEngine*)engine)->playerIsRed && !isRed)
        ((BattleEngine*)engine)->disengageSelectButton();

    if(imageOff != NULL)
        displayLabel->setPixmap(*imageOff);

}

Command* Building::getCommand(QString tp) {

    for(int i = 0 ; i < cmdList->size() ; i++) {
        //qDebug(tp.toAscii().append(" = ").append(cmdList->value(i)->getType()));
        if(cmdList->value(i)->getType().contains(tp))
            return cmdList->value(i);
    }

    return NULL;
}

Command* Building::getCommandByName(QString nm) {

    for(int i = 0 ; i < cmdList->size() ; i++) {
        //qDebug(nm.toAscii().append(" = ").append(cmdList->value(i)->getName()));
        if(cmdList->value(i)->getName().contains(nm))
            return cmdList->value(i);
    }

    return NULL;
}

QString Building::getType() {
    return type;
}

QPushButton* Building::getDiplayButton() {
    return displayButton;
}

void Building::freezeCommands() {
    for(int i = 0 ; i < cmdList->size() ; i++) {
        cmdList->value(i)->freeze();
    }
}

void Building::unfreezeCommands() {
    for(int i = 0 ; i < cmdList->size() ; i++) {
        cmdList->value(i)->unfreeze();
    }
}

Building::~Building() {
    if(isRed) {
        if(isSelected)
            ((BattleEngine*)engine)->deselectAllRedBuildings();
    }
    else {
        if(isSelected)
            ((BattleEngine*)engine)->deselectAllBlueBuildings();
    }

    displayLabel->clear();
    clearCommands();

    delete cmdList;
}
