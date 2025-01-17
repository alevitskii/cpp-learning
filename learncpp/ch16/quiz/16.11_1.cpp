#include <iostream>
#include <vector>

void printStack(const std::vector<int>& v)
{
  std::cout << "\t(Stack: ";
  if (!v.empty()) {
    for (const auto& val : v) { std::cout << val << ' '; }
  } else {
    std::cout << "empty";
  }
  std::cout << ")\n";
}

void push(std::vector<int>& v, int val)
{
  std::cout << "Push " << val;
  v.push_back(val);
  printStack(v);
}

void pop(std::vector<int>& v)
{
  std::cout << "Pop";
  v.pop_back();
  printStack(v);
}

int main()
{
  std::vector<int> v{};
  printStack(v);
  push(v, 1);
  push(v, 2);
  push(v, 3);
  pop(v);
  push(v, 4);
  pop(v);
  pop(v);
  pop(v);

  return 0;
}