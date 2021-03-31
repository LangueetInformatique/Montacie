// closure_compared_2_adaptor.cpp
// Program demonstartes lambda closure, compared to the usage of
// CTTL function adaptor call.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename SubstrT >
size_t grammar( SubstrT& edge_ )
{
    return ( entity( isalpha ) ).match( edge_ );
}

int main(/*int argc, char* argv[]*/)
{
    lambda< size_t >::scalar sresult;
    std::string inp = "abc";
    typedef const_edge<> SubstrT;
    SubstrT substring( inp );
    SubstrT saved_substr = substring;

    // invoke grammar production using CTTL lambda expression:
    (
        // call function template with one mutable argument:
        sresult = *scalar(
            CTTL_STATIC_ACTION(
                std::ptr_fun( &grammar< SubstrT > ),
                &substring
            )
        ),
        CTTL_LAMBDA_ASSERT( sresult != scalar( std::string::npos ) )
    ).evaluate();

    substring = saved_substr;

    // invoke grammar production using CTTL function adaptor:
    size_t result = 
        (
            CTTL_STATIC_RULE( &grammar< SubstrT > )
        ).match( substring );

    assert( result != std::string::npos );

    return 0;
}
