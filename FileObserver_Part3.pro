QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        FileModel/filedatamodel.cpp \
        Graph/abstractchart.cpp \
        Graph/barchart.cpp \
        Graph/chartadapter.cpp \
        Graph/piechart.cpp \
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
        Graph/abstractchart.h \
        Graph/barchart.h \
        Graph/chartadapter.h \
        Graph/ifilebrowserobserver.h \
        Graph/piechart.h \
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
