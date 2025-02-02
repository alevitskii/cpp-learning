#include <iostream>
#include <memory> // for std::shared_ptr

/*
Internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource (in a special "control
block"). As long as at least one std::shared_ptr is pointing to the resource, the resource will not be deallocated, even
if individual std::shared_ptr are destroyed. As soon as the last std::shared_ptr managing the resource goes out of scope
(or is reassigned to point at something else), the resource will be deallocated.

In C++17 and earlier, std::shared_ptr does not have proper support for managing arrays, and should not be used to manage
a C-style array. As of C++20, std::shared_ptr does have support for arrays.
*/

class Resource
{
public:
  Resource() { std::cout << "Resource acquired\n"; }
  ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
  // allocate a Resource object and have it owned by std::shared_ptr
  // always use std::make_shared, it's simpler, safer and faster (make_shared can combine memory allocation for the
  // resource and control block)
  auto ptr1{ std::make_shared<Resource>() };
  {
    /*
    Always make a copy of an existing std::shared_ptr if you need more than one std::shared_ptr pointing at the same
    resource. Two pointers created independently (not through a copy) won't know about each other and will both try to
    destroy the object.
    */
    auto ptr2{ ptr1 }; // create ptr2 using copy of ptr1

    std::cout << "Killing one shared pointer\n";
  } // ptr2 goes out of scope here, but nothing happens

  std::cout << "Killing another shared pointer\n";

  return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed