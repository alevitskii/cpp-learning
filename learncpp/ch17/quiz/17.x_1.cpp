#include "../../libs/random/Random.h"
#include <array>
#include <ios>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

namespace Potion {
  enum Type {
    healing,
    mana,
    speed,
    invisibility,
    max_potion,
  };

  constexpr std::array types{ healing, mana, speed, invisibility };
  static_assert(std::size(types) == max_potion);

  constexpr std::array prices{ 20, 30, 12, 50 };
  static_assert(std::size(prices) == max_potion);

  using namespace std::string_view_literals;
  constexpr std::array names{ "healing"sv, "mana"sv, "speed"sv, "invisibility"sv };
  static_assert(std::size(names) == max_potion);

} // namespace Potion

class Player
{
public:
  explicit Player(std::string&& n) : m_name{ n } {}

  const std::string& name() const { return m_name; }
  int gold() const { return m_gold; }
  int inventory(Potion::Type t) const { return m_potion_inventory[t]; }

  void purhase(Potion::Type t)
  {
    ++m_potion_inventory[t];
    m_gold -= Potion::prices[t];
  }

private:
  static constexpr int s_minStartingGold{ 80 };
  static constexpr int s_maxStartingGold{ 120 };

  std::array<int, Potion::max_potion> m_potion_inventory{};
  std::string m_name{};
  int m_gold{ Random::get(s_minStartingGold, s_maxStartingGold) };
};

void shop(Player& player)
{
  char input{};
  while (true) {
    std::cout << "Here is our selection for today:\n";
    for (auto t : Potion::types) {
      std::cout << t << ") " << Potion::names[t] << " costs " << Potion::prices[t] << '\n';
    }

    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";

    std::cin >> input;

    if (!std::cin) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "That is an invalid input.1  Try again\n";
      continue;
    }

    if (!std::cin.eof() && std::cin.peek() != '\n') {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "That is an invalid input.2  Try again\n";
      continue;
    }

    if (input == 'q') { return; }

    // convert char to int
    int num{ input - '0' };

    if (num < 0 || num >= Potion::max_potion) {
      std::cout << "That is an invalid input.3  Try again\n";
      continue;
    }

    Potion::Type potion{ static_cast<Potion::Type>(num) };
    if (player.gold() < Potion::prices[potion]) {
      std::cout << "You can not afford that.\n";
      continue;
    } else {
      player.purhase(potion);
      std::cout << "You purchased a potion of " << Potion::names[potion] << ".  You have " << player.gold()
                << " gold left.\n\n";
    }
  }
}

std::string getName()
{
  std::cout << "Enter your name: ";
  std::string name{};
  std::getline(std::cin >> std::ws, name);
  return name;
}

void printInventory(const Player& player)
{
  std::cout << "Your inventory contains:\n";
  for (auto t : Potion::types) {
    if (player.inventory(t)) { std::cout << player.inventory(t) << "x potion of " << Potion::names[t] << '\n'; }
  }
  std::cout << "You escaped with " << player.gold() << " gold remaining.\n";
}

int main()
{
  std::cout << "Welcome to Roscoe's potion emporium!\n";
  Player player{ getName() };
  std::cout << "Hello, " << player.name() << ", you have " << player.gold() << " gold.\n";

  std::cout << '\n';
  shop(player);
  std::cout << '\n';

  std::cout << '\n';
  printInventory(player);
  std::cout << '\n';

  std::cout << "Thanks for shopping at Roscoe's potion emporium!\n";

  return 0;
}