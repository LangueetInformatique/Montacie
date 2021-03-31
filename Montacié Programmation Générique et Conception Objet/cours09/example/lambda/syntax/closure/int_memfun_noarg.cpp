// int_memfun_noarg.cpp
// Program demonstrates calling member functions with no arguments.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct handler
{
    // member function with no arguments
    int mf()
    {
        return 2;
    }

    // constant member function with no arguments
    int mfc() const
    {
        return 3;
    }
};

int main(/*int argc, char* argv[]*/)
{
    int result = 0;
    lambda< int >::scalar_reference sresult( &result );
    handler hand;

    // calls to member function with no arguments:
    result = std::mem_fun( &handler::mf )( &hand );
    result = std::mem_fun( &handler::mfc )( &hand );
    (
        sresult = *scalar(
            CTTL_MEMBER_ACTION_NOARG(
                &hand,
                std::mem_fun( &handler::mf ) // or mfc
            )
        )
        ,
        CTTL_LAMBDA_ASSERT( sresult == 2 )
        ,
        sresult = *scalar(
            CTTL_MEMBER_ACTION_NOARG(
                &hand,
                std::mem_fun( &handler::mfc ) // or mfc
            )
        )
        ,
        CTTL_LAMBDA_ASSERT( sresult == 3 )

    ).evaluate();

    return 0;
}
