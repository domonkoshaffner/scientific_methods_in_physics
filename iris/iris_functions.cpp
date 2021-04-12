#include "iris_functions.h"

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

// Function for printing any vector
// Input is the vector to be printed

template <class T>
void vec_print(vector<T> data)
{
    for(int i = 0; i < data.size(); i++)
    {cout << data[i] << ", ";}
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
    vector<int> indices_test;
    int rand_num;
    bool exists;

    // Generate ten pseudo-random numbers
    // Using 20% as testing data
    while (indices_test.size() < 10)
    {
        rand_num = dis1(gen);
        exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false)
        {indices_test.push_back(rand_num);}
    }

    while (indices_test.size() < 20)
    {
        rand_num = dis2(gen);
        exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false)
        {indices_test.push_back(rand_num);}
    }

    while (indices_test.size() < 30)
    {
        rand_num = dis3(gen);
        exists = find(begin(indices_test), end(indices_test), rand_num) != end(indices_test);

        if(exists == false)
        {indices_test.push_back(rand_num);}
    }

    // Returning with the test vector indices
    return(indices_test);
}

//################################################

// Function for creating the training data set
// The input is a vector of the indices of the testing data set
// The otput is the training data set's indices

vector<int> train_generator(vector<int> indices_test)
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
    {split_data.push_back(data[indices[i]]);}

    // Returning with the split vector
    return(split_data);
}