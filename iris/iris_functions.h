#ifndef IRIS_FUNCTIONS_H
#define IRIS_FUNCTIONS_H

#include <iterator>
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <random>
#include <chrono>

using namespace std;

// Reading in the Iris features from .txt files
vector<double> reading_iris_values(string input);

// Reading in the Iris labels from .txt files
vector<int> reading_iris_y(string input);

// Function for printing an arbitrary vector
template <class T>
void vec_print(vector<T> &data);

// Function for generating the test indices in 20%-80%
vector<int> test_generator();

// Function for generating the training data set
vector<int> train_generator(vector<int> &indices_test);

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

#endif /* IRIS_FUNCTIONS_H */