#-------------------------------------------------
#
# Project created by QtCreator 2011-08-05T17:10:37
#
#-------------------------------------------------

QT       += core gui
QT       += network webkit
CONFIG += qt warn_off debug
CONFIG += uic2

MOBILITY += multimedia

QT       += phonon

#    QMAKE_LFLAGS.ARMCC += --rw-base 0x800000
#    QMAKE_LFLAGS.GCCE += -Tdata 0xC00000
#    QMAKE_CXXFLAGS.ARMCC += -OTime -O3
#    QMAKE_LFLAGS.ARMCC += --rw-base 0xE00000
#    QMAKE_LFLAGS.ARMCC += --rw-base 0xC00000
#    QMAKE_LFLAGS.GCCE += -Tdata 0xA00000
#    OPTION_GCCE -fvisibility-inlines-hidden
#    LINKEROPTION_GCCE -Tdata 0xC00000

TARGET = proj
TEMPLATE = app

Win32 {
    QMAKE_LFLAGS_RELEASE += -static-libgcc
}

SOURCES += main.cpp\
        mainclass.cpp \
    Unit.cpp \
    BattleEngine.cpp \
    Building.cpp \
    Command.cpp \
    flickcharm.cpp \
    Effect.cpp \
    AIEngine.cpp \
    MapEngine.cpp \
    MapPoint.cpp \
    KozakScroll.cpp \
    KozakElement.cpp \
    ChallengeEngine.cpp \
    BGM.cpp

HEADERS  += mainclass.h \
    Unit.h \
    BattleEngine.h \
    Building.h \
    Command.h \
    flickcharm.h \
    Effect.h \
    AIEngine.h \
    MapEngine.h \
    MapPoint.h \
    KozakScroll.h \
    KozakElement.h \
    ChallengeEngine.h \
    BGM.h

FORMS    += mainclass.ui


MOBILITY =

symbian {
    LIBS += -lcone -leikcore -lavkon
    TARGET.UID3 = 0xeaab1023
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x14000 #was 0x14000
    TARGET.EPOCHEAPSIZE = 0xF0000 0x9000000 #was 0x800000
#    SPRITES.SOURCES = g:/qt/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/*.png
#    DEPLOYMENT += SPRITES
    ICON = icon.svg
}

RESOURCES += \
    resources/Images/Images.qrc

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

