#include <iostream>
#include <string>
#include <string_view>

std::string getName()
{
  std::cout << "Enter the name of person #1: ";
  std::string name{};
  std::getline(std::cin >> std::ws, name);
  return name;
}

int getAge(std::string_view name)
{
  std::cout << "Enter the age of " << name << ": ";
  int age{};
  std::cin >> age;
  return age;
}

void printOlder(std::string_view olderName, int olderAge, std::string_view youngerName, int youngerAge)
{
  std::cout << olderName << " (age " << olderAge << ") is older than " << youngerName << " (age " << youngerAge
            << ")\n";
}

int main()
{
  std::string name1{ getName() };
  int age1{ getAge(name1) };
  std::string name2{ getName() };
  int age2{ getAge(name2) };
  if (age1 > age2)
    printOlder(name1, age1, name2, age2);
  else if (age1 < age2)
    printOlder(name2, age2, name1, age1);
  else
    std::cout << "Same age\n";

  return 0;
}