#include <iostream>

namespace Constants {
  constexpr double gravity{ 9.8 };
}

// Gets tower height from user and returns it
double getTowerHeight()
{
  std::cout << "Enter the height of the tower in meters: ";
  double towerHeight{};
  std::cin >> towerHeight;
  return towerHeight;
}

// Returns the current ball height after "seconds" seconds
constexpr double calculateBallHeight(double towerHeight, int seconds)
{
  // Using formula: s = (u * t) + (a * t^2) / 2
  // here u (initial velocity) = 0, so (u * t) = 0
  const double fallDistance{ Constants::gravity * (seconds * seconds) / 2.0 };
  const double ballHeight{ towerHeight - fallDistance };

  // If the ball would be under the ground, place it on the ground
  if (ballHeight < 0.0) return 0.0;

  return ballHeight;
}


int main()
{
  const double towerHeight{ getTowerHeight() };

  int seconds{ 0 };
  double ballHeight{ calculateBallHeight(towerHeight, seconds) };
  while (ballHeight > 0.0) {
    std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
    ++seconds;
    ballHeight = calculateBallHeight(towerHeight, seconds);
  }
  std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";

  return 0;
}