#include <iostream>
#include <memory> // for std::unique_ptr

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

std::ostream& operator<<(std::ostream& out, const Resource&)
{
  out << "I am a resource";
  return out;
}

// Return std::unique_ptr by value. Never return by ptr.
std::unique_ptr<Resource> createResource()
{
  // C++14 or earlier, move semantics will be employed.
  // C++17 or newer, the return will be elided.
  return std::make_unique<Resource>();
}

// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole
// std::unique_ptr<Resource>
void useResource(const Resource* res)
{
  if (res)
    std::cout << *res << '\n';
  else
    std::cout << "No resource\n";
}

// This function takes ownership of the Resource, which isn't what we want
void takeOwnership(std::unique_ptr<Resource> res)
{
  if (res) std::cout << *res << '\n';
} // the Resource is destroyed here

int main()
{
  /*
  std::unique_ptr knows how to destroy arrays too.

  Favor std::array, std::vector, or std::string over a smart pointer managing a fixed array, dynamic array, or C-style
  string.

  std::make_unique is non-copyable.

  We can get in trouble with std::unique_ptr if we create it dynamically and don't destroy or create an object holding
  std::unique_ptr dynamically and don't destroy it -- underlying object is not destroyed in both cases.
  */

  // use std::make_unique, it's shorter and resolves exception safety issue (prior C++17, in C++17 it's fixed)
  auto ptr{ std::make_unique<Resource>() };

  auto ptr2{ createResource() };

  // although you can pass a std::unique_ptr by const reference, it's better to pass the object itself (by ref or ptr) -
  // function won't know how you manage the resource on the caller side
  useResource(ptr.get()); // note: get() used here to get a pointer to the Resource

  // it's rarely desired to transfer ownership to a function
  // takeOwnership(std::move(ptr)); // ok: use move semantics

  std::cout << "Ending program\n";

  return 0;
} // The Resource is destroyed here