// sample code: void_regions.cpp
// Program demonstrates
// const_edge< policy_space< flag_follow_region > >

//#define CTTL_TRACE_EVERYTHING
//#define CTTL_TRACE_RULES    //define to turn light tracing on
//#define CTTL_TRACE_TRIVIAL    //define for trace messages only mode

#include <iostream>
#include "cttl/cttl.h"

using namespace cttl;

int main()
{
    std::string inp = "0123456789";

    std::cout
        << "   the input is /"
        << inp
        << '/'
        << std::endl
        << "valid chars are /"
        ;

    policy_space< flag_follow_region > void_region;
    void_region.region_insert( 0, 1 );
    void_region.region_insert( 9, 10 );
    void_region.region_insert( 5, 8 );

    size_t valid_offset = 0;
    while ( valid_offset < inp.length() ) {
        valid_offset = void_region.lower_bound( valid_offset, inp.length() );
        if ( valid_offset >= inp.length() )
            break;

        std::cout << inp[ valid_offset ];
        ++valid_offset;
    }

    const_edge< policy_space< flag_follow_region > > substring( inp, void_region );
    std::cout
        << '/'
        << std::endl
        << " substring.region_difference() is /"
        << substring.region_difference()
        << '/'
        << std::endl
        ;

    substring.first.go_bof();
    substring.second.go_eof();
    const_edge<> data = substring;
    std::cout
        << "the symbols are /"
        ;
    while( ( data( !first( isdigit ) ) ).match( substring ) != std::string::npos ) {
        std::cout << data.text();
    }

    std::cout
        << '/'
        << std::endl
        ;

    return 0;
}
