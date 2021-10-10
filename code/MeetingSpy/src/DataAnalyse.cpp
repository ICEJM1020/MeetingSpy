#include "DataAnalyse.h"

DataAnalyse::DataAnalyse()
{
	mlpack::data::Load(MODEL_FOLDER + "RFModel.xml", "RFModel", clf_rf);
	mlpack::data::Load(MODEL_FOLDER + "AdadsModel.xml", "AdadsModel", clf_ada);
}

DataAnalyse::~DataAnalyse()
{

}

std::string DataAnalyse::load_data()
{
	std::string msg = "";
	
	bool loaded = mlpack::data::Load(DATA_FOLDER + "data.csv", dataset);
	if (!loaded) {
		return "Load data file failed\n";
	}
	else {
		msg += "Load data file successfully\n";
		msg += "Get DATA " + std::to_string(dataset.n_rows) + " X " + std::to_string(dataset.n_cols);
		
		labels = conv_to<Row<size_t>>::from(dataset.row(dataset.n_rows - 1));
		dataset.shed_row(dataset.n_rows - 1);
		return msg;
	}
}

std::string DataAnalyse::train_rf_model(const size_t numTrees,
										const size_t minimumLeafSize,
										const double minimumGainSplit,
										const size_t maximumDepth)
{
	const int k = 10;
	mlpack::cv::KFoldCV<mlpack::tree::RandomForest<mlpack::tree::GiniGain, mlpack::tree::RandomDimensionSelect>, mlpack::cv::Accuracy> cv_clf(k, dataset, labels, 3, true);
	//mlpack::cv::KFoldCV<mlpack::adaboost::AdaBoost<mlpack::tree::DecisionStump<>>, mlpack::cv::Accuracy> ada_clf(k, dataset, labels, 3, true);
	double cvAcc = cv_clf.Evaluate(40, 1, 1e-6, 9);
	auto rf = cv_clf.Model();
	arma::Row<size_t> predictions;
	rf.Classify(dataset, predictions);
	const size_t correct = arma::accu(predictions == labels);
	double cvPrecision = mlpack::cv::Precision<mlpack::cv::Binary>::Evaluate(rf, dataset, labels);
	double cvRecall = mlpack::cv::Recall<mlpack::cv::Binary>::Evaluate(rf, dataset, labels);
	double cvF1 = mlpack::cv::F1<mlpack::cv::Binary>::Evaluate(rf, dataset, labels);

	std::string msg = "\nTraining Accuracy: " + std::to_string((double(correct) / double(labels.n_elem)));
	msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc);
	msg += "\nPrecision: " + std::to_string(cvPrecision);
	msg += "\nRecall: " + std::to_string(cvRecall);
	msg += "\nF1: " + std::to_string(cvF1);
		
	mlpack::data::Save(MODEL_FOLDER + "RFModel.xml", "RFModel", rf);
	msg += "\nModel save to \"models/mlpack/RFModel.xml\"";

	return msg;
}

std::string DataAnalyse::train_adads_model(const size_t iterations, 
										   const double tolerance)
{
	mlpack::tree::DecisionStump<> wl;
	const int k = 10;
	mlpack::cv::KFoldCV<mlpack::adaboost::AdaBoost<mlpack::tree::DecisionStump<>>, mlpack::cv::Accuracy> cv_clf(k, dataset, labels, 3, true);
	double cvAcc = cv_clf.Evaluate(wl, iterations, tolerance);
	auto rf = cv_clf.Model();
	arma::Row<size_t> predictions;
	rf.Classify(dataset, predictions);
	const size_t correct = arma::accu(predictions == labels);
	double cvPrecision = mlpack::cv::Precision<mlpack::cv::Binary>::Evaluate(rf, dataset, labels);
	double cvRecall = mlpack::cv::Recall<mlpack::cv::Binary>::Evaluate(rf, dataset, labels);
	double cvF1 = mlpack::cv::F1<mlpack::cv::Binary>::Evaluate(rf, dataset, labels);

	std::string msg = "\nTraining Accuracy: " + std::to_string((double(correct) / double(labels.n_elem)));
	msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc);
	msg += "\nPrecision: " + std::to_string(cvPrecision);
	msg += "\nRecall: " + std::to_string(cvRecall);
	msg += "\nF1: " + std::to_string(cvF1);
	msg += "\niterations: " + std::to_string(iterations);
	msg += "\ntolerance: " + std::to_string(tolerance);

	mlpack::data::Save(MODEL_FOLDER + "AdadsModel.xml", "AdadsModel", rf);
	msg += "\nModel save to \"models/mlpack/AdadsModel.xml\"";

	return msg;
}

std::string DataAnalyse::set_time()
{
	time_t now = time(NULL);
	tm* tm_t = localtime(&now);
	filename = DATA_FOLDER + 
		std::to_string(tm_t->tm_mon + 1) + "-" + std::to_string(tm_t->tm_mday) + "-" +
		std::to_string(tm_t->tm_hour) + "-" + std::to_string(tm_t->tm_min) + ".csv";

	std::fstream stream;
	stream.open(filename, std::fstream::out | std::fstream::app);
	stream << "attention" << "," << "disgust" << ","
		<< "engagement" << "," << "joy" << ","
		<< "browfurrow" << "," << "browraise" << ","
		<< "pitch" << "," << "roll" << ","
		<< "yaw" << ","
		<< "NoseX" << "," << "NoseY" << ","
		<< "UpCenterX" << "," << "UpCenterY" << ","
		<< "LEarX" << "," << "LEarY" << ","
		<< "LEyeX"<< "," << "LEyeY" << ","
		<< "REyeX" << "," << "REyeY" << ","
		<< "REarX" << "," << "REarY" << ","
		<< "LSX" << "," << "LSY" << ","
		<< "LAX" << "," << "LAY" << ","
		<< "LHX" << "," << "LHY" << ","
		<< "RSX" << "," << "RSY" << ","
		<< "RAX" << "," << "RAY" << ","
		<< "RHX" << "," << "RHY" <<
		std::endl;
	stream.close();

	return filename;
}


bool DataAnalyse::Analyse(int mt)
{
	dp::Result re;
	dp::personData temp;
	if (dp::stackStatus() > 0) {
		temp = dp::getData(true);
	}
	else {
		return false;
	}

	arma::mat input(temp.to_str());
	arma::mat probabilities;
	arma::Row<size_t> predictions;

	switch (mt)
	{
	case 0:
		clf_rf.Classify(input, predictions, probabilities);
		break;
	case 1:
		clf_ada.Classify(input, predictions, probabilities);
		break;
	default:
		clf_rf.Classify(input, predictions, probabilities);
		break;
	}

	arma::Mat<double> result = arma::mean(probabilities.t());
	re.relaxed = result.at(0);
	re.anxious = result.at(1);
	re.distracted = result.at(2);

	dp::putResult(re);

	return true;
}

void DataAnalyse::save_data()
{
	if (dp::stackStatus() > 0) {
		std::fstream stream;
		stream.open(filename, std::fstream::out | std::fstream::app);

		//while (dp::stackStatus() > 0) {
		dp::personData temp = dp::getData(false);
		stream << temp.to_str() << std::endl;
		//}
		
		stream.close();
	}
}

