#include <QCommandLineParser>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtShell>
#include <QtCore>
#include "qmljsify.h"

using namespace QtShell;

void create(Qmljsify& qmljsify) {
    qmljsify.create();
}

void convert(Qmljsify& qmljsify) {
    qmljsify.prepare();
    qmljsify.fetch();
    qmljsify.build();
    qmljsify.create();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("qmljsify");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;

    parser.setApplicationDescription("qmljsify - Download and convert a NPM package to a QML friendly JavaScript file");
    parser.addHelpOption();
    parser.addPositionalArgument("command", "Command [Available Commands: convert]");
    parser.addPositionalArgument("package", "NPM package to be qmljsified");

    QCommandLineOption noMinifyOption(QStringList() << "no-minify", "Turn off JavaScript Compression");
    parser.addOption(noMinifyOption);

    parser.parse(app.arguments());

    QStringList args = parser.positionalArguments();

    if (args.size() != 2) {
        parser.showHelp(0);
    }

    bool noMinify = parser.isSet(noMinifyOption);

    QString command = args[0];
    QString package = args[1];

    Qmljsify qmljsify;
    qmljsify.setBuildFolder(realpath_strip(pwd(), "build"));
    qmljsify.parsePackageString(package);
    qmljsify.setOutputFolder(pwd());
    qmljsify.setMinifyEnabled(!noMinify);

    if (command == "convert") {
        convert(qmljsify);
    } else if (command == "create") {
        create(qmljsify);
    } else {
        qDebug() << "Unknown commmand:" << command;
        parser.showHelp(-1);
    }

    return 0;
}
