#include <chrono>
#include <numeric>
#include <iterator>

#include <vector>       // std::vector
#include <exception>    // std::runtime_error, std::exception
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <random>       // std::default_random_engine, std::uniform_real_distribution
#include <algorithm>    // std::transform
#include <cstdlib>      // EXIT_FAILURE
#include <iomanip>

using namespace std;


int main()
{
    int size;

    float epochs;
    float eta;

    std::vector<float> m_w;
    std::vector<float> m_errors;
    std::vector<vector<float>> X;
    std::vector<float> y;

    for (int i=0; i<X[0].size() + 1; i++)
    {
        m_w.push_back(0);
    }

    for (int i=0; i < epochs; i++)
    {
        int errors = 0;

        for (int j = 0; j < X.size(); j++)
        {
            float update = eta * (y[j] - predict(X[j]));

            for (int w = 1; w < m_w.size(); w++)
            {
                m_w[w] += update * X[j][w-1];
            }

            m_w[0] = update;

            errors += update != 0 ? 1 : 0;
        }
        m_errors.push_back(errors);
    }


    

}