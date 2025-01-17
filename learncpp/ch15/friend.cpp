#include <iostream>

class Temperature; // forward declaration of Temperature

class Humidity
{
private:
  int m_humidity{ 0 };

public:
  explicit Humidity(int humidity) : m_humidity{ humidity } {}

  friend void printWeather(const Temperature& temperature, const Humidity& humidity);
  friend void printWeather2(const Temperature& temperature, const Humidity& humidity);
};


class Temperature
{
private:
  int m_temp{ 0 };

public:
  explicit Temperature(int temp) : m_temp{ temp } {}

  /*
  A friend function is a function (member or non-member) that can access the private and protected members of a class as
  though it were a member of that class.
  A friend function should prefer to use the class interface over direct access whenever possible.
  Prefer to implement a function as a non-friend when possible and reasonable.
  */
  friend void printWeather(const Temperature& temperature, const Humidity& humidity);

  // Friend functions defined inside a class are non-member functions.
  // Note that m_humidity is visible to the compiler because Humidity is defined above
  friend void printWeather2(const Temperature& temperature, const Humidity& humidity)
  {
    // Because print() is a friend of Temperature
    // it can access the private members of Temperature
    std::cout << "The temperature is " << temperature.m_temp << " and the humidity is " << humidity.m_humidity << '\n';
  }
};

void printWeather(const Temperature& temperature, const Humidity& humidity)
{
  std::cout << "The temperature is " << temperature.m_temp << " and the humidity is " << humidity.m_humidity << '\n';
}

// // // // // // // // // // // // // // // // // // // // // // // // //

// We forward declare Storage so it's visible as param in Display::displayStorage
class Storage;

class Display
{
private:
  bool m_displayIntFirst{};

public:
  Display(bool displayIntFirst) : m_displayIntFirst{ displayIntFirst } {}

  void setDisplayIntFirst(bool b) { m_displayIntFirst = b; }

  void displayStorage(const Storage& storage);
};

class Storage
{
private:
  int m_nValue{};
  double m_dValue{};

public:
  Storage(int nValue, double dValue) : m_nValue{ nValue }, m_dValue{ dValue } {}

  // Make the Display class a friend of Storage. Acts like a declaration too.
  // Display members can access the private members of any Storage object they have access to.
  // Display is a friend of Storage does not mean Storage is also a friend of Display.
  // Class friendship is also not transitive. Nor is friendship inherited.
  friend class Display;

  // Make only a member function a friend (tricky when both classes are defined in one cpp file - have to forward
  // declare and rearrage)
  friend void Display::displayStorage(const Storage& storage);
};

// Because Display is a friend of Storage, Display members can access the private members of Storage.
// We had to move definition after Storage to make Storage parameter work.
void Display::displayStorage(const Storage& storage)
{
  if (m_displayIntFirst)
    std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
  else // display double first
    std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}

int main()
{
  Humidity hum{ 10 };
  Temperature temp{ 12 };

  printWeather(temp, hum);

  Storage storage{ 5, 6.7 };
  Display display{ false };

  display.displayStorage(storage);

  display.setDisplayIntFirst(true);
  display.displayStorage(storage);

  return 0;
}