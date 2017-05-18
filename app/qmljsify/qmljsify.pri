CONFIG   += c++11

SOURCES += \
    $$PWD/qmljsify.cpp

RESOURCES +=     $$PWD/qmljsify.qrc

INCLUDEPATH += $$PWD

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD

HEADERS +=     \
    $$PWD/qmljsify.h

DISTFILES += \
    $$PWD/Qmljsify/templates/package.json
