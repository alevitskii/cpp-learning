#include <chrono> // for std::chrono
#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
  // prng (pseudo-random number generator) should be seeded only once.
  // std::mt19937 is the most ok prng in std, 19937 is the number of bits in its internal state.
  // After 2^19937-1 numbers prng starts producing same values (it's called period).

  // (preferable) seed using random device (implementation defined)
  std::mt19937 mt{ std::random_device{}() };

  // Seed our Mersenne Twister using steady_clock.
  // Steady is better than high_resolution_clock because high resolution relies on system clock which may be adjusted by
  // users. However, high resolution is more granular.
  std::mt19937 mt2{ static_cast<std::mt19937::result_type>(
    std::chrono::steady_clock::now().time_since_epoch().count()) };

  // Above we give the prng only one number while mt19937 has 624 values as its internal state.
  // The <random> library then fills the remaining 623 but it's not good. As a result prng is underseeded.
  std::random_device rd{};
  // std::seed_seq allows to provide multiple random values to seed the prng. Now prng is less underseeded.
  // Giving all 624 values may be slow and deplete the random device pool.
  // It's also OK to throw in clock time, process ids and other number in seed_seq.
  // Some prng benefit from warming up - discarding first 100s or 1000s numbers. seed_seq + mt19937 do it for us.
  std::seed_seq ss{
    rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()
  }; // get 8 integers of random numbers from std::random_device for our seed
  std::mt19937 mt3{ ss }; // initialize our Mersenne Twister with the std::seed_seq

  // Create a reusable random number generator that generates uniform numbers between 1 and 6
  std::uniform_int_distribution die6{ 1, 6 };

  // Print a bunch of random numbers
  for (int count{ 1 }; count <= 40; ++count) {
    std::cout << die6(mt3) << '\t'; // generate a roll of the die here

    // If we've printed 10 numbers, start a new row
    if (count % 10 == 0) std::cout << '\n';
  }

  return 0;
}