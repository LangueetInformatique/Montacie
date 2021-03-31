// int_memfun_onearg.cpp
// Program demonstrates calling member functions with one argument.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct handler
{
    // constant member function
    int mfv( int x_ ) const
    {
        return x_;
    }

    // member function with mutable argument
    int mfr( int& x_ )
    {
        return ++x_;
    }

    // constant member function with constant argument
    int const& mfrc( int const& x_ ) const
    {
        return x_;
    }
};

int main(/*int argc, char* argv[]*/)
{
    int result = 0;
    lambda< int >::scalar_reference sresult( &result );
    lambda< int >::scalar sargument( 0 );
    handler hand;

    // calls to member function with one argument:
    result = std::mem_fun( &handler::mfv )( &hand, sargument.top() );
    result = std::mem_fun( &handler::mfr )( &hand, sargument.top() );
    result = std::mem_fun( &handler::mfrc )( &hand, sargument.top() );
    (
        sresult = *scalar(
            CTTL_MEMBER_ACTION(
                &hand,
                std::mem_fun( &handler::mfv ),
                sargument.top()
            )
        ),
        CTTL_LAMBDA_ASSERT( sresult == 1 ),

        sresult = *scalar(
            CTTL_MEMBER_ACTION(
                &hand,
                std::mem_fun( &handler::mfr ),
                &sargument.top()
            )
        ),
        CTTL_LAMBDA_ASSERT( sresult == 2 ),

        sresult = *scalar(
            CTTL_MEMBER_ACTION(
                &hand,
                std::mem_fun( &handler::mfrc ),
                sargument.top()
            )
        ),
        CTTL_LAMBDA_ASSERT( sresult == 2 )

    ).evaluate();

    return 0;
}
