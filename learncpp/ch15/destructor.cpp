#include <iostream>

class Simple
{
private:
  int m_id{};

public:
  Simple(int id) : m_id{ id } { std::cout << "Constructing Simple " << m_id << '\n'; }

  /*
  Destructor must be only one, doesn't have parameters, has no return type.
  If a non-aggregate class type object has no user-declared destructor, the compiler will generate an implicit
  destructor with an empty body (just a placeholder).
  If a class doesn't have to do any cleanup, it's ok to not define a destructor.
  Note that `std::exit()` (always) and unhandled exceptions (may) terminate the program without stack unwinding
  (destructors are not called).
  */
  ~Simple() { std::cout << "Destructing Simple " << m_id << '\n'; }

  int getID() const { return m_id; }
};

int main()
{
  // Allocate a Simple
  Simple simple1{ 1 };
  {
    Simple simple2{ 2 };
  } // simple2 dies here

  return 0;
} // simple1 dies here