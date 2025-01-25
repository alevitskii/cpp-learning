#include <iostream>

class PoweredDevice
{
public:
  PoweredDevice(int power) { std::cout << "PoweredDevice: " << power << '\n'; }
};

class Scanner : virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
{
public:
  Scanner(int scanner, int power)
    : PoweredDevice{ power } // this line is required to create Scanner objects, but ignored in this case
  {
    std::cout << "Scanner: " << scanner << '\n';
  }
};

class Printer : virtual public PoweredDevice // note: PoweredDevice is now a virtual base class
{
public:
  Printer(int printer, int power)
    : PoweredDevice{ power } // this line is required to create Printer objects, but ignored in this case
  {
    std::cout << "Printer: " << printer << '\n';
  }
};

class Copier
  : public Scanner
  , public Printer
{
public:
  /*
  If a class inherits one or more classes that have virtual parents, the most derived class is responsible for
  constructing the virtual base class.
  */
  Copier(int scanner, int printer, int power)
    : PoweredDevice{ power }, // PoweredDevice is constructed here
      Scanner{ scanner, power }, Printer{ printer, power }
  {}
};

int main()
{
  /*
  For the constructor of the most derived class, virtual base classes are always created before non-virtual base
  classes, which ensures all bases get created before their derived classes.

  All classes inheriting a virtual base class will have a virtual table, even if they would normally not have one
  otherwise, and thus instances of the class will be larger by a pointer.
  */
  Copier copier{ 1, 2, 3 };

  return 0;
}