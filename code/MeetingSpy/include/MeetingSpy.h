#pragma once

#include <QtWidgets/QMainWindow>
#include <QDesktopWidget>
#include <qtimer>
#include <qtextcodec.h>
#include <qprocess>
#include <map>
#include "ui_MeetingSpy.h"
#include <QMenu>
#include <QStyle>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDir>

#include <opencv2/opencv.hpp>
#include <Windows.h>

#include "ReadCapture.h"
#include "FrameProcess.h"
#include "DataProcess.h"
#include "DataAnalyse.h"
#include "StatusLineBridge.h"
#include "StatusBarBridge.h"
#include "TrainModelWin.h"

class MeetingSpy : public QMainWindow
{
	Q_OBJECT

public:
	//parameter
	QTextCodec *codec;
	QTimer *timerWin;
	QTimer *timerDA;
	ReadCapture winCapture;
	FrameProcess FrameProcessor;
	DataAnalyse DataAnalyse;
	std::shared_ptr<TrainModelWin> trainWin;
	//vector<vector<int>> ColorList;
	//function
	MeetingSpy(QWidget *parent = Q_NULLPTR);


public slots:
	void ClickCaptrueOn();
	void UpdateModel();
	void readFrame();
	void processData();
	void chooseRFModel();
	void chooseAdadsModel();

private:
	//parameters
	int screen_Width;
	int screen_Height;
	Ui::MeetingSpyClass ui;
	bool cap_on;
	cv::Mat matFrame;
	std::map<string, QString> ColorList;
	int MODELSELECTION = 0;
	QString baseHTML = QDir::currentPath() + "/html/";
	QWebChannel* ChannelToSL;
	StatusLineBridge* SLBridge;
	QWebChannel* ChannelToSB;
	StatusBarBridge* SBBridge;

	//function
	void drawInterface();
	void getScreen();
	QImage cvMat2QImage(const cv::Mat& mat);
	void create_ColorList();
	void drawHTML();
	void ChannelToHTML_StatusLine(QWebEngineView* view);
	void ChannelToHTML_StatusBar(QWebEngineView* view);
};
