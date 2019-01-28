/*=============================================================================

  MYPROJECT: A software package for whatever.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "mpCatchMain.h"
#include "mpMyFunctions.h"
#include <iostream>
#include <vector>
#include <memory>

//==========================================================================================
// Uncomment each test case one at a time, and use valgrind to check and learn about memory.
// Reading:
// https://www.learncpp.com/cpp-tutorial/79-the-stack-and-the-heap/
//==========================================================================================

/*
TEST_CASE( "1. Create stack allocated array.", "[Valgrind tests]") {

  // Q1. Create a single object. Does a stack allocated object leak at end of scope?
  int a = 10;

  // Create an array of 10 integers.
  int myArray[10];

  // Q2. Above array is stack allocated. Does it leak memory at end of scope (function)?

  // Q3. Keep making and re-running the unit test, increasing the number of ints, until your program crashes. How many ints?

  std::cout << "Test 1: This line marks the end of test 1." << std::endl;
}
*/

/*
TEST_CASE( "2. Create heap allocated array", "[Valgrind tests]") {

  // Create an array of 10 integers
  int *myArray = new int[10];

  // Q4. Its heap allocated. Does it leak memory at end of scope?

  // Q5. Fix it by calling delete correctly.
  //     Note: Delete operator is different for arrays and non-arrays.

  // Q6. Increase the number of ints, can you allocate more than in the first test (Q3)?
  std::cout << "Test 2: This line marks the end of test 2." << std::endl;
}
*/

/*
class ContainerA {
public:
  ContainerA()
  {
    for (int i = 0; i < 10; i++)
    {
      myArray[i] = i; // just to show we can write to this address.
    }
  }
private:
  int myArray[10];
};
TEST_CASE( "3. Create abject containing a stack allocated block of memory", "[Valgrind tests]") {

  // Q7. Does this leak memory?
  for (int i = 0; i < 100; i++)
  {
    ContainerA myObject;
  }

  std::cout << "Test 3: This line marks the end of test 3." << std::endl;
}
*/

/*
class ContainerB {
public:
  ContainerB()
  {
    mySingleInteger = new int;
    *mySingleInteger = 1;
    myArray = new int[10];
    for (int i = 0; i < 10; i++)
    {
      myArray[i] = i;
    }
  }
private:
  int *myArray;
  int *mySingleInteger;
};
TEST_CASE( "4. Create abject containing a heap allocated block of memory", "[Valgrind tests]") {

  // Q8. Does this leak memory?
  for (int i = 0; i < 100; i++)
  {
    ContainerB myObject;
  }

  // Q9. Fix it by calling delete operators correctly.
  //     Note: Delete operator is different for arrays and non-arrays.

  std::cout << "Test 4: This line marks the end of test 4." << std::endl;
}
*/

/*
class ThingA {
public:
  ThingA() { std::cout << "Constructing ThingA" << std::endl;}
  ThingA(const ThingA &anotherThing)  { std::cout << "Copy constructing ThingA" << std::endl; }
  ~ThingA() { std::cout << "Destructing ThingA" << std::endl;}
};
TEST_CASE( "5. Vector example", "[Valgrind tests]") {

  // Above, we see how creating arrays and creating objects that contain objects
  // can lead to memory leaks. But what about standard containers like std::vector?

  std::vector<ThingA> myVec;
  for (int i = 0; i < 10; i++)
  {
    ThingA myA;
    std::cout << "Test 5: Created myA, i=" << i << std::endl;
    myVec.push_back(myA);
    std::cout << "Test 5: Added to list, i=" << i << std::endl;
  }

  // Q10. How many objects were created?
  //      Look in the log-file if unsure.

  std::cout << "Test 5: This line marks the end of test 5." << std::endl;

  // Q11. What would happen therefore if ThingA had pointers to other objects?
}
*/

/*
TEST_CASE( "6. First SmartPointer example", "[Valgrind tests]") {

  // Q12. What's going on here?
  //      Is p stack or heap allocated?
  std::unique_ptr<ThingA> p1(new ThingA);

  // Uncomment these and test if they work:
  // Q13. First, do they compile?
  // Q14. What are the implications.
  //std::unique_ptr<ThingA> p2;
  //p2 = p1;
  //std::unique_ptr<ThingA> p3(p1);

  // Q15. Then try these instead.
  //std::unique_ptr<ThingA> p2(nullptr);
  //p2 = std::move(p1);
  //REQUIRE(p1 == nullptr);
  //REQUIRE(p2 != nullptr);

  // Q16. Conclusion?

  std::cout << "Test 6: This line marks the end of test 6." << std::endl;
}
*/


/*
class ThingB {
public:
  ThingB()
  : p(new ThingA())
  {
    std::cout << "Constructing ThingB, with a pointer to ThingA" << std::endl;

  }
  ~ThingB() { std::cout << "Destructing ThingB" << std::endl; }
private:
  std::unique_ptr<ThingA> p;
};
std::unique_ptr<ThingB> FunctionThatDoesSomething(std::unique_ptr<ThingB>& myObject)
{
  std::unique_ptr<ThingB> localVariable = std::move(myObject);
  std::cout << "Variable passed in: " << myObject.get() << std::endl;
  std::cout << "localVariable: " << localVariable.get() << std::endl;
  return localVariable;
}
TEST_CASE( "7. ThingB containing ThingA", "[Valgrind tests]") {

  // As before, create a unique_ptr to hold a ThingB
  std::unique_ptr<ThingB> p1(new ThingB);

  std::cout << "Created a unique pointer p1 to an instance of ThingB" << std::endl;

  // Note how:
  // a) Each time we use a SmartPointer we assign it immediately.
  // b) We never mix Smart and non-Smart pointers.
  // This mechanism is breakable if you really want to.
  // But the point is that the code correctly describes the semantics.

  // Now try passing to a function?
  std::unique_ptr<ThingB> p2 = FunctionThatDoesSomething(p1);

  // Q14. What do you expect p2 and p1 to be? Write unit test to check.

  // Q15. In the definition for FunctionThatDoesSomething, what happens if
  //      we pass by value instead of pass by reference.

  // Q16. In the definition for FunctionThatDoesSomething, what happens if we specify const for the first argument?

  std::cout << "Test 7: This line marks the end of test 7." << std::endl;
}
*/

/*
TEST_CASE( "8. Shared pointer example", "[Valgrind tests]") {

  // Q17. Create a shared pointer to a ThingB.
  // Q18. Create another shared pointer to the same ThingB, using assignment.
  // Q19. Create another shared pointer to the same ThingB, using copy constructor.
  // Q20. So, are copy construct and assignment allowed?
  // Q21. When does constructor get called? How many times?
}
*/