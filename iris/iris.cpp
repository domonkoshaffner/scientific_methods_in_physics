#include <iterator>
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <random>

using namespace std;

//################################################

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
	{
        data.push_back(x);		
	}

	inFile.close();
	return data;
}

//################################################

// Function for reading in the flowers classification
// After reading in the names, they are converted into numerical values
// If the flower is Iris-setosa, the value is -1
// If the flower is Iris-versicolor, the value is 1
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
        {
            y.push_back(-1);
        }
        else if (values == "Iris-versicolor")
        {
            y.push_back(-1);
        }
        else if (values == "Iris-virginica")
        {
            y.push_back(0);
        }
    }

    inFile.close();
    return y;
}

//################################################

// Function for printing any vector
// Input is the vector to be printed

template <class T>
void vec_print(vector<T> data)
{
    for(int i = 0; i < data.size(); i++)
    {
        cout << data[i] << ", ";
    }
}

//################################################

// Function for splitting the data set into testing- and training data sets
// Using Mersenne Twister pseudo-random number generator
// Using 20% of the data set as training data
// Returning the indices of the training data

vector<int> test_generator()
{
    // Random seed
    random_device rd;

    // Initialize the pseudo-random number generator
    mt19937 gen(rd());

    // Generate pseudo-random numbers
    // Uniformly distributed in range (1, 150)
    uniform_int_distribution<> dis1(0, 49);
    uniform_int_distribution<> dis2(0, 99);
    uniform_int_distribution<> dis3(0, 149);

    // Creating array for the indices
    vector<int> indices_test;

    // Generate ten pseudo-random numbers
    // I'm using 80% training and 20% testing data
    while (indices_test.size() < 10)
    {
        int rand_num = dis1(gen);
        bool exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false){
            indices_test.push_back(rand_num);
        }
    }

    while (indices_test.size() < 20)
    {
        int rand_num = dis2(gen);
        bool exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false){
            indices_test.push_back(rand_num);
        }
    }

    while (indices_test.size() < 30)
    {
        int rand_num = dis3(gen);
        bool exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false){
            indices_test.push_back(rand_num);
        }
    }

    // Returning with the test vector
    return(indices_test);
}

//################################################

// Function for creating the test data set
// The input is a vector of the indices of the testing data set
// The otput is the training data set's indices

vector<int> train_generator(vector<int> indices_test)
{
    // Creating array for the indices
    vector<int> indices_train;

    // Starting index
    int i = 0;

    //Iterating through the vector
    //Filling up the vector with elements if they are not in indices_test
    while(i < 150)
    {
        bool exists = find(begin(indices_test), end(indices_test), i) != end(indices_test);

        if(exists == false)
        {
            indices_train.push_back(i);
        }

        i += 1;
    }

    // Returning with the train vector
    return(indices_train);
}

//################################################

// Function for splitting the data set into training and testing sets according to the indices
// Input is the vector of indices and the data to be split
// Output is the split data set

template <class T>
vector<T> data_split(vector<T> data, vector<int> indices)
{

    // Creating the new vector
    vector<T> split_data;

    // Iterating through the data
    for(int i = 0; i < indices.size(); i++)
    {
        split_data.push_back(data[indices[i]]);
    }

    // Returning with the split vector
    return(split_data);
}


//################################################

// Function for predicting the values
// First input is the X vector, containing the four properties of the flowers
// Second input is the weights vector, where the first value is the bias
// The output is either 1 or -1, depending on the classification

int class_prediction(vector<double> X, vector<double> weights)
{
    // Adding the bias to the classification value
    double classification = weights[0];

    // Multiplying the flower properties with the weights
    for(int i = 0; i < X.size(); i++)
    {
        classification += X[i]*weights[i+1];
    }

    // Returning with the value 1 - first class - if the classification value is above 0.5
    if(classification > 0.5)
    {
        return 1;
    }

    // Returning with the value 0 - second class - if the classification value is between -0.5 and 0.5
    else if(classification > -0.5 && classification <= 0.5)
    {
        return 0;
    }

    // Returning with the value -1 - third class - if the classification value is below -0.5
    else if(classification <= 0.5)
    {
        return -1;
    }

}

//################################################

// Predicting the classes based on the test dataset
//The first four inputs are the testing datasets
// The fifth input is the testing classification values
// The sixth input is the weights vector
// The seveth input is the epoch number
// The function calculates the prediction values and outputs the accuracy of the preceptor model

double test_predict(vector<double> a_test, vector<double> b_test, vector<double> c_test, vector<double> d_test, vector<int> y_test, vector<double> weights)
{
    // Creating the combined four property- and the calles results vector 
    vector<double> x_test(4);
    vector<int> class_result_vec(a_test.size());

    // Initialising some variables for the accuracy measure
    double correct_values = 0.0;
    double incorrect_values = 0.0;
    double accuracy;

    // Iterating through the data and collecting the test values in the x_test vector
    for(int i = 0; i < a_test.size(); i++)
    {
        x_test[0] = a_test[i];
        x_test[1] = b_test[i];
        x_test[2] = c_test[i];
        x_test[3] = d_test[i];

        // Predicting the results of the model
        class_result_vec[i] = class_prediction(x_test, weights);

        // If the prediction result matches the testing result, the correct_values variable is increased by one
        if(class_result_vec[i] == y_test[i])
        {
            correct_values += 1;
        }

        // If the prediction result doesn't match the testing result, the correct_values variable is increased by one      
        else
        {
            incorrect_values += 1;
        }
    }

    // Calculating the accuracy 
    accuracy = correct_values / (correct_values + incorrect_values) * 100;

    return accuracy;

}


