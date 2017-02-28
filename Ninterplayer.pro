#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T16:05:08
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ninterplayer
TEMPLATE = app


SOURCES += main.cpp\
        jnlprincipal.cpp \
    jnlsobre.cpp \
    visualizadormusica.cpp \
    estadoreprodutor.cpp \
    visualizadorlista.cpp \
    itemlistamusica.cpp

HEADERS  += jnlprincipal.h \
    jnlsobre.h \
    visualizadormusica.h \
    estadoreprodutor.h \
    visualizadorlista.h \
    itemlistamusica.h

FORMS    += jnlprincipal.ui \
    jnlsobre.ui \
    visualizadormusica.ui \
    estadoreprodutor.ui \
    visualizadorlista.ui \
    itemlistamusica.ui

RESOURCES += \
    estilos.qrc
