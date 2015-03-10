#ifndef AIATTACKCMD_H
#define AIATTACKCMD_H

#include <QObject>
#include "Unit.h"

class AIAttackCMD : public QObject
{
    Q_OBJECT
public:
    explicit AIAttackCMD(Unit* src, Unit* trgt);
    Unit* getSource();
    Unit* getTarget();
    int reportProblems(QList<Unit*>* enmy, QList<Unit*>* mine);

private:
    Unit* source;
    Unit* target;

signals:

public slots:

};

#endif // AIATTACKCMD_H
