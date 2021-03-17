#include <iterator>
#include <vector>       // std::vector
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

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
        else
        {
            y.push_back(1);
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
// The splitting is by the parity 
// The first input is the data to be splitted
// The second input is the remainder - if it's 0, the even-, if it's 1, the odd numbers are saved
// The output is either the training- or the testing data set

template <class T>
vector<T> train_test_split(vector<T> data, int remainder)
{
    vector<T> train_test_vector;

    for(int i = 0; i < data.size(); i++)
    {
        if(i%2 == remainder)
        {
            train_test_vector.push_back(data[i]);
        }
    }
    return(train_test_vector);
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

    // Returning with the value 1 - first class - if the classification value is above 0
    if(classification > 0)
    {
        return 1;
    }

    // Returning with the value -1 - second class - if the classification value is below 0
    else if(classification < 0)
    {
        return -1;
    }

}

//################################################

// Function for modifying the weights and bias according to the learning rate and epoch number
// First four inputs are the four properties
// The fifth input is the flower type vector
// The sixth input is the epoch number
// The seventh input is the learning rate
// The output vector is the weight vector, where the first element is the bias

vector<double> fitting_function(vector<double> a_train, vector<double> b_train, vector<double> c_train, vector<double> d_train, vector<int> y_train, int epochs, double learning_rate)
{
    // Creating a vector for the weight and for the four flower properties
    vector<double> weights(5, 0.0);
    vector<double> x_train(4);

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
            weights[0] = prec;
        }
    }

    // Returning the weights
    return weights;
}

//################################################

// Predicting the classes based on the test dataset
//The first four inputs are the testing datasets
// The fifth input is the testing classification values
// The sixth input is the weights vector
// The seveth input is the epoch number
// The function calculates the prediction values and outputs the accuracy of the preceptor model

void test_predict(vector<double> a_test, vector<double> b_test, vector<double> c_test, vector<double> d_test, vector<int> y_test, vector<double> weights, int epochs, double learning_rate)
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

    // Outputting the results
    cout << "\nThe prediction after " << epochs << " iteration(s), with a learning rate of " << learning_rate <<" is " << accuracy << "% accurate.\n";
}

//################################################
int main()
{  
    // Reading in the different properties of the flowers
    vector<double> a = reading_iris_values("C:/Users/haffn/Desktop/Adattud/iris/data/a.txt");
    vector<double> b = reading_iris_values("C:/Users/haffn/Desktop/Adattud/iris/data/b.txt");
    vector<double> c = reading_iris_values("C:/Users/haffn/Desktop/Adattud/iris/data/c.txt");
    vector<double> d = reading_iris_values("C:/Users/haffn/Desktop/Adattud/iris/data/d.txt");

    // Reading in the classification values of the flowers
    vector<int> y = reading_iris_y("C:/Users/haffn/Desktop/Adattud/iris/data/y.txt");

    // Splitting the properties into training and testing data
    vector<double> a_train = train_test_split(a, 0);
    vector<double> b_train = train_test_split(b, 0);
    vector<double> c_train = train_test_split(c, 0);
    vector<double> d_train = train_test_split(d, 0);

    vector<double> a_test = train_test_split(a, 1);
    vector<double> b_test = train_test_split(b, 1);
    vector<double> c_test = train_test_split(c, 1);
    vector<double> d_test = train_test_split(d, 1);

    // Splitting the classification values into training and testing data
    vector<int> y_train = train_test_split(y, 0);
    vector<int> y_test = train_test_split(y, 1);

    // Checking the vectors as the output
    //vec_print(y_train);

    // Creating the epochs variable
    int epochs = 1;

    // Cheking if the epoch is a valid number
    if(epochs <= 0)
    {
        cout << "\nPlease enter a valid epoch number!\n";
        exit(1);
    }

    // Creating the learning rate variable
    double learning_rate = 0.0001;

    // Cheking if the learning rate is a valid number
    if(learning_rate <= 0)
    {
        cout << "\nPlease enter a valid learning rate!\n";
        exit(1);
    }

    // Calling the fitting function
    vector<double> weights = fitting_function(a_train, b_train, c_train, d_train, y_train, epochs, learning_rate);

    // Printing the weights
    //vec_print(weights);

    // Printing the y_train values
    //vec_print(y_train);
    
    // Predicting the classes based on the test dataset
    test_predict(a_test, b_test, c_test, d_test, y_test, weights, epochs, learning_rate);
}