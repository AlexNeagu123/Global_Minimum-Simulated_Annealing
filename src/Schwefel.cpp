#include "Schwefel.h"
using Bitmask = std::bitset<my_constants::max_bitmask_size>;

double Schwefel::compute_value(FunctionPoint& current_point) {
	double s = 0.0;
	for (int j = 0; j < current_point.get_dimension(); ++j) {
		s = s + current_point[j] * sin(sqrt(abs(current_point[j])));
	}
	return 418.9829 * current_point.get_dimension() - s;
}

std::pair<double, double> Schwefel::get_domain() const {
	return domain;
}

FunctionPoint Schwefel::decode_mask(const Bitmask& mask) {
	return decoder.decode_bit_mask(mask);
}

double Schwefel::eval_mask(const Bitmask& mask) {
	FunctionPoint decoded = decode_mask(mask);
	return compute_value(decoded);
}

int Schwefel::get_dimension() const {
	return dimension;
}

double Schwefel::get_epsilon() const {
	return epsilon;
}

Bitmask Schwefel::generate_mask() {
	return decoder.generate_random_mask();
}

int Schwefel::get_bit_size() {
	return decoder.get_bit_count();
}

void Schwefel::print_name(std::ofstream& out) {
	out << "------[Schwefell Function]-----" << std::endl;
}