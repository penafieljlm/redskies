#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <QObject>
#include <QPushButton>
#include <QTimer>
#include <QLabel>

class MapPoint : public QPushButton {
    Q_OBJECT

    public:
        explicit MapPoint(int x, int y, QList <QIcon*>* butOnListImg, QLabel* nmLabel, QLabel* dscLabel, QLabel* prLabel, QWidget* parentWidget, QString image);
        ~MapPoint();

        int getX();
        int getY();
        void setX(int amt);
        void setY(int amt);
        QString getName();
        QString getDesc();
        void setName(QString nm);
        void setDesc(QString desc);

    signals:
        void deselected();
        void selected();

    private:
        int xCoord;
        int yCoord;
        QList <QIcon*>* iconAnim;
        QTimer* timer;
        int frameCounter;
        QString name;
        QString description;
        QLabel* nameLabel;
        QLabel* descLabel;
        QLabel* prevLabel;
        QString imagePath;

    public slots:
        void animate();
        void stopAnimate();
        void animateFrame();
};

#endif // MAPPOINT_H
