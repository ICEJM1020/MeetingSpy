#include "MeetingSpy.h"

MeetingSpy::MeetingSpy(QWidget *parent)
	: QMainWindow(parent)
{
	getScreen();
	create_ColorList();
	ui.setupUi(this);
	drawInterface();

	timerWin = new QTimer(this);
	timerWin->stop();// 时间到，读取当前摄像头信息

	timerDA = new QTimer(this);
	timerDA->stop();// 时间到，分析数据

	cap_on = true;
	codec = QTextCodec::codecForName("GBK");//文字格式

	connect(ui.OpenCaptureButton, SIGNAL(clicked()), this, SLOT(ClickCaptrueOn()));
	connect(ui.UpdateModelButton, SIGNAL(clicked()), this, SLOT(UpdateModel()));

	connect(timerWin, SIGNAL(timeout()), this, SLOT(readFrame()));
	connect(timerDA, SIGNAL(timeout()), this, SLOT(processData()));

}

void MeetingSpy::ClickCaptrueOn() {
	int fps = 30;
	if (cap_on) {
		//drawHTML();
		std::string time = DataAnalyse.set_time();
		QString Info = QString::fromStdString("Save to " + time);
		ui.textBrowser->setPlainText(Info);
		winCapture.startCap();
		timerWin->start(1000 / (fps));
		timerDA->start(400);
		ui.OpenCaptureButton->setText(codec->toUnicode("Capture Off"));
	}
	else {
		QString Info = QString::fromStdString("Capture is off");
		//ui.textBrowser->setPlainText(Info);
		ui.textBrowser->append(Info);
		winCapture.stopCap();
		timerWin->stop();
		//timerDA->stop();
		//timerInfo->stop();
		ui.CaptrueLabel->setText(codec->toUnicode("Capture closed"));
		ui.OpenCaptureButton->setText(codec->toUnicode("Capture On"));
	}
	cap_on = !cap_on;
	ui.OpenCaptureButton->repaint();
	ui.CaptrueLabel->repaint();
}

void MeetingSpy::UpdateModel()
{
	trainWin = std::make_shared<TrainModelWin>(this->width() / 2, this->height() / 2);
	trainWin->setColorList(ColorList);
	trainWin->show();

	/*auto msg = DataAnalyse.update_model();
	ui.textBrowser->append(QString::fromStdString(msg));*/
}

void MeetingSpy::readFrame()
{
	matFrame = winCapture.readNowFrame();

	//process image
	//cv:Mat dealedFrame = processImg(matFrame);
	//cv:Mat dealedFrame = matFrame;
	cv::Mat dealedFrame = FrameProcessor.Process(matFrame);
	
	QImage img;
	if (dealedFrame.empty()) img = cvMat2QImage(matFrame);
	else img = cvMat2QImage(dealedFrame);
	int a = ui.CaptrueLabel->width();
	int b = ui.CaptrueLabel->height();
	img = img.scaled(a, b);
	QPixmap qpixmap = QPixmap::fromImage(img);
	// 将图片显示到label上
	ui.CaptrueLabel->setPixmap(qpixmap);
	ui.CaptrueLabel->show();
	ui.CaptrueLabel->repaint();
}

void MeetingSpy::drawInterface()
{
	this->setGeometry(0, 0, screen_Width, screen_Height);
	this->setFixedSize(this->width(), this->height());

	ui.centralWidget->setStyleSheet(ColorList["main"]);

	ui.CaptrueLabel->setGeometry(100, 15, this->width()*0.6, this->height()*0.75);

	ui.OpenCaptureButton->setGeometry(20 + this->width() * 0.7, 20, this->width() * 0.1, this->height() * 0.05);
	ui.OpenCaptureButton->setStyleSheet(ColorList["button"]);
	ui.UpdateModelButton->setGeometry(20 + this->width() * 0.7, 20 + this->height() * 0.06, this->width() * 0.1, this->height() * 0.05);
	ui.UpdateModelButton->setStyleSheet(ColorList["button"]);

	ui.BarLabel->setGeometry(20 + this->width()*0.7, 50 + this->height()*0.1 + this->height()*0.3, this->width()*0.25, this->height()*0.28);
	
	ui.StatusLabel->setGeometry(120, this->height()*0.8, this->width()*0.9, this->height()*0.18);
	
	ui.textBrowser->setGeometry(20 + this->width()*0.7, 20 + 20 + this->height()*0.1, this->width()*0.25, this->height()*0.30);

	ui.modelSelectButton->setGeometry(30 + this->width() * 0.8, 20, this->width() * 0.1, this->height() * 0.03);
	ui.modelSelectButton->setStyleSheet(ColorList["menu"]);
	QMenu* modelMenu = new QMenu();
	modelMenu->setStyleSheet(ColorList["menu"]);
	QAction* selectRFAction = new QAction(tr("Random Forest"));
	QAction* selectAdadsAction = new QAction(tr("Adaboost-Decisionstump"));
	modelMenu->addAction(selectRFAction);
	modelMenu->addAction(selectAdadsAction); 
	connect(selectRFAction, SIGNAL(triggered()), this, SLOT(chooseRFModel()));
	connect(selectAdadsAction, SIGNAL(triggered()), this, SLOT(chooseAdadsModel()));
	ui.modelSelectButton->setMenu(modelMenu);

	drawHTML();
}

