QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        FileModel/filedatamodel.cpp \
        main.cpp \
        mainwindow.cpp \
        FileModel/fileexplorermodel.cpp \
        Strategy/basesizecalculationstrategy.cpp \
        Strategy/fileliststrategy.cpp \
        Strategy/filetypestrategy.cpp \
        Strategy/strategyoutputhandler.cpp

HEADERS += \
        FileModel/filedatamodel.h \
        FileModel/ifiledatamodel.h \
        mainwindow.h \
        FileModel/fileexplorermodel.h \
        Strategy/basesizecalculationstrategy.h \
        Strategy/fileliststrategy.h \
        Strategy/filetypestrategy.h \
        Strategy/isizecalculationstrategy.h \
        Strategy/strategyoutputhandler.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
