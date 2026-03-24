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

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(5);
  v.pushBack(5);
  v.pushBack(5);
  v.pushBack(5);
  size_t start = v.getSize();
  v.popBack();
  v.popBack();
  return start == 4 && v.getSize() == 2;

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

bool testEqual()
{
  topit::Vector< int > l;
  l.pushBack(1);
  l.pushBack(2);
  l.pushBack(3);
  topit::Vector< int > r;
  r.pushBack(1);
  r.pushBack(2);
  r.pushBack(3);
  return l == r;
}

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav{v};
  return v == yav;
}

bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > yav{v};
  return v == yav;
}

bool testMoveConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav{std::move(v)};
  return v == yav;
}

bool testMoveConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > yav{std::move(v)};
  return v == yav;
}

int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] = {
    { "Empty vector", testEmptyVector },
    { "Push back element", testPushBack },
    { "Get size", testGetSize },
    { "Pop Back", testPopBack },
    { "Inbound access", testElementInboundAccess },
    { "Outbound access", testElementOutboundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Outbound const access", testElementOutboundConstAccess },
    { "Equal of 2 vectors", testEqual },
    { "Test copy constructor for empty", testCopyConstructorForEmpty },
    { "Test copy constructor for non empty", testCopyConstructorForNonEmpty },
    { "Test move constructor for empty", testMoveConstructorForEmpty },
    { "Test move constructor for non empty", testMoveConstructorForNonEmpty }
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
