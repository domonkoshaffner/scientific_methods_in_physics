/*
#ifndef iris_model_hpp
#define iris_model_hpp
*/


#include "iris_model.h"

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


//#endif