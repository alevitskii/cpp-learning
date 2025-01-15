#include <iostream>
#include <string>
#include <string_view>

class Ball
{
public:
  Ball(double r) : Ball{ "black", r } {}; // print() is not called here, it'll be called in the deleg constructor
  Ball(std::string_view c = "black", double r = 10.0) : m_color{ c }, m_radius{ r } { print(); };
  void print() const { std::cout << "Ball(" << m_color << ", " << m_radius << ")\n"; }

private:
  std::string m_color{ "black" };
  double m_radius{ 10.0 };
};

int main()
{
  Ball def{};
  Ball blue{ "blue" };
  Ball twenty{ 20.0 };
  Ball blueTwenty{ "blue", 20.0 };

  return 0;
}