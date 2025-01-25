#include <iostream>

/*
The move constructor and move assignment are called when those functions have been defined, and the argument for
construction or assignment is an rvalue. Most typically, this rvalue will be a literal or temporary value. The C++
specification has a special rule that says automatic objects returned from a function by value can be moved even if they
are l-values.
The copy constructor and copy assignment are used otherwise (when the argument is an lvalue, or when the
argument is an rvalue and the move constructor or move assignment functions aren't defined).

The compiler will create an implicit move constructor and move assignment operator if all of the following are true:
- there are no user-declared copy constructors or copy assignment operators;
- there are no user-declared move constructors or move assignment operators;
- there is no user-declared destructor.
These functions do a memberwise move, which behaves as follows:
- if member has a move constructor or move assignment (as appropriate), it will be invoked;
- otherwise, the member will be copied.
Notably, this means that pointers will be copied, not moved!

You can delete the move constructor and move assignment using the `= delete` syntax.
The rule of five says that if the copy constructor, copy assignment, move constructor, move assignment, or destructor
are defined or deleted, then each of those functions should be defined or deleted.

If you make a class copyable but not movable it'll make the class not returnable by value in cases where mandatory copy
elision does not apply (deleted move constructor is still a declared function, and thus is eligible for overload
resolution).
*/

template<typename T> class Auto_ptr4
{
  T* m_ptr{};

public:
  Auto_ptr4(T* ptr = nullptr) : m_ptr{ ptr } {}

  ~Auto_ptr4() { delete m_ptr; }

  // Copy constructor
  // Do deep copy of a.m_ptr to m_ptr
  Auto_ptr4(const Auto_ptr4& a)
  {
    m_ptr = new T;
    *m_ptr = *a.m_ptr;
  }

  // Move constructor
  // Transfer ownership of a.m_ptr to m_ptr
  Auto_ptr4(Auto_ptr4&& a) noexcept : m_ptr(a.m_ptr) // move ctor and move assign should be marked noexcept
  {
    a.m_ptr = nullptr; // Move functions should always leave both objects in a valid state
  }

  // Copy assignment
  // Do deep copy of a.m_ptr to m_ptr
  Auto_ptr4& operator=(const Auto_ptr4& a)
  {
    // Self-assignment detection
    if (&a == this) return *this;

    // Release any resource we're holding
    delete m_ptr;

    // Copy the resource
    m_ptr = new T;
    *m_ptr = *a.m_ptr;

    return *this;
  }

  // Move assignment
  // Transfer ownership of a.m_ptr to m_ptr
  Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
  {
    // Self-assignment detection
    if (&a == this) return *this;

    // Release any resource we're holding
    delete m_ptr;

    // Transfer ownership of a.m_ptr to m_ptr
    m_ptr = a.m_ptr;
    a.m_ptr = nullptr; // Move functions should always leave both objects in a valid state

    return *this;
  }

  T& operator*() const { return *m_ptr; }
  T* operator->() const { return m_ptr; }
  bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr4<Resource> generateResource()
{
  Auto_ptr4<Resource> res{ new Resource };
  return res; // this return value will invoke the move constructor
}

int main()
{
  /*
  1. Inside generateResource(), local variable res is created and initialized with a dynamically allocated Resource,
  which causes the first "Resource acquired".

  2. Res is returned back to main() by value. Res is move constructed into a temporary object, transferring the
  dynamically created object stored in res to the temporary object. Without move, we'd copy construct the temp object -
  "Resource acquired".

  3. Res goes out of scope. Because res no longer manages a pointer (it was moved to the temporary), nothing interesting
  happens here. Without move res would get destroyed - "Resource destroyed".

  4. The temporary object is move assigned to mainres. This transfers the dynamically created object stored in the
  temporary to mainres. Without move mainres would be copy assigned - "Resource acquired".

  5. The assignment expression ends, and the temporary object goes out of expression scope and is destroyed. However,
  because the temporary no longer manages a pointer (it was moved to mainres), nothing interesting happens here either.
  Without move temp object would get destroyed - "Resource destroyed".

  6. At the end of main(), mainres goes out of scope, and our final "Resource destroyed" is displayed.

  Note: Without move you may only get 4 outputs (not 6) if your compiler elides the return value from function
  generateResource().
  */
  Auto_ptr4<Resource> mainres;
  mainres = generateResource(); // this assignment will invoke the move assignment

  return 0;
}