#include "iris_functions.h"
#include <iostream>

// Function for reading in the flowers properties
// The input is the location of the data set
// The output is the property vector 

vector<double> reading_iris_values(string input)
{
	vector<double> data;
	double x;
	ifstream inFile;
	inFile.open(input);

	if (!inFile)
	{
		std::cout << "Unable to open file" << endl << endl;
		exit(1);
	}

	while (inFile >> x)
	{data.push_back(x);}

	inFile.close();
	return data;
}


//################################################

// Function for reading in the flowers classification
// After reading in the names, they are converted into numerical values
// If the flower is Iris-setosa, the value is 0
// If the flower is Iris-versicolor, the value is 1
// If the flower is Iris-virginica, the value is 2
// The input is the location of the data set
// The output is the classification vector 

vector<int> reading_iris_y(string input)
{
    vector<int> y;
    ifstream inFile;
    inFile.open(input);
    string values;

	if (!inFile)
	{
		std::cout << "Unable to open file" << endl << endl;
		exit(1);
	}

    while(inFile >> values)
    {
        if (values == "Iris-setosa")
        {y.push_back(0);}
        else if (values == "Iris-versicolor")
        {y.push_back(1);}
        else if (values == "Iris-virginica")
        {y.push_back(2);}
    }

    inFile.close();
    return y;
}


//################################################

// Function for splitting the data set into testing- and training data sets
// Using Mersenne Twister pseudo-random number generator
// Using 20% of the data set as testing data
// Returning the indices of the testing data

vector<int> test_generator()
{
    // Random seed
    random_device rd;

    // Initialize the pseudo-random number generator
    mt19937 gen(rd());

    // Generate pseudo-random numbers
    // Uniformly distributed in range (1, 150)
    uniform_int_distribution<> dis1(0, 49);
    uniform_int_distribution<> dis2(50, 99);
    uniform_int_distribution<> dis3(100, 149);

    // Creating array for the indices
    vector<int> indices_test(30);
    int rand_num;
    bool exists;

    // Generate ten pseudo-random numbers
    // Using 20% as testing data

    for(int i = 0; i < 10; i++)
    {
        rand_num = dis1(gen);
        exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false)
        indices_test[i] = rand_num;      
    }

    for(int i = 10; i < 20; i++)
    {
        rand_num = dis2(gen);
        exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false)
        indices_test[i] = rand_num;      
    }

    for(int i = 20; i < 30; i++)
    {
        rand_num = dis3(gen);
        exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false)
        indices_test[i] = rand_num;
    }

    // Returning with the test vector indices
    return(indices_test);
}

//################################################

// Function for creating the training data set
// The input is a vector of the indices of the testing data set
// The otput is the training data set's indices

vector<int> train_generator(const vector<int> &indices_test)
{
    // Creating array for the indices
    vector<int> indices_train;

    // Starting index
    int i = 0;

    // Declaring boolean
    

    //Iterating through the vector
    //Filling up the vector with elements if they are not in indices_test
    while(i < 150)
    {
        bool exists = find(begin(indices_test), end(indices_test), i) != end(indices_test);

        if(exists == false)
        {indices_train.push_back(i);}

        i += 1;
    }

    // Returning with the train vector
    return(indices_train);
}


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

    // Creating the weights matrix;
    vector<double> weights(15);

    // Declaring rand_num
    double rand_num;

    // Filling up the matrix
    for(int i = 0; i < 15; i++)
    {
        rand_num = weight_gen(gen)/100000.0;
        weights[i] = rand_num;
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

vector<double> model(const vector <double> &a, const vector <double> &b, const vector <double> &c, const vector <double> &d, const vector <int> &y, vector<double> &weights)
{
    // Creating vectors to store the elements
    vector<double> result(a.size()*3);

    // Creating the x*weights + bias vectors
    for(int i = 0; i < a.size(); i++)
    {
        result[i*3] = weights[0] + a[i]*weights[3] + b[i]*weights[6] + c[i]*weights[9] + d[i]*weights[12];
        result[i*3 + 1] = weights[1] + a[i]*weights[4] + b[i]*weights[7] + c[i]*weights[10] + d[i]*weights[13];
        result[i*3 + 2] = weights[2] + a[i]*weights[5] + b[i]*weights[8] + c[i]*weights[11] + d[i]*weights[14];
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

vector<double> multiclass_perceptron(const vector <double> &a, const vector <double> &b, const vector <double> &c, const vector <double> &d, const vector <int> &y, vector<double> &weights, double alpha)
{
    // Getting the results of the dot product
    vector<double> all_evals = model(a, b, c, d, y, weights);

    // Declaring some variables
    vector<double> temp;
    int64_t index;

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

vector<int> final_pred(const vector <double> &a, const vector <double> &b, const vector <double> &c, const vector <double> &d, const vector <int> &y, vector<double> &weights)
{
    // Getting the results of the dot product
    vector<double> all_evals = model(a, b, c, d, y, weights);

    // Setting up index vector
    vector<int> indices(a.size());
    vector<double> temp;

    // Iterating through the data
    // Updating the weights
    for(int i = 0; i < a.size(); i++)
    {
        //getting the current max element in the list
        temp = {all_evals[i*3], all_evals[i*3+1], all_evals[i*3+2]};
        auto it = max_element(begin(temp), end(temp));
        indices[i] = it - temp.begin();
    }

    // Returning with the indices
    return indices;
}

//################################################

// Function for calculating the accuracy of the prediction
// Input: the prediction vector

void acc_calc(const vector<int> &prediction, const vector<int> &real_y)
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