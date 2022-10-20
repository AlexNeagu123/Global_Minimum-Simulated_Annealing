#pragma once

#include <cmath>
#include <utility>
#include <bitset>
#include "FunctionPoint.h"
#include "Arithmetics.h"
#include <fstream>

using Bitmask = std::bitset<my_constants::max_bitmask_size>;
class GenericFunction {
public:
	virtual int get_dimension() const = 0;
	virtual double get_epsilon() const = 0;
	virtual std::pair<double, double> get_domain() const = 0;
	virtual double compute_value(FunctionPoint& current_point) = 0;
	virtual double eval_mask(const Bitmask &mask) = 0;
	virtual void print_name(std::ofstream &out) = 0;
	virtual FunctionPoint decode_mask(const Bitmask& mask) = 0;
	virtual Bitmask generate_mask() = 0;
	virtual int get_bit_size() = 0;
};
