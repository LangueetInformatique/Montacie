// sample code: grammar.cpp
// demonstrates stateless cttl lexer

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

struct parser {

    static size_t start( const_edge<>& edge_ )
    {
        return (
            +(
                ( entity( isspace ) & rule( &parser::event_space ) )
                |
                ( entity( isalpha ) & rule( &parser::event_alpha ) )
                |
                ( entity( iscntrl ) & rule( &parser::event_cntrl ) )
                |
                ( entity( isdigit ) & rule( &parser::event_digit ) )
                |
                ( entity( ispunct ) & rule( &parser::event_punct ) )
            )

            ).match( edge_ );
    }

    static size_t event_alpha( const_edge<>& edge_ )
    {
        std::cout << "alpha;";
        return edge_.first.offset();
    }
    
    static size_t event_space( const_edge<>& edge_ )
    {
        std::cout << "space;";
        return edge_.first.offset();
    }

    static size_t event_cntrl( const_edge<>& edge_ )
    {
        std::cout << "cntrl;";
        return edge_.first.offset();
    }

    static size_t event_digit( const_edge<>& edge_ )
    {
        std::cout << "digits;";
        return edge_.first.offset();
    }

    static size_t event_punct( const_edge<>& edge_ )
    {
        std::cout << "punct;";
        return edge_.first.offset();
    }

};

int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout << "Enter some arguments to parse." << std::endl;
        return 1;
    }

    std::string inp;
    string_array2string( inp, &argv[ 1 ], ' ' );
    const_edge<> substring( inp );
    if ( parser::start( substring ) == std::string::npos ) {
        std::cout << "*** parser failed ***";
        return 1;
    }
    
    std::cout << std::endl;

    return 0;
}
