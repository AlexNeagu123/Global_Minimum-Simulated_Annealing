#pragma once
#include <cmath>

namespace my_constants {
	double constexpr PI = 3.14159265358979323846;
	int constexpr max_bitmask_size = 1000;
}
namespace annealing {
	double probability_function(double delta, double temperature);
}
double fast_exponentation(double base, int exponent);
int logarithm(int number);
