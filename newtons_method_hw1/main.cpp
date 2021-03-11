#include <iostream>
#include <fstream>

//Creating the function

double func(double x)
{
    return x*x - 612.0;
}

//Creating the derivative function

double func_deriv(double x)
{
    return 2.0*x;
}

// Creating the template function for the Newton's method

template<typename t_func, typename t_func_deriv, typename t_x0_first, typename t_eps>
t_x0_first Newton_method(t_func func, t_func_deriv func_deriv, t_x0_first x0, t_eps epsilon)
{

    //Calculating the next value
    t_x0_first x1 = x0 - (func(x0) / func_deriv(x0));

    //Iterating untill the precision is good enough
    while(abs(x1-x0) > epsilon)
    {
        x0 = x1;
        x1 = x0 - (func(x0) / func_deriv(x0));
    }
    return x1;

}

int main()
{
    //Value of the first x0
    double x0 = 10.0;
    //Required result
    double req_res = 24.738633753705963298928;
    //Difference
    double epsilon = 1e-3;

    //Calling the Newton method
    double newton_result = Newton_method(func, func_deriv, x0, epsilon);

    //Calculating the deviation of the req. res. and the actual res.
    double dev_res = abs(newton_result - req_res);

    //Checking if the results are sufficient
    if(dev_res < 1e-6){std::cout << "The result is sufficient.";}
    else{std::cout << "The result is not sufficient.";}
}

