#include "checkit.h"
#include "array_list.h"
// test if proper string is given 
void test_data_conv1()
{
   float sum;
   sum = data_conv_sum("3.25 7.0");
   checkit_double(sum, 10.25);
}

// test if it doesnt proper string is not given 
void test_data_conv2()
{
   float sum;
   sum = data_conv_sum("+ 4 7.0");
   checkit_double(sum, 30.0);
}

// test if non space char token is used 
void test_data_conv3()
{
   float sum;
   sum = data_conv_sum("3.25+7.0");
   checkit_double(sum, 10.25);

}
// multiple char tokesns separate 
void test_data_conv4()
{
   float sum;
   sum = data_conv_sum("3.25 + 7.0");
   checkit_double(sum, 23.25);

}

int main(void)
{
   test_data_conv1();
   test_data_conv2();
   test_data_conv3();
   test_data_conv4();
   return 0;
}