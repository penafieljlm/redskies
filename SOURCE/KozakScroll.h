#ifndef KOZAKSCROLL_H
#define KOZAKSCROLL_H

#include <QObject>
#include "KozakElement.h"
#include <QList>
#include <QPixmap>

class KozakScroll : public QObject
{
    Q_OBJECT
    public:
        explicit KozakScroll(QWidget* applyTo);
        void startScroll();
        void stopScroll();
        ~KozakScroll();

    private slots:
        void createKozak();
        void cleanKozak();

    signals:

    public slots:

    private:
        QWidget* target;
        QList <KozakElement*>* kozakList;
        QList <QPixmap*>* walkList;
        QTimer* spawnTimer;


};

#endif // KOZAKSCROLL_H
