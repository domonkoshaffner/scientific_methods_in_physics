#include <iostream>
#include <fstream>
#include <vector>

//#######################################
// Function for creating the y derivative function
// Input: y variable

double y_deriv(double y)
{
    return 1 + y * y;
}


//#######################################
// Function for the newton method
// Input: newton vector, which stores the rk results, time_step, number of steps and initial condition

void newton(std::vector<double> &newton_values, double delta_t, int N, double y0)
{
    newton_values[0] = y0;

    for(int i = 1; i < N; i++)
    {
        newton_values[i] = newton_values[i-1] + delta_t * y_deriv(newton_values[i-1]);
    }
}


//#######################################
// Function for the RK method
// Input: rk_values vector, which stores the rk results, time_step, number of steps and initial condition

void rk(std::vector<double> &rk_values, double delta_t, int N, double y0)
{
    // Initialising the rk_values with the initial condition
    rk_values[0] = y0;

    // Initialising the k variables
    double k1, k2, k3, k4;

    // Iterating through i = 1, ..., i = N
    for(int i = 1; i < N; i++)
    {
        // Calculating the k variables
        k1 = y_deriv(rk_values[i-1]);
        k2 = y_deriv(rk_values[i-1] + (delta_t * k1 * 0.5));
        k3 = y_deriv(rk_values[i-1] + (delta_t * k2 * 0.5));
        k4 = y_deriv(rk_values[i-1] + (delta_t * k3));

        // Filling up the rk_values vector with the results
        rk_values[i] = rk_values[i-1] + (delta_t * (k1 + 2*k2 + 2*k3 + k4) / 6);
    }
}


//#######################################
// Function for the analytical solution
// Input: analytical_values vector, which stores the analytical results, time_step, number of steps and initial condition
// The analytical solution of this first order linear equation: y(x) = tan(x)

void analytical(std::vector<double> &analytical_values, double delta_t, int N, double y0)
{
    // Initialising the rk_values with the initial condition
    analytical_values[0] = y0;

    // Iterating through i = 1, ..., i = N
    for(int i = 1; i < N; i++)
    {
        analytical_values[i] = tan(i*delta_t);
    }
}

//#######################################
// Main function

int main()
{
    // Initialising the number of steps, initial condition and step size
    int N = 10000;
    double y0 = 0.0;
    double delta_t = 0.0001;

    // Initialising the vector for the results
    std::vector<double> newton_values(N);
    std::vector<double> rk_values(N);
    std::vector<double> analytical_values(N);

    // Calling the different numerical differentiation functions
    newton(newton_values, delta_t, N, y0);
    rk(rk_values, delta_t, N, y0);
    analytical(analytical_values, delta_t, N, y0);

    // Writing the results into a .txt file
    std::ofstream results;
    results.open("../../../newton_RK_analytical_results_delta_t.txt");
    results << "Newton_method Runge_Kutta Analytical_solution\n";
    for(int i = 0; i < N; i++)
    {
        results << newton_values[i] << " " << rk_values[i] << " " << analytical_values[i] <<"\n";
    }
    results.close();
}

