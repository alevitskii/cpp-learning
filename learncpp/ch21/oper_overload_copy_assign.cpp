#include <algorithm> // for std::max and std::copy_n
#include <iostream>

/*
Copy assignment vs Copy constructor:
- if a new object has to be created before the copying can occur, the copy constructor is used (note: this includes
passing or returning objects by value);
- if a new object does not have to be created before the copying can occur, the assignment operator is used.

The rule of four and a half:
If a class requires a user-defined destructor, copy constructor, copy assignment operator, move constructor or swap
function (to implement "copy and swap" idiom), then it probably requires all of them. If we're user-defining any of
these functions, it's probably because we're dealing with dynamic memory allocation.

The rule of three/five/zero: https://en.cppreference.com/w/cpp/language/rule_of_three
*/

class MyString
{
private:
  char* m_data{};
  int m_length{};

public:
  MyString(const char* data = nullptr, int length = 0) : m_length{ std::max(length, 0) }
  {
    if (length) {
      m_data = new char[static_cast<std::size_t>(length)];
      std::copy_n(data, length, m_data); // copy length elements of data into m_data
    }
  }
  ~MyString() { delete[] m_data; }

  // We could also define copy constructor to properly init `m_data`
  MyString(const MyString&) = delete;

  /*
  Compiler provides an implicit public copy assignment operator for your class if you do not provide a user-defined one.
  It does memberwise assignment.
  You can `delete` assignment operator or make it private to prevent assignments.
  If your class has const members, the compiler will instead define the implicit operator= as deleted. You will need to
  overload manually.
  */

  // Overloaded assignment. Note return ref so it can be chained: s1 = s2 = s3...
  MyString& operator=(const MyString& str);

  friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
  out << s.m_data;
  return out;
}

MyString& MyString::operator=(const MyString& str)
{
  /*
  It's sometimes not necessary to check for self-assignment. But sometimes it's crucial like below. If MyString is
  self-assigned, m_data of `str` is deleted before doing copy.
  NOTE: a better way to handle self-assignment issues is via what's called the "copy and swap" idiom (as a way to
  implement the rule of 4 and a half, https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom).
  NOTE: current implementation doesn't provide strong exception guarantee. `new` may fail but m_data will already be
  destroyed. We can rearrange operations: allocate memory, copy m_data to it, and then `delete[]` m_data and reassign
  new address to it.
  */

  // self-assignment check
  if (this == &str) return *this;

  // if data exists in the current string, delete it
  if (m_data) delete[] m_data;

  m_length = str.m_length;
  m_data = nullptr; // doing this because `new` on the next line may throw -> MyString destructor might be called -> we
                    // may try to deallocate m_data twice)

  // allocate a new array of the appropriate length
  if (m_length) m_data = new char[static_cast<std::size_t>(str.m_length)];

  std::copy_n(str.m_data, m_length, m_data); // copies m_length elements of str.m_data into m_data

  // return the existing object so we can chain this operator
  return *this;
}

int main()
{
  MyString alex("Alex", 5); // Meet Alex
  MyString employee;
  employee = alex; // Alex is our newest employee
  std::cout << employee; // Say your name, employee

  return 0;
}