#pragma once

#include <armadillo>
#include <mlpack/core.hpp>

#include "mlpack/methods/random_forest/random_forest.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/methods/adaboost/adaboost.hpp"

#include <mlpack/core/cv/k_fold_cv.hpp>
#include <mlpack/core/cv/metrics/accuracy.hpp>
#include <mlpack/core/cv/metrics/precision.hpp>
#include <mlpack/core/cv/metrics/recall.hpp>
#include <mlpack/core/cv/metrics/F1.hpp>
#include <time.h>

#include "DataProcess.h"

using namespace arma;

class DataAnalyse
{
public:
	DataAnalyse();
	~DataAnalyse();

	bool Analyse(int mt);
	void save_data();
	std::string set_time();
	std::string load_data();
	std::string train_rf_model(const size_t numTrees = 20,
		const size_t minimumLeafSize = 1,
		const double minimumGainSplit = 1e-7,
		const size_t maximumDepth = 0);
	std::string train_adads_model(const size_t iterations = 100,
		const double tolerance = 1e-6);

private:
	mlpack::tree::RandomForest<mlpack::tree::GiniGain, mlpack::tree::RandomDimensionSelect> clf_rf;
	mlpack::adaboost::AdaBoost<mlpack::tree::DecisionStump<>> clf_ada;

	arma::mat dataset;
	Row<size_t> labels;
	std::string DATA_FOLDER = "data/";
	std::string MODEL_FOLDER = "models/mlpack/";
	std::string filename;
};

