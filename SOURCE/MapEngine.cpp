#include "MapEngine.h"

MapEngine::MapEngine(QWidget *mapWidget, QList<QIcon *> *onList, QLabel *nmLabel, QLabel *dscLabel, QLabel* prLabel) {
    mapList = new QList <MapPoint*> ();
    buttonList = onList;
    nameLabel = nmLabel;
    descLabel = dscLabel;
    prevLabel = prLabel;
    parentWidget = mapWidget;
}

MapEngine::~MapEngine() {
    clearPoints();
    delete mapList;
}

void MapEngine::buildMap(QString type) {
    if(type.contains("CustomGame")) {
        createPoint(831,426,"Manila","Description here!","/resource/cities/manila.png");
        createPoint(495,319,"Paris","Description here!","/resource/cities/paris.png");
        createPoint(282,352,"Washington D.C.","Description here!","/resource/cities/washington.png");
        createPoint(531,299,"Berlin","Description here!","/resource/cities/berlin.png");
        createPoint(587,283,"Moscow","Description here!","/resource/cities/moscow.png");
        createPoint(492,303,"London","Description here!","/resource/cities/london.png");
    }
}

void MapEngine::createPoint(int xCoord,int yCoord, QString name, QString desc, QString image) {
    MapPoint* newMapPoint = new MapPoint (xCoord, yCoord,buttonList,nameLabel,descLabel,prevLabel,parentWidget,image);
    newMapPoint->setName(name);
    newMapPoint->setDesc(desc);
    connect(newMapPoint,SIGNAL(selected()),this,SLOT(deselectAllPoints()));
    mapList->append(newMapPoint);
}

void MapEngine::deselectAllPoints() {
    for(int i = 0 ; i < mapList->size() ; i++) {
        mapList->value(i)->stopAnimate();
    }
}

void MapEngine::clearPoints() {
    for(int i = 0 ; i < mapList->size() ; i++) {
        delete mapList->value(i);
    }
    mapList->clear();
}
