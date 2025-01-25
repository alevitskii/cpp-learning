#include "../../libs/random/Random.h"
#include <iostream>
#include <string>
#include <string_view>

class Potion
{
public:
  enum Type { health, strength, poison, max_type };
  enum Size { small, medium, large, max_size };

  Potion(Type type, Size size) : m_type{ type }, m_size{ size } {}

  Type getType() const { return m_type; }
  Size getSize() const { return m_size; }

  // The names of potions are compile-time literals, we can return a std::string_view.
  static std::string_view getPotionTypeName(Type type)
  {
    static constexpr std::string_view names[]{ "Health", "Strength", "Poison" };
    return names[type];
  }

  static std::string_view getPotionSizeName(Size size)
  {
    static constexpr std::string_view names[]{ "Small", "Medium", "Large" };
    return names[size];
  }

  static Potion getRandomPotion()
  {
    Type type{ static_cast<Type>(Random::get(0, Type::max_type - 1)) };
    Size size{ static_cast<Size>(Random::get(0, Size::max_size - 1)) };
    return Potion{ type, size };
  }

  std::string getName() const
  {
    // We use a std::stringstream, but this could also be solved using std::string.
    std::stringstream result{};
    result << getPotionSizeName(getSize()) << " potion of " << getPotionTypeName(getType());
    // We can extract the string from an std::stringstream by using the str() member function.
    return result.str();
  }

private:
  Type m_type{};
  Size m_size{};
};

class Creature
{
public:
  Creature(std::string_view name, char symbol, int health, int damage, int gold)
    : m_name{ name }, m_symbol{ symbol }, m_health{ health }, m_damage{ damage }, m_gold{ gold }
  {}

  const std::string& getName() const { return m_name; };
  char getSymbol() const { return m_symbol; };
  int getHealth() const { return m_health; };
  int getDamage() const { return m_damage; };
  int getGold() const { return m_gold; };

  void reduceHealth(int v) { m_health -= v; }
  bool isDead() const { return m_health <= 0; }
  void addGold(int v) { m_gold += v; }

protected:
  std::string m_name;
  char m_symbol{};
  int m_health{};
  int m_damage{};
  int m_gold{};
};


class Player : public Creature
{
public:
  explicit Player(std::string_view name) : Creature{ name, '@', 10, 1, 0 } {}

  void levelUp()
  {
    ++m_level;
    ++m_damage;
  }

  int getLevel() const { return m_level; }

  bool hasWon() const { return m_level >= 20; }

  void drinkPotion(const Potion& potion)
  {
    switch (potion.getType()) {
    case Potion::health:
      m_health += ((potion.getSize() == Potion::large) ? 5 : 2);
      break;
    case Potion::strength:
      ++m_damage;
      break;
    case Potion::poison:
      reduceHealth(1);
      break;
      // Handle max_type to silence the compiler warning. Don't use default:
      // because we want the compiler to warn us if we add a new potion but
      // forget to implement its effect.
    case Potion::max_type:
      break;
    }
  }

private:
  int m_level{ 1 };
};

class Monster : public Creature
{
public:
  enum Type { dragon, orc, slime, max_types };

  Monster(Type type) : Creature{ monsterData[type] } {}

  static Monster getRandomMonster() { return Monster{ static_cast<Type>(Random::get(0, Type::max_types - 1)) }; }

private:
  static inline Creature monsterData[]{
    Creature{ "dragon", 'D', 20, 4, 100 },
    Creature{ "orc", 'o', 4, 2, 25 },
    Creature{ "slime", 's', 1, 1, 10 },
  };

  static_assert(std::size(monsterData) == max_types);
};

void attackMonster(Player& player, Monster& monster)
{
  monster.reduceHealth(player.getDamage());
  std::cout << "You hit the " << monster.getName() << " for " << player.getDamage() << " damage.\n";
  if (monster.isDead()) {
    std::cout << "You killed the " << monster.getName() << ".\n";
    player.levelUp();
    std::cout << "You are now level " << player.getLevel() << ".\n";
    player.addGold(monster.getGold());
    std::cout << "You found " << monster.getGold() << " gold.\n";

    // 30% chance of finding a potion
    constexpr int potionChance{ 30 };
    if (Random::get(1, 100) <= potionChance) {
      auto potion{ Potion::getRandomPotion() };

      std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
      char choice{};
      std::cin >> choice;

      if (choice == 'Y' || choice == 'y') {
        player.drinkPotion(potion);
        std::cout << "You drank a " << potion.getName() << ".\n";
      }
    }
  }
}

void attackPlayer(Player& player, Monster& monster)
{
  player.reduceHealth(monster.getDamage());
  std::cout << "The " << monster.getName() << " hit you for " << monster.getDamage() << " damage.\n";
}


void fightMonster(Player& player, Monster& monster)
{
  while (!(player.isDead() || monster.isDead())) {
    std::cout << "(R)un or (F)ight: ";
    char c{};
    std::cin >> c;
    if (c == 'f' || c == 'F') {
      attackMonster(player, monster);
      if (!monster.isDead()) { attackPlayer(player, monster); }
    } else if (c == 'r' || c == 'R') {
      if (Random::get(0, 1)) {
        std::cout << "You successfully fled.\n";
        return;
      } else {
        std::cout << "You failed to flee.\n";
        attackPlayer(player, monster);
      }
    }
  }
}

int main()
{
  std::cout << "Enter your name: ";
  std::string name;
  std::cin >> name;
  Player player{ name };
  std::cout << "Welcome, " << player.getName() << ".\n";
  while (!(player.isDead() || player.hasWon())) {
    Monster monster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a " << monster.getName() << " (" << monster.getSymbol() << ").\n";
    fightMonster(player, monster);
  }

  if (player.isDead()) {
    std::cout << "You died at level " << player.getLevel() << " and with " << player.getGold() << " gold.\n";
    std::cout << "Too bad you can't take it with you!\n";
  }
  if (player.hasWon()) { std::cout << "You won with " << player.getGold() << " gold.\n"; }

  return 0;
}