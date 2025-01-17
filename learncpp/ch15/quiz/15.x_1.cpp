#include "../../libs/random/Random.h"
#include <iostream>
#include <string>
#include <string_view>

class Monster
{
public:
  enum Type {
    dragon,
    goblin,
    ogre,
    orc,
    skeleton,
    troll,
    vampire,
    zombie,
    maxMonsterTypes, // must be last
  };

  Monster(Type t, std::string_view n, std::string_view r, int hp)
    : m_type{ t }, m_name{ n }, m_roar{ r }, m_hitPoints{ hp }
  {}

  constexpr std::string_view getTypeString() const
  {
    switch (m_type) {
    case dragon:
      return "dragon";
    case goblin:
      return "goblin";
    case ogre:
      return "ogre";
    case orc:
      return "orc";
    case skeleton:
      return "skeleton";
    case troll:
      return "troll";
    case vampire:
      return "vampire";
    case zombie:
      return "zombie";
    default:
      return "???";
    }
  }

  void print() const
  {
    std::cout << m_name << " the " << getTypeString();
    if (m_hitPoints > 0) {
      std::cout << " has " << m_hitPoints << " and says " << m_roar << ".\n";
    } else {
      std::cout << " is dead.\n";
    }
  }

private:
  Type m_type{};
  std::string m_name{};
  std::string m_roar{};
  int m_hitPoints{};
};

namespace MonsterGenerator {
  std::string_view getName(int n)
  {
    switch (n) {
    case 0:
      return "Blarg";
    case 1:
      return "Moog";
    case 2:
      return "Pksh";
    case 3:
      return "Tyrn";
    case 4:
      return "Mort";
    case 5:
      return "Hans";
    default:
      return "???";
    }
  }

  std::string_view getRoar(int n)
  {
    switch (n) {
    case 0:
      return "*ROAR*";
    case 1:
      return "*peep*";
    case 2:
      return "*squeal*";
    case 3:
      return "*whine*";
    case 4:
      return "*growl*";
    case 5:
      return "*burp*";
    default:
      return "???";
    }
  }

  Monster generate()
  {
    return Monster{
      static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes - 1)),
      getName(Random::get(0, 5)),
      getRoar(Random::get(0, 5)),
      Random::get(1, 100),
    };
  }

} // namespace MonsterGenerator

int main()
{
  Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
  skeleton.print();

  Monster vampire{ Monster::vampire, "Nibblez", "*hiss*", 0 };
  vampire.print();

  Monster m{ MonsterGenerator::generate() };
  m.print();

  return 0;
}