#include <algorithm>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>


class Point
{
private:
  int m_x{};
  int m_y{};

public:
  Point(int x, int y) : m_x{ x }, m_y{ y } {}

  friend std::ostream& operator<<(std::ostream& out, const Point& p)
  {
    return out << "Point(" << p.m_x << ", " << p.m_y << ')';
  }
};

class Shape
{
public:
  virtual std::ostream& print(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Shape& s) { return s.print(os); }
  virtual ~Shape() = default;
};

class Triangle : public Shape
{
public:
  Triangle(Point p1, Point p2, Point p3) : m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 } {}

  std::ostream& print(std::ostream& os) const override
  {
    return os << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')';
  }

private:
  Point m_p1;
  Point m_p2;
  Point m_p3;
};

class Circle : public Shape
{
public:
  Circle(Point p, int r) : m_p{ p }, m_r{ r } {}

  std::ostream& print(std::ostream& os) const override { return os << "Triangle(" << m_p << ", radius " << m_r << ')'; }

  int getRadius() const { return m_r; }

private:
  Point m_p;
  int m_r;
};


int getLargestRadius(const std::vector<std::unique_ptr<Shape>>& v)
{
  int mr{ -1 };
  for (const auto& s : v) {
    if (auto* c{ dynamic_cast<const Circle*>(s.get()) }) { mr = std::max(c->getRadius(), mr); }
  }
  return mr;
}


int main()
{
  std::vector<std::unique_ptr<Shape>> v;
  v.reserve(3);
  v.emplace_back(new Circle(Point{ 1, 2 }, 7));
  v.emplace_back(new Triangle(Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }));
  v.emplace_back(new Circle(Point{ 7, 8 }, 3));

  // print each shape in vector v on its own line here
  for (const auto& s : v) { std::cout << *s << '\n'; }

  std::cout << "The largest radius is: " << getLargestRadius(v) << '\n'; // write this function

  return 0;
}