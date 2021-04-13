// Including the neccessary header file

#include "iris_functions.h"

// Main function
// First the users has to give the source of the data set into the source_of_data string
// Reading in the files for the iris data set: features - a, b, c, d; labels - y
// Splitting the data into train and test data sets (80%-20%)
// Setting the epoch and learning rate
// Generating random weights
// Calling the multiclass perceptron model
// Writing the predictions into a .txt file


int main()
{  

    // Please enter the source of the data set
    string source_of_data = "C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/data/";

    // Please enter where you would like to save your file 
    string output_file = "C:/Users/haffn/Desktop/MSc-IV/Adattud/iris/";
    
    // Reading in the different properties of the flowers
    vector<double> a = reading_iris_values(source_of_data + "a_all.data");
    vector<double> b = reading_iris_values(source_of_data + "b_all.data");
    vector<double> c = reading_iris_values(source_of_data + "c_all.data");
    vector<double> d = reading_iris_values(source_of_data + "d_all.data");

    // Reading in the classification values of the flowers
    vector<int> y = reading_iris_y(source_of_data + "iris.data");

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
    const int epochs = 500;
    // Creating the learning rate variable
    const double learning_rate = 0.001;

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


    // Starting clock 
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // Calling the model
    vector<double> weights = weight_generation();

    // Iterating through the data
    for(int i = 0; i < epochs; i++)
    {
        weights = multiclass_perceptron(a_train, b_train, c_train, d_train, y_train, weights, learning_rate);
        cout << "Current epoch: " << i+1 << " / " << epochs << "\n";
    }


    // Final prediction
    vector<int> final_prediction = final_pred(a_test, b_test, c_test, d_test, y_test, weights);

    // Printing the results
    cout << "\nThe original labels: ";
    vec_print(y_test);
    cout << "\nThe predicted labels: ";
    vec_print(final_prediction);
    cout << "\n";

    // Printing the accuracy
    acc_calc(final_prediction, y_test);
    

    // Writing the vector into a txt file 
    //std::ofstream outFile(output_file + "accuracy_vector.txt");
    //for (const auto &e : final_prediction) outFile << e << "\n";

    // Stopping the clock
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // Printing the elapsed time in microseconds
    cout << "Required time for the model: " << chrono::duration_cast<chrono::microseconds> (end-begin).count()/1000 << " ms" << "\n";
}
