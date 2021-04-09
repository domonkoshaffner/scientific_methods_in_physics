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
	{data.push_back(x);}

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
    uniform_int_distribution<> dis2(50, 99);
    uniform_int_distribution<> dis3(100, 149);

    // Creating array for the indices
    vector<int> indices_test;
    int rand_num;
    bool exists;

    // Generate ten pseudo-random numbers
    // I'm using 80% training and 20% testing data
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

//################################################

// Generating random weight matrix

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

    // Filling up the matrix
    for(int i = 0; i < it; i++)
    {
        double rand_num = weight_gen(gen)/100000.0;
        weights.push_back(rand_num);
    }

    return weights;
}


//################################################

// Input 1-4: vectors of features 
// Input 5: y vector
// Input 6: weights vector
// Output: x*weight + bias

vector<double> model(vector <double> a_train, vector <double> b_train, vector <double> c_train, vector <double> d_train, vector <int> y_train, vector<double> weights)
{
    // Creating vectors to store the elements
    vector<double> result;

    // Creating the x*weights + bias vectors
    for(int i = 0; i < a_train.size(); i++)
    {
        result.push_back(weights[0] + a_train[i]*weights[3] + b_train[i]*weights[6] + c_train[i]*weights[9] + d_train[i]*weights[12]);
        result.push_back(weights[1] + a_train[i]*weights[4] + b_train[i]*weights[7] + c_train[i]*weights[10] + d_train[i]*weights[13]);
        result.push_back(weights[2] + a_train[i]*weights[5] + b_train[i]*weights[8] + c_train[i]*weights[11] + d_train[i]*weights[14]);
    }

    // Returning with the results
    return result;
}
//

//################################################

// Multiclass perceptron function


vector<double> multiclass_perceptron(vector <double> a_train, vector <double> b_train, vector <double> c_train, vector <double> d_train, vector <int> y_train, vector<double> weights, double alpha)
{
    // Getting the results of the dot product
    vector<double> all_evals = model(a_train, b_train, c_train, d_train, y_train, weights);
 

    // Iterating through the data
    // Updating the weights
    for(int i = 0; i < a_train.size(); i++)
    {
        //getting the current max element in the list
        vector<double> temp = {all_evals[i*3], all_evals[i*3+1], all_evals[i*3+2]};
        auto it = max_element(begin(temp), end(temp));
        int index = it - temp.begin();

        //updating the weights for the predicted indices
        weights[3 + index] -= alpha*a_train[i];
        weights[6 + index] -= alpha*b_train[i];
        weights[9 + index] -= alpha*c_train[i];
        weights[12 + index] -= alpha*d_train[i];

        //updating the weights for the actual indices
        weights[3 + y_train[i]] += alpha*a_train[i];
        weights[6 + y_train[i]] += alpha*b_train[i];
        weights[9 + y_train[i]] += alpha*c_train[i];
        weights[12 + y_train[i]] += alpha*d_train[i];
    }

    // Returning the weights
    return weights;
}


//################################################

// Final predection
vector<int> final_pred(vector <double> a_train, vector <double> b_train, vector <double> c_train, vector <double> d_train, vector <int> y_train, vector<double> weights)
{

    // Getting the results of the dot product
    vector<double> all_evals = model(a_train, b_train, c_train, d_train, y_train, weights);

    // Setting up index vector
    vector<int> indices;

    // Iterating through the data
    // Updating the weights
    for(int i = 0; i < a_train.size(); i++)
    {
        //getting the current max element in the list
        vector<double> temp = {all_evals[i*3], all_evals[i*3+1], all_evals[i*3+2]};
        auto it = max_element(begin(temp), end(temp));
        indices.push_back(it - temp.begin());
    }

    // Returning with the indices
    return indices;
}

//################################################

int main()
{  
    // Reading in the different properties of the flowers
    vector<double> a = reading_iris_values("C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/data/a_all.data");
    vector<double> b = reading_iris_values("C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/data/b_all.data");
    vector<double> c = reading_iris_values("C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/data/c_all.data");
    vector<double> d = reading_iris_values("C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/data/d_all.data");

    // Reading in the classification values of the flowers
    vector<int> y = reading_iris_y("C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/data/iris.data");

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
    int epochs = 500;
    // Creating the learning rate variable
    double learning_rate = 0.001;

    // Cheking if the epoch is a valid number
    if(epochs <= 0)
    {
        cout << "\nPlease enter a valid epoch number!\n";
        exit(1);
    }
    // Cheking if the learning rate is a valid number
    if(learning_rate <= 0)
    {
        cout << "\nPlease enter a valid learning rate!\n";
        exit(1);
    }


    // Calling the model
    vector<double> weights = weight_generation();

    // Iterating through the data
    for(int i = 0; i < epochs; i++)
    {weights = multiclass_perceptron(a_train, b_train, c_train, d_train, y_train, weights, learning_rate);}


    // Final prediction
    vector<int> final_prediction = final_pred(a_test, b_test, c_test, d_test, y_test, weights);

    // Printing the results
    cout << "The real labels: ";
    vec_print(y_test);
    cout << "\nThe predicted label: ";
    vec_print(final_prediction);
    cout << "\n";

    // Writing the vector into a txt file 
    std::ofstream outFile("C:/All Files/MSc-IV/Adattud/iris/accuracy_vector.txt");
    for (const auto &e : final_prediction) outFile << e << "\n";
    

}
