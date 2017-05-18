TEMPLATE = app

QT += qml quick
CONFIG += c++11
CONFIG-=app_bundle

QT += quick qml multimedia

include(qmljsify.pri)

SOURCES += main.cpp

TARGET = qmljsify

ROOTDIR = $$PWD/../..

# Default rules for deployment.
include(deployment.pri)
include(vendor/vendor.pri)

DISTFILES +=     qpm.json

