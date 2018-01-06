#include <QQmlApplicationEngine>
#include <QTest>
#include <Automator>
#include <QtShell>
#include <QJsonObject>
#include <QJsonParseError>
#include "tests.h"
#include "qmljsify.h"

using namespace QtShell;

void printException(QJSValue value)
{
    if (value.isError()) {
        QString message = QString("%1:%2: %3: %4")
                          .arg(value.property("fileName").toString())
                          .arg(value.property("lineNumber").toString())
                          .arg(value.property("name").toString())
                          .arg(value.property("message").toString());
        qWarning() << message;
    }
}

QVariantMap parse(const QString &text) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8(),&error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON::parse() error: "<< error.errorString();
    }

    return doc.object().toVariantMap();
}

static QString obtainPackageVersion(const QString& folder, const QString& packageName) {
    QString path = realpath_strip(folder, "node_modules", packageName, "package.json");

    QString content = cat(path);

    QVariantMap map = parse(content);

    return map["version"].toString();
}

Tests::Tests(QObject *parent) : QObject(parent)
{
    auto ref = [=]() {
        QTest::qExec(this, 0, 0); // Autotest detect available test cases of a QObject by looking for "QTest::qExec" in source code
    };
    Q_UNUSED(ref);
}

void Tests::test_normalizeFunctionName()
{
    QCOMPARE(Qmljsify::normalizeFunctionName("left-pad"), QString("leftPad"));
    QCOMPARE(Qmljsify::normalizeFunctionName("lodash.merge"), QString("lodashMerge"));
}

void Tests::test_prepare()
{
    Qmljsify jsify;

    QString buildFolder = realpath_strip(pwd(), "build");
    jsify.setBuildFolder(buildFolder);
    jsify.setPackage("lodash");

    jsify.prepare();

    QString index = realpath_strip(buildFolder, "index.js");
    QString webpack = realpath_strip(buildFolder, "webpack.config.js");

    QVERIFY(QFile::exists(index));
    QVERIFY(QFile::exists(webpack));

    QString content = cat(index);
    QVERIFY(content.indexOf("lodash") >= 0);
}

void Tests::test_create()
{
    Qmljsify jsify;

    QString buildFolder = realpath_strip(pwd(), "build");
    QString outputFolder = pwd();

    QString origJs = realpath_strip(pwd() , "sprintf.orig.js");

    QString package = "sprintf";
    jsify.setMinifyEnabled(true);
    jsify.setOutputFolder(outputFolder);

    jsify.setBuildFolder(buildFolder);
    jsify.setPackage(package);

    jsify.prepare();

    jsify.fetch();

    jsify.build();

    jsify.create();

    QVERIFY(QFile::exists(origJs));
    QVERIFY(cat(origJs).size() > 0);
}

void Tests::test_leftpad()
{
    Qmljsify jsify;

    QString buildFolder = realpath_strip(pwd(), "build");
    QString outputFolder = pwd();

    QString js = realpath_strip(pwd() , "left-pad.js");

    QString package = "left-pad";

    jsify.setMinifyEnabled(false);
    jsify.setOutputFolder(outputFolder);

    jsify.setBuildFolder(buildFolder);
    jsify.setPackage(package);

    jsify.prepare();

    jsify.fetch();

    jsify.build();

    jsify.create();

    QVERIFY(cat(js).indexOf("var leftPad") >= 0);
}

void Tests::test_lodashMerge()
{
    Qmljsify jsify;

    QString buildFolder = realpath_strip(pwd(), "build");
    QString outputFolder = pwd();

    QString origJs = realpath_strip(pwd() , "lodash.merge.orig.js");
    QString js = realpath_strip(pwd() , "lodash.merge.js");

    QString package = "lodash.merge@4.5.0";

    jsify.setMinifyEnabled(false);
    jsify.setOutputFolder(outputFolder);

    jsify.setBuildFolder(buildFolder);
    jsify.parsePackageString(package);

    QCOMPARE(jsify.package(), QString("lodash.merge"));
    QCOMPARE(jsify.packageVersion(), QString("4.5.0"));

    jsify.prepare();

    jsify.fetch();

    jsify.build();

    jsify.create();

    QVERIFY(cat(js).indexOf("var lodashMerge") >= 0);

    QCOMPARE(obtainPackageVersion(buildFolder, "lodash.merge") , QString("4.5.0"));

    cp("-v", origJs, realpath_strip(SRCDIR, "samples/"));
    cp("-v", js, realpath_strip(SRCDIR, "samples/"));
}


