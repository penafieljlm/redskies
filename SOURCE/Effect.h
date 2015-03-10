#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QPoint>
#include <QLabel>
#include <QTimer>
#include <QList>
#include <phonon/MediaObject>

class Effect : public QObject
{
        Q_OBJECT
    public:
        explicit Effect(QRect geom, QList <QPixmap*>* frames, int speed, bool loop, QWidget* labelParent, void* eng);
        void playAnimation();
        ~Effect();
        void alignToGround();
        void alignToAir();
        bool isFinished();

        void freeze();
        void unfreeze();

    private:
        QLabel* displayLabel;
        QTimer* animationTimer;
        QList <QPixmap*>* animationFrames;
        int animationSpeed;
        int currentFrame;
        bool loops;
        bool finished;
        void stopAnimation();
        Phonon::MediaObject* sfx;
        void* engine;

    private slots:
        void refreshFrame();

    signals:

    public slots:

};

#endif // EFFECT_H
