#include <iterator>
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <random>
#include <chrono>

using namespace std;

// Function for generating random weight matrix
vector<double> weight_generation();

// Function for the dot product of the weights and features
vector<double> model(vector <double> &a, vector <double> &b, vector <double> &c, vector <double> &d, vector <int> &y, vector<double> &weights);

// Multiclass perceptron function
vector<double> multiclass_perceptron(vector <double> &a, vector <double> &b, vector <double> &c, vector <double> &d, vector <int> &y, vector<double> &weights, double alpha);

// Function for calculating the final prediction
vector<int> final_pred(vector <double> &a, vector <double> &b, vector <double> &c, vector <double> &d, vector <int> &y, vector<double> &weights);

// Function for calculating the accuracy of the prediction
void acc_calc(vector<int> &prediction, vector<int> &real_y);