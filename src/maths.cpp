#include "./includes/maths.hpp"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include "includes/maths.hpp"

// #include "../lib/quick_imgui/include/quick_imgui/quick_imgui.hpp"

//////////////////////////////////////////
//  Basic generation and vizualisation  //
//////////////////////////////////////////

double generate_uniform_double()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator(seed);
    size_t       max{std::mt19937::max()};

    return static_cast<double>(generator()) / static_cast<double>(max);
}

static std::vector<double> generator_between_0_1(size_t nb_iterations)
{
    std::vector<double> generated{};
    generated.reserve(nb_iterations);

    for (int i = 0; i < nb_iterations; ++i)
    {
        generated.push_back(generate_uniform_double());
    }

    return generated;
}

// Data vizualisation
void print_vector(std::vector<double>& vector)
{
    for (double const value : vector)
    {
        std::cout << value << ", ";
    }
}

static std::array<double, 11> build_intervals(double const max)
{
    double                 increment{max / 10.f};
    std::array<double, 11> intervals{};

    std::cout << "intervals : ";
    for (int i{0}; i < 11; i++)
    {
        intervals[i] = static_cast<double>(i) * increment;
        std::cout << intervals[i] << ", ";
    }
    std::cout << "\n";
    return intervals;
}

static std::array<double, 10> data_in_intervals(std::vector<double> const& data, std::array<double, 11> intervals)
{
    std::array<double, 10> splitted_data_in_intervals{};
    double                 increment{1.f / static_cast<double>(data.size())};

    for (const double& value : data)
    {
        for (size_t i{1}; i < intervals.size(); i++) // start at 1 because intervals begin with 0
        {
            if (value < intervals[i])
            {
                splitted_data_in_intervals[i - 1] += increment; // do -1 because it starts at 1 and not 0
                break;
            }
        }
    }
    return splitted_data_in_intervals;
}

std::string visualization(const std::vector<double>& data)
{
    std::string            result{};
    auto                   max_element{std::max_element(data.begin(), data.end())};
    std::array<double, 11> intervals{build_intervals(*max_element)};
    std::array<double, 10> data_to_vizualise{data_in_intervals(data, intervals)};

    for (int i = 0; i < data_to_vizualise.size(); i++)
    {
        int bar_length{static_cast<int>(data_to_vizualise[i] * 50)};
        result += "[" + std::to_string(intervals[i]) + "-" + std::to_string(intervals[i + 1]) + "] ";
        result.append(bar_length, '#');
        result += " (" + std::to_string(data_to_vizualise[i]) + ")\n";
    }

    return result;
}

// TODO : Error handling (check warnings)


//////////////////////
// Uniform law  //
//////////////////////

static double generate_with_uniform_law(double min, double max)
{
    double u{generate_uniform_double()};
    return min + u * (max - min);

}

std::vector<double> use_uniform_law(size_t nb_iterations, double min, double max)
{
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(generate_with_uniform_law(min, max));
    }
    return generated_values;
}

//////////////////////
// Exponential law  //
//////////////////////

static double generate_with_exponential_law(double lambda)
{
    double u{generate_uniform_double()};

    return -1 * std::log(1 - u) / lambda;
}

std::vector<double> use_exponential_law(size_t nb_iterations, double lambda)
{
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    if (lambda <= 0) {return {};}
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(generate_with_exponential_law(lambda));
    }
    return generated_values;
}

///////////////////
// Bernoulli law //
///////////////////

static double generate_with_bernoulli_law(double p)
{
    double u{generate_uniform_double()};
    // warning u must be betwen 0 and 1 ?
    return (u <= (1 - p) ? 0 : 1);
}

std::vector<double> use_bernoulli_law(size_t nb_iterations, double probability_of_one)
{
    if (probability_of_one <= 0 || probability_of_one >= 1)
    {
        return {};
    }
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(generate_with_bernoulli_law(probability_of_one));
    }
    return generated_values;
}

