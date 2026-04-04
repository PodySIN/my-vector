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

bool testConstrucctorWithSizeAndInit()
{
  topit::Vector< int > v(3, 4);
  bool f = true;
  for (size_t i = 0; i < 3; i++) {
    if (v[i] != 4) {
      f = false;
    }
  }
  return v.getSize() == 3 && f;
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
  topit::Vector< int > yav = std::move(v);
  return v == yav;
}

bool testMoveConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  topit::Vector< int > yav = std::move(v);
  return yav[0] == 1 && yav[1] == 2 && yav.getSize() == 2;
}

bool testCopyOperatorForEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2;
  v2 = v1;
  return v1 == v2;
}

bool testCopyOperatorForNonEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2;
  v1.pushBack(1);
  v1.pushBack(2);
  v2 = v1;
  return v1 == v2 && v1[1] == 2 && v2[1] == 2;
}

bool testMoveOperatorForEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2;
  v2 = std::move(v1);
  return v1 == v2;
}

bool testMoveOperatorForNonEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2;
  v1.pushBack(1);
  v1.pushBack(2);
  v2 = std::move(v1);
  return v2[0] == 1 && v2[1] == 2;
}

bool testInitializerList()
{
  topit::Vector< int > v{6, 7};
  return v.getSize() == 2 && v[0] == 6 && v[1] == 7;
}

bool testReserveEmpty()
{
  topit::Vector< int > v;
  v.reserve(100);
  return v.getCapacity() == 100 && v.getSize() == 0;
}

bool testReserveNonEmpty()
{
  topit::Vector< int > v{1, 2, 4, 8, 16, 22};
  v.reserve(1000);
  return v.getCapacity() == 1000 && v.getSize() == 6 && v[0] == 1 && v[2] == 4 && v[5] == 22;
}

bool testReserveLessCapacity()
{
  topit::Vector< int > v{1, 2, 13, 7, 16, 22};
  v.reserve(1000);
  v.reserve(4);
  return v.getCapacity() == 4 && v.getSize() == 4 && v[0] == 1 && v[2] == 13 && v[3] == 7;
}

bool testShrinkToFit()
{
  topit::Vector< int > v{1, 2, 3};
  v.reserve(100);
  v.shrinkToFit();
  return v.getCapacity() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertEmptyVector()
{
  topit::Vector< int > v;
  v.insert(0, 1);
  return v.getSize() == 1 && v[0] == 1;
}

bool testInsertMiddleOfVector()
{
  topit::Vector< int > v{1, 2, 3};
  v.insert(1, 11);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 11 && v[2] == 2 && v[3] == 3;
}

bool testInsertStartOfVector()
{
  topit::Vector< int > v{1, 2, 3};
  v.insert(0, 11);
  return v.getSize() == 4 && v[0] == 11 && v[1] == 1 && v[2] == 2 && v[3] == 3;
}

bool testInsertEndOfVector()
{
  topit::Vector< int > v{1, 2, 3};
  v.insert(3, 11);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 11;
}

bool testInsertOutOfRangeVector()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.insert(4, 11);
  } catch (const std::out_of_range& e) {
    return true;
  }
  return false;
}

bool testInsertAnotherVector()
{
  topit::Vector< int > v{1, 2, 3};
  topit::Vector< int > v2{11, 12, 13};
  v.insert(1, v2, 0, 3);
  return v.getSize() == 6 && v[0] == 1 && v[1] == 11 && v[2] == 12 && v[3] == 13 && v[4] == 2 && v[5] == 3;
}

bool testInsertVectorEmpty()
{
  topit::Vector<int> v;
  topit::Vector<int> rhs{1, 2, 3};
  v.insert(0, rhs, 0, 3);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertVectorAtBeginning()
{
  topit::Vector<int> v{4, 5, 6};
  topit::Vector<int> rhs{1, 2, 3};
  v.insert(0, rhs, 0, 3);
  return v.getSize() == 6 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6;
}

bool testInsertVectorAtMiddle()
{
  topit::Vector<int> v{1, 2, 6, 7};
  topit::Vector<int> rhs{3, 4, 5};
  v.insert(2, rhs, 0, 3);
  return v.getSize() == 7 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6 && v[6] == 7;
}

bool testInsertVectorAtEnd()
{
  topit::Vector<int> v{1, 2, 3};
  topit::Vector<int> rhs{4, 5, 6};
  v.insert(3, rhs, 0, 3);
  return v.getSize() == 6 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6;
}

bool testInsertVectorPartialRange()
{
  topit::Vector<int> v{1, 2, 7, 8};
  topit::Vector<int> rhs{3, 4, 5, 6, 9};
  v.insert(2, rhs, 0, 4);
  return v.getSize() == 8 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6 && v[6] == 7 && v[7] == 8;
}

bool testInsertVectorOutOfRange()
{
  topit::Vector<int> v{1, 2, 3};
  topit::Vector<int> rhs{4, 5, 6};
  try {
    v.insert(5, rhs, 0, 3);
  } catch (const std::out_of_range& e) {
    return true;
  }
  return false;
}

bool testEraseOneElementBeginning()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(0);
  return v.getSize() == 4 && v[0] == 2 && v[1] == 3 && v[2] == 4 && v[3] == 5;
}

