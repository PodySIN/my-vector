#include <iomanip>
#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(5);
  v.pushBack(8);
  v.pushBack(11);
  return v[0] == 5 && v[1] == 8 && v[2] == 11;
}

bool testGetSize()
{
  topit::Vector< int > v;
  size_t start = v.getSize();
  v.pushBack(5);
  v.pushBack(5);
  v.pushBack(5);
  v.pushBack(5);
  return start == 0 && v.getSize() == 4;
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int >& rv = v;
  try {
    const int& val = rv.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testElementOutboundConstAccess()
{
  topit::Vector< int > v;
  topit::Vector< int >& rv = v;
  try {
    rv.at(10);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try {
    int& val = v.at(0);
    return val == 1;
  } catch (...) {
    return false;
  }
}

bool testElementOutboundAccess()
{
  topit::Vector< int > v;
  try {
    v.at(10);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] = {
    { "Empty vector", testEmptyVector },
    { "Push back element", testPushBack },
    { "Get size", testGetSize },
    { "Inbound access", testElementInboundAccess },
    { "Outbound access", testElementOutboundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Outbound const access", testElementOutboundConstAccess }
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