//################################################

// Function for modifying the weights and bias according to the learning rate and epoch number
// First four inputs are the four properties
// The fifth input is the flower type vector
// The sixth input is the epoch number
// The seventh input is the learning rate
// The output vector is the weight vector, where the first element is the bias

vector<double> fitting_function(vector<double> a_train, vector<double> b_train, vector<double> c_train, vector<double> d_train, vector<double> a_test, vector<double> b_test, vector<double> c_test, vector<double> d_test, vector<int> y_train, vector<int> y_test, int epochs, double learning_rate)
{
    // Creating a vector for the weight and for the four flower properties
    vector<double> weights(5, 0.0);
    vector<double> x_train(4);

    // Creating variables for measuring the accuracy
    double accuracy;
    vector<double> accuracy_vec;

    // Creating a variable for the preceptor 
    double prec;

    // Iterating through the epochs
    for(int i = 0; i <= epochs; i++)
    {
        // Iterating through the data
        for(int j = 0; j < a_train.size(); j++)
        {
            // Selecting the flower properties
            // Pushing them to the x_train vector
            x_train[0] = a_train[j];
            x_train[1] = b_train[j];
            x_train[2] = c_train[j];
            x_train[3] = d_train[j];            

            // Calculating the current preceptor value
            // Dot product of the four properties and weights, then adding the bias
            // The result is 1 or -1 depending on the type, subtracting this from the true value
            // Multiplying this with the learning_rate
            prec = learning_rate * (y_train[j] - class_prediction(x_train, weights));

            // Iterating through the weights and multiplying the preceptor result with the properties
            // Updating the weights
            for(int k = 1; k < weights.size(); k++)
            {
                weights[k] += prec * x_train[k-1];
            }

            // Updating the bias
            weights[0] += prec;
        }

        accuracy = test_predict(a_test, b_test, c_test, d_test, y_test, weights);
        accuracy_vec.push_back(accuracy);
    }

    // Returning the weights
    return accuracy_vec;
}

//################################################


int main()
{  
    // Reading in the different properties of the flowers
    vector<double> a = reading_iris_values("C:/All Files/MSc-IV/Adattud/iris/data/a_all.data");
    vector<double> b = reading_iris_values("C:/All Files/MSc-IV/Adattud/iris/data/b_all.data");
    vector<double> c = reading_iris_values("C:/All Files/MSc-IV/Adattud/iris/data/c_all.data");
    vector<double> d = reading_iris_values("C:/All Files/MSc-IV/Adattud/iris/data/d_all.data");

    // Reading in the classification values of the flowers
    vector<int> y = reading_iris_y("C:/All Files/MSc-IV/Adattud/iris/data/iris.data");

    // Calling the test- and train generation function sand returning the indices of the data sets
    vector<int> indices_test = test_generator();
    vector<int> indices_train = train_generator(indices_test);

    //Calling the data splitting function to categorise the data sets into testing and training data sets
    vector<double> a_test = data_split(a, indices_test);
    vector<double> a_train = data_split(a, indices_train);
    vector<double> b_test = data_split(b, indices_test);
    vector<double> b_train = data_split(b, indices_train);
    vector<double> c_test = data_split(c, indices_test);
    vector<double> c_train = data_split(c, indices_train);
    vector<double> d_test = data_split(d, indices_test);
    vector<double> d_train = data_split(d, indices_train);
    vector<int> y_test = data_split(y, indices_test);
    vector<int> y_train = data_split(y, indices_train);


    // Creating the epochs variable
    int epochs = 100;

    // Cheking if the epoch is a valid number
    if(epochs <= 0)
    {
        cout << "\nPlease enter a valid epoch number!\n";
        exit(1);
    }

    // Creating the learning rate variable
    double learning_rate = 0.01;

    // Cheking if the learning rate is a valid number
    if(learning_rate <= 0)
    {
        cout << "\nPlease enter a valid learning rate!\n";
        exit(1);
    }


    // Calling the fitting function
    vector<double> accuracy = fitting_function(a_train, b_train, c_train, d_train, a_test, b_test, c_test, d_test, y_train, y_test, epochs, learning_rate);

    // Outputting the results
    //cout << "\nThe prediction after " << epochs << " iteration(s), with a learning rate of " << learning_rate <<" is " << accuracy[epochs-1] << "% accurate.\n";

    // Printing the accuracy vector
    //vec_print(accuracy);

    // Writing the vector into a txt file 
    std::ofstream outFile("C:/All Files/MSc-IV/Adattud/iris/accuracy_vector.txt");
    for (const auto &e : accuracy) outFile << e << "\n";

}