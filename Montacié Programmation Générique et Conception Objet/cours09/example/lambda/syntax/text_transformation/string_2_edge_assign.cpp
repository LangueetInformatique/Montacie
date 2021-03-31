// string_2_edge_assign.cpp
// Program demonstrates text transformation using cttl::edge class
// via overloaded assignment operator for std::string.

#define CTTL_TRACE_RULES // automatically turns lambda tracing on

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

template< typename SubstrT >
size_t match_and_replace( SubstrT& substr_ )
{
    return
        (
            *(
                symbol( "target" )
                &
                *(
                    scalar( &substr_ ) = scalar( std::string( "source" ) )
                    ,
                    CTTL_LAMBDA_ASSERT(
                        alias::text( scalar( &substr_ ) )
                        ==
                        scalar( std::string( "source" ) )
                    )
                )
            )
        ).match( substr_ );
}

int main(/*int argc, char* argv[]*/)
{
    std::string inp = "target";
    typedef edge<> SubstrT;
    SubstrT substring( inp );

    size_t result = 
        (
            CTTL_STATIC_RULE( match_and_replace< SubstrT > )
        ).match( substring );

    assert( result != std::string::npos );

    return 0;
}
