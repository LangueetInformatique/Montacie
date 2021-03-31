// grammar_production.cpp
// Program demonstrates call to CTTL grammar production function from lambda expression
// expression.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename SubstrT >
size_t grammar( SubstrT const& edge_ )
{
    return edge_.second.offset();
}

int main(/*int argc, char* argv[]*/)
{
    lambda< size_t >::scalar sresult;
    std::string inp = "abc";
    typedef const_edge<> SubstrT;
    SubstrT substring( inp );

    // call CTTL grammar production function from lambda expression:
    (
        // call function template with one constant argument:
        sresult = *scalar(
            CTTL_STATIC_ACTION(
                std::ptr_fun( &grammar< SubstrT > ),
                substring
            )
        ),
        CTTL_LAMBDA_ASSERT( sresult != scalar( std::string::npos ) ),
        CTTL_LAMBDA_ASSERT( sresult == scalar( 3u ) )

    ).evaluate();


    // invoke grammar production using CTTL function adaptor:
    size_t result = 
        (
            CTTL_STATIC_RULE( &grammar< SubstrT > )
        ).match( substring );

    assert( result == 3 );

    return 0;
}
