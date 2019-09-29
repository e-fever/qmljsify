TEMPLATE = app

QT += qml quick
CONFIG += c++11
CONFIG-=app_bundle
CONFIG -= qtquickcompiler

QT += quick qml

include(qmljsify.pri)

SOURCES += main.cpp

TARGET = qmljsify

ROOTDIR = $$PWD/../..

# Default rules for deployment.
include(deployment.pri)
include(vendor/vendor.pri)

DISTFILES +=     qpm.json

