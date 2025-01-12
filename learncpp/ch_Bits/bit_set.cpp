#include <bitset>
#include <iostream>

int main()
{
  std::bitset<8> bits{ 0b0000'1101 };

  bits.set(3); // set bit position 3 to 1 (now we have 0000 1101)
  bits.flip(4); // flip bit 4 (now we have 0001 1101)
  bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

  std::cout << bits.size() << " bits are in the bitset\n";
  std::cout << bits.count() << " bits are set to true\n";

  std::cout << std::boolalpha;
  std::cout << "All bits are true: " << bits.all() << '\n';
  std::cout << "Some bits are true: " << bits.any() << '\n';
  std::cout << "No bits are true: " << bits.none() << '\n';

  // operations include &, |, ~, ^ (xor), <<, >> (and assignment counterpars, except ~ because it's unary)

  std::bitset<4> x{ 0b1100 };

  std::cout << x << '\n';
  std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
  std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1000


  // Bitwise operators will promote operands with narrower integral types to int or unsigned int.
  // operator~ and operator<< are width-sensitive and may produce different results depending on the width of the
  // operand.
  // static_cast the result of such bitwise operations back to the narrower integral type before using to ensure correct
  // results.
  std::uint8_t c{ 0b00001111 };

  std::cout << std::bitset<32>(~c) << '\n'; // incorrect: prints 11111111111111111111111111110000
  std::cout << std::bitset<32>(c << 6) << '\n'; // incorrect: prints 00000000000000000000001111000000
  // std::uint8_t cneg{ ~c }; // error: narrowing conversion from unsigned int to std::uint8_t
  c = ~c; // possible warning: narrowing conversion from unsigned int to std::uint8_t

  c = 0b00001111;

  std::cout << std::bitset<32>(static_cast<std::uint8_t>(~c))
            << '\n'; // correct: prints 00000000000000000000000011110000
  std::cout << std::bitset<32>(static_cast<std::uint8_t>(c << 6))
            << '\n'; // correct: prints 00000000000000000000000011000000
  std::uint8_t cneg{ static_cast<std::uint8_t>(~c) }; // compiles
  c = static_cast<std::uint8_t>(~c);

  return 0;
}