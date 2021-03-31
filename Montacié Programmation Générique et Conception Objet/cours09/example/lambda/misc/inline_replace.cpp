// inline_replace.cpp

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

#include <iostream>
#include "cttl/cttl.h"
#include "lambda/lambda.h"

#include "utils/fileio.h"
using namespace cttl;

template< typename SubstrT >
struct inline_replace_parser {

    typedef typename SubstrT::string_T string_T;

    static size_t search_and_replace( SubstrT& substr_ )
    {
        return
            (
                *!!(
                    ( '<' + !symbol( '>' ) )
                    &
                    *(
                        scalar( &substr_ ) = scalar( string_T( "" ) )
                    )
                )
            ).match( substr_ );
    }

};  // inline_replace_parser< SubstrT >


int main(int argc, char* argv[])
{
    if ( argc != 2 ) {
        std::cout
            << "Usage: program removes html tags from a file and prints the result:"
            << std::endl
            << '\t'
            << argv[ 0 ]
            << " path/filename.html"
            << std::endl
            ;

        return 1;
    }

    // construct input
    std::string inp;

    // load data from file
    file2string( argv[ 1 ], inp );
    assert( inp.length() );

    // construct mutable substring
    typedef edge<> substr_T;
    substr_T substring( inp );

    // search for tags and delete them from the input string
    inline_replace_parser< substr_T >::search_and_replace( substring );

    // send modified input to the standard output
    std::cout << inp;
    return 0;
}
