#include <iostream>
#include <string>
#include <string_view>

/*
First, we need to add a member to Animal for each way we want to differentiate Cat and Dog. Over time, our Animal class
could become quite large memory-wise, and complicated!

Second, this solution only works if the base class member can be determined at initialization time. For example, if
speak() returned a randomized result for each Animal (e.g. calling Dog::speak() could return "woof", "arf", or "yip"),
this kind of solution starts to get awkward and fall apart.
*/

class Animal
{
protected:
  std::string m_name;
  std::string m_speak;

  // We're making this constructor protected because
  // we don't want people creating Animal objects directly,
  // but we still want derived classes to be able to use it.
  Animal(std::string_view name, std::string_view speak) : m_name{ name }, m_speak{ speak } {}

  // To prevent slicing (covered later)
  Animal(const Animal&) = delete;
  Animal& operator=(const Animal&) = delete;

public:
  std::string_view getName() const { return m_name; }
  std::string_view speak() const { return m_speak; }
};

class Cat : public Animal
{
public:
  Cat(std::string_view name) : Animal{ name, "Meow" } {}
};

class Dog : public Animal
{
public:
  Dog(std::string_view name) : Animal{ name, "Woof" } {}
};

int main()
{
  const Cat fred{ "Fred" };
  const Cat misty{ "Misty" };
  const Cat zeke{ "Zeke" };

  const Dog garbo{ "Garbo" };
  const Dog pooky{ "Pooky" };
  const Dog truffle{ "Truffle" };

  // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
  const auto animals{ std::to_array<const Animal*>({ &fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

  for (const auto animal : animals) { std::cout << animal->getName() << " says " << animal->speak() << '\n'; }
  return 0;
}