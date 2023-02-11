#include "DeJong.h"
using Bitmask = std::bitset<my_constants::max_bitmask_size>;

double DeJong::compute_value(FunctionPoint& current_point) {
	double s = 0;
	for (int j = 0; j < current_point.get_dimension(); ++j)
		s = s + current_point[j] * current_point[j];
	return s;
}

std::pair<double, double> DeJong::get_domain() const {
	return domain;
}

FunctionPoint DeJong::decode_mask(const Bitmask& mask) {
	return decoder.decode_bit_mask(mask);
}

double DeJong::eval_mask(const Bitmask& mask) {
	FunctionPoint decoded = decode_mask(mask);
	return compute_value(decoded);
}

int DeJong::get_dimension() const {
	return dimension;
}

double DeJong::get_epsilon() const {
	return epsilon;
}

Bitmask DeJong::generate_mask() {
	return decoder.generate_random_mask();
}

int DeJong::get_bit_size() {
	return decoder.get_bit_count();
}

void DeJong::print_name(std::ofstream& out) {
	out << "------[DeJong Function]-----" << std::endl;
}