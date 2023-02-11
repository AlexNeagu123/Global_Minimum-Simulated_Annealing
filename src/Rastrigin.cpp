#include "Rastrigin.h"
using Bitmask = std::bitset<my_constants::max_bitmask_size>;

double Rastrigin::compute_value(FunctionPoint& current_point) {
	double s = 0.0;
	for (int j = 0; j < current_point.get_dimension(); ++j) {
		s = s + (current_point[j] * current_point[j] - 10.0 * cos(2 * my_constants::PI * current_point[j]));
	}
	return 10.0 * current_point.get_dimension() + s;
}

std::pair<double, double> Rastrigin::get_domain() const {
	return domain;
}

FunctionPoint Rastrigin::decode_mask(const Bitmask& mask) {
	return decoder.decode_bit_mask(mask);
}

double Rastrigin::eval_mask(const Bitmask& mask) {
	FunctionPoint decoded = decode_mask(mask);
	return compute_value(decoded);
}

int Rastrigin::get_dimension() const {
	return dimension;
}

double Rastrigin::get_epsilon() const {
	return epsilon;
}

Bitmask Rastrigin::generate_mask() {
	return decoder.generate_random_mask();
}

int Rastrigin::get_bit_size() {
	return decoder.get_bit_count();
}

void Rastrigin::print_name(std::ofstream& out) {
	out << "------[Rastrigin Function]-----" << std::endl;
}