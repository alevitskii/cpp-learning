#include <exception> // for std::exception
#include <iostream>
#include <stdexcept> // for std::runtime_error
#include <string>


// We can derive from `std::exception` (base) or other exceptions in std library
class ArrayException : public std::exception
{
private:
  std::string m_error{}; // handle our own string

public:
  ArrayException(std::string_view error) : m_error{ error } {}

  // std::exception::what() returns a const char*, so we must as well
  const char* what() const noexcept override { return m_error.c_str(); }
};

class ArrayException2 : public std::runtime_error
{
public:
  // std::runtime_error takes a const char* null-terminated string.
  // std::string_view may not be null-terminated, so it's not a good choice here.
  // Our ArrayException will take a const std::string& instead,
  // which is guaranteed to be null-terminated, and can be converted to a const char*.
  ArrayException2(const std::string& error) : std::runtime_error{ error } // std::runtime_error will handle the string
  {}

  // no need to override what() since we can just use std::runtime_error::what()
};

class IntArray
{
private:
  int m_data[3]{}; // assume array is length 3 for simplicity

public:
  IntArray() {}

  int getLength() const { return 3; }

  int& operator[](const int index)
  {
    if (index < 0 || index >= getLength()) throw ArrayException("Invalid index");

    return m_data[index];
  }
};

int main()
{
  IntArray array;

  try {
    int value{ array[5] };
  } catch (const ArrayException& exception) // derived catch blocks go first
  {
    std::cerr << "An array exception occurred (" << exception.what() << ")\n";
  } catch (const std::exception& exception) {
    std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
  }
}