#include "StatusLineBridge.h"

StatusLineBridge::StatusLineBridge(QObject *parent, QWebEngineView* view)
	: QObject(parent)
{
	webview_s = view;
}

StatusLineBridge::~StatusLineBridge()
{
}

void StatusLineBridge::feedback_s() {
	dp::Result re = dp::getResult();
	if (re.anxious == -1) {

	}
	else
	{
		webview_s->page()->runJavaScript(QString("recvData('%1','%2','%3')").arg(re.anxious).arg(re.distracted).arg(re.relaxed));
	}
}

void StatusLineBridge::StopPage_s() {
	webview_s->page()->runJavaScript(QString("StopInterval()"));
}


