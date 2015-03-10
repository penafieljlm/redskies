#include "AIAttackCMD.h"

AIAttackCMD::AIAttackCMD(Unit *src, Unit *trgt) {
    source = src;
    target = trgt;
}

Unit* AIAttackCMD::getSource() {
    return source;
}

Unit* AIAttackCMD::getTarget() {
    return target;
}

int AIAttackCMD::reportProblems(QList <Unit*>* enmy, QList <Unit*>* mine) {
    if(enmy->indexOf(target) < 0 && mine->indexOf(source) >= 0)
        return 1;
    else if(enmy->indexOf(target) >= 0 && mine->indexOf(source) < 0)
        return -1;
    else
        return 0;

    return 0;
}
