//#include <chrono>
//#include <numeric>
#include <iterator>

#include <vector>       // std::vector
//#include <exception>    // std::runtime_error, std::exception
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
//#include <random>       // std::default_random_engine, std::uniform_real_distribution
//#include <algorithm>    // std::transform
//#include <cstdlib>      // EXIT_FAILURE
//#include <iomanip>

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
        classification += X[i]*weights[i+1]
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


    // Creating the X values vector
    vector<double> x_train(4);

    // Filling up the vector with the appropriate values
    // Calling the functions for the prediction
    for(int i = 0; i < a_train.size(); i++)
    {
        x_train[0] = a_train[i];
        x_train[1] = b_train[i];
        x_train[2] = c_train[i];
        x_train[3] = d_train[i];
    }

}