
#include <iostream>

// Creating the Vector2d class

template<typename T>
class Vector2d
{
  // Defining the variables 
  public:
    T x, y;

    // Defining the += operation with vectors
    Vector2d& operator+=( Vector2d<T> const& v )
    {
      x += v.x; y += v.y;
      return *this;
    }

    // Defining the -= operation with vectors
    Vector2d& operator-=( Vector2d<T> const& v )
    {
      x -= v.x; y -= v.y;
      return *this;
    }

    // Defining the *= operation with vectors
    Vector2d& operator*=( Vector2d<T> const& v )
    {
      x *= v.x; y *= v.y;
      return *this;
    }

    // Defining the /= operation with vectors
    Vector2d& operator/=( Vector2d<T> const& v )
    {
      x /= v.x; y /= v.y;
      return *this;
    }
};


// Defining some additional operations


// Addition of two vectors
template<typename T>
Vector2d<T> operator+( Vector2d<T> const& a, Vector2d<T> const& b )
{
  return Vector2d<T>{ a.x + b.x, a.y + b.y };
}


// Subtraction of two vectors
template<typename T>
Vector2d<T> operator-( Vector2d<T> const& a, Vector2d<T> const& b )
{
  return Vector2d<T>{ a.x - b.x, a.y - b.y };
}


// Vector constant multiplication from the right-hand side  
template<typename T>
Vector2d<T> operator*( Vector2d<T> const& a, T const& constant )
{
  return Vector2d<T>{ a.x * constant, a.y * constant };
}


// Vector constant multiplication from the left-hand side  
template<typename T>
Vector2d<T> operator*( T const& constant, Vector2d<T> const& a )
{
  return Vector2d<T>{ constant * a.x, constant * a.y };
}


// Vector constant division from the right-hand side  
template<typename T>
Vector2d<T> operator/( Vector2d<T> const& a, T const& constant )
{
  return Vector2d<T>{ a.x / constant, a.y / constant };
}


// Calculating the dot product of the vector
template<typename T>
double dot( Vector2d<T> const& a, Vector2d<T> const& b )
{
  return { a.x * b.x + a.y * b.y };
}


// Calculating the length of the vector
template<typename T>
double length( Vector2d<T> const& a )
{
  return { sqrt(a.x * a.x + a.y * a.y) };
}


// Calculating the square of length of the vector
template<typename T>
double sqlength( Vector2d<T> const& a )
{
  return { (a.x * a.x + a.y * a.y) };
}


// Calculating the normalised vector 
template<typename T>
Vector2d<T> normalize( Vector2d<T> const& a )
{
  return Vector2d<T>{ a.x / length(a), a.y / length(a) };
}


// Writing the vector to the output
template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2d<T> const& a )
{
    o << "(" << a.x << ", " << a.y << ")";
    return o;
}


// Getting the vector as an input
template<typename T>
std::istream& operator>>( std::istream& i, Vector2d<T>& a )
{
    i >> a.x;
    i >> a.y;
    return i;
}
