#include <iostream>


double calcDistFallen(int sec) { return 9.8 * sec * sec / 2; }

void calcAndPrint(int height, int sec)
{
  double distFallen{ calcDistFallen(sec) };
  if (distFallen < height)
    std::cout << "At " << sec << " seconds, the ball is at height: " << height - distFallen << " meters\n";
  else
    std::cout << "At " << sec << " seconds, the ball is on the ground.\n";
}

int main()
{
  std::cout << "Enter the height of the tower in meters: ";
  int height{};
  std::cin >> height;

  calcAndPrint(height, 0);
  calcAndPrint(height, 1);
  calcAndPrint(height, 2);
  calcAndPrint(height, 3);
  calcAndPrint(height, 4);
  calcAndPrint(height, 5);

  return 0;
}