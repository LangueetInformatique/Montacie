// void_memfun_onearg.cpp
// Program demonstrates calling void member functions with one argument.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct handler
{
    // constant void member function
    void mfc( int ) const
    {
    }

    // void member function with mutable argument
    void mf( int& x_ )
    {
        ++x_;
    }
};

int main(/*int argc, char* argv[]*/)
{
    int result = 0;
    lambda< int >::scalar_reference sresult( &result );
    lambda< int >::scalar sargument( 0 );
    handler hand;

    // calls to member function with one argument:
    std::mem_fun( &handler::mfc )( &hand, sargument.top() );
    std::mem_fun( &handler::mf )( &hand, sargument.top() );
    (
        sresult = *scalar(
            CTTL_MEMBER_ACTION(
                &hand,
                std::mem_fun( &handler::mfc ),
                sargument.top()
            )
        ),
        CTTL_LAMBDA_ASSERT( sargument == 1 ),

        sresult = *scalar(
            CTTL_MEMBER_ACTION(
                &hand,
                std::mem_fun( &handler::mf ),
                &sargument.top()
            )
        ),
        CTTL_LAMBDA_ASSERT( sargument == 2 )

    ).evaluate();

    return 0;
}
