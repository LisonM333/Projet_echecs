#include "./includes/maths.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

std::vector<double> generator_between_0_1(size_t nb_iterations)
{
    std::vector<double> generated{};
    generated.reserve(nb_iterations);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator(seed);
    size_t       max{std::mt19937::max()};

    for (int i = 0; i < 10; ++i)
    {
        generated.push_back(static_cast<double>(generator()) / static_cast<double>(max));
        std::cout << static_cast<double>(generator()) / static_cast<double>(max) << " ";
        // std::cout << std::endl;
    }

    return generated;
}

std::string visualization(std::vector<double>& data)
{
    std::string result{};
    std::sort(data.begin(), data.end());
    std::reverse(data.begin(), data.end());
    for (double number : data)
    {
        for (unsigned int tab{0}; tab < std::floor(number * 10); tab++)
        {
            result.append("\t");
        }
        result.append("__\n");
    }
    return result;
}