QT += core gui sql charts

HEADERS += \
    dbconnector.h \
    main.h \
    mainwindow.h
#   chart.h \
#   chartview.h

SOURCES += \
    dbconnector.cpp \
    main.cpp \
    mainwindow.cpp
#   chart.cpp \
#   chartview.cpp


FORMS += \
    dbconnector.ui \
    mainwindow.ui

INSTALLS += target
CONFIG += force_debug_info
