QT = core
QT += widgets
QT += charts

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Statistics.cpp \
        charttemplate.cpp \
        fileexplorermodel.cpp \
        getstatistics.cpp \
        main.cpp \
        mainwindow.cpp \
        maptransformer.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Statistics.h \
    charttemplate.h \
    fileexplorermodel.h \
    getstatistics.h \
    mainwindow.h \
    maptransformer.h
