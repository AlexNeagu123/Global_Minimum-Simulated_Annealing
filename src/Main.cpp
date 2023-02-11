#include <iostream>
#include <random>
#include <bitset>
#include "Rastrigin.h"
#include "Algorithms.h"
#include "Michalewiczs.h"
#include "DeJong.h"
#include "Schwefel.h"

void print_answer(std::pair<FunctionPoint, double> answer) {
	out << "The minimum value is: " << answer.second << std::endl << std::endl;
}

void solve_5d_cases() {
	GenericFunction* functions[4];
	functions[0] = new Rastrigin(std::make_pair(-5.12, 5.12), 5, 0.00001);
	functions[1] = new Michalewiczs(std::make_pair(0, my_constants::PI), 5, 0.00001);
	functions[2] = new DeJong(std::make_pair(-5.12, 5.12), 5, 0.00001);
	functions[3] = new Schwefel(std::make_pair(-500, 500), 5, 0.00001);
	// print_answer(hill_climbing::compute_minimum(functions[3], 10000, 0));
	for (int i = 0; i < 4; ++i) {
		/*print_answer(hill_climbing::compute_minimum(functions[i], 10000, 0));
		print_answer(hill_climbing::compute_minimum(functions[i], 10000, 1));*/
		print_answer(hill_climbing::compute_minimum(functions[i], 10000, 2));
	}
}
void solve_10d_cases() {
	GenericFunction* functions[4];
	functions[0] = new Rastrigin(std::make_pair(-5.12, 5.12), 10, 0.00001);
	functions[1] = new Michalewiczs(std::make_pair(0, my_constants::PI), 10, 0.00001);
	functions[2] = new DeJong(std::make_pair(-5.12, 5.12), 10, 0.00001);
	functions[3] = new Schwefel(std::make_pair(-500, 500), 10, 0.00001);
	print_answer(hill_climbing::compute_minimum(functions[3], 5000, 0));
	//print_answer(simulated_annealing::compute_minimum(functions[0], 10000, 20, 100, 50));
	//print_answer(simulated_annealing::compute_minimum(functions[1], 10000, 20, 100, 50));
	//print_answer(simulated_annealing::compute_minimum(functions[2], 10000, 20, 100, 50));
	/*print_answer(hill_climbing::compute_minimum(functions[2], 1, 2));*/
	for (int i = 0; i < 4; ++i) {
		/*print_answer(hill_climbing::compute_minimum(functions[i], 5000, 0));
		print_answer(hill_climbing::compute_minimum(functions[i], 5000, 1));*/
		print_answer(hill_climbing::compute_minimum(functions[i], 5000, 2));
	}
}

void solve_30d_cases() {
	GenericFunction* functions[4];
	functions[0] = new Rastrigin(std::make_pair(-5.12, 5.12), 30, 0.00001);
	functions[1] = new Michalewiczs(std::make_pair(0, my_constants::PI), 30, 0.00001);
	functions[2] = new DeJong(std::make_pair(-5.12, 5.12), 30, 0.00001);
	functions[3] = new Schwefel(std::make_pair(-500, 500), 30, 0.00001);
	/*print_answer(simulated_annealing::compute_minimum(functions[0], 10000, 20, 100, 50));
	print_answer(simulated_annealing::compute_minimum(functions[1], 10000, 20, 100, 50));
	print_answer(simulated_annealing::compute_minimum(functions[2], 10000, 20, 100, 50));*/
	// print_answer(simulated_annealing::compute_minimum(functions[3], 500000, 25, 250, 100));
	for (int i = 0; i < 4; ++i) {
		/*print_answer(hill_climbing::compute_minimum(functions[i], 500, 0));
		print_answer(hill_climbing::compute_minimum(functions[i], 500, 1));*/
		print_answer(hill_climbing::compute_minimum(functions[i], 500, 2));
	}
}

int main() {
	// solve_10d_cases();
	for(int i = 0; i < 30; ++i) {
		out << "Running nr " << i << std::endl;
		solve_5d_cases();
		solve_10d_cases();
		solve_30d_cases();
	}
	// solve_10d_cases();
	/*print_answer(simulated_annealing::compute_minimum(function, 10, 10, 10, 1000));*/
}