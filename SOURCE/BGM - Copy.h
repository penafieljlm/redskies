#ifndef BGM_H
#define BGM_H

#include <QObject>
#include <phonon/MediaObject>
#include <QSound>
#include <QTimer>

class BGM : public QObject
{
    Q_OBJECT
public:
    BGM(QString path);
    ~BGM();
    void play();
    void stop();

signals:

private slots:

    void playLoop();

private:
    Phonon::MediaObject* music;
    QSound* wav;

};

#endif // BGM_H
