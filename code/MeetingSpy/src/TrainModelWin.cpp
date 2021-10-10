#include "TrainModelWin.h"

TrainModelWin::TrainModelWin(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	pointX = 100;
	pointY = 100;

	da = std::make_shared<DataAnalyse>();
	//this->drawInterface();
}

TrainModelWin::TrainModelWin(int center_x, int center_y, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	if (center_x < 700 || center_y < 400) {
		WIDTH = 300;
		HEIGHT = 500;
		pointX = center_x - (this->WIDTH / 2);
		pointY = center_y - (this->HEIGHT / 2);

		//this->drawInterface();
	}
	else {
		pointX = center_x - (this->WIDTH / 2);
		pointY = center_y - (this->HEIGHT / 2);
		//this->drawInterface();
	}
	da = std::make_shared<DataAnalyse>();
}

TrainModelWin::~TrainModelWin()
{
}

void TrainModelWin::drawInterface()
{
	this->setGeometry(pointX, pointY, this->WIDTH, this->HEIGHT);
	this->setFixedSize(this->width(), this->height());
	this->setStyleSheet(ColorList["main"]);
	
	ui.tabWidget->setGeometry(5, 10, this->width() - 10, this->height()*0.5);
	ui.textBrowser->setGeometry(5, 30+ this->height() * 0.5, this->width() - 10, this->height() * 0.4);

	ui.tabWidget->setCurrentIndex(0);
	QFont topbutton("Times", 10);
	ui.tabWidget->setFont(topbutton);
	ui.tabWidget->setTabText(0, "RaodomForest");
	ui.tabWidget->setTabText(1, "Adaboost-DecisionStump");

	QFont tabFont("Times", 10, 75);

	//set Widget for random forest
	{
		ui.formLayoutWidget->setGeometry(0, 0, ui.tabWidget->width(), ui.tabWidget->height());
		ui.formLayoutWidget->setStyleSheet(ColorList["sub_main"]);
		ui.formLayoutWidget->setFont(tabFont);
		
		ui.trainRFbtn->setStyleSheet(ColorList["sub_button"]);
		ui.trainRFbtn->setCursor(Qt::PointingHandCursor);
		connect(ui.trainRFbtn, SIGNAL(clicked()), this, SLOT(trainRFModel()));

	}

	//set Widget for adaboost
	{
		ui.formLayoutWidget_2->setGeometry(0, 0, ui.tabWidget->width(), ui.tabWidget->height());
		ui.formLayoutWidget_2->setStyleSheet(ColorList["sub_main"]);
		ui.formLayoutWidget_2->setFont(tabFont);

		ui.trainAdadsbtn->setStyleSheet(ColorList["sub_button"]);
		ui.trainAdadsbtn->setCursor(Qt::PointingHandCursor);
		connect(ui.trainAdadsbtn, SIGNAL(clicked()), this, SLOT(trainAdadsModel()));

	}
}

void TrainModelWin::setColorList(std::map<std::string, QString> list)
{
	this->ColorList = list;
	this->drawInterface();
	this->repaint();
}

void TrainModelWin::trainAdadsModel()
{
	const size_t iterations = (ui.adads_iterationsEdit->text().toInt());
	const double tolerance = atof((ui.adads_toleranceEdit->text().toStdString()).c_str());
	QString msg = "Training Model: Adaboost-DecisionStump";
	msg += "\nParameters:";
	msg += "\niterations:" + QString::fromStdString(std::to_string(iterations));
	msg += "\ntolerance:" + QString::fromStdString(std::to_string(tolerance));

	ui.textBrowser->append(msg);

	//train Model
	ui.textBrowser->append(QString::fromStdString(da->load_data()));
	
	ui.textBrowser->append(QString::fromStdString(da->train_adads_model(iterations,tolerance)));

}

void TrainModelWin::trainRFModel()
{
	const size_t numTrees = ui.rf_numTreesEdit->text().toInt();
	const size_t minimumLeafSize = ui.rf_minLeafsizeEdit->text().toInt();
	const double minimumGainSplit = atof((ui.rf_minGainSplitEdit->text().toStdString()).c_str());
	const size_t maximumDepth = ui.rf_maxDepthEdit->text().toInt();

	QString msg = "Training Model: RaondomForest";
	msg += "\nParameters:";
	msg += "\nnumTrees:" + QString::fromStdString(std::to_string(numTrees));
	msg += "\nminimumLeafSize:" + QString::fromStdString(std::to_string(minimumLeafSize));
	msg += "\nminimumGainSplit:" + QString::fromStdString(std::to_string(minimumGainSplit));
	msg += "\nmaximumDepth:" + QString::fromStdString(std::to_string(maximumDepth));

	ui.textBrowser->append(msg);

	//train Model
	ui.textBrowser->append(QString::fromStdString(da->load_data()));
	ui.textBrowser->append(QString::fromStdString(da->train_rf_model(numTrees,minimumLeafSize,minimumGainSplit,maximumDepth)));
}

