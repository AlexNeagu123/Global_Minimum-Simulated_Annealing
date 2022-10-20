#include "Michalewiczs.h"
using Bitmask = std::bitset<my_constants::max_bitmask_size>;

double Michalewiczs::compute_value(FunctionPoint& current_point) {
	int m = 10;
	double s = 0.0;
	for (int i = 0; i < current_point.get_dimension(); ++i) {
		s = s + sin(current_point[i]) * fast_exponentation(
			sin((i + 1) * current_point[i] * current_point[i] / my_constants::PI),
			(2 * m)
		);
	}
	return -s;
}

std::pair<double, double> Michalewiczs::get_domain() const {
	return domain;
}

FunctionPoint Michalewiczs::decode_mask(const Bitmask& mask) {
	return decoder.decode_bit_mask(mask);
}

double Michalewiczs::eval_mask(const Bitmask& mask) {
	FunctionPoint decoded = decode_mask(mask);
	return compute_value(decoded);
}

int Michalewiczs::get_dimension() const {
	return dimension;
}

double Michalewiczs::get_epsilon() const {
	return epsilon;
}

Bitmask Michalewiczs::generate_mask() {
	return decoder.generate_random_mask();
}

int Michalewiczs::get_bit_size() {
	return decoder.get_bit_count();
}

void Michalewiczs::print_name(std::ofstream& out) {
	out << "------[Michalewiczs Function]-----" << std::endl;
}