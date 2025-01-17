#include "../../libs/random/Random.h"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

namespace WordList {
  std::vector<std::string_view>
    words{ "mystery", "broccoli", "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

  std::string_view getRandomWord()
  {
    return WordList::words[Random::get<std::size_t>(0, std::size(WordList::words) - 1)];
  }

} // namespace WordList

class Session
{
public:
  explicit Session(int a) : m_attempts{ a } {}
  std::string_view getWord() const { return m_word; }

  void setGuessed(char c) { m_letters[toIndex(c)] = true; }

  bool isGuessed(char c) const { return m_letters[toIndex(c)]; }

  int attemptsLeft() const { return m_attempts; };
  void decrementAttempts() { --m_attempts; };

  bool isLetterInWord(char c) const
  {
    for (auto ch : m_word) {
      if (ch == c) { return true; }
    }

    return false;
  }

  bool won() const
  {
    for (auto c : m_word) {
      if (!isGuessed(c)) { return false; }
    }

    return true;
  }

private:
  std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32) - 1); }

  std::string_view m_word{ WordList::getRandomWord() };
  std::vector<bool> m_letters{ std::vector<bool>(26, false) };
  int m_attempts{};
};

void displayState(const Session& s)
{
  std::cout << "The word: " << (s.getWord()) << ' ';
  for (auto c : s.getWord()) { std::cout << (s.isGuessed(c) ? c : '_'); }

  std::cout << "   Wrong guesses: ";
  for (int i = 0; i < s.attemptsLeft(); ++i) { std::cout << '+'; }
  for (char c = 'a'; c <= 'z'; ++c) {
    if (s.isGuessed(c) && !s.isLetterInWord(c)) { std::cout << c; }
  }

  std::cout << '\n';
}

char getLetter(const Session& s)
{
  char c{};
  bool valid{ true };
  while (true) {
    std::cout << "Enter your next letter: ";
    std::cin >> c;

    if (!std::cin) {
      std::cin.clear();
      valid = false;
    }
    if (!std::isalpha(c) || !std::islower(c)) { valid = false; }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!valid) {
      std::cout << "That wasn't a valid input. Try again.\n";
      valid = true;
      continue;
    }

    if (s.isGuessed(c)) {
      std::cout << "You already guessed that. Try again.\n";
      continue;
    }
    return c;
  }
}

void handleGuess(Session& s, char c)
{
  s.setGuessed(c);

  if (s.isLetterInWord(c)) {
    std::cout << "Yes, '" << c << "' is in the word!\n";
    return;
  }

  std::cout << "No, '" << c << "' is not in the word!\n";
  s.decrementAttempts();
}

int main()
{
  std::cout << "Welcome to C++man (a variant of Hangman)\n";
  std::cout << "To win: guess the word. To lose: run out of pluses.\n";

  Session s{ 6 };

  while (s.attemptsLeft() > 0 && !s.won()) {
    displayState(s);
    char ch{ getLetter(s) };
    handleGuess(s, ch);
  }

  displayState(s);

  if (!s.attemptsLeft())
    std::cout << "You lost!  The word was: " << s.getWord() << '\n';
  else
    std::cout << "You won!\n";

  return 0;
}