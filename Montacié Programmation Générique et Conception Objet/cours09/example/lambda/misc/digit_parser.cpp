// sample code: digit_parser.cpp
//
// Convert binary number to digit names, e.g. "01" -> "zero one"

//#define NDEBUG    // define before assert.h to stop assertions from being compiled 
//#define CTTL_TRACE_EVERYTHING

#include "cttl/cttl.h"
#include "lambda/lambda.h"

using namespace cttl;

struct digit_parser {
    std::vector< std::string > vect_digit_names;
    lambda< char >::scalar sdigit;

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

    template< typename SubstrT >
    size_t grammar( SubstrT& edge_ )
    {
        return (
            *(
                first( isdigit )
                &
                *(
                    // calculate digit that got parsed:
                    sdigit = scalar( &edge_.first )[ 0 ] - '0',
                    // replace digit name:
                    scalar( &edge_ ) = *scalar( CTTL_MEMBER_ACTION(
                        *this,
                        std::mem_fun( &digit_parser::get_digit_name ),
                        sdigit.top()
                    ))
                )
            )
        ).match( edge_ );
    }

};

int main(int argc, char* argv[])
{
    if ( argc == 1 ) {
        std::cout
            << "usage: specify binary number, for example:"
            << std::endl
            << argv[ 0 ] << " 11010"
            ;
        return 1;
    }

    std::string inp = argv[ 1 ];
    assert( inp.length() );
    typedef edge< policy_space<> > SubstrT;
    SubstrT substring( inp );

    digit_parser parser;
    if ( parser.grammar( substring ) != std::string::npos ) {
        std::cout << inp;
        return 0;
    }

    std::cout << "*** parser failed ***" << std::endl;
    return 1;
}
