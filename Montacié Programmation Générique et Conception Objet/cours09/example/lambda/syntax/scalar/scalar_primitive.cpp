// scalar_primitive.cpp
// Program demonstrates the interface of scalar primitive.

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // C++ interface of scalar primitive
    lambda< int >::scalar Variable( 4 ); // instantiate integer scalar
    assert( Variable.top() == 4 );       // read access to top element
    Variable.push( 3 );                  // push new value
    assert( Variable.top() == 3 );       // verify result
    Variable.top() = 2;                  // write access to top element
    assert( Variable.top() == 2 );       // verify result
    Variable.pop();                      // does nothing unless Variable is a stack
    assert( Variable.size() == 1 );      // non-stack scalar has constant size

    return 0;
}