bool testEraseOneElementMiddle()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(2);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 4 && v[3] == 5;
}

bool testEraseOneElementEnd()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(4);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4;
}

bool testEraseOneElementOutOfRange()
{
  topit::Vector< int > v{1, 2, 3};
  try {
    v.erase(5);
  } catch (const std::out_of_range& e) {
    return true;
  }
  return false;
}

bool testEraseOneElementFromEmpty()
{
  topit::Vector< int > v;
  try {
    v.erase(0);
  } catch (const std::out_of_range& e) {
    return true;
  }
  return false;
}

bool testEraseRangeBeginning()
{
  topit::Vector< int > v{1, 2, 3, 4, 5, 6};
  v.erase(0, 3);
  return v.getSize() == 3 && v[0] == 4 && v[1] == 5 && v[2] == 6;
}

bool testEraseRangeMiddle()
{
  topit::Vector< int > v{1, 2, 3, 4, 5, 6};
  v.erase(2, 5);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 6;
}

bool testEraseRangeEnd()
{
  topit::Vector< int > v{1, 2, 3, 4, 5, 6};
  v.erase(3, 6);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testEraseRangeWhole()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(0, 5);
  return v.getSize() == 0;
}

bool testEraseRangeOutOfRange()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  try {
    v.erase(2, 10);
  } catch (const std::out_of_range& e) {
    return true;
  }
  return false;
}

bool testEraseRangeStartGreaterThanEnd()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  try {
    v.erase(4, 2);
  } catch (const std::out_of_range& e) {
    return true;
  }
  return false;
}

bool testEraseRangeEmpty()
{
  topit::Vector< int > v{1, 2, 3, 4, 5};
  v.erase(2, 2);
  return v.getSize() == 5 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5;
}

bool testInsertIteratorSingleAtBeginning()
{
  topit::Vector<int> v{2, 3, 4};
  auto it = v.insert(v.begin(), 1);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && *it == 1;
}

bool testInsertIteratorSingleAtMiddle()
{
  topit::Vector<int> v{1, 2, 4, 5};
  auto it = v.insert(v.begin() + 2, 3);
  return v.getSize() == 5 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && *it == 3;
}

bool testInsertIteratorSingleAtEnd()
{
  topit::Vector<int> v{1, 2, 3};
  auto it = v.insert(v.end(), 4);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && *it == 4;
}

bool testInsertIteratorSingleIntoEmpty()
{
  topit::Vector<int> v;
  auto it = v.insert(v.begin(), 42);
  return v.getSize() == 1 && v[0] == 42 && *it == 42;
}

bool testInsertIteratorRangeAtBeginning()
{
  topit::Vector<int> v{4, 5, 6};
  topit::Vector<int> source{1, 2, 3};
  auto it = v.insert(v.begin(), source.begin(), source.end());
  return v.getSize() == 6 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6 && *it == 1;
}

bool testInsertIteratorRangeAtMiddle()
{
  topit::Vector<int> v{1, 2, 6, 7};
  topit::Vector<int> source{3, 4, 5};
  auto it = v.insert(v.begin() + 2, source.begin(), source.end());
  return v.getSize() == 7 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6 && v[6] == 7 && *it == 3;
}

bool testInsertIteratorRangeAtEnd()
{
  topit::Vector<int> v{1, 2, 3};
  topit::Vector<int> source{4, 5, 6};
  auto it = v.insert(v.end(), source.begin(), source.end());
  return v.getSize() == 6 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5 && v[5] == 6 && *it == 4;
}

bool testInsertIteratorRangeEmpty()
{
  topit::Vector<int> v{1, 2, 3};
  topit::Vector<int> source;
  auto it = v.insert(v.begin() + 1, source.begin(), source.end());
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3 && it == v.begin() + 1;
}

bool testInsertIteratorRangeIntoEmpty()
{
  topit::Vector<int> v;
  topit::Vector<int> source{1, 2, 3};
  auto it = v.insert(v.begin(), source.begin(), source.end());
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3 && *it == 1;
}

bool testEraseIteratorSingleBeginning()
{
  topit::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.erase(v.begin());
  return v.getSize() == 4 && v[0] == 2 && v[1] == 3 && v[2] == 4 && v[3] == 5 && *it == 2;
}

bool testEraseIteratorSingleMiddle()
{
  topit::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.erase(v.begin() + 2);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 4 && v[3] == 5 && *it == 4;
}

bool testEraseIteratorSingleEnd()
{
  topit::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.erase(v.end() - 1);
  return v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && it == v.end();
}

bool testEraseIteratorSingleLast()
{
  topit::Vector<int> v{1, 2, 3};
  auto it = v.erase(v.begin() + 2);
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2 && it == v.end();
}

