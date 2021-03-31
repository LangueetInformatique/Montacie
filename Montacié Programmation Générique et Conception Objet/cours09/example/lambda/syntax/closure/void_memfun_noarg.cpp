// void_memfun_noarg.cpp
// Program demonstrates calling void member functions with no arguments.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct handler
{
    // void member function with no arguments 
          
    void vmf()
    {
    }

    // constant void member function with no arguments
    void vmfc() const
    {
    }
};

int main(/*int argc, char* argv[]*/)
{
    lambda< int >::scalar sresult;
    handler hand;

    // calls to member function with no arguments:
    std::mem_fun( &handler::vmf )( &hand );
    std::mem_fun( &handler::vmfc )( &hand );
    (
        sresult = *scalar(
            CTTL_MEMBER_ACTION_NOARG(
                &hand,
                std::mem_fun( &handler::vmf )
            )
        )
        ,
        CTTL_LAMBDA_ASSERT( sresult == 1 )
        ,
        sresult = *scalar(
            CTTL_MEMBER_ACTION_NOARG(
                &hand,
                std::mem_fun( &handler::vmfc )
            )
        )
        ,
        CTTL_LAMBDA_ASSERT( sresult == 1 )

    ).evaluate();

    return 0;
}