void MeetingSpy::getScreen()
{
	QDesktopWidget* thisDesktop = QApplication::desktop();
	//获取可用桌面大小  
	QRect deskRect = thisDesktop->screenGeometry(thisDesktop);
	//获取设备屏幕大小  
	QRect screenRect = thisDesktop->screenGeometry();

	int width = GetSystemMetrics(SM_CXFULLSCREEN);
	int height = GetSystemMetrics(SM_CYFULLSCREEN);
	/*screen_Width = screenRect.width();
	screen_Height = screenRect.height();*/
	screen_Width = width;
	screen_Height = height;
}

void MeetingSpy::create_ColorList()
{
	ColorList.insert(map<string, QString>::value_type("main", "background-color:rgb(225,238,210)"));
	ColorList.insert(map<string, QString>::value_type("button", "background-color:rgb(230,155,3);border-radius: 15px;"));
	ColorList.insert(map<string, QString>::value_type("sub_main", "background-color:rgb(190,225,200);"));
	ColorList.insert(map<string, QString>::value_type("sub_button", "background-color:rgb(210,125,3);border-radius: 15px;height:30px;"));
	ColorList.insert(map<string, QString>::value_type("menu", "QToolButton {background-color:rgb(230,155,3);border-radius: 10px;}"
		                                                      "QMenu {background-color:rgb(230,155,3);border-radius: 5px;}"
															  "QMenu::item {border-radius: 10px; border: 1px solid none;background-color:rgb(230,155,3);}"
															  "QMenu::item:selected {background-color:rgb(210,125,3);}"));
}

void MeetingSpy::chooseRFModel()
{
	
	ui.textBrowser->append(QString("Model selected to RandomForest"));
	ui.modelSelectButton->setText("RandomForest");
	ui.modelSelectButton->repaint();
	MODELSELECTION = 0;
}

void MeetingSpy::chooseAdadsModel()
{
	
	ui.textBrowser->append(QString("Model selected to Adaboost-Decisionstump"));
	ui.modelSelectButton->setText("Adaboost-DS");
	ui.modelSelectButton->repaint();
	MODELSELECTION = 1;
}

QImage MeetingSpy::cvMat2QImage(const cv::Mat& mat)    // Mat 改成 QImage
{
	if (mat.type() == CV_8UC1)                  // 单通道
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		image.setColorCount(256);               // 灰度级数256
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		uchar *pSrc = mat.data;                 // 复制mat数据
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}

	else if (mat.type() == CV_8UC3)             // 3通道
	{
		const uchar *pSrc = (const uchar*)mat.data;         // 复制像素
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);    // R, G, B 对应 0,1,2
		return image.rgbSwapped();              // rgbSwapped是为了显示效果色彩好一些。
	}
	else if (mat.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)mat.data;         // 复制像素
															// Create QImage with same dimensions as input Mat 
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);        // B,G,R,A 对应 0,1,2,3
		return image.copy();
	}
	else
	{
		return QImage();
	}
} 

void MeetingSpy::processData() {
	DataAnalyse.save_data();
	DataAnalyse.Analyse(MODELSELECTION);
}

void MeetingSpy::drawHTML()
{
	QWebEngineView* view = new QWebEngineView(ui.StatusLabel);
	view->resize(ui.StatusLabel->width(), ui.StatusLabel->height());
	view->load(QUrl::fromLocalFile(baseHTML + "StatusLine.html"));
	view->show();
	ChannelToHTML_StatusLine(view);

	QWebEngineView* view_2 = new QWebEngineView(ui.BarLabel);
	view_2->resize(ui.BarLabel->width(), ui.BarLabel->height());
	view_2->load(QUrl::fromLocalFile(baseHTML + "StatusBar.html"));
	view_2->show();
	ChannelToHTML_StatusBar(view_2);
}

void MeetingSpy::ChannelToHTML_StatusLine(QWebEngineView* view)
{
	ChannelToSL = new QWebChannel(view->page());
	SLBridge = new StatusLineBridge(this, view);

	ChannelToSL->registerObject("StatusLineBridge", SLBridge);
	view->page()->setWebChannel(ChannelToSL);
}

void MeetingSpy::ChannelToHTML_StatusBar(QWebEngineView* view)
{
	ChannelToSB = new QWebChannel(view->page());
	SBBridge = new StatusBarBridge(this, view);

	ChannelToSB->registerObject("StatusBarBridge", SBBridge);
	view->page()->setWebChannel(ChannelToSB);
}