// search_replace.cpp

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING //define to turn tracing on
//#define CTTL_TRACE_RULES  //define to turn light tracing on

#include <iostream>
#include "cttl/cttl.h"

#include "utils/fileio.h"
using namespace cttl;

template< typename SubstrT >
struct search_replace_parser {

    typedef SubstrT substr_T;
    typedef typename SubstrT::strict_edge_T strict_input_T;
    typedef typename SubstrT::node_T node_T;
    typedef typename SubstrT::string_T string_T;

    static size_t search( SubstrT& substr_ )
    {
        return (
            (
                '<' + !symbol( '>' )
            )
        
            ).bang_find( substr_ );
    }

    static size_t replace( strict_input_T& substr_ )
    {
        substr_.text( "" );
        return 0;
    }


    static size_t search_and_replace( SubstrT& substr_ )
    {
        return (
            *
            (
                CTTL_STATIC_RULE( search )
                &
                CTTL_STATIC_RULE( replace )
            )
            
        ).match( substr_ );
    }

};  // search_replace_parser< SubstrT >


int main(int argc, char* argv[])
{
    if ( argc != 2 ) {
        std::cout
            << "Usage: program removes markup tags from a file and prints the result:"
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
    search_replace_parser< substr_T >::search_and_replace( substring );

    // send modified input to the standard output
    std::cout << inp;
    return 0;
}
