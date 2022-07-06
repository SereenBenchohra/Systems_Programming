/*
 * Provided unit test driver for the unitTest.h test macros. Sample tests are
 * provided for each test macro to help get you started but you will need to
 * write more to ensure your implementations are correct.
 *
 * See the assignment for an example of how to run this program or see its
 * usage message.
 *
 * Run the reference solution to see the required message formats.
 *
 * DON'T hand this source or any other source in to the Evaluation System or
 * your build/make will probably fail. For this exercise you will just be
 * handing in unitTest.h.
 */
#include <stdio.h>
#include <stdlib.h>
#include "unitTest.h"

/*
 * Macro constants for each of the test types...
 */
#define SIGNED 1
#define UNSIGNED 2
#define REAL 3
#define BOOLEAN 4
#define CHAR 5
#define STRING 6

/* Simple function used to verify text substitution in the unit test macro.
 */
long someSignedFunc(long value)
{
   return value;
}

/* Simple function used to verify text substitution in the unit test macro.
 */
unsigned long someUnsignedFunc(unsigned long value)
{
   return value;
}

/* Simple function used to verify text substitution in the unit test macro.
 */
double someDoubleFunc(double value)
{
   return value;
}

/* Simple function used to verify text substitution in the unit test macro.
 */
long someBooleanFunc(long value)
{
   return value;
}

/* Simple function used to verify text substitution in the unit test macro.
 */
char someCharFunc(char value)
{
   return value;
}

/* Simple function used to verify text substitution in the unit test macro.
 */
char* someStringFunc(char *string)
{
   return string;
}

void test_TEST_SIGNED()
{
   /* Provided: A test that should pass, i.e., report nothing */
   TEST_SIGNED(someSignedFunc(-976), -976);

   /* Provided: A test that should fail, i.e., report failure */
   TEST_SIGNED(someSignedFunc(976), -976);

   /* TODO: Add additional tests, as necessary, to ensure correctness! */
}

void test_TEST_UNSIGNED()
{
   /* Provided: A test that should pass, i.e., report nothing */
   TEST_UNSIGNED(someUnsignedFunc(976), 976);

   /* Provided: A test that should fail, i.e., report failure */
   TEST_UNSIGNED(someUnsignedFunc(3999888777), 3999888776);

   /* TODO: Add additional tests, as necessary, to ensure correctness! */
}

void test_TEST_REAL()
{
   /* Provided: A test that should pass, i.e., report nothing */
   TEST_REAL(someDoubleFunc(27.01), 27.011, 0.001);

   /* Provided: A test that should fail, i.e., report failure */
   TEST_REAL(someDoubleFunc(-27.01), -27.0115, 0.001);

   /* TODO: Add additional tests, as necessary, to ensure correctness! */
}

void test_TEST_BOOLEAN()
{
   /* Provided: A test that should pass, i.e., report nothing */
   TEST_BOOLEAN(someSignedFunc(-7), 1);

   /* Provided: A test that should fail, i.e., report failure */
   TEST_BOOLEAN(someSignedFunc(987), 0);

   /* TODO: Add additional tests, as necessary, to ensure correctness! */
}

void test_TEST_CHAR()
{
   /* Provided: A test that should pass, i.e., report nothing */
   TEST_CHAR(someCharFunc(65), 'A');

   /* Provided: A test that should fail, i.e., report failure */
   TEST_CHAR(someCharFunc(90), 'z');

   /* TODO: Add additional tests, as necessary, to ensure correctness! */
}

void test_TEST_STRING()
{
   /* Provided: A test that should pass, i.e., report nothing */
   TEST_STRING(someStringFunc("Hello, World!"), "Hello, World!");

   /* Provided: A test that should fail, i.e., report failure */
   TEST_STRING(someStringFunc("Red"), "ReD");

   /* TODO: Add additional tests, as necessary, to ensure correctness! */
}

void showUsageAndExit()
{
   fprintf(stderr, "Usage: testUnitTestMacros macroName\n");
   exit(EXIT_FAILURE);
}

int checkArgs(int argc, char *argv[])
{
   int testType = 0;

   if (argc != 2)
      showUsageAndExit();

   if (0 == strcmp(argv[1], "TEST_SIGNED"))
      testType = SIGNED;
   else if (0 == strcmp(argv[1], "TEST_UNSIGNED"))
      testType = UNSIGNED;
   else if (0 == strcmp(argv[1], "TEST_REAL"))
      testType = REAL;
   else if (0 == strcmp(argv[1], "TEST_BOOLEAN"))
      testType = BOOLEAN;
   else if (0 == strcmp(argv[1], "TEST_CHAR"))
      testType = CHAR;
   else if (0 == strcmp(argv[1], "TEST_STRING"))
      testType = STRING;
   else {
      fprintf(stderr, "Unknown test type: \"%s\"\n", argv[1]);
      showUsageAndExit();
   }

   return testType;
}
      
int main(int argc, char *argv[])
{
   int testType = checkArgs(argc, argv);

   switch (testType)
   {
      case SIGNED:
         test_TEST_SIGNED();
      break;
  
      case UNSIGNED:
         test_TEST_UNSIGNED();
      break;
  
      case REAL:
         test_TEST_REAL();
      break;
      
      case BOOLEAN:
         test_TEST_BOOLEAN();
      break;
  
      case CHAR:
         test_TEST_CHAR();
      break;
  
      case STRING:
         test_TEST_STRING();
      break;
  
      default:
         fprintf(stderr, "Missing case for test type %d\n", testType);
         exit(EXIT_FAILURE);
      break;
   }

   return 0;
}
