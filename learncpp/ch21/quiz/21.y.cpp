#include "../../libs/random/Random.h"
#include <array>
#include <cassert>
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>

constexpr int g_consoleLines{ 25 };

class Direction
{

public:
  enum Type { left, right, up, down, maxDirections };

  Direction(Type type) : m_type{ type } {}

  Type getType() const { return m_type; }

  Direction operator-() const
  {
    switch (m_type) {
    case Direction::up:
      return Direction::down;
    case Direction::down:
      return Direction::up;
    case Direction::left:
      return Direction::right;
    case Direction::right:
      return Direction::left;
    default:
      break;
    }
    assert(0 && "Unsupported direction was passed!");
    return Direction{ up };
  }

  static Direction getRandomDirection() { return Direction{ static_cast<Type>(Random::get(0, maxDirections - 1)) }; }

private:
  Type m_type{};
};

std::ostream& operator<<(std::ostream& stream, Direction dir)
{
  switch (dir.getType()) {
  case Direction::up:
    return (stream << "up");
  case Direction::down:
    return (stream << "down");
  case Direction::left:
    return (stream << "left");
  case Direction::right:
    return (stream << "right");
  default:
    break;
  }

  assert(0 && "Unsupported direction was passed!");
  return (stream << "unknown direction");
}

struct Point
{
  Point getAdjacentPoint(Direction d) const
  {
    switch (d.getType()) {
    case Direction::left:
      return Point{ x - 1, y };
    case Direction::right:
      return Point{ x + 1, y };
    case Direction::up:
      return Point{ x, y - 1 };
    case Direction::down:
      return Point{ x, y + 1 };
    default:
      break;
    }
    assert(0 && "Invalid direction");
    return *this;
  }

  int x{ 0 };
  int y{ 0 };
};

bool operator==(const Point& p1, const Point& p2) { return p1.x == p2.x && p1.y == p2.y; }
bool operator!=(const Point& p1, const Point& p2) { return !(p1 == p2); }

namespace UserInput {
  bool isValidCommand(char ch) { return ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'q'; }

  char getCommand()
  {
    char c{};
    while (true) {
      std::cin >> c;
      if (!std::cin || (!std::cin.eof() && std::cin.peek() != '\n') || !isValidCommand(c)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      return c;
    }
  }

  Direction charToDirection(char c)
  {
    switch (c) {
    case 'w':
      return Direction::up;
    case 'a':
      return Direction::left;
    case 's':
      return Direction::down;
    case 'd':
      return Direction::right;
    default:
      break;
    }
    assert(0 && "Unsupported command was passed!");
    return Direction{ Direction::up };
  }
} // namespace UserInput

class Tile
{
public:
  Tile() = default;
  explicit Tile(int n) : m_number{ n } {}
  bool isEmpty() const { return m_number == 0; }
  int getNum() const { return m_number; }

private:
  int m_number{ 0 };
};

std::ostream& operator<<(std::ostream& os, const Tile& t)
{
  if (t.isEmpty()) {
    os << "    ";
  } else if (t.getNum() <= 9) {
    os << "  " << t.getNum() << ' ';
  } else {
    os << ' ' << t.getNum() << ' ';
  }
  return os;
}

class Board
{
public:
  Board() = default;

  friend std::ostream& operator<<(std::ostream& os, const Board& t);

  bool moveTile(Direction d)
  {
    for (int y{ 0 }; y < m_size; ++y) {
      for (int x{ 0 }; x < m_size; ++x) {
        if (m_board[y][x].isEmpty()) {
          Point adj{ Point{ x, y }.getAdjacentPoint(-d) };
          if (adj.x >= 0 && adj.x < m_size && adj.y >= 0 && adj.y < m_size) {
            std::swap(m_board[y][x], m_board[adj.y][adj.x]);
            return true;
          }
        }
      }
    }
    return false;
  };

  bool playerWon()
  {
    static const Board s_solved{};
    return *this == s_solved;
  }

  void randomize()
  {
    for (int i{ 0 }; i < 1000;) {
      if (moveTile(Direction::getRandomDirection())) { ++i; }
    }
  }

  friend bool operator==(const Board& b1, const Board& b2)
  {
    for (int y = 0; y < m_size; ++y)
      for (int x = 0; x < m_size; ++x)
        if (b1.m_board[y][x].getNum() != b2.m_board[y][x].getNum()) return false;

    return true;
  }

private:
  static constexpr std::size_t m_size{ 4 };
  std::array<std::array<Tile, m_size>, m_size> m_board{ {
    { Tile{ 1 }, Tile{ 2 }, Tile{ 3 }, Tile{ 4 } },
    { Tile{ 5 }, Tile{ 6 }, Tile{ 7 }, Tile{ 8 } },
    { Tile{ 9 }, Tile{ 10 }, Tile{ 11 }, Tile{ 12 } },
    { Tile{ 13 }, Tile{ 14 }, Tile{ 15 }, Tile{} },
  } };
};

std::ostream& operator<<(std::ostream& os, const Board& b)
{
  for (int i{ 0 }; i < g_consoleLines; ++i) { os << '\n'; }
  for (const auto& row : b.m_board) {
    for (const auto& tile : row) { os << tile; }
    os << '\n';
  }
  os << '\n';
  return os;
}

int main()
{
  Board board{};
  board.randomize();
  std::cout << board;

  std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';

  std::cout << "Enter a command: ";
  while (!board.playerWon()) {
    char c{ UserInput::getCommand() };
    if (c == 'q') {
      std::cout << "\n\nBye!\n\n";
      break;
    }
    Direction d{ UserInput::charToDirection(c) };
    bool userMoved{ board.moveTile(d) };
    if (userMoved) std::cout << board;
  };

  std::cout << "\n\nYou won!\n\n";

  return 0;
}