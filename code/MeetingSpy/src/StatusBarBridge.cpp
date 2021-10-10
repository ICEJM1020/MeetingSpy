#include "StatusBarBridge.h"

StatusBarBridge::StatusBarBridge(QObject* parent, QWebEngineView* view)
{
	webview_a = view;
}

StatusBarBridge::~StatusBarBridge()
{

}

void StatusBarBridge::feedback_a()
{
	dp::Result re = dp::getTemp();
	if (re.anxious == -1) {

	}
	else
	{
		webview_a->page()->runJavaScript(QString("recvData('%1','%2','%3')").arg(re.anxious).arg(re.distracted).arg(re.relaxed));
	}
}

void StatusBarBridge::StopPage_a()
{
	webview_a->page()->runJavaScript(QString("StopInterval()"));
}
