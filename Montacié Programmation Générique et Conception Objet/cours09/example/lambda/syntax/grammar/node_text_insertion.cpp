// node_text_insertion.cpp
// Program inserts digit names in a binary number, e.g. "01" -> "0zero1one"
// Demonstrates node text insertion.

#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct digit_parser {
    std::vector< std::string > vect_digit_names;

    digit_parser()
        : vect_digit_names( 2 )
    {
        vect_digit_names[ 0 ] = "zero";
        vect_digit_names[ 1 ] = "one";
    }

    std::string get_digit_name( char digit_ ) const
    {
        assert( digit_ == 0 || digit_ == 1 );
        return vect_digit_names[ digit_ ];
    }

    size_t grammar( edge<>& edge_ )
    {
        lambda< char >::scalar sdigit_value;
        return (
            *(
                first( isdigit )
                +
                *(
                    // get digit:
                    sdigit_value = scalar( &edge_.first )[ -1 ] - '0',
                    // insert digit name:
                    scalar( &edge_.first )
                    += // += insert after, -= before
                    *scalar( CTTL_MEMBER_ACTION(
                        *this,
                        std::mem_fun( &digit_parser::get_digit_name ),
                        sdigit_value.top()
                    ))
                )
            )
        ).match( edge_ );
    }

};

int main( int argc, char* argv[] )
{
    if ( argc == 1 ) {
        std::cout
            << "usage: specify binary number, for example:"
            << std::endl
            << argv[ 0 ] << " 01101"
            ;
        return 1;
    }

    std::string inp;
    string_array2string( inp, argv + 1 );
    assert( inp.length() );
    edge<> substring( inp );

    digit_parser parser;
    if ( parser.grammar( substring ) != std::string::npos ) {
        std::cout << inp;
        return 0;
    }

    std::cout << "*** parser failed ***" << std::endl;
    return 1;
}
