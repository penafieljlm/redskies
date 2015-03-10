#include <QtGui/QApplication>
#include "mainclass.h"
#include "flickcharm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainClass w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.show();
#endif

    w.showExpanded();

    FlickCharm fc;
    fc.setEngine(((void*)(w.getBattleEngine())),w.getUI());
    fc.activateOn(w.getUI()->leftBaseScroll);
    fc.activateOn(w.getUI()->battleFieldScroll);
    fc.activateOn(w.getUI()->rightBaseScroll);
    fc.activateOn(w.getUI()->mapScroller);
    fc.activateOn(w.getUI()->descArea_2);

    return a.exec();
}
