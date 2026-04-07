#pragma once

#include <string>
#include <vector>

enum class Law : uint8_t {
    EXPONENTIAL,
};

double generate();
// std::vector<double> generate_with_law(Law const& law, size_t nb_iterations);

std::vector<double> use_exponential_law(size_t nb_iterations, double lambda);
std::vector<double> use_bernoulli_law(size_t nb_iterations, double probability_of_one);
std::vector<double> use_binomial_law(size_t nb_iterations, size_t nb_bernoulli_iterations, double probability_of_one);
std::vector<double> use_geometrical_law(size_t nb_iterations, double p);

std::string bernoulli_vizualisation(std::vector<double> const& generated_with_bernoulli_law);
std::string visualization(const std::vector<double>& data);

void print_vector(std::vector<double>& vector);

// void visualizeImgui();