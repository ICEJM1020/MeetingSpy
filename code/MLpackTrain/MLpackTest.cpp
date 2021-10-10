// MLpackTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <armadillo>
#include <mlpack/core.hpp>

#include "mlpack/methods/random_forest/random_forest.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/methods/adaboost/adaboost.hpp"

#include <mlpack/core/hpt/hpt.hpp>
#include <mlpack/core/cv/k_fold_cv.hpp>
#include <mlpack/core/cv/metrics/accuracy.hpp>
#include <mlpack/core/cv/metrics/precision.hpp>
#include <mlpack/core/cv/metrics/recall.hpp>
#include <mlpack/core/cv/metrics/F1.hpp>

using namespace mlpack;
using namespace mlpack::tree;
using namespace mlpack::cv;
using namespace mlpack::hpt;



int main()
{
	std::string msg = "";
	arma::mat dataset;
	bool loaded = mlpack::data::Load("data.csv", dataset);
	if (!loaded) {
		std::cout << "Load data file failed\n";
	}
	else {
		/*msg += "Load data file successfully\n";
		msg += "Get DATA " + std::to_string(dataset.n_rows) + " X " + std::to_string(dataset.n_cols) + "\n";
		arma::Row<size_t> labels;
		labels = arma::conv_to<arma::Row<size_t>>::from(dataset.row(dataset.n_rows - 1));
		dataset.shed_row(dataset.n_rows - 1);*/

		//model selection
		/*RandomForest<GiniGain, RandomDimensionSelect> rf;
		rf = RandomForest<GiniGain, RandomDimensionSelect>(dataset, labels, 3, 30);*/

		/*const size_t k = 15;
	

		KFoldCV<RandomForest<GiniGain, RandomDimensionSelect>, Accuracy> cv_rf_clf(k,dataset, labels, 3, true);
		double cvAcc_1 = cv_rf_clf.Evaluate(40, 1, 1e-6, 9);
		auto rf_1 = cv_rf_clf.Model();
		arma::Row<size_t> predictions_1;
		rf_1.Classify(dataset, predictions_1);
		double cvPrecision_1 = Precision<Binary>::Evaluate(rf_1, dataset, labels);
		double cvRecall_1 = Recall<Binary>::Evaluate(rf_1, dataset, labels);
		double cvF1_1 = F1<Binary>::Evaluate(rf_1, dataset, labels);

		const size_t correct_1 = arma::accu(predictions_1 == labels);
		msg += "\nRandom Forest:";
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_1) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_1);
		msg += "\nPrecision: " + std::to_string(cvPrecision_1);
		msg += "\nRecall: " + std::to_string(cvRecall_1);
		msg += "\nF1: " + std::to_string(cvF1_1);
		std::cout << msg;*/

		/*HyperParameterTuner<RandomForest<GiniGain, RandomDimensionSelect>, Accuracy, KFoldCV> hpt_rf(k, dataset, labels, 3, true);
		arma::vec numTreesSet = { 5, 7, 10};
		arma::vec minimumLeafSizeSet = { 1,2,3 };
		arma::vec minimumGainSplitSet = { 1e-5, 1e-3, 1e-2};
		arma::vec maximumDepthSet = { 3,4,5 };
		double a,b,c,d;
		std::tie(a, b, c, d) = hpt_rf.Optimize(numTreesSet, minimumLeafSizeSet, minimumGainSplitSet, maximumDepthSet);
		std::cout << a << b << c << d;*/

		//
		///*adaboost::AdaBoost<DecisionStump<>> adaclf;
		//adaclf = adaboost::AdaBoost<DecisionStump<>>(dataset, labels, 3, wl_1);*/
		/*DecisionStump<> wl_1;
		msg = "\nAdaboost-DecisionStump:";
		KFoldCV<adaboost::AdaBoost<DecisionStump<>>, Accuracy> cv_ada_clf(k, dataset, labels, 3, true);
		double cvAcc_2 = cv_ada_clf.Evaluate(wl_1, 25, 1e-2);
		auto rf_2 = cv_ada_clf.Model();
		arma::Row<size_t> predictions_2;
		rf_2.Classify(dataset, predictions_2);
		double cvPrecision_2 = Precision<Binary>::Evaluate(rf_2, dataset, labels);
		double cvRecall_2 = Recall<Binary>::Evaluate(rf_2, dataset, labels);
		double cvF1_2 = F1<Binary>::Evaluate(rf_2, dataset, labels);

		const size_t correct_2 = arma::accu(predictions_2 == labels);
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_2) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_2);
		msg += "\nPrecision: " + std::to_string(cvPrecision_2);
		msg += "\nRecall: " + std::to_string(cvRecall_2);
		msg += "\nF1: " + std::to_string(cvF1_2);
		std::cout << msg;*/

		/*DecisionStump<> wl_1;
		HyperParameterTuner<adaboost::AdaBoost<DecisionStump<>>, Accuracy, KFoldCV> hpt_ada_ds(k, dataset, labels, 3, true);
		arma::vec iterationsSet{5, 10, 15, 20, 30, 40, 50};
		arma::vec toleranceSet{1, 0.1, 0.01, 0.001, 0.0001};
		double bestIterations, bestTolerance;
		std::tie(bestIterations, bestTolerance) = hpt_ada_ds.Optimize(Fixed(wl_1), iterationsSet, toleranceSet);
		std::cout << "bestIterations: " << bestIterations << "\n" << "bestTolerance: " << bestTolerance;*/

		/*const size_t correct = arma::accu(predictions == labels);
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_2) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_2);
		msg += "\nPrecision: " + std::to_string(cvPrecision_2);
		msg += "\nRecall: " + std::to_string(cvRecall_2);
		msg += "\nF1: " + std::to_string(cvF1_2);
		std::cout << msg;*/

		///*init mlpack adaboost type
		//adaboost::AdaBoost<Perceptron<>> adaclf;
		//adaclf = adaboost::AdaBoost<>(dataset, labels, 3, wl_1);*/
		/*perceptron::Perceptron<> wl_2;
		msg = "\nAdaboost-Perceptron:";
		KFoldCV<adaboost::AdaBoost<>, Accuracy> cv_ada_P_clf(k, dataset, labels, 3, true);
		double cvAcc_3 = cv_ada_P_clf.Evaluate(wl_2);
		auto rf_3 = cv_ada_P_clf.Model();
		arma::Row<size_t> predictions_3;
		rf_3.Classify(dataset, predictions_3);
		double cvPrecision_3 = Precision<Binary>::Evaluate(rf_3, dataset, labels);
		double cvRecall_3 = Recall<Binary>::Evaluate(rf_3, dataset, labels);
		double cvF1_3 = F1<Binary>::Evaluate(rf_3, dataset, labels);

		const size_t correct_3 = arma::accu(predictions_3 == labels);
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_3) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_3);
		msg += "\nPrecision: " + std::to_string(cvPrecision_3);
		msg += "\nRecall: " + std::to_string(cvRecall_3);
		msg += "\nF1: " + std::to_string(cvF1_3);
		std::cout << msg;*/


		
		///*DecisionTree<> dtclf;
		//dtclf = DecisionTree<>(dataset, labels, 3);*/
		/*msg = "\nDecision Tree:";
		AllDimensionSelect tempSelect = AllDimensionSelect();
		KFoldCV<DecisionTree<>, Accuracy> cv_dt_clf(k, dataset, labels, 3, true);
		double cvAcc_4 = cv_dt_clf.Evaluate(9, 1e-5, 3, tempSelect);
		auto rf_4 = cv_dt_clf.Model();
		arma::Row<size_t> predictions_4;
		rf_4.Classify(dataset, predictions_4);
		double cvPrecision_4 = Precision<Binary>::Evaluate(rf_4, dataset, labels);
		double cvRecall_4 = Recall<Binary>::Evaluate(rf_4, dataset, labels);
		double cvF1_4 = F1<Binary>::Evaluate(rf_4, dataset, labels);

		const size_t correct_4 = arma::accu(predictions_4 == labels);
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_4) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_4);
		msg += "\nPrecision: " + std::to_string(cvPrecision_4);
		msg += "\nRecall: " + std::to_string(cvRecall_4);
		msg += "\nF1: " + std::to_string(cvF1_4);
		std::cout << msg;*/

		/*HyperParameterTuner<DecisionTree<>, Accuracy, KFoldCV> hpt_dt(k, dataset, labels, 3, true);
		arma::vec minLeafSet{3, 6, 9};
		arma::vec minSpitSet{0.0001, 0.00001, 0.000001, 0.0000001};
		arma::vec maxDepthSet{2, 3, 4, 5};
		AllDimensionSelect tempSelect = AllDimensionSelect();
		double BestminLeafSet, BestminSpitSet, BestmaxDepthSet;
		std::tie(BestminLeafSet, BestminSpitSet, BestmaxDepthSet) = hpt_dt.Optimize(minLeafSet, minSpitSet, maxDepthSet, Fixed(tempSelect));
		std::cout << BestminLeafSet << "," << BestminSpitSet <<","<< BestmaxDepthSet;
		//BestminLeafSet << 9 << BestminSpitSet << 0.0001 << BestmaxDepthSet << 5;
		*/

		/*const size_t correct = arma::accu(predictions == labels);
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_2) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_2);
		msg += "\nPrecision: " + std::to_string(cvPrecision_2);
		msg += "\nRecall: " + std::to_string(cvRecall_2);
		msg += "\nF1: " + std::to_string(cvF1_2);
		std::cout << msg;
		
		/*adaboost::AdaBoost<DecisionTree<>> adaclf;
		dtclf = DecisionTree<>(dataset, labels, 3);*/
		/*DecisionTree<> wl_3;
		msg = "\nAdaboost-DecisionTree:";
		KFoldCV<adaboost::AdaBoost<DecisionTree<>>, Accuracy> cv_ada_dt_clf(k, dataset, labels, 3, true);
		double cvAcc_5 = cv_ada_dt_clf.Evaluate(wl_3);
		auto rf_5 = cv_ada_dt_clf.Model();
		arma::Row<size_t> predictions_5;
		rf_5.Classify(dataset, predictions_5);
		double cvPrecision_5 = Precision<Binary>::Evaluate(rf_5, dataset, labels);
		double cvRecall_5 = Recall<Binary>::Evaluate(rf_5, dataset, labels);
		double cvF1_5 = F1<Binary>::Evaluate(rf_5, dataset, labels);

		const size_t correct_5 = arma::accu(predictions_5 == labels);
		msg += "\nTraining Accuracy: " + std::to_string((double(correct_5) / double(labels.n_elem)));
		msg += "\nKFoldCV Accuracy: " + std::to_string(cvAcc_5);
		msg += "\nPrecision: " + std::to_string(cvPrecision_5);
		msg += "\nRecall: " + std::to_string(cvRecall_5);
		msg += "\nF1: " + std::to_string(cvF1_5);
		std::cout << msg;*/


		//mlpack::data::Save<adaboost::AdaBoost<DecisionStump<>>>("AdaModel.xml", "AdaModel", rf_2);
		//mlpack::data::Save<RandomForest<GiniGain, RandomDimensionSelect>>("RFModel.xml", "RFModel", rf_1);
	
		RandomForest<GiniGain, RandomDimensionSelect> clf;
		mlpack::data::Load("RFModel.xml", "RFModel", clf);
		msg = "Reload it : ";
		/*double cvPrecision2 = Precision<Binary>::Evaluate(clf, dataset, labels);
		msg += "\nPrecision: " + std::to_string(cvPrecision2);
		double cvRecall2 = Recall<Binary>::Evaluate(clf, dataset, labels);
		msg += "\nRecall: " + std::to_string(cvRecall2);
		double cvF12 = F1<Binary>::Evaluate(clf, dataset, labels);
		msg += "\nF1: " + std::to_string(cvF12);*/
		std::cout << msg;
		arma::mat sample("94.0458,0.281167,1.02107,0.00181479,0.122677,0.00073466,-18.2187,12.0354,-8.20159,347,162,316,"
			"265,405,151,380,140,316,129,265,136,425,254,566,312,390,349,201,266,3,311,168,348");
		arma::mat probabilities;
		arma::Row<size_t> predictions;
		clf.Classify(sample, predictions, probabilities);
		//arma::u64 result = predictions.at(0);
		//std::cout << "\nClassification result: " << predictions << "\n" << "Probabilities: " <<arma::mean(probabilities.t());
		arma::Mat<double> result = arma::mean(probabilities.t());
		std::cout << typeid(result[0]).name() << std::endl;
		std::cout << result.at(1) << std::endl;
		std::cout << result.at(2) << std::endl;
	}
}

