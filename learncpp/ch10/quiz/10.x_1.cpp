int main()
{
  int a{ 5 }; // 1a, no conversion
  int b{ 'a' }; // 1b, promotion
  // int c{ 5.4 }; // 1c, error, narrowing conversion
  int d{ true }; // 1d, promotion
  int e{ static_cast<int>(5.4) }; // 1e, explicit conversion
  double f{ 5.0f }; // 1f, promotion
  double g{ 5 }; // 1g, conversion
  long h{ 5 }; // 1h, conversion, even if both int and long are 4 bytes
  // float i{ f }; // 1i (uses previously defined variable f), error, narrowing conversion
  float j{ 5.0 }; // 1j, conversion, 5.0 is constexpr and fits the range of j
}
