#include "vector2.h"

#include <iostream>
#include <fstream>


int main()
{

    // Defining the v1 and v2 vectors
    double v1_x = 6.0;
    double v1_y = 15.0;

    Vector2d<double> v1 = {v1_x, v1_y};
    Vector2d<double> v2 = {3.0, 3.0};

    // Defining the multiplication- and divison scalar

    double scalar_multipl = 5.0;
    double scalar_divison = 5.0;


    // Printing the two vectors
    std::cout << "The two vectors: v1 = (" << v1.x << ", " << v1.y << "); v2 = (" << v2.x << ", " << v2.y << ")\n\n";


    // Trying out the vector + operator
    auto w1 = v1 + v2;
    std::cout << "Vector addition: (" << v1.x << ", " << v1.y << ") + (" << v2.x << ", " << v2.y << ") = (";
    std::cout << w1.x << ", " << w1.y << ")\n";


    // Trying out the vector - operator
    auto w2 = v1 - v2;
    std::cout << "Vector subtraction: (" << v1.x << ", " << v1.y << ") - (" << v2.x << ", " << v2.y << ") = (";
    std::cout << w2.x << ", " << w2.y << ")\n";


    // Trying out the vector += operator
    std::cout << "\n";
    std::cout << "The result of (" << v1.x << ", " << v1.y << ") += (" << v2.x << ", " << v2.y << "): (";
    v1 += v2;
    std::cout << v1.x << ", " << v1.y << ")\n";

    // Re-initialising the v1 vecotr:
    v1 = {v1_x, v1_y};


    // Trying out the vector -= operator
    std::cout << "The result of (" << v1.x << ", " << v1.y << ") -= (" << v2.x << ", " << v2.y << "): (";
    v1 -= v2;
    std::cout << v1.x << ", " << v1.y << ")\n";

    // Re-initialising the v1 vecotr:
    v1 = {v1_x, v1_y};


    // Trying out the vector *= operator
    std::cout << "The result of (" << v1.x << ", " << v1.y << ") *= (" << v2.x << ", " << v2.y << "): (";
    v1 *= v2;
    std::cout << v1.x << ", " << v1.y << ")\n";

    // Re-initialising the v1 vecotr:
    v1 = {v1_x, v1_y};


    // Trying out the vector /= operator
    std::cout << "The result of (" << v1.x << ", " << v1.y << ") /= (" << v2.x << ", " << v2.y << "): (";
    v1 /= v2;
    std::cout << v1.x << ", " << v1.y << ")\n";

    // Re-initialising the v1 vecotr:
    v1 = {v1_x, v1_y};


    // Trying out the vector scalar multiplication operator from the right-hand side
    auto w3 = v1 * scalar_multipl;
    std::cout << "\n";
    std::cout << "Vector multiplication with scalar from right-hand side: (" << v1.x << ", " << v1.y << ") *  " << scalar_multipl << " = (";
    std::cout << w3.x << ", " << w3.y << ")\n";


    // Trying out the vector scalar multiplication operator from the left-hand side
    auto w4 = scalar_multipl * v1;
    std::cout << "Vector multiplication with scalar from left-hand side: " << scalar_multipl << " * (" << v1.x << ", " << v1.y << ") = (";
    std::cout << w4.x << ", " << w4.y << ")\n";


    // Trying out the vector scalar division operator from the right-hand side
    auto w5 = v1 / scalar_divison;
    std::cout << "Vector division with scalar from right-hand side: (" << v1.x << ", " << v1.y << ") /  " << scalar_divison << " = (";
    std::cout << w5.x << ", " << w5.y << ")\n";

    
    // Trying out the vector dot product
    auto w6 = dot(v1, v2);
    std::cout << "\n";
    std::cout << "Dot product of two vectors: (" << v1.x << ", " << v1.y << ") dot (" << v2.x << ", " << v2.y << ") = ";
    std::cout << w6 << "\n";


    // Trying out the length of a vector
    auto w7 = length(v1);
    std::cout << "Length of a vector: len(" << v1.x << ", " << v1.y << ") = ";
    std::cout << w7 << "\n";


    // Trying out the sqlength of a vector
    auto w8 = sqlength(v1);
    std::cout << "Square length of a vector: sqlen(" << v1.x << ", " << v1.y << ") = ";
    std::cout << w8 << "\n";

    
    // Trying out the normalisation of a vector
    auto w9 = normalize(v1);
    std::cout << "Normalising a vector: norm(" << v1.x << ", " << v1.y << ") = (";
    std::cout << w9.x << ", " << w9.y << ")\n";


    // Trying out the << operator
    Vector2d<double> v_input = {};
    std::cout << "\n";
    std::cout << "Please enter the two-dimensional vector's elements!\n";
    std::cin >> v_input;
    std::cout << "The input vector you entered is: (" << v_input.x << ", " << v_input.y << ")";

}

