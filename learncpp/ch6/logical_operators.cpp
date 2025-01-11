int main()
{
  /*
  Operands in logical operators are evaluated left to rigt (it's an exception to the rule that operands may evaluate in
  any order)

  Operands supports short-circuit evaluation but only for builtin logical oper, if overloaded - C++ stops supporting it

  && has precedence over ||

  C++ doesn't have logical xor but it may be simulated using != if operands can be converted to bool
  !!a != !!b != ..., or static_cast<bool>(a) != static_cast<bool>(b) ...
  Double inversion is necessary when the number of operands is odd, otherwise it'll produce an inverted result.
  */
  return 0;
}