#ifndef KOZAKELEMENT_H
#define KOZAKELEMENT_H

#include <QObject>
#include <QLabel>
#include <QTimer>

class KozakElement : public QLabel {
    Q_OBJECT
    public:
        explicit KozakElement(QWidget *parent, QList<QPixmap*>* walkList);
        ~KozakElement();
        int randomNum(int low, int hi);
    public slots:
        void startScroll();
        void scroll();
        void endScroll();
        void animate();

    signals:
        void end();
        void start();

    public slots:

    private:
        QList<QPixmap*>* animList;
        QTimer* animTimer;
        QWidget* parentWidget;
        int frameCounter;
        int scale;
        QTimer* frameTimer;
};

#endif // KOZAKELEMENT_H
