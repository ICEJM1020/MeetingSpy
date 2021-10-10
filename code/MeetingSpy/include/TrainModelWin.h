#pragma once

#include <QWidget>
#include "ui_TrainModelWin.h"
#include <iostream>
#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QTabBar>
#include <QPushButton>

#include "DataAnalyse.h"

class TrainModelWin : public QWidget
{
	Q_OBJECT

public:
	TrainModelWin(QWidget *parent = Q_NULLPTR);
	TrainModelWin(int center_x, int cneter_y, QWidget* parent = Q_NULLPTR);
	~TrainModelWin();
	void setColorList(std::map<std::string, QString> ColorList);
	
	std::shared_ptr<DataAnalyse> da;

private slots:
	void trainRFModel();
	void trainAdadsModel();

private:
	Ui::TrainModelWin ui;
	int WIDTH = 500;
	int HEIGHT = 700;
	int pointX = 100;
	int pointY = 100;
	std::map<std::string, QString> ColorList;

	void drawInterface();
	
};
