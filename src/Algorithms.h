#pragma once
#pragma warning(disable : 4996)
#include "FunctionPoint.h"
#include "GenericFunction.h"
#include <ctime>
#include <chrono>
#include <time.h>
#include <fstream>

std::ofstream out("20oct_30_worst_rulari.out");

using Bitmask = std::bitset<my_constants::max_bitmask_size>;
namespace hill_climbing {
	Bitmask best_improvement(GenericFunction* function, Bitmask& current_mask) {
		int len = function->get_bit_size();
		Bitmask best = current_mask;
		double best_val = function->eval_mask(best);
		for (int i = 0; i < len; ++i) {
			current_mask[i] = !current_mask[i];
			double current_val = function->eval_mask(current_mask);
			if (current_val < best_val) {
				best = current_mask;
				best_val = current_val;
			}
			current_mask[i] = !current_mask[i];
		}
		return best;
	}
	Bitmask first_improvement(GenericFunction* function, Bitmask& current_mask) {
		int len = function->get_bit_size();
		std::vector<int> bits(len);
		for (int i = 0; i < len; ++i) {
			bits[i] = i;
		}
		std::random_shuffle(bits.begin(), bits.end());
		Bitmask first = current_mask, closest_mask;
		double init_value = function->eval_mask(current_mask);
		double min_delta = 1e9;
		for (int bit : bits) {
			first[bit] = !first[bit];
			double neighbour_value = function->eval_mask(first);
			if (neighbour_value < init_value) {
				return first;
			}
			else {
				if (min_delta < neighbour_value - init_value) {
					closest_mask = first;
					min_delta = neighbour_value - init_value;
				}
			}
			first[bit] = !first[bit];
		}
		return closest_mask;
	}
	Bitmask worst_improvement(GenericFunction* function, Bitmask& current_mask) {
		int len = function->get_bit_size();
		Bitmask worst_mask = current_mask;
		double init_value = function->eval_mask(current_mask);
		double min_difference = 2000000000.0;
		for (int i = 0; i < len; ++i) {
			current_mask[i] = !current_mask[i];
			double candidate_value = function->eval_mask(current_mask);
			if (candidate_value < init_value && init_value - candidate_value < min_difference) {
				min_difference = init_value - candidate_value;
				worst_mask = current_mask;
			}
			current_mask[i] = !current_mask[i];
		}
		return worst_mask;
	}
	std::pair<FunctionPoint, double> compute_minimum(GenericFunction* function, int iteration_limit, int type) {
		
		switch (type) {
			case 0: out << "Hill Climbing Algorithm (BEST IMPROVEMENT):" << std::endl; break;
			case 1: out << "Hill Climbing Algorithm (FIRST IMPROVEMENT):" << std::endl; break;
			case 2: out << "Hill Climbing Algorithm (WORST IMPROVEMENT):" << std::endl; break;
		}

		function -> print_name(out);
		out << std::fixed << std::setprecision(10);
		out << "Parameters: " << std::endl;
		out << "Number Of Dimensions: " << function->get_dimension() << std::endl;
		out << "Number of hill climbing iterations: " << iteration_limit << std::endl;
		out << "Epsilon value is: " << function->get_epsilon() << std::endl;
		auto start = std::chrono::system_clock::now();

		Bitmask answer_mask = function -> generate_mask();
		double answer_value = function->eval_mask(answer_mask);

		for (int i = 0; i < iteration_limit; ++i) {
			Bitmask final_mask = function -> generate_mask();
			double final_value = function->eval_mask(final_mask);
			bool local = false;
			do {
				Bitmask next_mask;
				switch (type) {
					case 0: {
						next_mask = best_improvement(function, final_mask);
						break;
					}
					case 1: {
						next_mask = first_improvement(function, final_mask);
						break;
					}
					case 2: {
						next_mask = worst_improvement(function, final_mask);
						break;
					}
				}
				double current_value = function->eval_mask(next_mask);
				if (current_value < final_value) {
					final_mask = next_mask;
					final_value = current_value;
				}
				else {
					local = true;
				}
			} while (!local);
			if (final_value < answer_value) {
				answer_mask = final_mask;
				answer_value = final_value;
			}
		}

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		out << "Finished computation at " << std::ctime(&end_time);
		out << "Elapsed time: " << elapsed_seconds.count() << "s";
		out << std::endl;
		return std::make_pair(function->decode_mask(answer_mask), function->eval_mask(answer_mask));
	}
};

namespace simulated_annealing {
	std::pair<FunctionPoint, double> compute_minimum(GenericFunction* function, double init_temperature, int coolings, int downgrade_nr, int iteration_limit) {
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);
		
		out << std::fixed;
		out << std::setprecision(10);

		out << "Simulated Annealing heuristic on Hill Climbing Algorithm (using FIRST IMPROVEMENT): " << std::endl;
		function -> print_name(out);
		out << "Parameters: " << std::endl;
		out << "Number Of Dimensions: " << function->get_dimension() << std::endl;
		out << "Number of hill climbing iterations: " << iteration_limit << std::endl;
		out << "Epsilon value is: " << function->get_epsilon() << std::endl;
		out << "Initial temperature: " << init_temperature << std::endl;
		out << "Number of coolings: " << coolings << std::endl;
		out << "Number of downgrades to a worse neighbour: " << downgrade_nr << std::endl;
		
		auto start = std::chrono::system_clock::now();

		Bitmask answer_mask = function->generate_mask();
		for (int i = 0; i < iteration_limit; ++i) {
			Bitmask candidate_mask = function->generate_mask();
			bool no_downgrades = false;
			for (double temperature = init_temperature, step = 0; step < coolings && !no_downgrades; temperature /= 2.0, step++) {
				int changes = 0;
				while (true) {
					Bitmask next_mask = hill_climbing::first_improvement(function, candidate_mask);
					double current_value = function->eval_mask(candidate_mask);
					double neighbour_value = function->eval_mask(next_mask);
					if (neighbour_value < current_value) {
						candidate_mask = next_mask;
					}
					else if (changes < downgrade_nr && dis(gen) < annealing::probability_function(abs(current_value - neighbour_value), temperature)) {
						if (current_value < function->eval_mask(answer_mask)) {
							answer_mask = candidate_mask;
						}
						candidate_mask = next_mask;
						changes += 1;
					}
					else {
						no_downgrades = true;
						break;
					}
				}
			}
			if (function->eval_mask(candidate_mask) < function->eval_mask(answer_mask)) {
				answer_mask = candidate_mask;
			}
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		out << "Finished computation at " << std::ctime(&end_time);
		out << "Elapsed time: " << elapsed_seconds.count() << "s";
		out << std::endl;
		return std::make_pair(function->decode_mask(answer_mask), function->eval_mask(answer_mask));
	}
}