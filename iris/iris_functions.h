#ifndef IRIS_FUNCTIONS_H
#define IRIS_FUNCTIONS_H

#include <iterator>
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <random>
#include <chrono>

using namespace std;

//###############################

// TEMPLATE FUNCTIONS 

// Function for splitting the data set into training and testing sets according to the indices
// Input is the vector of indices and the data to be split
// Output is the split data set

template <class T>
vector<T> data_split(const vector<T> &data, const vector<int> &indices)
{
    // Creating the new vector
    vector<T> split_data(indices.size());

    // Iterating through the data
    for(int i = 0; i < indices.size(); i++)
    {split_data[i] = data[indices[i]];}

    // Returning with the split vector
    return(split_data);
}


// Function for printing any vector
// Input is the vector to be printed

template <class T>
void vec_print(const vector<T> &data)
{
    for(int i = 0; i < data.size(); i++)
    {cout << data[i] << ", ";}
}

//###############################

// DEFINITIONS

// Reading in the Iris features from .txt files
vector<double> reading_iris_values(string input);

// Reading in the Iris labels from .txt files
vector<int> reading_iris_y(string input);

// Function for generating the test indices in 20%-80%
vector<int> test_generator();

// Function for generating the training data set
vector<int> train_generator(const vector<int> &indices_test);

// Function for generating random weight matrix
vector<double> weight_generation();

// Function for the dot product of the weights and features
vector<double> model(const vector <double> &a, const vector <double> &b, const vector <double> &c, const vector <double> &d, const vector <int> &y, vector<double> &weights);

// Multiclass perceptron function
vector<double> multiclass_perceptron(const vector <double> &a, const vector <double> &b, const vector <double> &c, const vector <double> &d, const vector <int> &y, vector<double> &weights, double alpha);

// Function for calculating the final prediction
vector<int> final_pred(const vector <double> &a, const vector <double> &b, const vector <double> &c, const vector <double> &d, vector <int> &y, vector<double> &weights);

// Function for calculating the accuracy of the prediction
void acc_calc(const vector<int> &prediction, const vector<int> &real_y);

#endif /* IRIS_FUNCTIONS_H */