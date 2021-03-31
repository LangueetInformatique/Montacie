// debugging_n_tracing.cpp
// Program demonstrates lambda tracing macros.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

int main(int argc, char* argv[])
{
    CTTL_TRACE_DEPOSIT_JUSTIFY();
    CTTL_TRACE_DEPOSIT_TEXT( "BEGIN" );
    CTTL_TRACE_DEPOSIT_TEXT( 123 );
    CTTL_TRACE_DEPOSIT_TEXT( std::endl );
    (
        CTTL_LAMBDA_TRACE( "File: " __FILE__ " Line:" CTTL_QUOTED_EXPRESSION( __LINE__ )  )
    ).evaluate();
    CTTL_TRACE_DEPOSIT_JUSTIFY();
    CTTL_TRACE_DEPOSIT_TEXT( "END" );

    return 0;
}
/*Output:
    BEGIN123
    ( ++ "File: .\main.cpp Line:18"  0 )
    END
*/