std::string bernoulli_vizualisation(std::vector<double> const& generated_with_bernoulli_law)
{
    std::string result{};
    int         count_ones{static_cast<int>(std::count(generated_with_bernoulli_law.begin(), generated_with_bernoulli_law.end(), 1))};
    double      proba_ones{
        static_cast<double>(count_ones) / static_cast<double>(generated_with_bernoulli_law.size())
    };

    // Probabilities of 1
    int bar_length{static_cast<int>(proba_ones * 50)};
    result += "[" + std::to_string(1) + "] ";
    result.append(bar_length, '#');
    result += " (" + std::to_string(proba_ones) + ")\n";

    // Probabilities of 0
    bar_length = static_cast<int>((1 - proba_ones) * 50);
    result += "[" + std::to_string(1) + "] ";
    result.append(bar_length, '#');
    result += " (" + std::to_string(1 - proba_ones) + ")\n";

    return result;
}

//////////////////
// Binomial law //
//////////////////

static double generate_with_binomial_law(size_t nb_iterations_with_bernoulli, double probability_of_one)
{
    std::vector<double> bernoulli_generated(use_bernoulli_law(nb_iterations_with_bernoulli, probability_of_one));
    return std::accumulate(bernoulli_generated.begin(), bernoulli_generated.end(), 0.0);
}

std::vector<double> use_binomial_law(size_t nb_iterations, size_t nb_bernoulli_iterations, double probability_of_one)
{
    if (probability_of_one <= 0 || probability_of_one >= 1)
    {
        return {};
    }
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(generate_with_binomial_law(nb_bernoulli_iterations, probability_of_one));
    }
    return generated_values;
}

/////////////////////
// Geometrical law //
/////////////////////

static int generate_with_geometrical_law(double p)
{
    int count{1};
    while (generate_with_bernoulli_law(p) != 1)
    {
        count += 1;
    }
    return count;
};

// warning binomial and geometrical are not double TODO : adapt double to int
std::vector<double> use_geometrical_law(size_t nb_iterations, double p)
{
    // if (p <= 0 || probability_of_one >= 1)
    // {
    //     return {};
    // }
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(static_cast<double>(generate_with_geometrical_law(p)));
    }
    return generated_values;
}

/////////////////
// Poisson law //
/////////////////

template<typename T>
static T factoriel(T n)
{
    if (n == 0 || n == 1)
    {return 1;}
    return n * factoriel(n - 1);
}

static double generate_with_poisson_law(double lambda)
{
    double u{generate_uniform_double()};

    return std::pow(lambda, u) * std::exp(-lambda) / factoriel(u);
}

std::vector<double> use_poisson_law(size_t nb_iterations, double lambda)
{
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(generate_with_poisson_law(lambda));
    }
    return generated_values;
}


////////////////////
// Gaussienne law //
////////////////////

static double generate_with_gaussienne_law(double moyenne, double ecart_type)
{
    double u{generate_uniform_double()};
    const double pi = 3.14159265358979323846;
    return (1.0 / (ecart_type * std::sqrt(2.0 * pi))) *
           std::exp(-std::pow(u - moyenne, 2) / (2.0 * std::pow(ecart_type, 2)));
}

std::vector<double> use_gaussienne_law(size_t nb_iterations, double moyenne, double ecart_type)
{
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);

    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(generate_with_gaussienne_law(moyenne, ecart_type));
    }
    return generated_values;
}

////////////////////////
// Hypergeometric law //
////////////////////////

static double combinaison(int n, int k) {
    if (k < 0 || k > n) return 0.0;
    if (k == 0 || k == n) return 1.0;
    double res = 1.0;
    for (int i = 1; i <= k; ++i) {
        res *= (n - k + i);
        res /= i;
    }
    return res;
}

static int generate_with_hypergeometric_law(int N, int K, int n)
{
    double u = generate_uniform_double();
    int succes = 0;
    for (int i {0}; i< n; i++){
        double p = (double)K / N;
        double u = generate_uniform_double();

        if (u < p) {
            succes++;
            K--;
        }
        N--;
    }
    return succes;  
}

std::vector<double> use_hypergeometrical_law(size_t nb_iterations, int N, int K, int n)
{
    std::vector<double> generated_values{};
    generated_values.reserve(nb_iterations);
    for (size_t i{0}; i < nb_iterations; i++)
    {
        generated_values.push_back(static_cast<double>(generate_with_hypergeometric_law(N, K, n)));
    }
    return generated_values;
}