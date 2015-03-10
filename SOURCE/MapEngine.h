#ifndef MAPENGINE_H
#define MAPENGINE_H

#include <QObject>
#include <QIcon>
#include "MapPoint.h"
#include <QLabel>

class MapEngine : public QObject {
    Q_OBJECT
    public:
        explicit MapEngine(QWidget* mapWidget, QList <QIcon*>* onList, QLabel* nmLabel, QLabel* dscLabel, QLabel* prLabel);
        ~MapEngine();

        void buildMap(QString type);

        void createPoint(int xCoord,int yCoord, QString name, QString desc, QString image);

        void clearPoints();

    signals:

    private:
        QList <QIcon*>* buttonList;
        QList <MapPoint*>* mapList;
        QLabel* nameLabel;
        QLabel* descLabel;
        QLabel* prevLabel;
        QWidget* parentWidget;

    public slots:
        void deselectAllPoints();

};

#endif // MAPENGINE_H
