QT       += core gui

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
    ../../images/cards/10_of_clubs.png \
    ../../images/cards/10_of_diamonds.png \
    ../../images/cards/10_of_hearts.png \
    ../../images/cards/10_of_spades.png \
    ../../images/cards/11_of_clubs.png \
    ../../images/cards/11_of_diamonds.png \
    ../../images/cards/11_of_hearts.png \
    ../../images/cards/11_of_spades.png \
    ../../images/cards/12_of_clubs.png \
    ../../images/cards/12_of_diamonds.png \
    ../../images/cards/12_of_hearts.png \
    ../../images/cards/12_of_spades.png \
    ../../images/cards/13_of_clubs.png \
    ../../images/cards/13_of_diamonds.png \
    ../../images/cards/13_of_hearts.png \
    ../../images/cards/13_of_spades.png \
    ../../images/cards/14_of_clubs.png \
    ../../images/cards/14_of_diamonds.png \
    ../../images/cards/14_of_hearts.png \
    ../../images/cards/14_of_spades.png \
    ../../images/cards/2_of_clubs.png \
    ../../images/cards/2_of_diamonds.png \
    ../../images/cards/2_of_hearts.png \
    ../../images/cards/2_of_spades.png \
    ../../images/cards/3_of_clubs.png \
    ../../images/cards/3_of_diamonds.png \
    ../../images/cards/3_of_hearts.png \
    ../../images/cards/3_of_spades.png \
    ../../images/cards/4_of_clubs.png \
    ../../images/cards/4_of_diamonds.png \
    ../../images/cards/4_of_hearts.png \
    ../../images/cards/4_of_spades.png \
    ../../images/cards/5_of_clubs.png \
    ../../images/cards/5_of_diamonds.png \
    ../../images/cards/5_of_hearts.png \
    ../../images/cards/5_of_spades.png \
    ../../images/cards/6_of_clubs.png \
    ../../images/cards/6_of_diamonds.png \
    ../../images/cards/6_of_hearts.png \
    ../../images/cards/6_of_spades.png \
    ../../images/cards/7_of_clubs.png \
    ../../images/cards/7_of_diamonds.png \
    ../../images/cards/7_of_hearts.png \
    ../../images/cards/7_of_spades.png \
    ../../images/cards/8_of_clubs.png \
    ../../images/cards/8_of_diamonds.png \
    ../../images/cards/8_of_hearts.png \
    ../../images/cards/8_of_spades.png \
    ../../images/cards/9_of_clubs.png \
    ../../images/cards/9_of_diamonds.png \
    ../../images/cards/9_of_hearts.png \
    ../../images/cards/9_of_spades.png \
    ../../images/cards/green.png
