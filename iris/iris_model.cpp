#include "iris_model.h"


//################################################

// Function for generating random weight matrix
// Output: the weight matrix

vector<double> weight_generation()
{
    // Random seed
    random_device rd;

    // Initialize the pseudo-random number generator
    mt19937 gen(rd());

    // Generate pseudo-random numbers
    // Uniformly distributed in range (0, 1)
    uniform_int_distribution<> weight_gen(0, 100000);

    // Creating the weights matrix
    const int num_of_rows = 5;
    const int num_of_cols = 3;
    int it = num_of_rows*num_of_cols;
    vector<double> weights;

    // Declaring rand_num
    double rand_num;

    // Filling up the matrix
    for(int i = 0; i < it; i++)
    {
        rand_num = weight_gen(gen)/100000.0;
        weights.push_back(rand_num);
    }

    // Returning the weights
    return weights;
}


//################################################

// Function for the dot product of the weights and features
// Input 1-4: vectors of features 
// Input 5: y vector
// Input 6: weights vector
// Output: x*weight + bias

vector<double> model(vector <double> a, vector <double> b, vector <double> c, vector <double> d, vector <int> y, vector<double> weights)
{
    // Creating vectors to store the elements
    vector<double> result;

    // Creating the x*weights + bias vectors
    for(int i = 0; i < a.size(); i++)
    {
        result.push_back(weights[0] + a[i]*weights[3] + b[i]*weights[6] + c[i]*weights[9] + d[i]*weights[12]);
        result.push_back(weights[1] + a[i]*weights[4] + b[i]*weights[7] + c[i]*weights[10] + d[i]*weights[13]);
        result.push_back(weights[2] + a[i]*weights[5] + b[i]*weights[8] + c[i]*weights[11] + d[i]*weights[14]);
    }

    // Returning with the results
    return result;
}


//################################################

// Multiclass perceptron function
// Input 1-4: vectors of features 
// Input 5: y vector
// Input 6: weights vector
// Input 7: epoch number
// Input 8: learning rate
// Output: recalculated weights

vector<double> multiclass_perceptron(vector <double> a, vector <double> b, vector <double> c, vector <double> d, vector <int> y, vector<double> weights, double alpha)
{
    // Getting the results of the dot product
    vector<double> all_evals = model(a, b, c, d, y, weights);

    // Declaring some variables
    vector<double> temp;
    int index;

    // Iterating through the data
    // Updating the weights
    for(int i = 0; i < a.size(); i++)
    {
        //getting the current max element in the list
        temp = {all_evals[i*3], all_evals[i*3+1], all_evals[i*3+2]};
        auto it = max_element(begin(temp), end(temp));
        index = it - temp.begin();

        //updating the weights for the predicted indices
        weights[3 + index] -= alpha*a[i];
        weights[6 + index] -= alpha*b[i];
        weights[9 + index] -= alpha*c[i];
        weights[12 + index] -= alpha*d[i];

        //updating the weights for the actual indices
        weights[3 + y[i]] += alpha*a[i];
        weights[6 + y[i]] += alpha*b[i];
        weights[9 + y[i]] += alpha*c[i];
        weights[12 + y[i]] += alpha*d[i];
    }

    // Returning the weights
    return weights;
}


//################################################

// Function for calculating the final prediction
// Input 1-4: vectors of features 
// Input 5: y vector
// Input 6: weights vector
// Output: predicted labels

vector<int> final_pred(vector <double> a, vector <double> b, vector <double> c, vector <double> d, vector <int> y, vector<double> weights)
{
    // Getting the results of the dot product
    vector<double> all_evals = model(a, b, c, d, y, weights);

    // Setting up index vector
    vector<int> indices;
    vector<double> temp;

    // Iterating through the data
    // Updating the weights
    for(int i = 0; i < a.size(); i++)
    {
        //getting the current max element in the list
        temp = {all_evals[i*3], all_evals[i*3+1], all_evals[i*3+2]};
        auto it = max_element(begin(temp), end(temp));
        indices.push_back(it - temp.begin());
    }

    // Returning with the indices
    return indices;
}

//################################################

// Function for calculating the accuracy of the prediction
// Input: the prediction vector

void acc_calc(vector<int> prediction, vector<int> real_y)
{
    // Creating vector for the correct and incorrect predictions
    double correct_pred = 0.0;
    double incorrect_pred = 0.0;

    // Iterating through the data
    // Calculating the correct- and incorrect predictions
    for(int i = 0; i < prediction.size(); i++)
    {
        if(prediction[i] == real_y[i]){correct_pred += 1.0;}
        else{incorrect_pred += 1.0;}
    }

    // Calculating the accuracy
    double acc = 100.0*correct_pred/(correct_pred + incorrect_pred);

    // Printing the resulted accuracy
    cout << "\n" << "The accuracy of the model: " << acc << " %\n";

}