#pragma once

#include <QObject>
#include <QWebEngineView>

#include "DataProcess.h"

class StatusLineBridge : 
	public QObject
{
	Q_OBJECT

public:
	StatusLineBridge(QObject *parent, QWebEngineView* view);
	~StatusLineBridge();

	QWebEngineView* webview_s;

public slots:
	void feedback_s();
	void StopPage_s();
};
