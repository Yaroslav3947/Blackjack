QT       += core gui

#QT += multimedia
QT += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Card.cpp \
    Dealer.cpp \
    Deck.cpp \
    Game.cpp \
    I_Participant.cpp \
    Player.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Card.h \
    Dealer.h \
    Deck.h \
    Game.h \
    I_Participant.h \
    Player.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \


RESOURCES += \
    res.qrc
