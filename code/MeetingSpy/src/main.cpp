#include "MeetingSpy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MeetingSpy w;
	w.show();
	return a.exec();
}
