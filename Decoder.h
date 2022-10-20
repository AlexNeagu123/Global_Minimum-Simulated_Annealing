#pragma once
#include <bitset>
#include "FunctionPoint.h"
#include "Arithmetics.h"
#include <chrono>
#include <random>

class BitmaskDecoder {
	std::pair<double, double> domain;
	double epsilon;
	int dimension;
	int one_dim_length;
	int bit_count;
public:
	BitmaskDecoder(const std::pair<double, double> &_domain, double _epsilon, int _dimension) : domain(_domain), epsilon(_epsilon), dimension(_dimension) {
		double dim_length = (domain.first - domain.second) / epsilon;
		one_dim_length = logarithm((int) dim_length);
		bit_count = one_dim_length * dimension;
	};
	std::bitset<my_constants::max_bitmask_size> generate_random_mask() const {
		std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
		std::bitset<my_constants::max_bitmask_size> mask;
		for (int i = 0; i < bit_count; ++i) {
			mask[i] = std::uniform_int_distribution<int>(0, 1)(rng);
		}
		return mask;
	}
	FunctionPoint decode_bit_mask(std::bitset<my_constants::max_bitmask_size> mask) const {
		FunctionPoint decoding_point(dimension);
		for (int i = 0; i < dimension; ++i) {
			long long coordinate_int = 0;
			for (int j = 0; j < one_dim_length; ++j) {
				coordinate_int <<= 1;
				coordinate_int += mask[i * one_dim_length + j];
			}
			double coordinate = coordinate_int;
			coordinate = coordinate / (fast_exponentation(2LL, one_dim_length) - 1) * (domain.second - domain.first) + domain.first;
			decoding_point[i] = coordinate;
		}
		return decoding_point;
	}
	inline int get_bit_count() const {
		return bit_count;
	}
};