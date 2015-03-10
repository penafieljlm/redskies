#ifndef COMMAND_H
#define COMMAND_H

#include <QIcon>
#include <QPushButton>
#include <QtCore/QCoreApplication>
#include "ui_mainclass.h"


class Command: public QPushButton {

    Q_OBJECT

    public:
        explicit Command(QIcon *on, QIcon *off, QString nm, QString desc, QString tp, void* batEng, void* parent);
        ~Command();
        QIcon* getOnImage();
        QIcon* getOffImage();
        QString getName();
        QString getDesc();
        QString getType();
        void moveToEndPoint();

        void setPoints(QPoint* start, QPoint* end);
        void* getParentBuilding();
        void emitExecute();
        void setCostReq(int amt);
        int getCostReq();
        void setTechReq(int amt);
        int getTechReq();

        void setCountdownMAX(int amt);

        void executeCountdown();

        bool isReady();

        int getCountdown();

        void freeze();
        void unfreeze();

    public slots:
        void decCountdown();

    private:
        bool ready;
        int cost;
        int tech;
        QIcon* onImage;
        QIcon* offImage;
        QString name;
        QString type;
        QString description;
        void* engine;
        void interfaceConnect();
        QPoint* endPoint;
        QPoint* startPoint;
        void* parentBuilding;
        int countdown;
        int countdownMAX;
        QTimer* countdownTimer;

    signals:
        void execute();

};

#endif // COMMAND_H
