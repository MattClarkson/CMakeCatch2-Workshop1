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
#include "mpExceptionMacro.h"
#include <iostream>
#include <vector>
#include <memory>

//==========================================================================================
// Uncomment each test case one at a time, use debugger to learn about program flow
// See also: http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/03cpp/sec07Exceptions.html
//==========================================================================================
class ThingA {
public:
  ThingA() { std::cerr << "Constructing ThingA." << std::endl;}
  ~ThingA() { std::cerr << "Destructing ThingA." << std::endl;}
};

/*
TEST_CASE( "1. Basic Program Flow, and Memory Handling.", "[Exceptions tests]") {

  // Step through this example with debugger.

  std::cerr << "Test 1: Start." << std::endl;

  // From the notes:
  try
  {
    std::cerr << "Test 1: Inside try." << std::endl;

    ThingA a;
    bool isOK = false;
    // Imagine this: isOK = someFunction();
    if (!isOK)
    {
      std::cerr << "Test 1: About to throw." << std::endl;

      throw std::runtime_error("Something is wrong");

      std::cerr << "Test 1: Immediately after throw." << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Caught Exception:" << e.what() << std::endl;
  }

  std::cerr << "Test 1: This line marks the end of test 1." << std::endl;

  // Q1. Check you understand the output in log file, or order of operations in debugger.

  // Q2. Change `ThingA a` to be dynamically allocated using new.  Does it leak?

  // Q3. Change the pointer to ThingA to be a smart pointer. Does it leak?

  // Q4. How should this influence the design of your code?
}
*/

// Imagine some functions calling functions, in some convoluted process.

void Func1(int a)
{
  if (a == 1)
  {
    mpExceptionThrow() << "a == 1, so its an error from Func1";
  }
}

void Func2(int a)
{
  Func1(a);
  if (a == 2)
  {
    mpExceptionThrow() << "a == 2, so its an error from Func2";
  }
}

void Func3(int a)
{
  Func2(a);
  if (a == 3)
  {
    mpExceptionThrow() << "a == 3, so its an error from Func3";
  }
}


TEST_CASE( "2. Throw at any level, catch at most appropriate level.", "[Exceptions tests]") {

  int startingValue = 1;

  // So, if you call this, it should throw.
  try
  {
    Func3(1);
  }
  catch (const mp::Exception& e)
  {
    std::cerr << "Test 2. Caught exception " << e.GetDescription() << std::endl;
  }

  // Q5. Try stepping through with debugger, or placing debug statements to trace where the flow goes.
}