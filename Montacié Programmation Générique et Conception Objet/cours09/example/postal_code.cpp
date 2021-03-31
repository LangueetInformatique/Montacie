// postal_code.cpp
//#define CTTL_TRACE_EVERYTHING
#include "cttl/cttl.h"

using namespace cttl;

int main()
{
    const int ST_LENGTH = 2;  // state code length
    const int ZIP_LENGTH = 5; // zip code length

    std::string inp = "VT05401 MA-02190 CT, 06320";
    const_edge< policy_space<> > substring( inp );

    size_t result = (
        +( // one or more of
            (
                // state code
                entity( isalpha ) // nearest terminal symbol
                &
                ( symbol() + std::make_pair( ST_LENGTH, ST_LENGTH ) )
            )
            +   // followed by
            first( ",-" ) * 1   // optional comma or dash
            +   // followed by
            (
                // zip code
                entity( isdigit )
                &
                ( symbol() + std::make_pair( ZIP_LENGTH, ZIP_LENGTH ) )
            )
        )
    ).match( substring );

    assert( result == 0 );
    assert( substring.length() == 0 );
    return 0;
}
