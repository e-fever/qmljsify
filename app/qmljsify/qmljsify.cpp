#include <QtCore>
#include <QFile>
#include <QtShell>
#include <QProcess>
#include <QQmlApplicationEngine>
#include "qmljsify.h"

using namespace QtShell;

#define TEMPLATES ":/Qmljsify/templates"

static void writeToFile(QString file, QString content) {
    rm("-f", file);

    QFile output(file);
    output.open(QIODevice::ReadWrite);
    output.write(content.toLocal8Bit());
    output.close();
}

static QString which(QString program) {
    //@TODO : Fix it. It doesn't work on windows
    QProcess process;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    process.setProcessEnvironment(env);

    process.start("/usr/bin/which", QStringList() << program);

    process.waitForFinished();

    QString content = process.readAll();

    if (process.exitStatus() == QProcess::CrashExit) {
        qDebug() << "which" << program << process.errorString() ;
    }

    return content.replace("\n", "");
}

static void execute(QString cwd, QString command , QStringList arguments) {
    qDebug().noquote() << command << arguments.join(" ");
    QProcess process;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    process.setProcessEnvironment(env);
    process.setWorkingDirectory(cwd);

    process.setProcessChannelMode(QProcess::ForwardedOutputChannel);

    process.start(command , arguments);

    process.waitForFinished();

    if (process.exitStatus() == QProcess::CrashExit) {
        qDebug() << command << process.errorString();
    }
}

Qmljsify::Qmljsify()
{
    m_minifyEnabled = false;
}

QString Qmljsify::buildFolder() const
{
    return m_buildFolder;
}

void Qmljsify::setBuildFolder(const QString &buildFolder)
{
    m_buildFolder = buildFolder;
}

void Qmljsify::prepare()
{
    QStringList files;
    files << "index.js" << "webpack.config.js" << "package.json";

    mkdir("-p", m_buildFolder);

    for (int i = 0 ; i < files.size() ; i++) {
        QString file = files[i];
        QString inputPath = realpath_strip(TEMPLATES, file);
        QString outputPath = realpath_strip(m_buildFolder, file);
        QString content = cat(inputPath);

        content = content.replace("%{PACKAGE}", m_package);

        writeToFile(outputPath, content);
    }
}

void Qmljsify::fetch()
{
    QString npm = which("npm");

    execute(m_buildFolder, npm, QStringList() << "install" << "--save" << m_package);
    execute(m_buildFolder, npm,  QStringList() << "install");
}

void Qmljsify::build()
{
    QString webpack = which("webpack");
    if (webpack.isEmpty()) {
        qWarning() << "webpack command not found. Please check your PATH environment variable.";
    }
    QStringList arguments;

    if (m_minifyEnabled) {
        arguments << "--env" << "minify";
    }

    execute(m_buildFolder, webpack, arguments);
}

void Qmljsify::create()
{
    QString file = ":/Qmljsify/WrapperCreator.qml";

    QQmlApplicationEngine engine;
    engine.load(file);

    QObject* script = engine.rootObjects().first();

    QString bundle = realpath_strip(m_buildFolder, "dist/bundle.js");;

    QString orig = realpath_strip(m_outputFolder, m_package + ".orig.js");

    cp(bundle, orig);

    qDebug().noquote() <<  QtShell::basename(orig) << " saved";

    QVariant result;

    QMetaObject::invokeMethod(script,
                              "create",
                              Qt::DirectConnection,
                              Q_RETURN_ARG(QVariant, result),
                              Q_ARG(QVariant, QUrl::fromLocalFile(orig).toString()),
                              Q_ARG(QVariant, QtShell::basename(orig)));

    QString output =  realpath_strip(m_outputFolder, m_package + ".js");
    writeToFile(output, result.toString());

    qDebug().noquote() << QtShell::basename(output) << " saved";
}

bool Qmljsify::minifyEnabled() const
{
    return m_minifyEnabled;
}

void Qmljsify::setMinifyEnabled(bool minifyEnabled)
{
    m_minifyEnabled = minifyEnabled;
}

QString Qmljsify::outputFolder() const
{
    return m_outputFolder;
}

void Qmljsify::setOutputFolder(const QString &outputFolder)
{
    m_outputFolder = outputFolder;
}

QString Qmljsify::package() const
{
    return m_package;
}

void Qmljsify::setPackage(const QString &package)
{
    m_package = package;
}
