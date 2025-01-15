#include <iostream>
#include <string>
#include <string_view>


struct Monster
{
  enum Type {
    unknown,
    ogre,
    dragon,
    orc,
    giant_spider,
    slime,
  };

  std::string name{};
  int health{};
  Type type{};
};

constexpr std::string_view getMonsterTypeString(Monster::Type mt)
{
  using enum Monster::Type;
  switch (mt) {
  case ogre:
    return "Ogre";
  case dragon:
    return "Dragon";
  case orc:
    return "Orc";
  case giant_spider:
    return "Giant Spider";
  case slime:
    return "Slime";
  default:
    return "Unknown";
  }
}

void printMonster(const Monster& m)
{
  std::cout << "This " << getMonsterTypeString(m.type) << " is named " << m.name << " and has " << m.health
            << " health.\n";
}

int main()
{
  Monster ogre{ "Torg", 145, Monster::Type::ogre };
  Monster slime{ "Blurp", 23, Monster::Type::slime };

  printMonster(ogre);
  printMonster(slime);
  return 0;
}