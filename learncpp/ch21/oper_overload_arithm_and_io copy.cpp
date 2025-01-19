/*
When evaluating an expression containing an operator, the compiler uses the following rules:
- if all of the operands are fundamental data types, the compiler will call a built-in routine if one exists. If one
does not exist, the compiler will produce a compiler error;
- if any of the operands are program-defined types (e.g. one of your classes, or an enum type), the compiler will use
the function overload resolution algorithm to see if it can find an overloaded operator that is an unambiguous best
match.

Can't create new operators.
Can't be overloaded: conditional (?:), sizeof, scope (::), member selector (.), pointer member selector (.*), typeid,
and the casting operators.
It is not possible to change the number of operands an operator supports.
All operators keep their default precedence and associativity (regardless of what they’re used for) and this can not be
changed.

Best practices:
1. An overloaded operator should operate on at least one program-defined type (either as a parameter of the function, or
the implicit object);
2. When overloading operators, it’s best to keep the function of the operators as close to the original intent of the
operators as possible;
3. If the meaning of an overloaded operator is not clear and intuitive, use a named function instead;
4. Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value;
5. Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally
return the leftmost operand by reference.

Prefer overloading operators as normal functions instead of friends if it's possible to do so without adding additional
functions.

- If you're overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member
function (language requirement).
- If you're overloading a unary operator, do so as a member function.
- If you're overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal
function (preferred) or friend function.
- If you're overloading a binary operator that modifies its left operand, but you can't add members to the class
definition of the left operand (e.g. operator<<, which has a left operand of type ostream), do so as a normal function
(preferred) or friend function.
- If you're overloading a binary operator that modifies its left operand (e.g. operator+=), and you can modify the
definition of the left operand, do so as a member function.
*/

#include <cassert>
#include <iostream>


class MinMax
{
private:
  int m_min{}; // The min value seen so far
  int m_max{}; // The max value seen so far

public:
  MinMax(int min, int max) : m_min{ min }, m_max{ max } {}

  int getMin() const { return m_min; }
  int getMax() const { return m_max; }

  // can be a member function, left operand is `*this`
  MinMax operator+(const MinMax& m)
  {
    int min{ m_min < m.m_min ? m_min : m.m_min };
    int max{ m_max > m.m_max ? m_max : m.m_max };
    return MinMax{ min, max };
  }
  // Can be a friend function. Friend function is not a member function (even if defined inside the class definition)
  friend MinMax operator+(const MinMax& m, int value);
};

MinMax operator+(const MinMax& m, int value)
{
  int min{ m.m_min < value ? m.m_min : value };
  int max{ m.m_max > value ? m.m_max : value };
  return MinMax{ min, max };
}

// can be a normal function
MinMax operator+(int value, const MinMax& m)
{
  // calls operator+(MinMax, int)
  return m + value;
}

// // // // // // // // // // // // // // // // // // // // // // // // //

class Point
{
private:
  double m_x{};
  double m_y{};
  double m_z{};

public:
  Point(double x = 0.0, double y = 0.0, double z = 0.0) : m_x{ x }, m_y{ y }, m_z{ z } {}

  friend std::ostream& operator<<(std::ostream& out, const Point& point);
  friend std::istream& operator>>(std::istream& in, Point& point);

  Point operator-() const;
  Point operator+() const;
  Point operator!() const;

  // We need to define only 2: == and <, the rest can be deduced
  friend bool operator==(const Point& p1, const Point& p2)
  {
    return p1.m_x == p2.m_x && p1.m_y == p2.m_y && p1.m_z == p2.m_z;
  }
  friend bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }
  friend bool operator<(const Point& p1, const Point& p2)
  {
    return p1.m_x < p2.m_x && p1.m_y < p2.m_y && p1.m_z < p2.m_z;
  }
  friend bool operator>(const Point& p1, const Point& p2) { return p2 < p1; }
  friend bool operator<=(const Point& p1, const Point& p2) { return !(p1 > p2); }
  friend bool operator>=(const Point& p1, const Point& p2) { return !(p1 < p2); }

  Point& operator++() // return by refernce so it can be chained
  {
    ++m_x;
    ++m_y;
    ++m_z;
    return *this;
  }
  // Compiler searches for int parameter to figure out that it's a postfix operator.
  // Return by value because ref to temp object is UB after the scope.
  Point operator++(int)
  {
    Point temp{ *this };
    ++(*this); // let the prefix ++ do the work
    return temp;
  }
  Point& operator--()
  {
    --m_x;
    --m_y;
    --m_z;
    return *this;
  }
  Point operator--(int)
  {
    Point temp{ *this };
    --(*this);
    return temp;
  }
};

Point Point::operator-() const { return { -m_x, -m_y, -m_z }; }
// Note that we're returning by value because users of this function will probably expect the returned object to be
// modifiable.
Point Point::operator+() const { return *this; }
Point Point::operator!() const
{
  return m_x == 0.0 && m_y == 0.0 && m_z == 0.0; // true if set to origin, false otherwise
};


std::ostream& operator<<(std::ostream& out, const Point& point)
{
  // Since operator<< is a friend of the Point class, we can access Point's members directly.
  out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

  return out;
}

// note that parameter point must be non-const so we can modify the object
// note that this implementation is a non-friend
std::istream& operator>>(std::istream& in, Point& point)
{
  // This version subject to partial extraction issues
  // in >> point.m_x >> point.m_y >> point.m_z;

  double x{}, y{}, z{};
  in >> x >> y >> z;
  if (x < 0.0 || y < 0.0 || z < 0.0) // if any extractable input is negative (just as an example)
    in.setstate(std::ios_base::failbit); // set failure mode manually
  // we mimic the behavior for fundamental types -- if extraction failed, set to 0
  point = in ? Point{ x, y, z } : Point{};

  return in;
}


int main()
{
  MinMax m1{ 10, 15 };
  MinMax m2{ 8, 11 };
  MinMax m3{ 3, 12 };

  MinMax mFinal{ m1 + m2 + 5 + 8 + m3 + 16 };

  std::cout << "Result: (" << mFinal.getMin() << ", " << mFinal.getMax() << ")\n";

  // // // // // // // // // // // // // // // // // // // // // // // // //

  std::cout << "Enter a point: ";

  Point point{};
  std::cin >> point;

  std::cout << "You entered: " << point << '\n';

  return 0;
}