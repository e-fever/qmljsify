#ifndef QMLJSIFY_H
#define QMLJSIFY_H

#include <QString>

class Qmljsify
{
public:
    Qmljsify();

    QString buildFolder() const;

    void setBuildFolder(const QString &buildFolder);

    QString package() const;

    void setPackage(const QString &package);

    void prepare();

    void fetch();

    void build();

    /// Create a wrapper of compiled JavaScript
    void create();

    bool minifyEnabled() const;

    void setMinifyEnabled(bool minifyEnabled);

    QString createdJavaScriptFile() const;
    void setCreatedJavaScriptFile(const QString &createdJavaScriptFile);

    QString outputFolder() const;
    void setOutputFolder(const QString &outputFolder);

    static QString normalizeFunctionName(const QString& package);

    QString packageVersion() const;

    void setPackageVersion(const QString &packageVersion);

    void parsePackageString(const QString& text);

    static QString queryPackageVersion(const QString& folder, const QString& packageName);

private:

    QString m_buildFolder;

    QString m_package;

    QString m_packageVersion;

    QString m_outputFolder;

    bool m_minifyEnabled;
};

#endif // QMLJSIFY_H
