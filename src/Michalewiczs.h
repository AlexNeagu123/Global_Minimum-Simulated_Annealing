#pragma once
#include "GenericFunction.h"
#include "Arithmetics.h"
#include "Decoder.h"
using Bitmask = std::bitset<my_constants::max_bitmask_size>;

class Michalewiczs : public GenericFunction {
	std::pair<double, double> domain;
	const double epsilon;
	int dimension;
public:
	BitmaskDecoder decoder;
	explicit Michalewiczs(const std::pair<double, double>& _domain, int _dimension, double _epsilon) : domain(_domain), epsilon(_epsilon), dimension(_dimension), decoder(domain, epsilon, dimension) {};
	double compute_value(FunctionPoint& current_point) override;
	std::pair<double, double> get_domain() const override;
	int get_dimension() const override;
	double get_epsilon() const override;
	void print_name(std::ofstream& out) override;
	FunctionPoint decode_mask(const Bitmask& mask) override;
	Bitmask generate_mask() override;
	double eval_mask(const Bitmask& mask) override;
	int get_bit_size() override;
};
