#include <iostream>
#include <fstream>
#include <vector>

//#######################################
// Function for creating the f(x) function

double f(double F, double q, double a, double h, double x)
{
    return (F/q) * (cosh(q*x/F) - cosh(q*a/(F*2))) + h;
}


//#######################################
// Function for creating the derivative f(x) function

double f_deriv(double F, double q, double a, double h, double x, double dx)
{
    return (128 * (f(F, q, a, h, x + dx) - f(F, q, a, h, x - dx)) - 
             24 * (f(F, q, a, h, x + 2*dx) - f(F, q, a, h, x - 2*dx)) + 
                  (f(F, q, a, h, x + 4*dx) - f(F, q, a, h, x - 4*dx)))/15;
}


//#######################################
// Calculating the central values for the central numerical integration

double centr_int_mid_points_calc(double delta_x, int iteration, double F, double q, double a, double h)
{
    // Declaring variable for the mid points
    double mid_points;

    // Declaring variable for the mid-point integration
    double M = 0.0;

    // Iterating through the data and claculating the mid-point numerical integration
    for(int i = 0; i < iteration-1; i ++)
    {
        //calculating the mid-points
        mid_points = delta_x * i + delta_x/2;

        //calculating the integral value
        M += sqrt(1 + (f_deriv(F, q, a, h, mid_points, delta_x)) * (f_deriv(F, q, a, h, mid_points, delta_x))) * delta_x;

    }

    // Returning the value of the integration
    return M;
}


//#######################################
// Calculating the trapezoidal rule integration

double trapezoidal_int(double delta_x, int iteration, double F, double q, double a, double h)
{
    // Declaring a variable for the trapezoidal rule int.
    double T = 0.0;

    // Iterating through the number of points and summing up the int. value
    for(int i = 0; i < iteration; i ++)
    {
        T += sqrt(1 + (f_deriv(F, q, a, h, i*delta_x, delta_x)) * (f_deriv(F, q, a, h, i*delta_x, delta_x))) * delta_x;
    }

    // The first and last values are only considered 0.5 times
    T -= 0.5 * sqrt(1 + (f_deriv(F, q, a, h, 0, delta_x)) * (f_deriv(F, q, a, h, 0, delta_x))) * delta_x;
    T -= 0.5 * sqrt(1 + (f_deriv(F, q, a, h, iteration*delta_x, delta_x)) * (f_deriv(F, q, a, h, iteration*delta_x, delta_x))) * delta_x;

    // Returning the value of the integration
    return T;
}


//#######################################
// Function for calculating the Simpson-integral

double simpson_int(double M, double T)
{
    // Calculating the Simpson integral
    return (2*M + T) / 3;
}


//#######################################
// Main function

int main()
{
    // Declaring the neccessary variables
    double F = 900.0;
    double q = 1.8;
    double a = 200.0;
    double h = 35.0;

    // Setting the deltax varaible for the numerical integration
    int n = 10000;

    // Calculating deltax
    double delta_x = a / n;


    // Calling the centr_mid_points_calc function for the central numerical int. and printing the result
    double mid_points = centr_int_mid_points_calc(delta_x, n, F, q, a, h);
    std::cout << "\nResult of the mid-point numerical integration: " << mid_points << ".";

    // Calling the trapezoidal_int function for the numerical int. and printing the result
    double trapez_int_result = trapezoidal_int(delta_x, n, F, q, a, h);
    std::cout << "\nResult of the trapezoidal numerical integration: " << trapez_int_result << ".";

    // Calling the simpson_int function for the numerical int. and printing the result
    double simpson_result = simpson_int(mid_points, trapez_int_result);
    std::cout << "\nResult of the Simpson numerical integration: " << simpson_result << ".\n";


    // Writing the results into a .txt file
    //std::ofstream outFile(output_file + "accuracy_vector.txt");
    //for (const auto &e : final_prediction) outFile << e << "\n";
}