bool testEraseIteratorRangeBeginning()
{
  topit::Vector<int> v{1, 2, 3, 4, 5, 6};
  auto it = v.erase(v.begin(), v.begin() + 3);
  return v.getSize() == 3 && v[0] == 4 && v[1] == 5 && v[2] == 6 && *it == 4;
}

bool testEraseIteratorRangeMiddle()
{
  topit::Vector<int> v{1, 2, 3, 4, 5, 6};
  auto it = v.erase(v.begin() + 2, v.begin() + 5);
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 6 && *it == 6;
}

bool testEraseIteratorRangeEnd()
{
  topit::Vector<int> v{1, 2, 3, 4, 5, 6};
  auto it = v.erase(v.begin() + 3, v.end());
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3 && it == v.end();
}

bool testEraseIteratorRangeWhole()
{
  topit::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.erase(v.begin(), v.end());
  return v.getSize() == 0 && it == v.end();
}

bool testEraseIteratorRangeEmpty()
{
  topit::Vector<int> v{1, 2, 3, 4, 5};
  auto it = v.erase(v.begin() + 2, v.begin() + 2);
  return v.getSize() == 5 && it == v.begin() + 2;
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
    { "Test constructor with size and init", testConstrucctorWithSizeAndInit },
    { "Test copy constructor for empty", testCopyConstructorForEmpty },
    { "Test copy constructor for non empty", testCopyConstructorForNonEmpty },
    { "Test move constructor for empty", testMoveConstructorForEmpty },
    { "Test move constructor for non empty", testMoveConstructorForNonEmpty },
    { "Test copy operator for empty", testCopyOperatorForEmpty },
    { "Test copy operator for not empty", testCopyOperatorForNonEmpty },
    { "Test move operator for empty", testMoveOperatorForEmpty },
    { "Test move operator for non empty", testMoveOperatorForNonEmpty },
    { "Test constructor for non-empty initializer list", testInitializerList },
    { "Test reserve for empty vector", testReserveEmpty },
    { "Test reserve for non empty vector", testReserveNonEmpty },
    { "Test reserve for capacity smaller than container capacity", testReserveLessCapacity },
    { "Test shrink to fit", testShrinkToFit },
    { "Test insert empty vector", testInsertEmptyVector },
    { "Test insert start of vector", testInsertStartOfVector },
    { "Test insert middle of vector", testInsertMiddleOfVector },
    { "Test insert end of vector", testInsertEndOfVector },
    { "Test insert out of range vector", testInsertOutOfRangeVector },
    { "Test insert another vector", testInsertAnotherVector },
    { "Test insert vector empty", testInsertVectorEmpty },
    { "Test insert vector at beginning", testInsertVectorAtBeginning },
    { "Test insert vector at middle", testInsertVectorAtMiddle },
    { "Test insert vector at end", testInsertVectorAtEnd },
    { "Test insert vector partial range", testInsertVectorPartialRange },
    { "Test insert vector out of range", testInsertVectorOutOfRange },
    { "Erase one element beginning", testEraseOneElementBeginning },
    { "Erase one element middle", testEraseOneElementMiddle },
    { "Erase one element end", testEraseOneElementEnd },
    { "Erase one element out of range", testEraseOneElementOutOfRange },
    { "Erase one element from empty", testEraseOneElementFromEmpty },
    { "Erase range beginning", testEraseRangeBeginning },
    { "Erase range middle", testEraseRangeMiddle },
    { "Erase range end", testEraseRangeEnd },
    { "Erase range whole", testEraseRangeWhole },
    { "Erase range out of range", testEraseRangeOutOfRange },
    { "Erase range start greater than end", testEraseRangeStartGreaterThanEnd },
    { "Erase range empty", testEraseRangeEmpty },
    { "Insert iterator single at beginning", testInsertIteratorSingleAtBeginning },
    { "Insert iterator single at middle", testInsertIteratorSingleAtMiddle },
    { "Insert iterator single at end", testInsertIteratorSingleAtEnd },
    { "Insert iterator single into empty", testInsertIteratorSingleIntoEmpty },
    { "Insert iterator range at beginning", testInsertIteratorRangeAtBeginning },
    { "Insert iterator range at middle", testInsertIteratorRangeAtMiddle },
    { "Insert iterator range at end", testInsertIteratorRangeAtEnd },
    { "Insert iterator range empty", testInsertIteratorRangeEmpty },
    { "Insert iterator range into empty", testInsertIteratorRangeIntoEmpty },
    { "Erase iterator single beginning", testEraseIteratorSingleBeginning },
    { "Erase iterator single middle", testEraseIteratorSingleMiddle },
    { "Erase iterator single end", testEraseIteratorSingleEnd },
    { "Erase iterator single last", testEraseIteratorSingleLast },
    { "Erase iterator range beginning", testEraseIteratorRangeBeginning },
    { "Erase iterator range middle", testEraseIteratorRangeMiddle },
    { "Erase iterator range end", testEraseIteratorRangeEnd },
    { "Erase iterator range whole", testEraseIteratorRangeWhole },
    { "Erase iterator range empty", testEraseIteratorRangeEmpty }
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
