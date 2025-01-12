#include "../../libs/random/Random.h"
#include <ios>
#include <iostream>
#include <limits>

namespace Params {
  constexpr int numberOfAttempts{ 7 };
  constexpr int maxNumber{ 100 };
  constexpr int minNumber{ 1 };
} // namespace Params

void ignoreLine() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

int getNumber(int guessNumber)
{
  while (true) {
    std::cout << "Guess #" << guessNumber << ": ";
    int x{};
    std::cin >> x;
    bool success{ std::cin };
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!success || x < Params::minNumber || x > Params::maxNumber) { continue; }

    return x;
  }
}

bool isGuessCorrect(int num, int guessed)
{
  if (num < guessed) {
    std::cout << "Your guess is too low.\n";
  } else if (num > guessed) {
    std::cout << "Your guess is too high.\n";
  } else {
    std::cout << "Correct! You win!\n";
    return true;
  }
  return false;
}

void play()
{
  int guessed{ Random::get(Params::minNumber, Params::maxNumber) };
  std::cout << "Let's play a game. I'm thinking of a number between " << Params::minNumber << " and "
            << Params::maxNumber << ". You have " << Params::numberOfAttempts << " tries to guess what it is.\n";

  for (int attempt{ 1 }; attempt <= Params::numberOfAttempts; ++attempt) {
    if (isGuessCorrect(getNumber(attempt), guessed)) { return; }
  }
  std::cout << "Sorry, you lose. The correct number was " << guessed << ".\n";
}

bool wannaPlay()
{
  while (true) {
    std::cout << "Would you like to play again (y/n)? ";
    char c{};
    std::cin >> c;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (c) {
    case 'y':
      return true;
    case 'n':
      return false;
    }
  }
}

int main()
{
  do {
    play();
  } while (wannaPlay());

  std::cout << "Thank you for playing.\n";

  return 0;
}