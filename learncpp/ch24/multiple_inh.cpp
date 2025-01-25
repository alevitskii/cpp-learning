#include <string>

/*
Avoid multiple inheritance unless alternatives lead to more complexity.
*/

struct Point2D
{
  int x{};
  int y{};
};

class Box // mixin Box class
{
public:
  void setTopLeft(Point2D point) { m_topLeft = point; }
  void setBottomRight(Point2D point) { m_bottomRight = point; }

private:
  Point2D m_topLeft{};
  Point2D m_bottomRight{};
};

class Label // mixin Label class
{
public:
  void setText(const std::string_view str) { m_text = str; }
  void setFontSize(int fontSize) { m_fontSize = fontSize; }

private:
  std::string m_text{};
  int m_fontSize{};
};

class Tooltip // mixin Tooltip class
{
public:
  void setText(const std::string_view str) { m_text = str; }

private:
  std::string m_text{};
};

class Button
  : public Box
  , public Label
  , public Tooltip
{
}; // Button using three mixins

// The Curiously Recurring Template Pattern (CRTP), https://en.cppreference.com/w/cpp/language/crtp
template<class T> class Mixin
{
  // Mixin<T> can use template type parameter T to access members of Derived
  // via (static_cast<T*>(this))
};

class Derived : public Mixin<Derived>
{
};

int main()
{
  Button button{};
  button.Box::setTopLeft({ 1, 1 });
  button.Box::setBottomRight({ 10, 10 });
  button.Label::setText("Submit");
  button.Label::setFontSize(6);
  button.Tooltip::setText("Submit the form to the server");
}