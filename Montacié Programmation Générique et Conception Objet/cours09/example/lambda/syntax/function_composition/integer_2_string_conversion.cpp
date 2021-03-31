// integer_2_string_conversion.cpp
// Program demonstrates value translation and data type conversion
// from int to std::string.

#define CTTL_TRACE_DEPOSITS // turns on tracing of lambda expressions

#include "cttl/cttl.h"
#include "lambda/lambda.h"
#include "utils/itos.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    // This is a workaround for microsoft compiler;
    // GNU compiler won't need it:
    typedef CTTL_STD_STRING ( *function_T ) ( int );

    lambda< std::string >::scalar str;
    (
        ( str^function_T( &itos<int> ) ) = 123,   // convert integer to string
        CTTL_LAMBDA_ASSERT( str == scalar( std::string( "123" ) ) )
    ).evaluate();

    return 0;
}