unix:!symbian:!maemo5 {
    target.path = /opt/RedSkies/bin
    INSTALLS += target

#    AIRRedaa1walk.path = /resource/Red/Aircraft/AA/lv1/walk
#    AIRRedaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/walk/1.png"
#    AIRRedaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/walk/2.png"
#    AIRRedaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/walk/3.png"
#    AIRRedaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/walk/4.png"
#    INSTALLS += AIRRedaa1walk

#    AIRRedaa1attack.path = /resource/Red/Aircraft/AA/lv1/attack
#    AIRRedaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/attack/1.png"
#    AIRRedaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/attack/2.png"
#    AIRRedaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/attack/3.png"
#    AIRRedaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/attack/4.png"
#    INSTALLS += AIRRedaa1attack

#    AIRRedaa1steady.path = /resource/Red/Aircraft/AA/lv1/steady
#    AIRRedaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/steady/1.png"
#    AIRRedaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/steady/2.png"
#    AIRRedaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/steady/3.png"
#    AIRRedaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv1/steady/4.png"
#    INSTALLS += AIRRedaa1steady

#    AIRRedaa2walk.path = /resource/Red/Aircraft/AA/lv2/walk
#    AIRRedaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/walk/1.png"
#    AIRRedaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/walk/2.png"
#    AIRRedaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/walk/3.png"
#    AIRRedaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/walk/4.png"
#    INSTALLS += AIRRedaa2walk

#    AIRRedaa2attack.path = /resource/Red/Aircraft/AA/lv2/attack
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/1.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/2.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/3.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/4.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/5.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/6.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/7.png"
#    AIRRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/attack/8.png"
#    INSTALLS += AIRRedaa2attack

#    AIRRedaa2steady.path = /resource/Red/Aircraft/AA/lv2/steady
#    AIRRedaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/steady/1.png"
#    AIRRedaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/steady/2.png"
#    AIRRedaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/steady/3.png"
#    AIRRedaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv2/steady/4.png"
#    INSTALLS += AIRRedaa2steady

#    AIRRedaa3walk.path = /resource/Red/Aircraft/AA/lv3/walk
#    AIRRedaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/walk/1.png"
#    AIRRedaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/walk/2.png"
#    AIRRedaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/walk/3.png"
#    AIRRedaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/walk/4.png"
#    INSTALLS += AIRRedaa3walk

#    AIRRedaa3attack.path = /resource/Red/Aircraft/AA/lv3/attack
#    AIRRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/attack/1.png"
#    AIRRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/attack/2.png"
#    AIRRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/attack/3.png"
#    AIRRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/attack/4.png"
#    INSTALLS += AIRRedaa3attack

#    AIRRedaa3steady.path = /resource/Red/Aircraft/AA/lv3/steady
#    AIRRedaa3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AA/lv3/steady/1.png"
#    INSTALLS += AIRRedaa3steady

#    AIRRedai1walk.path = /resource/Red/Aircraft/AI/lv1/walk
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/walk/1.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/walk/2.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/walk/3.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/walk/4.png"
#    INSTALLS += AIRRedai1walk

#    AIRRedai1attack.path = /resource/Red/Aircraft/AI/lv1/attack
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/attack/1.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/attack/2.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/attack/3.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/attack/4.png"
#    INSTALLS += AIRRedai1attack

#    AIRRedai1steady.path = /resource/Red/Aircraft/AI/lv1/steady
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/steady/1.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/steady/2.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/steady/3.png"
#    AIRRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv1/steady/4.png"
#    INSTALLS += AIRRedai1steady

#    AIRRedai2walk.path = /resource/Red/Aircraft/AI/lv2/walk
#    AIRRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/walk/1.png"
#    AIRRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/walk/2.png"
#    AIRRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/walk/3.png"
#    AIRRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/walk/4.png"
#    INSTALLS += AIRRedai2walk

#    AIRRedai2attack.path = /resource/Red/Aircraft/AI/lv2/attack
#    AIRRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/attack/1.png"
#    AIRRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/attack/2.png"
#    AIRRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/attack/3.png"
#    AIRRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/attack/4.png"
#    INSTALLS += AIRRedai2attack

#    AIRRedai2steady.path = /resource/Red/Aircraft/AI/lv2/steady
#    AIRRedai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/steady/1.png"
#    AIRRedai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/steady/2.png"
#    AIRRedai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/steady/3.png"
#    AIRRedai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv2/steady/4.png"
#    INSTALLS += AIRRedai2steady

#    AIRRedai3walk.path = /resource/Red/Aircraft/AI/lv3/walk
#    AIRRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/walk/1.png"
#    AIRRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/walk/2.png"
#    AIRRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/walk/3.png"
#    AIRRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/walk/4.png"
#    INSTALLS += AIRRedai3walk

#    AIRRedai3attack.path = /resource/Red/Aircraft/AI/lv3/attack
#    AIRRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/attack/1.png"
#    AIRRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/attack/2.png"
#    AIRRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/attack/3.png"
#    AIRRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/attack/4.png"
#    INSTALLS += AIRRedai3attack

#    AIRRedai3steady.path = /resource/Red/Aircraft/AI/lv3/steady
#    AIRRedai3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AI/lv3/steady/1.png"
#    INSTALLS += AIRRedai3steady

#    AIRRedat1walk.path = /resource/Red/Aircraft/AT/lv1/walk
#    AIRRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/walk/1.png"
#    AIRRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/walk/2.png"
#    AIRRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/walk/3.png"
#    AIRRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/walk/4.png"
#    INSTALLS += AIRRedat1walk

#    AIRRedat1attack.path = /resource/Red/Aircraft/AT/lv1/attack
#    AIRRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/attack/1.png"
#    AIRRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/attack/2.png"
#    AIRRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/attack/3.png"
#    AIRRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/attack/4.png"
#    INSTALLS += AIRRedat1attack

#    AIRRedat1steady.path = /resource/Red/Aircraft/AT/lv1/steady
#    AIRRedat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/steady/1.png"
#    AIRRedat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/steady/2.png"
#    AIRRedat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/steady/3.png"
#    AIRRedat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv1/steady/4.png"
#    INSTALLS += AIRRedat1steady

#    AIRRedat2walk.path = /resource/Red/Aircraft/AT/lv2/walk
#    AIRRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/walk/1.png"
#    AIRRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/walk/2.png"
#    AIRRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/walk/3.png"
#    AIRRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/walk/4.png"
#    INSTALLS += AIRRedat2walk

#    AIRRedat2attack.path = /resource/Red/Aircraft/AT/lv2/attack
#    AIRRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/attack/1.png"
#    AIRRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/attack/2.png"
#    AIRRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/attack/3.png"
#    AIRRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/attack/4.png"
#    INSTALLS += AIRRedat2attack

#    AIRRedat2steady.path = /resource/Red/Aircraft/AT/lv2/steady
#    AIRRedat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/steady/1.png"
#    AIRRedat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/steady/2.png"
#    AIRRedat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/steady/3.png"
#    AIRRedat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv2/steady/4.png"
#    INSTALLS += AIRRedat2steady

#    AIRRedat3walk.path = /resource/Red/Aircraft/AT/lv3/walk
#    AIRRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/walk/1.png"
#    AIRRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/walk/2.png"
#    AIRRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/walk/3.png"
#    AIRRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/walk/4.png"
#    INSTALLS += AIRRedat3walk

#    AIRRedat3attack.path = /resource/Red/Aircraft/AT/lv3/attack
#    AIRRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/attack/1.png"
#    AIRRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/attack/2.png"
#    AIRRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/attack/3.png"
#    AIRRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/attack/4.png"
#    INSTALLS += AIRRedat3attack

#    AIRRedat3steady.path = /resource/Red/Aircraft/AT/lv3/steady
#    AIRRedat3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Aircraft/AT/lv3/steady/1.png"
#    INSTALLS += AIRRedat3steady

#    INFRedai1walk.path = /resource/Red/Infantry/AI/lv1/walk
#    INFRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/walk/1.png"
#    INFRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/walk/2.png"
#    INFRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/walk/3.png"
#    INFRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/walk/4.png"
#    INFRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/walk/5.png"
#    INSTALLS += INFRedai1walk

#    INFRedai1attack.path = /resource/Red/Infantry/AI/lv1/attack
#    INFRedai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/attack/1.png"
#    INFRedai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/attack/2.png"
#    INSTALLS += INFRedai1attack

#    INFRedai1steady.path = /resource/Red/Infantry/AI/lv1/steady
#    INFRedai1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv1/steady/1.png"
#    INSTALLS += INFRedai1steady

#    INFRedai2walk.path = /resource/Red/Infantry/AI/lv2/walk
#    INFRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/walk/1.png"
#    INFRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/walk/2.png"
#    INFRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/walk/3.png"
#    INFRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/walk/4.png"
#    INFRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/walk/5.png"
#    INSTALLS += INFRedai2walk

#    INFRedai2attack.path = /resource/Red/Infantry/AI/lv2/attack
#    INFRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/attack/1.png"
#    INFRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/attack/2.png"
#    INSTALLS += INFRedai1steady

#    INFRedai2steady.path = /resource/Red/Infantry/AI/lv2/steady
#    INFRedai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv2/steady/1.png"
#    INSTALLS += INFRedai2steady

#    INFRedai3walk.path = /resource/Red/Infantry/AI/lv3/walk
#    INFRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/walk/1.png"
#    INFRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/walk/2.png"
#    INFRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/walk/3.png"
#    INFRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/walk/4.png"
#    INFRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/walk/5.png"
#    INSTALLS += INFRedai3walk

#    INFRedai3attack.path = /resource/Red/Infantry/AI/lv3/attack
#    INFRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/attack/1.png"
#    INFRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/attack/2.png"
#    INSTALLS += INFRedai3attack

#    INFRedai3steady.path = /resource/Red/Infantry/AI/lv3/steady
#    INFRedai3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AI/lv3/steady/1.png"
#    INSTALLS += INFRedai3steady

#    INFRedat1walk.path = /resource/Red/Infantry/AT/lv1/walk
#    INFRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/walk/1.png"
#    INFRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/walk/2.png"
#    INFRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/walk/3.png"
#    INFRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/walk/4.png"
#    INFRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/walk/5.png"
#    INSTALLS += INFRedat1walk

#    INFRedat1attack.path = /resource/Red/Infantry/AT/lv1/attack
#    INFRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/attack/1.png"
#    INFRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/attack/2.png"
#    INSTALLS += INFRedat1attack

#    INFRedat1steady.path = /resource/Red/Infantry/AT/lv1/steady
#    INFRedat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv1/steady/1.png"
#    INSTALLS += INFRedat1steady

#    INFRedat2walk.path = /resource/Red/Infantry/AT/lv2/walk
#    INFRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/walk/1.png"
#    INFRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/walk/2.png"
#    INFRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/walk/3.png"
#    INFRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/walk/4.png"
#    INFRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/walk/5.png"
#    INSTALLS += INFRedat2walk

#    INFRedat2attack.path = /resource/Red/Infantry/AT/lv2/attack
#    INFRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/attack/1.png"
#    INFRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/attack/2.png"
#    INSTALLS += INFRedat2attack

#    INFRedat2steady.path = /resource/Red/Infantry/AT/lv2/steady
#    INFRedat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv2/steady/1.png"
#    INSTALLS += INFRedat2steady

#    INFRedat3walk.path = /resource/Red/Infantry/AT/lv3/walk
#    INFRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/walk/1.png"
#    INFRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/walk/2.png"
#    INFRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/walk/3.png"
#    INFRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/walk/4.png"
#    INFRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/walk/5.png"
#    INSTALLS += INFRedat3walk

#    INFRedat3attack.path = /resource/Red/Infantry/AT/lv3/attack
#    INFRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/attack/1.png"
#    INFRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/attack/2.png"
#    INSTALLS += INFRedat3attack

#    INFRedat3steady.path = /resource/Red/Infantry/AT/lv3/steady
#    INFRedat3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Infantry/AT/lv3/steady/1.png"
#    INSTALLS += INFRedat3steady

#    VEHRedaa1walk.path = /resource/Red/Vehicle/AA/lv1/walk
#    VEHRedaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv1/walk/1.png"
#    INSTALLS += VEHRedaa1walk

#    VEHRedaa1attack.path = /resource/Red/Vehicle/AA/lv1/attack
#    VEHRedaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv1/attack/1.png"
#    VEHRedaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv1/attack/2.png"
#    INSTALLS += VEHRedaa1attack

#    VEHRedaa1steady.path = /resource/Red/Vehicle/AA/lv1/steady
#    VEHRedaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv1/steady/1.png"
#    INSTALLS += VEHRedaa1steady

#    VEHRedaa2walk.path = /resource/Red/Vehicle/AA/lv2/walk
#    VEHRedaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/walk/1.png"
#    INSTALLS += VEHRedaa2walk

#    VEHRedaa2attack.path = /resource/Red/Vehicle/AA/lv2/attack
#    VEHRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/attack/1.png"
#    VEHRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/attack/2.png"
#    VEHRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/attack/3.png"
#    VEHRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/attack/4.png"
#    VEHRedaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/attack/5.png"
#    INSTALLS += VEHRedaa2attack

#    VEHRedaa2steady.path = /resource/Red/Vehicle/AA/lv2/steady
#    VEHRedaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv2/steady/1.png"
#    INSTALLS += VEHRedaa2steady

#    VEHRedaa3walk.path = /resource/Red/Vehicle/AA/lv3/walk
#    VEHRedaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/walk/1.png"
#    INSTALLS += VEHRedaa3walk

#    VEHRedaa3attack.path = /resource/Red/Vehicle/AA/lv3/attack
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/1.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/2.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/3.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/4.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/5.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/6.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/7.png"
#    VEHRedaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/attack/8.png"
#    INSTALLS += VEHRedaa3attack

#    VEHRedaa3steady.path = /resource/Red/Vehicle/AA/lv3/steady
#    VEHRedaa3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AA/lv3/steady/1.png"
#    INSTALLS += VEHRedaa3steady

#    VEHRedai1walk.path = /resource/Red/Vehicle/AI/lv1/walk
#    VEHRedai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv1/walk/1.png"
#    INSTALLS += VEHRedai1walk

#    VEHRedai1attack.path = /resource/Red/Vehicle/AI/lv1/attack
#    VEHRedai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv1/attack/1.png"
#    VEHRedai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv1/attack/2.png"
#    INSTALLS += VEHRedai1attack

#    VEHRedai1steady.path = /resource/Red/Vehicle/AI/lv1/steady
#    VEHRedai1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv1/steady/1.png"
#    INSTALLS += VEHRedai1steady

#    VEHRedai2walk.path = /resource/Red/Vehicle/AI/lv2/walk
#    VEHRedai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv2/walk/1.png"
#    INSTALLS += VEHRedai2walk

#    VEHRedai2attack.path = /resource/Red/Vehicle/AI/lv2/attack
#    VEHRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv2/attack/1.png"
#    VEHRedai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv2/attack/2.png"
#    INSTALLS += VEHRedai2attack

#    VEHRedai2steady.path = /resource/Red/Vehicle/AI/lv2/steady
#    VEHRedai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv2/steady/1.png"
#    INSTALLS += VEHRedai2steady

#    VEHRedai3walk.path = /resource/Red/Vehicle/AI/lv3/walk
#    VEHRedai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv3/walk/1.png"
#    INSTALLS += VEHRedai3walk

#    VEHRedai3attack.path = /resource/Red/Vehicle/AI/lv3/attack
#    VEHRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv3/attack/1.png"
#    VEHRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv3/attack/2.png"
#    VEHRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv3/attack/3.png"
#    VEHRedai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv3/attack/4.png"
#    INSTALLS += VEHRedai3attack

#    VEHRedai3steady.path = /resource/Red/Vehicle/AI/lv3/steady
#    VEHRedai3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AI/lv3/steady/1.png"
#    INSTALLS += VEHRedai3steady

#    VEHRedat1walk.path = /resource/Red/Vehicle/AT/lv1/walk
#    VEHRedat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv1/walk/1.png"
#    INSTALLS += VEHRedat1walk

#    VEHRedat1attack.path = /resource/Red/Vehicle/AT/lv1/attack
#    VEHRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv1/attack/1.png"
#    VEHRedat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv1/attack/2.png"
#    INSTALLS += VEHRedat1attack

#    VEHRedat1steady.path = /resource/Red/Vehicle/AT/lv1/steady
#    VEHRedat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv1/steady/1.png"
#    INSTALLS += VEHRedat1steady

#    VEHRedat2walk.path = /resource/Red/Vehicle/AT/lv2/walk
#    VEHRedat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv2/walk/1.png"
#    INSTALLS += VEHRedat2walk

#    VEHRedat2attack.path = /resource/Red/Vehicle/AT/lv2/attack
#    VEHRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv2/attack/1.png"
#    VEHRedat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv2/attack/2.png"
#    INSTALLS += VEHRedat2attack

#    VEHRedat2steady.path = /resource/Red/Vehicle/AT/lv2/steady
#    VEHRedat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv2/steady/1.png"
#    INSTALLS += VEHRedat2steady

#    VEHRedat3walk.path = /resource/Red/Vehicle/AT/lv3/walk
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/1.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/2.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/3.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/4.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/5.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/6.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/7.png"
#    VEHRedat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/walk/8.png"
#    INSTALLS += VEHRedat3walk

#    VEHRedat3attack.path = /resource/Red/Vehicle/AT/lv3/attack
#    VEHRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/attack/1.png"
#    VEHRedat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/attack/2.png"
#    INSTALLS += VEHRedat3attack

#    VEHRedat3steady.path = /resource/Red/Vehicle/AT/lv3/steady
#    VEHRedat3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Vehicle/AT/lv3/steady/1.png"
#    INSTALLS += VEHRedat3steady

#    BLGRedCC1.path = /resource/Red/Building/Capitol
#    BLGRedCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Capitol/lv1.png"
#    BLGRedCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Capitol/lv1ON.png"
#    BLGRedCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Capitol/lv2.png"
#    BLGRedCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Capitol/lv2ON.png"
#    BLGRedCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Capitol/lv3.png"
#    BLGRedCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Capitol/lv3ON.png"
#    INSTALLS += BLGRedCC1

#    BLGRedBRK1.path = /resource/Red/Building/Barracks
#    BLGRedBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Barracks/lv1.png"
#    BLGRedBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Barracks/lv1ON.png"
#    BLGRedBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Barracks/lv2.png"
#    BLGRedBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Barracks/lv2ON.png"
#    BLGRedBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Barracks/lv3.png"
#    BLGRedBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Barracks/lv3ON.png"
#    INSTALLS += BLGRedBRK1

#    BLGRedWAR1.path = /resource/Red/Building/Warfactory
#    BLGRedWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Warfactory/lv1.png"
#    BLGRedWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Warfactory/lv1ON.png"
#    BLGRedWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Warfactory/lv2.png"
#    BLGRedWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Warfactory/lv2ON.png"
#    BLGRedWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Warfactory/lv3.png"
#    BLGRedWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Warfactory/lv3ON.png"
#    INSTALLS += BLGRedWAR1

#    BLGRedAIR1.path = /resource/Red/Building/Airfield
#    BLGRedAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Airfield/lv1.png"
#    BLGRedAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Airfield/lv1ON.png"
#    BLGRedAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Airfield/lv2.png"
#    BLGRedAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Airfield/lv2ON.png"
#    BLGRedAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Airfield/lv3.png"
#    BLGRedAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Airfield/lv3ON.png"
#    INSTALLS += BLGRedAIR1

#    BLGRedECO1.path = /resource/Red/Building/EconomicCenter
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv1.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv1ON.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv2.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv2ON.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv3.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv3ON.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv4.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv4ON.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv5.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv5ON.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv6.png"
#    BLGRedECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/EconomicCenter/lv6ON.png"
#    INSTALLS += BLGRedECO1

#    BLGRedTEC1.path = /resource/Red/Building/TechCenter
#    BLGRedTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/TechCenter/lv1.png"
#    BLGRedTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/TechCenter/lv1ON.png"
#    BLGRedTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/TechCenter/lv2.png"
#    BLGRedTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/TechCenter/lv2ON.png"
#    BLGRedTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/TechCenter/lv3.png"
#    BLGRedTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/TechCenter/lv3ON.png"
#    INSTALLS += BLGRedTEC1

#    BLGRedWEP1.path = /resource/Red/Building/Superweapon
#    BLGRedWEP1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Superweapon/lv1.png"
#    BLGRedWEP1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Red/Building/Superweapon/lv1ON.png"
#    INSTALLS += BLGRedWEP1

#    AIRBlueaa1walk.path = /resource/Blue/Aircraft/AA/lv1/walk
#    AIRBlueaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/walk/1.png"
#    AIRBlueaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/walk/2.png"
#    AIRBlueaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/walk/3.png"
#    AIRBlueaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/walk/4.png"
#    INSTALLS += AIRBlueaa1walk

#    AIRBlueaa1attack.path = /resource/Blue/Aircraft/AA/lv1/attack
#    AIRBlueaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/attack/1.png"
#    AIRBlueaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/attack/2.png"
#    AIRBlueaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/attack/3.png"
#    AIRBlueaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/attack/4.png"
#    INSTALLS += AIRBlueaa1attack

#    AIRBlueaa1steady.path = /resource/Blue/Aircraft/AA/lv1/attack
#    AIRBlueaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/steady/1.png"
#    AIRBlueaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/steady/2.png"
#    AIRBlueaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/steady/3.png"
#    AIRBlueaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv1/steady/4.png"
#    INSTALLS += AIRBlueaa1steady

#    AIRBlueaa2walk.path = /resource/Blue/Aircraft/AA/lv2/walk
#    AIRBlueaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/walk/1.png"
#    AIRBlueaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/walk/2.png"
#    AIRBlueaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/walk/3.png"
#    AIRBlueaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/walk/4.png"
#    INSTALLS += AIRBlueaa2walk

#    AIRBlueaa2attack.path = /resource/Blue/Aircraft/AA/lv2/attack
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/1.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/2.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/3.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/4.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/5.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/6.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/7.png"
#    AIRBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/attack/8.png"
#    INSTALLS += AIRBlueaa2attack

#    AIRBlueaa2steady.path = /resource/Blue/Aircraft/AA/lv2/attack
#    AIRBlueaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/steady/1.png"
#    AIRBlueaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/steady/2.png"
#    AIRBlueaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/steady/3.png"
#    AIRBlueaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv2/steady/4.png"
#    INSTALLS += AIRBlueaa2steady

#    AIRBlueaa3walk.path = /resource/Blue/Aircraft/AA/lv3/walk
#    AIRBlueaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/walk/1.png"
#    AIRBlueaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/walk/2.png"
#    AIRBlueaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/walk/3.png"
#    AIRBlueaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/walk/4.png"
#    INSTALLS += AIRBlueaa3walk

#    AIRBlueaa3attack.path = /resource/Blue/Aircraft/AA/lv3/attack
#    AIRBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/attack/1.png"
#    AIRBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/attack/2.png"
#    AIRBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/attack/3.png"
#    AIRBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/attack/4.png"
#    INSTALLS += AIRBlueaa3attack

#    AIRBlueaa3steady.path = /resource/Blue/Aircraft/AA/lv3/attack
#    AIRBlueaa3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AA/lv3/steady/1.png"
#    INSTALLS += AIRBlueaa3steady

#    AIRBlueai1walk.path = /resource/Blue/Aircraft/AI/lv1/walk
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/walk/1.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/walk/2.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/walk/3.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/walk/4.png"
#    INSTALLS += AIRBlueai1walk

#    AIRBlueai1attack.path = /resource/Blue/Aircraft/AI/lv1/attack
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/attack/1.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/attack/2.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/attack/3.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/attack/4.png"
#    INSTALLS += AIRBlueai1attack

#    AIRBlueai1steady.path = /resource/Blue/Aircraft/AI/lv1/attack
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/steady/1.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/steady/2.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/steady/3.png"
#    AIRBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv1/steady/4.png"
#    INSTALLS += AIRBlueai1steady

#    AIRBlueai2walk.path = /resource/Blue/Aircraft/AI/lv2/walk
#    AIRBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/walk/1.png"
#    AIRBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/walk/2.png"
#    AIRBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/walk/3.png"
#    AIRBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/walk/4.png"
#    INSTALLS += AIRBlueai2walk

#    AIRBlueai2attack.path = /resource/Blue/Aircraft/AI/lv2/attack
#    AIRBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/attack/1.png"
#    AIRBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/attack/2.png"
#    AIRBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/attack/3.png"
#    AIRBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/attack/4.png"
#    INSTALLS += AIRBlueai2attack

#    AIRBlueai2steady.path = /resource/Blue/Aircraft/AI/lv2/attack
#    AIRBlueai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/steady/1.png"
#    AIRBlueai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/steady/2.png"
#    AIRBlueai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/steady/3.png"
#    AIRBlueai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv2/steady/4.png"
#    INSTALLS += AIRBlueai2steady

#    AIRBlueai3walk.path = /resource/Blue/Aircraft/AI/lv3/walk
#    AIRBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/walk/1.png"
#    AIRBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/walk/2.png"
#    AIRBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/walk/3.png"
#    AIRBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/walk/4.png"
#    INSTALLS += AIRBlueai3walk

#    AIRBlueai3attack.path = /resource/Blue/Aircraft/AI/lv3/attack
#    AIRBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/attack/1.png"
#    AIRBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/attack/2.png"
#    AIRBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/attack/3.png"
#    AIRBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/attack/4.png"
#    INSTALLS += AIRBlueai3attack

#    AIRBlueai3steady.path = /resource/Blue/Aircraft/AI/lv3/attack
#    AIRBlueai3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AI/lv3/steady/1.png"
#    INSTALLS += AIRBlueai3steady

#    AIRBlueat1walk.path = /resource/Blue/Aircraft/AT/lv1/walk
#    AIRBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/walk/1.png"
#    AIRBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/walk/2.png"
#    AIRBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/walk/3.png"
#    AIRBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/walk/4.png"
#    INSTALLS += AIRBlueat1walk

#    AIRBlueat1attack.path = /resource/Blue/Aircraft/AT/lv1/attack
#    AIRBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/attack/1.png"
#    AIRBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/attack/2.png"
#    AIRBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/attack/3.png"
#    AIRBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/attack/4.png"
#    INSTALLS += AIRBlueat1attack

#    AIRBlueat1steady.path = /resource/Blue/Aircraft/AT/lv1/attack
#    AIRBlueat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/steady/1.png"
#    AIRBlueat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/steady/2.png"
#    AIRBlueat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/steady/3.png"
#    AIRBlueat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv1/steady/4.png"
#    INSTALLS += AIRBlueat1steady

#    AIRBlueat2walk.path = /resource/Blue/Aircraft/AT/lv2/walk
#    AIRBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/walk/1.png"
#    AIRBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/walk/2.png"
#    AIRBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/walk/3.png"
#    AIRBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/walk/4.png"
#    INSTALLS += AIRBlueat2walk

#    AIRBlueat2attack.path = /resource/Blue/Aircraft/AT/lv2/attack
#    AIRBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/attack/1.png"
#    AIRBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/attack/2.png"
#    AIRBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/attack/3.png"
#    AIRBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/attack/4.png"
#    INSTALLS += AIRBlueat2attack

#    AIRBlueat2steady.path = /resource/Blue/Aircraft/AT/lv2/attack
#    AIRBlueat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/steady/1.png"
#    AIRBlueat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/steady/2.png"
#    AIRBlueat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/steady/3.png"
#    AIRBlueat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv2/steady/4.png"
#    INSTALLS += AIRBlueat2steady

#    AIRBlueat3walk.path = /resource/Blue/Aircraft/AT/lv3/walk
#    AIRBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/walk/1.png"
#    AIRBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/walk/2.png"
#    AIRBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/walk/3.png"
#    AIRBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/walk/4.png"
#    INSTALLS += AIRBlueat3walk

#    AIRBlueat3attack.path = /resource/Blue/Aircraft/AT/lv3/attack
#    AIRBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/attack/1.png"
#    AIRBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/attack/2.png"
#    AIRBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/attack/3.png"
#    AIRBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/attack/4.png"
#    INSTALLS += AIRBlueat3attack

#    AIRBlueat3steady.path = /resource/Blue/Aircraft/AT/lv3/attack
#    AIRBlueat3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Aircraft/AT/lv3/steady/1.png"
#    INSTALLS += AIRBlueat3steady

#    INFBlueai1walk.path = /resource/Blue/Infantry/AI/lv1/walk
#    INFBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/walk/1.png"
#    INFBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/walk/2.png"
#    INFBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/walk/3.png"
#    INFBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/walk/4.png"
#    INFBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/walk/5.png"
#    INSTALLS += INFBlueai1walk

#    INFBlueai1attack.path = /resource/Blue/Infantry/AI/lv1/attack
#    INFBlueai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/attack/1.png"
#    INFBlueai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/attack/2.png"
#    INSTALLS += INFBlueai1attack

#    INFBlueai1steady.path = /resource/Blue/Infantry/AI/lv1/attack
#    INFBlueai1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv1/steady/1.png"
#    INSTALLS += INFBlueai1steady

#    INFBlueai2walk.path = /resource/Blue/Infantry/AI/lv2/walk
#    INFBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/walk/1.png"
#    INFBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/walk/2.png"
#    INFBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/walk/3.png"
#    INFBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/walk/4.png"
#    INFBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/walk/5.png"
#    INSTALLS += INFBlueai2walk

#    INFBlueai2attack.path = /resource/Blue/Infantry/AI/lv2/attack
#    INFBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/attack/1.png"
#    INFBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/attack/2.png"
#    INSTALLS += INFBlueai1steady

#    INFBlueai2steady.path = /resource/Blue/Infantry/AI/lv2/attack
#    INFBlueai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv2/steady/1.png"
#    INSTALLS += INFBlueai2steady

#    INFBlueai3walk.path = /resource/Blue/Infantry/AI/lv3/walk
#    INFBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/walk/1.png"
#    INFBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/walk/2.png"
#    INFBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/walk/3.png"
#    INFBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/walk/4.png"
#    INFBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/walk/5.png"
#    INSTALLS += INFBlueai3walk

#    INFBlueai3attack.path = /resource/Blue/Infantry/AI/lv3/attack
#    INFBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/attack/1.png"
#    INFBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/attack/2.png"
#    INSTALLS += INFBlueai3attack

#    INFBlueai3steady.path = /resource/Blue/Infantry/AI/lv3/attack
#    INFBlueai3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AI/lv3/steady/1.png"
#    INSTALLS += INFBlueai3steady

#    INFBlueat1walk.path = /resource/Blue/Infantry/AT/lv1/walk
#    INFBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/walk/1.png"
#    INFBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/walk/2.png"
#    INFBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/walk/3.png"
#    INFBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/walk/4.png"
#    INFBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/walk/5.png"
#    INSTALLS += INFBlueat1walk

#    INFBlueat1attack.path = /resource/Blue/Infantry/AT/lv1/attack
#    INFBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/attack/1.png"
#    INFBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/attack/2.png"
#    INSTALLS += INFBlueat1attack

#    INFBlueat1steady.path = /resource/Blue/Infantry/AT/lv1/attack
#    INFBlueat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv1/steady/1.png"
#    INSTALLS += INFBlueat1steady

#    INFBlueat2walk.path = /resource/Blue/Infantry/AT/lv2/walk
#    INFBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/walk/1.png"
#    INFBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/walk/2.png"
#    INFBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/walk/3.png"
#    INFBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/walk/4.png"
#    INFBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/walk/5.png"
#    INSTALLS += INFBlueat2walk

#    INFBlueat2attack.path = /resource/Blue/Infantry/AT/lv2/attack
#    INFBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/attack/1.png"
#    INFBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/attack/2.png"
#    INSTALLS += INFBlueat2attack

#    INFBlueat2steady.path = /resource/Blue/Infantry/AT/lv2/attack
#    INFBlueat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv2/steady/1.png"
#    INSTALLS += INFBlueat2steady

#    INFBlueat3walk.path = /resource/Blue/Infantry/AT/lv3/walk
#    INFBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/walk/1.png"
#    INFBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/walk/2.png"
#    INFBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/walk/3.png"
#    INFBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/walk/4.png"
#    INFBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/walk/5.png"
#    INSTALLS += INFBlueat3walk

#    INFBlueat3attack.path = /resource/Blue/Infantry/AT/lv3/attack
#    INFBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/attack/1.png"
#    INFBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/attack/2.png"
#    INSTALLS += INFBlueat3attack

#    INFBlueat3steady.path = /resource/Blue/Infantry/AT/lv3/attack
#    INFBlueat3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Infantry/AT/lv3/steady/1.png"
#    INSTALLS += INFBlueat3steady

#    VEHBlueaa1walk.path = /resource/Blue/Vehicle/AA/lv1/walk
#    VEHBlueaa1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv1/walk/1.png"
#    INSTALLS += VEHBlueaa1walk

#    VEHBlueaa1attack.path = /resource/Blue/Vehicle/AA/lv1/attack
#    VEHBlueaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv1/attack/1.png"
#    VEHBlueaa1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv1/attack/2.png"
#    INSTALLS += VEHBlueaa1attack

#    VEHBlueaa1steady.path = /resource/Blue/Vehicle/AA/lv1/attack
#    VEHBlueaa1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv1/steady/1.png"
#    INSTALLS += VEHBlueaa1steady

#    VEHBlueaa2walk.path = /resource/Blue/Vehicle/AA/lv2/walk
#    VEHBlueaa2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/walk/1.png"
#    INSTALLS += VEHBlueaa2walk

#    VEHBlueaa2attack.path = /resource/Blue/Vehicle/AA/lv2/attack
#    VEHBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/attack/1.png"
#    VEHBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/attack/2.png"
#    VEHBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/attack/3.png"
#    VEHBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/attack/4.png"
#    VEHBlueaa2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/attack/5.png"
#    INSTALLS += VEHBlueaa2attack

#    VEHBlueaa2steady.path = /resource/Blue/Vehicle/AA/lv2/attack
#    VEHBlueaa2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv2/steady/1.png"
#    INSTALLS += VEHBlueaa2steady

#    VEHBlueaa3walk.path = /resource/Blue/Vehicle/AA/lv3/walk
#    VEHBlueaa3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/walk/1.png"
#    INSTALLS += VEHBlueaa3walk

#    VEHBlueaa3attack.path = /resource/Blue/Vehicle/AA/lv3/attack
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/1.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/2.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/3.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/4.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/5.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/6.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/7.png"
#    VEHBlueaa3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/attack/8.png"
#    INSTALLS += VEHBlueaa3attack

#    VEHBlueaa3steady.path = /resource/Blue/Vehicle/AA/lv3/attack
#    VEHBlueaa3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AA/lv3/steady/1.png"
#    INSTALLS += VEHBlueaa3steady

#    VEHBlueai1walk.path = /resource/Blue/Vehicle/AI/lv1/walk
#    VEHBlueai1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv1/walk/1.png"
#    INSTALLS += VEHBlueai1walk

#    VEHBlueai1attack.path = /resource/Blue/Vehicle/AI/lv1/attack
#    VEHBlueai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv1/attack/1.png"
#    VEHBlueai1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv1/attack/2.png"
#    INSTALLS += VEHBlueai1attack

#    VEHBlueai1steady.path = /resource/Blue/Vehicle/AI/lv1/attack
#    VEHBlueai1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv1/steady/1.png"
#    INSTALLS += VEHBlueai1steady

#    VEHBlueai2walk.path = /resource/Blue/Vehicle/AI/lv2/walk
#    VEHBlueai2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv2/walk/1.png"
#    INSTALLS += VEHBlueai2walk

#    VEHBlueai2attack.path = /resource/Blue/Vehicle/AI/lv2/attack
#    VEHBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv2/attack/1.png"
#    VEHBlueai2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv2/attack/2.png"
#    INSTALLS += VEHBlueai2attack

#    VEHBlueai2steady.path = /resource/Blue/Vehicle/AI/lv2/attack
#    VEHBlueai2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv2/steady/1.png"
#    INSTALLS += VEHBlueai2steady

#    VEHBlueai3walk.path = /resource/Blue/Vehicle/AI/lv3/walk
#    VEHBlueai3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv3/walk/1.png"
#    INSTALLS += VEHBlueai3walk

#    VEHBlueai3attack.path = /resource/Blue/Vehicle/AI/lv3/attack
#    VEHBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv3/attack/1.png"
#    VEHBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv3/attack/2.png"
#    VEHBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv3/attack/3.png"
#    VEHBlueai3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv3/attack/4.png"
#    INSTALLS += VEHBlueai3attack

#    VEHBlueai3steady.path = /resource/Blue/Vehicle/AI/lv3/attack
#    VEHBlueai3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AI/lv3/steady/1.png"
#    INSTALLS += VEHBlueai3steady

#    VEHBlueat1walk.path = /resource/Blue/Vehicle/AT/lv1/walk
#    VEHBlueat1walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv1/walk/1.png"
#    INSTALLS += VEHBlueat1walk

#    VEHBlueat1attack.path = /resource/Blue/Vehicle/AT/lv1/attack
#    VEHBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv1/attack/1.png"
#    VEHBlueat1attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv1/attack/2.png"
#    INSTALLS += VEHBlueat1attack

#    VEHBlueat1steady.path = /resource/Blue/Vehicle/AT/lv1/attack
#    VEHBlueat1steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv1/steady/1.png"
#    INSTALLS += VEHBlueat1steady

#    VEHBlueat2walk.path = /resource/Blue/Vehicle/AT/lv2/walk
#    VEHBlueat2walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv2/walk/1.png"
#    INSTALLS += VEHBlueat2walk

#    VEHBlueat2attack.path = /resource/Blue/Vehicle/AT/lv2/attack
#    VEHBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv2/attack/1.png"
#    VEHBlueat2attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv2/attack/2.png"
#    INSTALLS += VEHBlueat2attack

#    VEHBlueat2steady.path = /resource/Blue/Vehicle/AT/lv2/attack
#    VEHBlueat2steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv2/steady/1.png"
#    INSTALLS += VEHBlueat2steady

#    VEHBlueat3walk.path = /resource/Blue/Vehicle/AT/lv3/walk
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/1.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/2.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/3.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/4.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/5.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/6.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/7.png"
#    VEHBlueat3walk.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/walk/8.png"
#    INSTALLS += VEHBlueat3walk

#    VEHBlueat3attack.path = /resource/Blue/Vehicle/AT/lv3/attack
#    VEHBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/attack/1.png"
#    VEHBlueat3attack.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/attack/2.png"
#    INSTALLS += VEHBlueat3attack

#    VEHBlueat3steady.path = /resource/Blue/Vehicle/AT/lv3/attack
#    VEHBlueat3steady.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Vehicle/AT/lv3/steady/1.png"
#    INSTALLS += VEHBlueat3steady

#    BLGBlueCC1.path = /resource/Blue/Building/Capitol
#    BLGBlueCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Capitol/lv1.png"
#    BLGBlueCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Capitol/lv1ON.png"
#    BLGBlueCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Capitol/lv2.png"
#    BLGBlueCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Capitol/lv2ON.png"
#    BLGBlueCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Capitol/lv3.png"
#    BLGBlueCC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Capitol/lv3ON.png"
#    INSTALLS += BLGBlueCC1

#    BLGBlueBRK1.path = /resource/Blue/Building/Barracks
#    BLGBlueBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Barracks/lv1.png"
#    BLGBlueBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Barracks/lv1ON.png"
#    BLGBlueBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Barracks/lv2.png"
#    BLGBlueBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Barracks/lv2ON.png"
#    BLGBlueBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Barracks/lv3.png"
#    BLGBlueBRK1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Barracks/lv3ON.png"
#    INSTALLS += BLGBlueBRK1

#    BLGBlueWAR1.path = /resource/Blue/Building/Warfactory
#    BLGBlueWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Warfactory/lv1.png"
#    BLGBlueWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Warfactory/lv1ON.png"
#    BLGBlueWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Warfactory/lv2.png"
#    BLGBlueWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Warfactory/lv2ON.png"
#    BLGBlueWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Warfactory/lv3.png"
#    BLGBlueWAR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Warfactory/lv3ON.png"
#    INSTALLS += BLGBlueWAR1

#    BLGBlueAIR1.path = /resource/Blue/Building/Airfield
#    BLGBlueAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Airfield/lv1.png"
#    BLGBlueAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Airfield/lv1ON.png"
#    BLGBlueAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Airfield/lv2.png"
#    BLGBlueAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Airfield/lv2ON.png"
#    BLGBlueAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Airfield/lv3.png"
#    BLGBlueAIR1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Airfield/lv3ON.png"
#    INSTALLS += BLGBlueAIR1

#    BLGBlueECO1.path = /resource/Blue/Building/EconomicCenter
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv1.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv1ON.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv2.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv2ON.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv3.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv3ON.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv4.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv4ON.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv5.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv5ON.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv6.png"
#    BLGBlueECO1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/EconomicCenter/lv6ON.png"
#    INSTALLS += BLGBlueECO1

#    BLGBlueTEC1.path = /resource/Blue/Building/TechCenter
#    BLGBlueTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/TechCenter/lv1.png"
#    BLGBlueTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/TechCenter/lv1ON.png"
#    BLGBlueTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/TechCenter/lv2.png"
#    BLGBlueTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/TechCenter/lv2ON.png"
#    BLGBlueTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/TechCenter/lv3.png"
#    BLGBlueTEC1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/TechCenter/lv3ON.png"
#    INSTALLS += BLGBlueTEC1

#    BLGBlueWEP1.path = /resource/Blue/Building/Superweapon
#    BLGBlueWEP1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Superweapon/lv1.png"
#    BLGBlueWEP1.files += "G:/QT/RedSkies/proj/resources/Images/animated/Blue/Building/Superweapon/lv1ON.png"
#    INSTALLS += BLGBlueWEP1

#    CMDICONS.path = /resource/cmdIcons
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/airfield.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/barracks.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/ecoC.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/sell.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/superweapon.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/techC.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/upgrade.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/warfactory.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/repair.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/artillery.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/blitz.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/ecoBoom.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/revolt.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/laser.png"
#    CMDICONS.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/nuke.png"
#    INSTALLS += CMDICONS

#    CMDICONSON.path = /resource/cmdIcons/on
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/airfield.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/barracks.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/ecoC.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/sell.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/superweapon.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/techC.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/upgrade.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/warfactory.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/repair.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/artillery.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/blitz.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/ecoBoom.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/revolt.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/laser.png"
#    CMDICONSON.files += "G:/QT/RedSkies/proj-build-simulator/cmdIcons/on/nuke.png"
#    INSTALLS += CMDICONSON

#    UNITICONS.path = /resource/unitIcons
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAA1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAA2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAA3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAI1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAI2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAI3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAT1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAT2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/airAT3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/infAI1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/infAI2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/infAI3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/infAT1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/infAT2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/infAT3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAA1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAA2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAA3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAI1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAI2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAI3.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAT1.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAT2.png"
#    UNITICONS.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/vehAT3.png"
#    INSTALLS += UNITICONS

#    UNITICONSON.path = /resource/unitIcons/on
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAA1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAA2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAA3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAI1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAI2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAI3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAT1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAT2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/airAT3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/infAI1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/infAI2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/infAI3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/infAT1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/infAT2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/infAT3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAA1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAA2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAA3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAI1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAI2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAI3.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAT1.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAT2.png"
#    UNITICONSON.files += "G:/QT/RedSkies/proj-build-simulator/unitIcons/on/vehAT3.png"
#    INSTALLS += UNITICONSON

#    GND1.path = /resource/effects/gnd1
#    GND1.files += "G:/resource/effects/gnd1/1.png"
#    GND1.files += "G:/resource/effects/gnd1/2.png"
#    GND1.files += "G:/resource/effects/gnd1/3.png"
#    GND1.files += "G:/resource/effects/gnd1/4.png"
#    GND1.files += "G:/resource/effects/gnd1/5.png"
#    GND1.files += "G:/resource/effects/gnd1/6.png"
#    GND1.files += "G:/resource/effects/gnd1/7.png"
#    GND1.files += "G:/resource/effects/gnd1/8.png"
#    GND1.files += "G:/resource/effects/gnd1/9.png"
#    GND1.files += "G:/resource/effects/gnd1/10.png"
#    GND1.files += "G:/resource/effects/gnd1/11.png"
#    INSTALLS += GND1

#    GND2.path = /resource/effects/gnd2
#    GND2.files += "G:/resource/effects/gnd2/1.png"
#    GND2.files += "G:/resource/effects/gnd2/2.png"
#    GND2.files += "G:/resource/effects/gnd2/3.png"
#    GND2.files += "G:/resource/effects/gnd2/4.png"
#    GND2.files += "G:/resource/effects/gnd2/5.png"
#    GND2.files += "G:/resource/effects/gnd2/6.png"
#    GND2.files += "G:/resource/effects/gnd2/7.png"
#    GND2.files += "G:/resource/effects/gnd2/8.png"
#    GND2.files += "G:/resource/effects/gnd2/9.png"
#    GND2.files += "G:/resource/effects/gnd2/10.png"
#    GND2.files += "G:/resource/effects/gnd2/11.png"
#    GND2.files += "G:/resource/effects/gnd2/12.png"
#    GND2.files += "G:/resource/effects/gnd2/13.png"
#    INSTALLS += GND2

#    GND3.path = /resource/effects/gnd3
#    GND3.files += "G:/resource/effects/gnd3/1.png"
#    GND3.files += "G:/resource/effects/gnd3/2.png"
#    GND3.files += "G:/resource/effects/gnd3/3.png"
#    GND3.files += "G:/resource/effects/gnd3/4.png"
#    GND3.files += "G:/resource/effects/gnd3/5.png"
#    GND3.files += "G:/resource/effects/gnd3/6.png"
#    GND3.files += "G:/resource/effects/gnd3/7.png"
#    GND3.files += "G:/resource/effects/gnd3/8.png"
#    GND3.files += "G:/resource/effects/gnd3/9.png"
#    GND3.files += "G:/resource/effects/gnd3/10.png"
#    GND3.files += "G:/resource/effects/gnd3/11.png"
#    GND3.files += "G:/resource/effects/gnd3/12.png"
#    GND3.files += "G:/resource/effects/gnd3/13.png"
#    INSTALLS += GND3

#    AIR1.path = /resource/effects/air1
#    AIR1.files += "G:/resource/effects/air1/1.png"
#    AIR1.files += "G:/resource/effects/air1/2.png"
#    AIR1.files += "G:/resource/effects/air1/3.png"
#    AIR1.files += "G:/resource/effects/air1/4.png"
#    AIR1.files += "G:/resource/effects/air1/5.png"
#    AIR1.files += "G:/resource/effects/air1/6.png"
#    AIR1.files += "G:/resource/effects/air1/7.png"
#    AIR1.files += "G:/resource/effects/air1/8.png"
#    AIR1.files += "G:/resource/effects/air1/9.png"
#    AIR1.files += "G:/resource/effects/air1/10.png"
#    INSTALLS += AIR1

#    AIR2.path = /resource/effects/air2
#    AIR2.files += "G:/resource/effects/air2/1.png"
#    AIR2.files += "G:/resource/effects/air2/2.png"
#    AIR2.files += "G:/resource/effects/air2/3.png"
#    AIR2.files += "G:/resource/effects/air2/4.png"
#    AIR2.files += "G:/resource/effects/air2/5.png"
#    AIR2.files += "G:/resource/effects/air2/6.png"
#    AIR2.files += "G:/resource/effects/air2/7.png"
#    AIR2.files += "G:/resource/effects/air2/8.png"
#    AIR2.files += "G:/resource/effects/air2/9.png"
#    AIR2.files += "G:/resource/effects/air2/10.png"
#    INSTALLS += AIR2

#    AIR3.path = /resource/effects/air3
#    AIR3.files += "G:/resource/effects/air3/1.png"
#    AIR3.files += "G:/resource/effects/air3/2.png"
#    AIR3.files += "G:/resource/effects/air3/3.png"
#    AIR3.files += "G:/resource/effects/air3/4.png"
#    AIR3.files += "G:/resource/effects/air3/5.png"
#    AIR3.files += "G:/resource/effects/air3/6.png"
#    AIR3.files += "G:/resource/effects/air3/7.png"
#    AIR3.files += "G:/resource/effects/air3/8.png"
#    AIR3.files += "G:/resource/effects/air3/9.png"
#    AIR3.files += "G:/resource/effects/air3/10.png"
#    INSTALLS += AIR3

#    CITY.path += /resource/cities
#    CITY.files += "G:/resource/cities/berlin.png"
#    CITY.files += "G:/resource/cities/manila.png"
#    CITY.files += "G:/resource/cities/moscow.png"
#    CITY.files += "G:/resource/cities/null.png"
#    CITY.files += "G:/resource/cities/paris.png"
#    CITY.files += "G:/resource/cities/london.png"
#    CITY.files += "G:/resource/cities/washington.png"
#    INSTALLS += CITY

#    COLOR.path += /resource/color
#    COLOR.files += "G:/resource/color/red.png"
#    COLOR.files += "G:/resource/color/blue.png"
#    INSTALLS += COLOR

#    FAC.path += /resource/factions
#    FAC.files += "G:/resource/factions/eco.png"
#    FAC.files += "G:/resource/factions/mil.png"
#    FAC.files += "G:/resource/factions/soc.png"
#    FAC.files += "G:/resource/factions/tec.png"
#    INSTALLS += FAC

#    LV.path += /resource/levels
#    LV.files += "G:/resource/levels/sample.png"
#    INSTALLS += LV

#    LASER.path += /resource/effects
#    LASER.files += "G:/resource/effects/redLaser.png"
#    LASER.files += "G:/resource/effects/blueLaser.png"
#    INSTALLS += LASER

}

unix:!symbian:!maemo5 {
    icon.files = proj.png
    icon.path = /usr/share/icons/hicolor/64x64/apps
    INSTALLS += icon
}
