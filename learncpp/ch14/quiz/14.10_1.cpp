#include <iostream>
#include <string>
#include <string_view>

class Ball
{
public:
  Ball(std::string_view c, double r) : m_color{ c }, m_radius{ r } {};
  const std::string& getColor() const { return m_color; }
  double getRadius() const { return m_radius; }

private:
  std::string m_color{ "none" };
  double m_radius{ 0.0 };
};

void print(const Ball& b) { std::cout << "Ball(" << b.getColor() << ", " << b.getRadius() << ")\n"; }

int main()
{
  Ball blue{ "blue", 10.0 };
  print(blue);

  Ball red{ "red", 12.0 };
  print(red);

  return 0;
}