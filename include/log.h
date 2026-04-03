#ifndef INCLUDE_INCLUDE_LOG_H_
#define INCLUDE_INCLUDE_LOG_H_

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>
#include "global.h"

namespace DataStructures {
	struct Polyline;	
};


namespace Log {

extern std::string measurement_directory;

enum class Algorithm {
  SIMPLIFICATION_KLW_MANHATTAN,
  SIMPLIFICATION_KLW_EUCLIDEAN,
  SIMPLIFICATION_KLW_IMPLICIT_EUCLIDEAN,
  SIMPLIFICATION_KLW_SEMIEXPLICIT_EUCLIDEAN,
  SIMPLIFICATION_KLW_CHEBYSHEV,
  SIMPLIFICATION_KLW_IMPLICIT_MINKOWSKI,

  SIMPLIFICATION_BC_MANHATTAN,
  SIMPLIFICATION_BC_EUCLIDEAN,
  SIMPLIFICATION_BC_IMPLICIT_EUCLIDEAN,
  SIMPLIFICATION_BC_SEMIEXPLICIT_EUCLIDEAN,
  SIMPLIFICATION_BC_CHEBYSHEV,
  SIMPLIFICATION_BC_IMPLICIT_MINKOWSKI,

  SIMPLIFICATION_IMAI_IRI_EUCLIDEAN,
  SIMPLIFICATION_GLOBAL_IMAI_IRI_HEURISTIC_EUCLIDEAN,

  BUILD_DS_EUCLIDEAN,
};

std::string algorithm_name(Algorithm);

typedef std::chrono::duration<double> Time;

struct DataSet final {
  std::string const header;
  Algorithm const algorithm;
  Dimension const dimension;
  PointCount const point_count;
  std::vector<Time> times;
  std::vector<size_t> simplification_sizes;
  std::vector<std::string> case_names;
};


class PerformanceLogger final {
private:
	std::vector<DataSet> data_sets;

public:
	void begin_data_set(Algorithm, Dimension, PointCount, std::string);

  void add_data(PointCount, std::chrono::duration<double>, std::string);
  void emit();

};

struct AlgorithmConfiguration final {
	bool output_visualization;
	std::optional<PerformanceLogger> logger;
};

void measure_suite(std::filesystem::path path);
void measure_suite_bc(std::filesystem::path path);
void measure_suite_klw(std::filesystem::path path);
void measure_suite_local(std::filesystem::path path);
void measure_suite_heuristic(std::filesystem::path path);

} // namespace Log
#endif // INCLUDE_INCLUDE_LOG_H_
