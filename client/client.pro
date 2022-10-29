QT += core gui sql charts network

HEADERS += \
	csv_import.h \
	dbconnector.h \
	main.h \
	mainwindow.h \
	mytcpsocket.h \
	timetest.h

SOURCES += \
	csv_import.cpp \
	dbconnector.cpp \
	main.cpp \
	mainwindow.cpp \
	mytcpsocket.cpp \
	timetest.cpp


FORMS += \
	dbconnector.ui \
	mainwindow.ui

INSTALLS += target
CONFIG += force_debug_info
