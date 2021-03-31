// lambda_assert.cpp
// Program demonstrates lambda binary switch parser
// and CTTL_LAMBDA_ASSERT macro.

//#define NDEBUG
#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "abc";
    const_edge<> substring( inp );
    (
        CTTL_LAMBDA_TRACE( "checkpoint" )
        |
        symbol( "xyz" )
        |
        CTTL_LAMBDA_ASSERT( scalar( !"bad input" ) )

    ).match( substring );

    return 0;
}