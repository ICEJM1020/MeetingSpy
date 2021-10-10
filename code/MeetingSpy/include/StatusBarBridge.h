#pragma once

#include <QObject>
#include <QWebEngineView>
#include <QDebug>
#include "DataProcess.h"

class StatusBarBridge :
    public QObject
{
    Q_OBJECT

public:
    StatusBarBridge(QObject* parent, QWebEngineView* view);
    ~StatusBarBridge();

    QWebEngineView* webview_a;

public slots:
    void feedback_a();
    void StopPage_a();
};

