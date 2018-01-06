QT       += testlib qml

TARGET = untitled
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES +=     main.cpp     tests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
ROOTDIR = $$PWD/../../

include(vendor/vendor.pri)
include($$ROOTDIR/app/qmljsify/qmljsify.pri)

DEFINES += QUICK_TEST_SOURCE_DIR=\\\"$$PWD/qmltests\\\"

DISTFILES +=     qpm.json     qmltests/tst_QmlTests.qml \
    samples/sprintf.js \
    samples/sprintf.min.js \
    samples/sprintf-0.1.5.min.js

HEADERS +=     tests.h
