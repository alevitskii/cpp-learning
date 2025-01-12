// Aliases' scope is the same as of variable identifiers.
// Aliases can be placed in a header file and included.

int main()
{
  using Miles = long; // define Miles as an alias for type long
  using Speed = long; // define Speed as an alias for type long

  // typedef and using do the same thing - they create type alias
  typedef long Miles2;
  using Miles22 = long;

  // Using is sometimes easier to read so it's preferable (typedef is an old style)
  typedef int (*FcnType)(double, char); // FcnType hard to find
  using FcnType = int (*)(double, char); // FcnType easier to find

  Miles distance{ 5 }; // distance is actually just a long
  Speed mhz{ 3200 }; // mhz is actually just a long

  // The following is syntactically valid but semantically meaningless.
  distance = mhz;

  return 0;
}