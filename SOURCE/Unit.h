#ifndef UNIT_H
#define UNIT_H

#include <QList>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include "ui_mainclass.h"
#include <phonon/MediaObject>

class Unit : public QMainWindow{

    private: Q_OBJECT

    public:
    explicit Unit(bool flying, bool red, int dmg, int hp, int spd, int rng, int rld, int wid, int ht, int rfrsh, QString atk, QString def, void* eng, Ui::MainClass* u, int lv);
        ~Unit();

        QString getAttackType();
        QString getDefenseType();
        void takeDamage(int amount);

        bool getFaction();
        int getPosition();
        int getAttackRange();

        int getHP();
        void buildSpriteBase(QList <QPixmap*>* walk, QList <QPixmap*>* attack, QList <QPixmap*>* steady);
        void freeze();
        void unfreeze();

        void increaseAttack(int amt);

    public slots:
        void move();
        void attack(Unit* target);
        void stand();
        void wakeUnit(); //signals the unit to start acting, called after loading all the necessary data

    protected:
        void setSpeed(int arg);
        void setFrameRate(int arg);

    public slots:
        void refreshFrame();
        void brain(); //function responsible for unit actions

    public:
        //ID
        QString attackType;
        QString defenseType;

        bool frozen;

        //Combat
        bool isLoaded; //if true, unit can attack
        bool isAttacking; //true if engaged with an enemy unit
        int reloadLimit; //if reloadGague is == to this, isLoaded = true
        int reloadGague; //set to zero after unit attacks and slowly increases
        int level;
        //Stats
        bool isRed;
        bool isFlying;
        int hitpoints;
        int speed;
        int damage;
        int attackRange;

        //Graphics
        int stance; //0 = move, 1 = attack, 2 = steady
        int walkFrameIndex;
        int steadyFrameIndex;
        int attackFrameIndex;
        QList <QPixmap*> *walkSprite; //frames for walk animation
        QList <QPixmap*> *steadySprite; //frames for steady animation
        QList <QPixmap*> *attackSprite; //frames for attack animation
        QPixmap* currentSprite;
        QLabel* displayLabel; //label w/c will display the sprite
        int frameDelay;
        QTimer* frameTimer;

        //Geometry
        int width;
        int height;
        int xCoord;
        int yCoord;

        int position;
        QTimer* moveTimer;

        //AI
        QTimer* consciousness; //timer for the brain function

        void* engine;   //BattleEngine that runs this unit

        Ui::MainClass* ui;

        Unit* crosshair;

        Phonon::MediaObject* gun;
    private slots:
        void stopSound();




};

#endif // UNIT_H


