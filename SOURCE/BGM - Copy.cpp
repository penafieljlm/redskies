#include "BGM.h"

BGM::BGM(QString path) {
    music = NULL;
    wav = NULL;
    if(path.contains("mp3"))
        music = Phonon::createPlayer(Phonon::NotificationCategory,Phonon::MediaSource(path));
    else if(path.contains("wav")) {
        wav = new QSound(path);
        wav->setLoops(-1);
    }
}

void BGM::play() {
    if(music) {
        connect(music,SIGNAL(finished()),this,SLOT(playLoop()));
        music->play();
    }
    if(wav) {
        wav->play();
    }
}

void BGM::playLoop() {
    if(music) {
        music->stop();
        music->play();
    }
}

void BGM::stop() {
    if(music) {
        disconnect(music,SIGNAL(finished()),this,SLOT(playLoop()));
        music->stop();
    }
    if(wav) {
        wav->stop();
    }
}

BGM::~BGM() {
    if(music) {
        music->stop();
        delete music;
    }
    if(wav) {
        wav->stop();
        delete wav;
    }
}
