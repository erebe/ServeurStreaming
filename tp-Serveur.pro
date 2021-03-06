######################################################################
# Automatically generated by qmake (2.01a) Sat Dec 10 23:09:42 2011
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . Http Multi Tcp_pull Tcp_push Udp_pull Udp_push
INCLUDEPATH += . Http Tcp_pull Tcp_push Udp_pull Udp_push Multi

CONFIG += debug console
CONFIG -= app_bundle
QT += network
QT -= gui

# Input
HEADERS += Http/client.h \
           Http/serveur.h \
           Multi/serveurMulti.h \
           Tcp_pull/demandetcppull.h \
           Tcp_pull/serveurtcppull.h \
           Tcp_push/clientTcpPush.h \
           Tcp_push/serveurTcpPush.h \
           Udp_pull/clientUdpPull.h \
           Udp_pull/serveurUdpPull.h \
           Udp_push/clientUdpPush.h \
           Udp_push/serveurUdpPush.h
SOURCES += main.cpp \
           Http/client.cpp \
           Http/serveur.cpp \
           Multi/serveurMulti.cpp \
           Tcp_pull/demandetcppull.cpp \
           Tcp_pull/serveurtcppull.cpp \
           Tcp_push/clientTcpPush.cpp \
           Tcp_push/serveurTcpPush.cpp \
           Udp_pull/clientUdpPull.cpp \
           Udp_pull/serveurUdpPull.cpp \
           Udp_push/clientUdpPush.cpp \
           Udp_push/serveurUdpPush.cpp
