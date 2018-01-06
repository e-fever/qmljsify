#pragma once
#include <QObject>

class Tests : public QObject
{
    Q_OBJECT
public:
    explicit Tests(QObject *parent = 0);

private slots:

    void test_normalizeFunctionName();

    void test_prepare();

    void test_create();

    void test_leftpad();

};

