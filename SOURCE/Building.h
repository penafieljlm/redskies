#ifndef BUILDING_H
#define BUILDING_H

#include <QPushButton>
#include <QLabel>
#include "Unit.h"
#include "Command.h"
#include <QObject>

class Building: public QObject{

    private: Q_OBJECT

    public:
        explicit Building(QPixmap* imgOn, QPixmap* imgOff, QString nm, QString setDesc, bool red, int slot, void* eng, Ui::MainClass* u, QString tp, int hp = 1000);
        ~Building();

        void addCmd(QIcon* imgOn, QIcon* imgOff, QString nm, QString desc, QString type, int price = 0, int tech = 0);
        void select();
        void deselect();

        QString getType();
        bool getFaction();

        int getLevel();
        QString getName();
        QString getDesc();

        void setHitpoints(int val);
        QPushButton* getDiplayButton();
        void displayCommands();
        void hideCommands();
        void clearCommands();
        Command* getCommand(QString tp);
        Command* getCommandByName(QString nm);

        QLabel* getDisplayLabel();

        int getHitpoints();

        int getHpMAX();
        void setHpMAX(int amt);
        void setSellPrice(int amt);
        int getSellPrice();

        bool getRed();

        void freezeCommands();
        void unfreezeCommands();

    public slots:
        void promote();

    signals:
        void hpModify();

    protected:
        int sellPrice;
        QString name;
        QString type;
        int level;
        int hitpoints;
        int hpMax;
        bool isSelected;
        bool isRed;

        //Graphics
        QPushButton* displayButton;
        QLabel* displayLabel;
        QPixmap* imageOn;
        QPixmap* imageOff;
        QString description;
        QString buildingName;

        QList <Command*>* cmdList;

        void* engine; //BattleEngine responsible for this building
        Ui::MainClass *ui;

};

#endif // BUILDING_H
