#include <iomanip>
#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] = {
    { "Empty vector", testEmptyVector }
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  size_t pass_count = 0;
  for (size_t i = 0; i < count; i++) {
    bool res = tests[i].second();
    pass = pass && res;
    if (res) {
      pass_count++;
    } else {
      std::cout << tests[i].first << ": " << res << "\n";
    }
  }
  std::cout << "RESULT: " << pass << "\n";
  std::cout << "PASSED: " << pass_count << "\n";
}
