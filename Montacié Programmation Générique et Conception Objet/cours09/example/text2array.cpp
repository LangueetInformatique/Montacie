// sample code: text2array.cpp
// converts text file to array of string literals.

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING
//#define CTTL_TRACE_RULES
//#define CTTL_TEXT_ARRAY_INSERT_LINE_NUMBERS

#include <iostream>
#include "cttl/cttl.h"
#include "utils/itos.h"
#include "utils/fileio.h"

using namespace cttl;

struct text2array {
    static size_t match_lines( edge<>& edge_ )
    {
        return (
            +lookbehind(
                CTTL_STATIC_RULE( text2array::event_line )
                +
                *CTTL_STATIC_RULE( text2array::find_escape ),
                symbol( '\n' )
            )
        ).match( edge_ );
    }

    static size_t event_line( edge<>& edge_ )
    {
#ifdef CTTL_TEXT_ARRAY_INSERT_LINE_NUMBERS
        static size_t line_count = 0;
        edge_.first.insert_go( "/" "*" );
        edge_.first.insert_go( itos( line_count++ ) );
        edge_.first.insert_go( "*" "/" );
#endif //CTTL_TEXT_ARRAY_INSERT_LINE_NUMBERS
        edge_.first.insert_go( "\t\"" );
        edge_.second.insert_stay( "\"," );
        return edge_.first.offset();
    }

    static size_t find_escape( edge<>& edge_ )
    {
        return (
            (
                symbol( '\\' )
                |
                symbol( '\"' )
                |
                symbol( '\'' )
                |
                symbol( '\t' )
            )
            &
            CTTL_STATIC_RULE( text2array::event_escape_char )

        ).find( edge_ );
    }

    static size_t event_escape_char( edge<>& edge_ )
    {
        if ( edge_.first[ 0 ] == '\t' )
            edge_.text( "\\t" );
        else
            edge_.first.insert_go( "\\" );
        return edge_.second.offset();
    }

    static bool parse( edge<>& substr_ )
    {
        match_lines( substr_ );
        if ( substr_.length() ) {
            (
                CTTL_STATIC_RULE( text2array::event_line )
                +
                *CTTL_STATIC_RULE( text2array::find_escape )
            ).match( substr_ );
        }
        return true;
    }
};

int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout
            << "usage: specify input file to convert to array of string literals"
            << std::endl
            ;
        return 1;
    }

    std::string inp;
    file2string( argv[ 1 ], inp );
    assert( inp.length() );
    edge<> substring( inp );

    if ( text2array::parse( substring ) ) {
        std::cout
            << "extern const char* char_array[] = {"
            << std::endl
            ;

        std::cout << inp;

        std::cout
            << std::endl
            << "\tNULL"
            << std::endl
            << "};\t// char_array"
            << std::endl
            ;

        return 0;
    }

    std::cout << "*** parser failed ***" << std::endl;
    return 1;
}
